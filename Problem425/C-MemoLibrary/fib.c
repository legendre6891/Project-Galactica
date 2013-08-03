#include <stdio.h>
#include "memoization.h"


#define SOME_MEMOIZATION_CONTEXT 0

MEMOIZED_FUNCT(SOME_MEMOIZATION_CONTEXT, int, fibMemo,int, a)
/* int fibMemo(int a) */
{
  if (a == 0 || a == 1 || a < 0){
    return 1;}
  else{
    return fibMemo(a-1) + fibMemo(a-2);}
}

int main(int argc, char *argv[])
{
  initGlobalMemoizationContexts();
  enableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT);

  printf ("F 50 is %d\n", fibMemo(40));

  disableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT);
  freeGlobalMemoizationContexts();

  return 0;
}
