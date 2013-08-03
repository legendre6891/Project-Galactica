#include "digits.h"
#include <math.h>

int* IntegerDigits(unsigned int n)
{
  int d = IntegerLength(n);
  int* r = malloc(sizeof(int) * d);

  int a;

  while(d--)
    {
      a = n%10;
      r[d] = a;
      n = n/10;
    }
  return r;
}

/* Computes the number of digits of a non-negative integer n.
 */
inline int IntegerLength(unsigned int n)
{
  if (n == 0)
    {
      return 1;
    }
  return floor(log10(n) + 1.0);
}
