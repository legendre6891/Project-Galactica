#include <stdio.h>
#include "list_utilities.h"

void print_integer_list(int* xs, int length)
{
  printf ("{ ");
  int i = 0;
  for (i = 0; i < length; i++)
    {
      printf ("%d", xs[i]);
      if (i != length - 1)
	printf (", ");
    }
  printf("};\n");
  return;
}
