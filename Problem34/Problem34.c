#include <stdio.h>
#include <math.h>
#include "../clib/digits.h"


inline unsigned int factorial(unsigned int n) {
  static const unsigned int table[] = {1, 1, 2, 6, 24, 120, 720,
    5040, 40320, 362880, 3628800, 39916800, 479001600};
  return table[n];
}

int main(int argc, char *argv[])
{
  unsigned long long int i;
  int* p;
  int sum;
  int l;

  for (i = 1; i < 10000000; ++i)
    {
      p = IntegerDigits(i);
      sum = 0;
      l = IntegerLength(i);
      
      for (int j = 0; j < l; j++)
	sum += factorial(p[j]);

      if (sum == i)
	printf("%d\n", i);
    }
}
