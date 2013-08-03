#include <stdio.h>
#include "../clib/memoization.h"
#include "../clib/digits.h"
#include "../clib/list_utilities.h"
#include "../clib/prime_q.h"
#include <assert.h>


#define SOME_MEMOIZATION_CONTEXT 0





struct _integer_list
{
  int* xs;
  int len;
};

typedef struct _integer_list integer_list;

integer_list dice_integer(int n)
{
  integer_list l;
  l.len = IntegerLength(n);
  l.xs = IntegerDigits(n);
  return l;
}

void print_list(integer_list l)
{
  print_integer_list(l.xs, l.len);
  return;
}

int from_digits(integer_list l)
{
  int r = 0;
  int i = 0;

  for(i = 0; i < l.len; i++)
    {
      r = r*10 + l.xs[i];
    }

  return r;
}

integer_list* change_kth_digit(integer_list L, int k)
{
  int m;
  if (k == 0)
    m = 8;
  else
    m = 9;

  integer_list* result = malloc(m * sizeof(integer_list));

  int i = 0;
  for (i = 0; i < m; ++i)
    {
      result[i].len = L.len;
      result[i].xs = malloc(L.len * sizeof(int));
      for (int j = 0; j < L.len; ++j)
	{
	  result[i].xs[j] = L.xs[j];
	}
    }

  i = 0;
  if (k == 0)
    {
      for (int j = 1; j <= 9; ++j)
	{
	  if (j != L.xs[0])
	    {
	      result[i].xs[0] = j;
	      i++;
	    }
	}
    }
  else
    {
      for (int j = 0; j <= 9; ++j)
	{
	  if (j != L.xs[k])
	    {
	      /* printf ("Setting stuff here ...with i = %d out of m=%d\n", i,m); */
	      /* printf ("j = %d, L.xs[k] = %d\n",j, L.xs[k]); */
	      result[i].xs[k] = j;
	      i++;
	    }
	}
    }     
  /* printf ("survived ...\n"); */
  return result;
}



int chop_left(int n)
{
  if (n < 10)
    {
      return 0;
    }
  else
    {
      integer_list a = dice_integer(n);
      integer_list b;
      b.len = a.len - 1;
      b.xs = malloc(sizeof(int) * b.len);
      for (int i = 0 ; i < b.len; ++i)
	{
	  b.xs[i] = a.xs[i+1];
	}
      
      int r = from_digits(b);
      free(a.xs);
      free(b.xs);
      return r;
    }
}



integer_list connected(int n)
{
  integer_list a = dice_integer(n);
  
  integer_list result;
  result.len = 9*(a.len);
  result.xs = malloc(sizeof(int) * result.len);



  int i,j,k,l;
  

  // first gather all the change digits;
  i = 0;
  integer_list* p;

  for (k = 0; k < a.len; k++)
    {
      p = change_kth_digit(a, k);
      
      if (k == 0)
	l = 8;
      else
	l = 9;

      for (j = 0; j < l; j++)
	{
	  result.xs[i] = from_digits(p[j]);
	  i++;
	  free(p[j].xs);
	}
      free(p);
    }
  assert(i == 9*a.len - 1);
  result.xs[i] = chop_left(n);





  // don't forget to free a.xs!
  // also p and p.xs!!

  free(a.xs);
  return result;
}



/* short admissable(int a, int b) */
MEMOIZED_FUNCT(SOME_MEMOIZATION_CONTEXT, short, admissable, int, a, int, b)
{
  if (prime_q(a) == 0 || prime_q(b) == 0)
    return 0;

  if (a == b)
    return 1;

  
  integer_list l;
  l = connected(b);


  for (int i = 0; i < l.len; ++i)
    {
      if (l.xs[i] >= b)
	continue;
      if (admissable(a, l.xs[i]) != 0)
	return 1;
    }
  
  return 0;
}
  
  

int main(int argc, char *argv[])
{
  int i;
  integer_list a;
  
  a = dice_integer(125);
  free(a.xs);

  initGlobalMemoizationContexts();
  enableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT);





  /* print_list(p[8]); */
  /* for (i = 0; i < 8; i++) */
  /*   printf("%d\n", from_digits(p[i])); */
 
  /* a = connected(999999); */
  /* print_list(a); */
  /* free(a.xs); */


  /* printf ("%d\n", admissable(2,999991)); */
  /* return 0; */
  for (i = 1; i < 10000000; ++i)
    {
      if (prime_q(i) == 0)
	continue;
      else
	{
	  printf("%d\n", i);
	  printf("admissable(2,i) = %d\n", admissable(2,i));
	  continue;
	}

      a = connected(i);
      printf("%d\n", i);
      free(a.xs);
    }
  /* for (i = 0; i < 10000000; ++i) */
  /*   { */
  /*     IntegerLength(i); */
  /*     /\* a = dice_integer(i); *\/ */
  /*     /\* from_digits(a); *\/ */
  /*     /\* print_list(a); *\/ */
  /*     /\* printf ("%d\n", from_digits(a)); *\/ */

  /*     /\* free(a.xs); *\/ */
  /*   } */

  disableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT);
  freeGlobalMemoizationContexts();

  return 0;
}
