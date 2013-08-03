#include <stdio.h>
#include <time.h>
#include "memoization.h"

/*------------------------------------------------ 
	Memoization Example Function
 ------------------------------------------------*/
 
 #define SOME_MEMOIZATION_CONTEXT 0
 
// Testing Macro Functions
//**********************************
int SOME_VAR0 = COUNT_ARGUMENTS();
int SOME_VAR1 = COUNT_ARGUMENTS(1);
int SOME_VAR2 = COUNT_ARGUMENTS(1,2);
int SOME_SIZE0 = SIZE_OF_ARGS();
int SOME_SIZE1 = SIZE_OF_ARGS(1);
int SOME_SIZE2 = SIZE_OF_ARGS(1,2);
//int SOME_ARGS0 = MERGE_ARGUMENTS_PAIRWISE();							//Testing for failures
int SOME_ARGS1 = MERGE_ARGUMENTS_PAIRWISE(1,+0);
//int SOME_ARGS2a, SOME_ARGS2b = MERGE_ARGUMENTS_PAIRWISE(1,+0,2,+1);	//Testing for failures

// Testing Memoization
//**********************************

/* Memoized variant of a factorial */
MEMOIZED_FUNCT(SOME_MEMOIZATION_CONTEXT, unsigned long, factorialMemoExample, int, n){
//unsigned long factorialMemoExample(unsigned int val){
	if (n<=1) {
		return(1);
	} else {
		return (unsigned long)n*(unsigned long)factorialMemoExample(n-1);
	}
 }

/* Normal, non-memoized variant of a factorial */
unsigned long factorialMemoExample_Baseline(int n){
	if (n<=1) {
		return(1);
	} else {
		return (unsigned long)n*(unsigned long)factorialMemoExample(n-1);
	}
 }


 /* Run a performance and a sanity check on the factorials */
void runFactorialExampleComparison(){
	initGlobalMemoizationContexts();
	enableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT);
	int i, depth;
	unsigned long val;

	clock_t start, end;
	double elapsedTime;

	// Depth - Highest factorial to calculate
	// To note, the given value of 100k will definitely overflow.
	// This is okay, as the specific values aren't important, it's just an example function.
	depth = 100000;
	
	// Time comparison check
	//---------------------------------
	start = clock();
	// Baseline timing
	for (i=0; i<depth; i++){
		val = factorialMemoExample_Baseline(i);
	}
	end = clock();
	elapsedTime = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Baseline was: %f\n", elapsedTime);
	
	// Memoization Timing (Populating, No Cache Hits)
	start = clock();
	for (i=0; i<depth; i++){
		val = factorialMemoExample(i);
	}
	end = clock();
	elapsedTime = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Memoized was: %f\n", elapsedTime);
	
	// Memoization Timing (Populated, All Cache Hits)
	start = clock();
	for (i=0; i<depth; i++){
		val = factorialMemoExample(i);
	}
	end = clock();
	elapsedTime = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Memoized2 was: %f\n", elapsedTime);

	//Sanity Checks
	//---------------------------------
	//Sanity Check - Comparing values of memoized function versus baseline
	for (i=0; i<depth; i++){
		if(factorialMemoExample(i) != factorialMemoExample_Baseline(i)){
			printf("Mismatch for value %i, Baseline was: %lu but Memoized was %lu\n", 
							   i, factorialMemoExample_Baseline(i), factorialMemoExample(i));
		}
	}
	clearGlobalMemoizationContexts();
	
	//Sanity Check 2 - Repopulating and Comparing values of memoized function versus baseline
	for (i=0; i<depth; i++){
		if(factorialMemoExample(i) != factorialMemoExample_Baseline(i)){
			printf("Mismatch for value %i, Baseline was: %lu but Memoized was %lu\n", 
							   i, factorialMemoExample_Baseline(i), factorialMemoExample(i));
		}
	}
	disableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT);
	freeGlobalMemoizationContexts();
}

// Basic Main Function
int main(int argc, char *argv[]) {
	runFactorialExampleComparison();
    return 0;
}
