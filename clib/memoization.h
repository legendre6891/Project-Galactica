#ifndef __MEMOIZATION_H__
#define __MEMOIZATION_H__

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include "macro_utilities.h"
#include "khash.h"

/** File: memoization.h
	Author: Ben Nye

	Licensing (APL V2.0)
	---------------------------------------------
    Copyright 2011 Benjamin D. Nye

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
	
       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   ---------------------------------------------
	
	Notes:
	--------------------------------------------
	The goal of this module is to provide generic memoization
	capabilities for C functions, provided these functions:
		A. Have a fixed number of arguments (non-variadic)
		B. Have a fixed meaning for arguments (assumes pointers always go to same data)
		C. Returns the same value, given the same arguments
		D. Have no meaningful side effects
		E. Less than 64 args.
		F. All arguments remain the same type and order during runtime (Don't think this can be altered in C or C++ anyway...)
		
	This particular implementation relies on a global cache for function signatures, but it would be fairly straightforward
	to modify the code to have different functions employ different caches.  Doing this would require modifying setMemoizationCacheValue
	and fetchMemoizationCacheValue to have an additional argument, then making a variant of the MEMOIZED_FUNCT macro that takes the name
	of the cache to use as an argument.
		
	To note, it is possible to use this to have functions that have a single side effect
	such as creating a memory block and returning a pointer.  However, this will make the memoized
	function work differently (as it will always return refs to the same pointer, while the
	original will return new pointers to new arrays each time).  This use is not recommended.
		
	Strategy for approaching this problem:
		1. Implementing a generic cache data structure, which stores:
			A. The total cache size allocated
			B. A mapping of function signature to (isKnown, output)
			C. These mappings will be keyed by context, so that caches can be cleared on context exit
		2. Implementing functions to manage this data structure
		3. Implementing a function to get the value of 'output' and 'isKnown'
		4. Implementing a pre-processor macro for generating pairs of functions,
		   a core function and a memoization wrapper counterpart.
		   
	NOTE: This memoization library has been designed and tested using the GNU C compiler.
		  It should theoretically port to other systems, as it is relatively minimal, but
		  could encounter two possible issues:
		  1. GNU Attributes - These were added as optimizations and would need to be stripped out (e.g. always_inline)
		  2. Variadic Macros - These are necessary for this approach to work.  Due to differences in C pre-processors,
			 some of these macros may have issues, especially if a function has no arguments.
			 
		To fix the first issue, one could simply remove all GNU-based tags.  I don't think I left any in, but it is
		certainly possible.  Standardization in C compilers is... mixed.  To fix the second issue, the only good fix
		is to use a new compiler.  In theory these arg counting macros should work, but in practice not all compilers
		handle variadic macros and a few notable ones (e.g. some MS variants) complain if you put no args into a 
		variadic macro.  So would have to not do that.  Sorry, I don't make the compilers.
*/

/** Constants */
// Initialize the Mapping System
#define MEMOIZATION_VERBOSITY 0
#define MAX_NUM_CONTEXTS 8
#define LARGEST_ARGSIZE_EXPECTED 256
#define HASH_ALGORITHM_SEED 0

/** Typedefs */
typedef void (*memoization_function_pointer)(void);

/** Hashing and Hashmap Related Functions */

// Function Signature
typedef struct S_FUNCTION_MEMOIZATION_SIGNATURE{
	memoization_function_pointer functionPointer;		// Pointer to the function cached
	unsigned int numArgs;								// Number of arguments the function takes
	unsigned int sizeOfArgs;							// Total size of all args, in counted in same units as sizeof
	uint32_t key;										// A key for this entry
	void* argumentKey;									// Memory block that concatenates all input values as a big bitstring
} FUNCTION_MEMOIZATION_SIGNATURE;

/***********************
 * Hashing Functions   *
 ***********************/

/** Compare two memoization function signatures 
	@param[in] functSig1: First function signature 
	@param[in] functSig2: Second function signature
	@return: 1 if function signatures are equivalent, 0 otherwise
*/
static inline unsigned int cmp_memoization_signatures(FUNCTION_MEMOIZATION_SIGNATURE* functSig1, FUNCTION_MEMOIZATION_SIGNATURE* functSig2){
	return ((functSig1->functionPointer == functSig2->functionPointer) && 
			(functSig1->sizeOfArgs == functSig2->sizeOfArgs) &&
			memcmp(functSig1->argumentKey, functSig2->argumentKey, functSig1->sizeOfArgs)==0);
}

/** Get the hash key from a function signature 
	@param[in] functSig: Function signature to get a key from.  This does not calculate the key, it just reads it.
	@return: Function signature hash key (a uint32 hashing value)
*/
static inline uint32_t hash_memoization_signature(FUNCTION_MEMOIZATION_SIGNATURE* functSig){
	return functSig->key;
}

/** Calculate a memoization hash key based on the structure
	@param[in] functSig: Function signature to get a key from.  This does not calculate the key, it just reads it.
	@return: Function signature hash key (a uint32 hashing value)
*/
inline uint32_t calc_hash_memoization_signature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData);

#define kh_memoization_hash_func(key) (hash_memoization_signature(key))
#define kh_memoization_hash_equal(a, b) (cmp_memoization_signatures(a, b))

/* Hash Maps for Storage */
#define MEMOIZATION_CONTEXT_MAP_INIT(name)								\
	KHASH_INIT(name, FUNCTION_MEMOIZATION_SIGNATURE*, void*, 1, kh_memoization_hash_func, kh_memoization_hash_equal)

MEMOIZATION_CONTEXT_MAP_INIT(MEMO_CACHE)

/***********************
 * Memoization Macro   *
 ***********************/
 
/** Macro for designating a function as memoized.
	To memoize a function in context 0 whose definition was: 
		"long myFunct(long val, long x){return val+x;}" 
	then write:
		"MEMOIZED_FUNCT(0, long, myFunct, long, val, long, x){return val+x;}"
	This will resolve to:
		"long myFunct(long val, long x){
			<cached function that calls myFunct_MEMOIZED_CONTEXT_0 when it needs a value>
		 }
		 
		 long myFunct_MEMOIZED_CONTEXT_0(long val, long x){return val+x;}"
	@param[in] CONTEXT_ID: A positive integer (or CPP definition that resolves to one) representing the cache context to use
	@param[in] RETURN_TYPE: The return type for the function
	@param[in] FUNCT_NAME: The name for the cached function.  If you want a drop-in replacement, keep this as your original function name
	@param[in] ARG_0_TYPE: Optionally, the type of the first argument.  Must be a valid type within the scope of the function definition.
	@param[in] ARG_0_NAME: Optionally, the name of the first argument  Must be a valid C identifier.
	@param[in] ARG_1_TYPE: (the second argument type, etc)
	@param[in] ARG_1_NAME: (the second argument name, etc)
	...
	@return: Cached function definition, in the form: 
				<RETURN_TYPE> <FUNCT_NAME>(<ARG_0_TYPE> <ARG_0_NAME>, ...){<cached function implementation>}
				<RETURN_TYPE> <FUNCT_NAME>_MEMOIZED_CONTEXT_<CONTEXT_ID>(<ARG_0_TYPE> <ARG_0_NAME>, ...)
			 
*/
#define MEMOIZED_FUNCT(CONTEXT_ID, RETURN_TYPE, FUNCT_NAME, ...) 												\
			RETURN_TYPE FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (MERGE_ARGUMENTS_PAIRWISE(__VA_ARGS__)); \
																												\
			RETURN_TYPE FUNCT_NAME (MERGE_ARGUMENTS_PAIRWISE(__VA_ARGS__)){										\
				if (isGlobalMemoizationContextEnabled((unsigned int)CONTEXT_ID)) {								\
					unsigned int numArgs = COUNT_ARGUMENTS(__VA_ARGS__)/2;										\
					unsigned long offset = 0;																	\
					void* argumentKey = NULL; 																	\
					FUNCTION_MEMOIZATION_SIGNATURE* functSig;													\
					int fetchExitCode, setExitCode;																\
					RETURN_TYPE returnVal;																		\
					void* returnValPtr = NULL;																	\
					argumentKey = malloc(sizeof(numArgs) + SIZE_OF_ARGS(FILTER_ODD_ARGUMENTS(__VA_ARGS__)));	\
					STORE_ARGUMENT(argumentKey, numArgs, offset);												\
					if (numArgs > 0) {																			\
						STORE_ARGUMENTS(argumentKey, offset, FILTER_ODD_ARGUMENTS(__VA_ARGS__));				\
					}																							\
					functSig = makeMemoizationSignature((memoization_function_pointer)FUNCT_NAME, 				\
														numArgs, 												\
														sizeof(numArgs) + SIZE_OF_ARGS(FILTER_ODD_ARGUMENTS(__VA_ARGS__)),\
														argumentKey);											\
					returnValPtr = fetchMemoizationCacheValue(CONTEXT_ID, functSig, &fetchExitCode); 			\
					if (fetchExitCode == 0){																	\
						freeMemoizationSignature(functSig);														\
						returnVal = *((RETURN_TYPE*)returnValPtr);												\
						return returnVal;																		\
					} else {																					\
						returnVal = FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (FILTER_ODD_ARGUMENTS(__VA_ARGS__));	\
						returnValPtr = malloc(sizeof(RETURN_TYPE));												\
						memcpy(returnValPtr, &returnVal, sizeof(RETURN_TYPE));									\
						setExitCode = setMemoizationCacheValue(CONTEXT_ID, functSig, returnValPtr);				\
						if (setExitCode != 0){																	\
							free(returnValPtr);																	\
							freeMemoizationSignature(functSig);													\
						}																						\
						return returnVal;																		\
					}																							\
				} else {																						\
					return FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (FILTER_ODD_ARGUMENTS(__VA_ARGS__));	\
				}																								\
			}																									\
																												\
			RETURN_TYPE FUNCT_NAME ## _MEMOIZED_CONTEXT_ ## CONTEXT_ID (MERGE_ARGUMENTS_PAIRWISE(__VA_ARGS__))
			


// The main cache for the container- stores functions by which context they live in
typedef struct S_MEMOIZATION_DATA_CONTAINER{
	unsigned int numContexts;									// Number of data contexts
	int* isContextEnabled;										// Flags to determine if the context is enabled
	int* isCacheDirty;											// Flags to determine if cache could have been altered
	khash_t(MEMO_CACHE)** contexts;								// Memoization contexts
} MEMOIZATION_DATA_CONTAINER;


/* Memoization container management */
void initGlobalMemoizationContexts();
int isGlobalMemoizationContextEnabled(unsigned int contextID);
int isGlobalMemoizationContextDirty(unsigned int contextID);
void enableGlobalMemoizationContext(unsigned int contextID);
void disableGlobalMemoizationContext(unsigned int contextID);
void clearGlobalMemoizationContexts();
void clearGlobalMemoizationContext(unsigned int contextID);
void freeGlobalMemoizationContexts();

MEMOIZATION_DATA_CONTAINER* newMemoizationContainer(unsigned int numContexts);
int isMemoizationContextEnabled(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
int isMemoizationContextDirty(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void enableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void disableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void clearMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container);
void freeMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container);

void clearMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);

/* Memoization Key Management*/
FUNCTION_MEMOIZATION_SIGNATURE* makeMemoizationSignature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData);
void clearMemoizationSignatureInternalData(FUNCTION_MEMOIZATION_SIGNATURE* functSig);
void freeMemoizationSignature(FUNCTION_MEMOIZATION_SIGNATURE* memoizationSig);

/* Value Fetching Function */
int setMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig, void* returnVal);
void* fetchMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig,  int* exitCode);

#endif
