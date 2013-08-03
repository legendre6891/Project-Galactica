#include <stdio.h>
/* #include "../clib/memoization.h" */
#include "../clib/digits.h"
#include "../clib/list_utilities.h"
#include "../clib/prime_q.h"
#include <assert.h>


#define SOME_MEMOIZATION_CONTEXT 0
#define UPPER_LIMIT 1000
#define PI_UPPER_LIMIT 168



struct _integer_list
{
  int* xs;
  int len;
};

typedef struct _integer_list integer_list;



struct _pair
{
  short x;
  short y;
};

typedef struct _pair pair;

pair mList[UPPER_LIMIT];
int notP = PI_UPPER_LIMIT;


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
      if (a.xs[1] == 0)
	{
	  free(a.xs);
	  return 0;
	}
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
/* MEMOIZED_FUNCT(SOME_MEMOIZATION_CONTEXT, short, admissable, int, a, int, b) */
/* { */
/*   if (prime_q(a) == 0 || prime_q(b) == 0) */
/*     return 0; */

/*   if (a == b) */
/*     return 1; */

  
/*   integer_list l; */
/*   l = connected(b); */


/*   for (int i = 0; i < l.len; ++i) */
/*     { */
/*       if (l.xs[i] >= b) */
/* 	continue; */
/*       if (admissable(a, l.xs[i]) != 0) */
/* 	return 1; */
/*     } */
  
/*   return 0; */
/* } */


short two_admissable(int a)
{
  /* if (prime_q(a) == 0) */
  /*   return 0; */

  if (a == 2)
    return 1;

  
  integer_list l;
  l = connected(a);


  for (int i = 0; i < l.len; ++i)
    {
      if (l.xs[i] >= a)
	continue;
      if (mList[l.xs[i]].x == 1)
	return 1;
    }
  
  free(l.xs);
  return 0;
}  


void initialize_mList()
{
  for (int i = 0; i < UPPER_LIMIT; ++i)
    {
      if (prime_q(i) == 0)
	continue;
      /* printf("%d\n", i); */
      mList[i].x = two_admissable(i);
      if (mList[i].x == 1)
	notP--;
    }
}

int main(int argc, char *argv[])
{
  int i;
  int sum = 0;
  int last = 2;
  integer_list a;


  /* a = connected(103); */
  /* print_list(a); */
  /* return 0; */
  
  initialize_mList();

  /* for (i = 0; i < UPPER_LIMIT; ++i) */
  /*   { */
  /*     if (prime_q(i) == 0) */
  /* 	continue; */
  /*     if (mList[i].x == 0) */
  /* 	printf ("%d\n",i); */
      
  /*   } */

  /* printf ("%d\n", notP); */

  while(notP != 0)
    {
      /*
       * 1. Find the first x = 0 element; Call this q. Dec. notP
       * 2. Add this to the sum; 
       * 3. Mark its x = -1
       * 4. Save it somewhere.
       * 5. Mark y = 1 for all q-admissable primes.
       * 6. Find the first prime Q such that Q.x = 1 and Q.y = 1
       * 7. Mark p.x = 1 for all p >= Q. Decrement notP while doing so.
       */

      
      while(1)
	{
	  last++;
	  if (prime_q(last) == 0 || mList[last].x == 1)
	    {
	      continue;
	    }
	  break;
	}

      notP = 0;
    }

  return 0;

  for (i = 0; i < UPPER_LIMIT; ++i)
    {
      if (prime_q(i) == 0)
	continue;
      printf("[x, y] at %d = [%d, %d]\n", i, mList[i].x, mList[i].y);
      
    }
  return 0;
}
