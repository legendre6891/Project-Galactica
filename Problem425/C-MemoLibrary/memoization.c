#include <stdlib.h>
#include "memoization.h"
#include "murmur_hash3.h"

/** File: memoization.c
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
*/

// Storage for a global memoization container
MEMOIZATION_DATA_CONTAINER* MEMOIZATION_DATA_CACHE = NULL;

/* Internal Declarations*/
void freeMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);
void clearMemoizationContextInternalData(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID);

/*------------------------------------------------ 
	Memoization Container Maintenance Functions 
 ------------------------------------------------*/
 
/** Create a new memoization data container structure and return a pointer to it 
	@param[in] numContexts: Number of memoization contexts to store.
	@return: A new memoization data container, for storing and retreiving function calls by context
*/
MEMOIZATION_DATA_CONTAINER* newMemoizationContainer(unsigned int numContexts){
	unsigned int i;
	MEMOIZATION_DATA_CONTAINER* container = malloc(sizeof(MEMOIZATION_DATA_CONTAINER));
	container->numContexts = numContexts;
	container->contexts = calloc(numContexts, sizeof(khash_t(MEMO_CACHE)*));
	container->isContextEnabled = calloc(numContexts, sizeof(int));
	container->isCacheDirty = calloc(numContexts, sizeof(int));
	for (i=0; i<numContexts; i++){
		// All caches initially inactive by default.
		container->isContextEnabled[i] = 0;
		container->isCacheDirty[i] = 0;
		container->contexts[i] = kh_init(MEMO_CACHE);
	}
	return container;
}

/** Check if a memoization context is enabled (e.g. can store and fetch cached values)
	@param[in] container: The memoization container to check the context for
	@param[in] contextID: The context to check
	@return: 1 if the context was enabled, else 0
*/
int isMemoizationContextEnabled(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	return ((contextID < container->numContexts) && container->isContextEnabled[contextID]);
}

/** Returns 1 if the cache is dirty, or 0 if the cache has been disabled since last clear or the context does not exist 
	NOTE: This is conservative, as it assumes that enabling a cache makes it dirty.  This may not always be true, but
	to do a more fine-grained check one needs to set the isCacheDirty flag either every time or the first time a cache
	is used.  This adds extra per-call overhead that didn't seem warranted.
	@param[in] container: The memoization container to check the context for
	@param[in] contextID: The context to check
	@return: 1 if the context was dirty (could have been modified), else 0
*/
int isMemoizationContextDirty(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	return ((contextID < container->numContexts) && container->isCacheDirty[contextID]);
}

/** Enable a memoization context- allowing caching and fetching of functions in that context 
	@param[in] container: The memoization container to enable the context for
	@param[in] contextID: The context to enable
*/
void enableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		container->isContextEnabled[contextID] = 1;
		container->isCacheDirty[contextID] = 1;
	}
}

/** Disable a memoization context- allowing caching and fetching of functions in that context 
	@param[in] container: The memoization container to disable the context for
	@param[in] contextID: The context to disable
*/
void disableMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		container->isContextEnabled[contextID] = 0;
	}
}

/** Turn all caches on or off 
	@param[in] container: The memoization container to enable/disable all contexts
	@param[in] isEnabled: The flag for determining if the contexts should be enabled or disabled.  If True, enable all.  Else disable all.
*/
void setAllMemoizationContextsIsEnabled(MEMOIZATION_DATA_CONTAINER* container, int isEnabled){
	int i;
	if (isEnabled){
		for (i=0; i<container->numContexts; i++){
			enableMemoizationContext(container, i);
		}
	} else {
		for (i=0; i<container->numContexts; i++){
			disableMemoizationContext(container, i);
		}
	}
}

/** Clear the memoization container- clears out all contexts 
	@param[in] container: The memoization container to clear all contexts of.
*/
void clearMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container){
	unsigned int i;
	for (i=0; i < container->numContexts; i++){
		clearMemoizationContext(container, i);
	}
}

/** Free the memoization container- frees all contexts and destroys the container 
	@param[in] container: The memoization container to free all data for and destroy.
*/
void freeMemoizationContainer(MEMOIZATION_DATA_CONTAINER* container){
	unsigned int i;
	for (i=0; i < container->numContexts; i++){
		freeMemoizationContext(container, i);
	}
	free(container->isCacheDirty);
	free(container->isContextEnabled);
	free(container->contexts);
	free(container);
}

/** Clear the memoization context- clears all the allocated data in the function signatures and clears the hash table 
	@param[in] container: The memoization container to containing the context data
	@param[in] contextID: The context to clear all data for
*/
void clearMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		clearMemoizationContextInternalData(container, contextID);
		khash_t(MEMO_CACHE)* context = container->contexts[contextID];
		kh_clear(MEMO_CACHE, context); 
		if (!container->isContextEnabled[contextID]){
			container->isCacheDirty[contextID] = 0;
		}
	}
}

/**	Free a memoization context from a container.  This is not exposed as tearing this down could be bad. 
	This is because, due to performance reasons, no checks are made to ensure that a context exists
	before attempting to access it.  As such, the full container should be torn down entirely, or not at all.
	@param[in] container: The memoization container to containing the context data
	@param[in] contextID: The context to free all data for and replace with a NULL pointer.
*/
void freeMemoizationContext(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		// Free the internal data for function signatures and pointers to this data
		clearMemoizationContextInternalData(container, contextID);
		
		// Free the hash table
		khash_t(MEMO_CACHE)* context = container->contexts[contextID];
		kh_destroy(MEMO_CACHE, context);
		container->contexts[contextID] = NULL;
	}
}

/** Free the memory allocated internally to the keys in the hash data structure (as the hash table can't free this) 
	@param[in] container: The memoization container to containing the context data
	@param[in] contextID: The context to clear the memoization internal data for (e.g. the hash table)
*/
void clearMemoizationContextInternalData(MEMOIZATION_DATA_CONTAINER* container, unsigned int contextID){
	if (contextID < container->numContexts){
		int i;
		khash_t(MEMO_CACHE)* context = container->contexts[contextID];
		for (i=kh_begin(context); i < kh_end(context); i++){
			if (kh_exist(context, i)) {
				clearMemoizationSignatureInternalData(kh_key(context, i));
				free(kh_key(context, i));
				free(kh_value(context, i));
			}
		}
	}
}

/*------------------------------------------------ 
	Memoization Container Global Functions
	(For managing a global container declared here)
 ------------------------------------------------*/
void initGlobalMemoizationContexts(){
	MEMOIZATION_DATA_CACHE = newMemoizationContainer(MAX_NUM_CONTEXTS);
}

int isGlobalMemoizationContextEnabled(unsigned int contextID){
	return isMemoizationContextEnabled(MEMOIZATION_DATA_CACHE, contextID);
}

int isGlobalMemoizationContextDirty(unsigned int contextID){
	return isMemoizationContextDirty(MEMOIZATION_DATA_CACHE, contextID);
}

void enableGlobalMemoizationContext(unsigned int contextID){
	enableMemoizationContext(MEMOIZATION_DATA_CACHE, contextID);
}

void disableGlobalMemoizationContext(unsigned int contextID){
	disableMemoizationContext(MEMOIZATION_DATA_CACHE, contextID);
}

void clearGlobalMemoizationContexts(){
	clearMemoizationContainer(MEMOIZATION_DATA_CACHE);
}

void clearGlobalMemoizationContext(unsigned int contextID){
	clearMemoizationContext(MEMOIZATION_DATA_CACHE, contextID);
}

void freeGlobalMemoizationContexts(){
	freeMemoizationContainer(MEMOIZATION_DATA_CACHE);
	MEMOIZATION_DATA_CACHE = NULL;
}

/*------------------------------------------------ 
	Memoization Key Functions
 ------------------------------------------------*/
/** Calculate the hash value for a function memoization signature
	@param[in] functPointer: Pointer to a function
	@param[in] numArgs: Number of arguments for the function
	@param[in] sizeOfArgs: A sum of sizeOf for the type of all given arguments
	@param[in] argumentData: A pointer to a memory block that stores a copy of all argument values passed to the function during this call
	@return: A 32 bit hash value calculated from the input params
*/
inline uint32_t calc_hash_memoization_signature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData){
	uint32_t hashInputLen = SIZE_OF_ARGS(functPointer, numArgs, sizeOfArgs) + sizeOfArgs;
	void* hashInput = malloc(hashInputLen);
	uint32_t key = 0;
	uint32_t offset = 0;
	hashInput = STORE_ARGUMENTS(hashInput, offset, functPointer, sizeOfArgs);
	memcpy(hashInput+offset, argumentData, sizeOfArgs);
	MurmurHash3_x86_32(hashInput, hashInputLen, HASH_ALGORITHM_SEED, &key);
	free(hashInput);
	return key;
}
 
/** Make a memoization signature, given information about the function call
	A memoization signature represents a single function call to a function
	@param[in] functPointer: Pointer to a function that is being memoized
	@param[in] numArgs: Number of arguments for the function
	@param[in] sizeOfArgs: A sum of sizeOf for the type of all given arguments
	@param[in] argumentData: Pointer to a memory block that stores a copy of all argument values passed to the function during this call
	@return: Function signature representing the function call signature
*/
FUNCTION_MEMOIZATION_SIGNATURE* makeMemoizationSignature(memoization_function_pointer functPointer, unsigned int numArgs, unsigned int sizeOfArgs, void* argumentData){
	FUNCTION_MEMOIZATION_SIGNATURE* functSig = malloc(sizeof(FUNCTION_MEMOIZATION_SIGNATURE));
	uint32_t key = calc_hash_memoization_signature(functPointer, numArgs, sizeOfArgs, argumentData);
	functSig->functionPointer = functPointer;
	functSig->numArgs = numArgs;
	functSig->sizeOfArgs = sizeOfArgs;
	functSig->key = key;
	functSig->argumentKey = argumentData;
	return functSig;
}

/** Free the internal data in a function call signature (Good for tying up loose ends for an array of signatures) 
	@param[in,out] functSig: Pointer to function signature that will be modified by freeing any allocated data.
*/
void clearMemoizationSignatureInternalData(FUNCTION_MEMOIZATION_SIGNATURE* functSig){
	free(functSig->argumentKey);
}

/** Free a function call signature 
	@param[in,out] functSig: Pointer to function signature that will be modified by freeing all internal data, then freeing the singnature
*/
void freeMemoizationSignature(FUNCTION_MEMOIZATION_SIGNATURE* functSig){
	clearMemoizationSignatureInternalData(functSig);
	free(functSig);
}

/*------------------------------------------------ 
	Memoization Access Functions (For Accesing Global Cache)
 ------------------------------------------------*/

 /** Cache Setting Function: Maps a function call signature to a return value
	@param[in] contextID: The number for the context to store this data in
	@param[in] functSig: Pointer to a function signature (call signature) that will be added to the memoization cache
	@param[in] returnVal: Pointer to a memory-allocated copy of the return value for the function call
	@return: Exit code representing success (0) or failure (-1) in storing the (call, value) map in the cache.
 */
int setMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig, void* returnVal){
	int exitCode;
	MEMOIZATION_DATA_CONTAINER* container = MEMOIZATION_DATA_CACHE;
	if (contextID < container->numContexts  && container->contexts[contextID] != NULL){
		int hashExitCode;
		khint_t hashIndex = kh_put(MEMO_CACHE, container->contexts[contextID], functSig, &hashExitCode);
		if (hashExitCode != 0){
			exitCode = 0;
			kh_value(container->contexts[contextID], hashIndex) = returnVal;
		} else {
			exitCode = -1;
		}
	} else {
		exitCode = -1;
	}
	return exitCode;
}

 
/** Cache Fetching Function: Getting a return value, given a function call signature
	@param[in] contextID: The number for the context to fetch the value from
	@param[in] functSig: Pointer to a function signature (call signature) that will be searched for in the memoization cache
	@param[in] exitCode: Exit code representing success in finding a value in the cache (0) or failure to find the value (-1)
	@return: Pointer to a memory-allocated copy of the return value for the cached function call.
*/
void* fetchMemoizationCacheValue(unsigned int contextID, FUNCTION_MEMOIZATION_SIGNATURE* functSig,  int* exitCode){
	void* returnVal = NULL;
	MEMOIZATION_DATA_CONTAINER* container = MEMOIZATION_DATA_CACHE;
	if ((contextID < container->numContexts) && container->contexts[contextID] != NULL){
		khint_t hashIndex = kh_get(MEMO_CACHE, container->contexts[contextID], functSig);
		if ((hashIndex < kh_n_buckets(container->contexts[contextID])) && 
			(kh_exist(container->contexts[contextID], hashIndex))){
			*exitCode = 0;
			returnVal = kh_value(container->contexts[contextID], hashIndex);
		} else {
			*exitCode=-1;
		}
	} else {
		*exitCode=-1;
	}
	return returnVal;
}


