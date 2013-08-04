#include <stdio.h>
/* #include "../clib/memoization.h" */
#include "../clib/digits.h"
#include "../clib/list_utilities.h"
#include "../clib/prime_q.h"
#include <assert.h>


#define SOME_MEMOIZATION_CONTEXT 0
/* #define UPPER_LIMIT 1000000 */
/* #define PI_UPPER_LIMIT 78498//9592//303//9592   /\*  *\/ */

#define UPPER_LIMIT 10000000
#define PI_UPPER_LIMIT 664579


int flag;
struct _integer_list
{
  int* xs;
  short len;
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
integer_list ALL[UPPER_LIMIT];

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

/* MEMOIZED_FUNCT(SOME_MEMOIZATION_CONTEXT,int, from_digits, integer_list, l) */
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

/* MEMOIZED_FUNCT(SOME_MEMOIZATION_CONTEXT, integer_list*, change_kth_digit, integer_list, L, int, k) */
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

integer_list all_connected(int n)
{
  return ALL[n];
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
  /* assert(i == 9*a.len - 1); */
  result.xs[i] = chop_left(n);
  // don't forget to free a.xs!
  // also p and p.xs!!
  free(a.xs);
  return result;
}


short two_admissable(int a)
{
  /* if (prime_q(a) == 0) */
  /*   return 0; */

  if (a == 2)
    return 1;


  integer_list l;
  l = all_connected(a);


  for (int i = 0; i < l.len; ++i)
    {
      if (l.xs[i] >= a)
        continue;
      if (mList[l.xs[i]].x == 1)
        {
          /* free(l.xs); */
          return 1;
        }
    }

  /* free(l.xs); */
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
      mList[i].y = 0;
      if (mList[i].x == 1)
        notP--;
    }
}


int mark(int q)
{
  mList[q].y = 1;

  int p;
  int Qfound = 0;
  int Q;

  flag = 0;
  for (p = q+1; p < UPPER_LIMIT; ++p)
    {
      if (prime_q(p) == 0)
        {
          /* mList[p].x = 0; */
          /* mList[p].y = 0; */
          continue;
        }

      /* if (mList[p].x == 1) */
      /* 	continue; */
      mList[p].y = 0;

      integer_list l;
      l = all_connected(p);

      for (int i = 0; i < l.len; ++i)
        {
          if (l.xs[i] >= p)
            continue;
          if (mList[l.xs[i]].y == 1)
            {
              mList[p].y = 1;
	      flag++;

              if (Qfound == 0 && mList[p].x==1)
                {
                  /* printf ("wow p = %d\n",p); */
                  Q = p;
                  Qfound = 1;
                }

              break;
            }
        }
      /* free(l.xs); */
    }
  return Q;
}

int main(int argc, char *argv[])
{
  /* initGlobalMemoizationContexts(); */
  /* enableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT); */

  long int i;
  long int sum = 0;
  int last = 2;
  integer_list a;

  for (i = 1; i < UPPER_LIMIT; ++i)
    {
      if (prime_q(i) != 0)
        ALL[i] = connected(i);
      printf ("%ld\n",i);
    }
  /* return 0; */

  initialize_mList();

  /* for (i = 0; i < UPPER_LIMIT; ++i) */
  /*   { */
  /*     if (prime_q(i) == 0) */
  /*    continue; */
  /*     if (mList[i].x == 0) */
  /*    printf ("%d\n",i); */

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
       * 7. Mark p.x = 1 for all p >= Q, p.y = 1. Decrement notP while doing so.
       * 8. Mark y = 0 for all p >= q.
       */

      // Step 1 and 4.
      while(1)
        {
          last++;
          /* printf ("last = %d, notP = %d\n", last, notP); */
          if (prime_q(last) == 0 || mList[last].x == 1)
            {
              continue;
            }
          break;
        }
      notP--;
      printf ("last = %d, notP = %d\n", last, notP);
      if (mList[last].x == -2)
        {
          printf ("skipped last = %d\n", last);
          continue;
        }


      // Step 2.
      sum += last;

      // Step 3.
      mList[last].x = -1;

      // Step 5.
      int Q = mark(last);

      /* for (int b = 0; b < UPPER_LIMIT; ++b) */
      /*        { */
      /*          if (prime_q(b) != 0) */
      /*            printf("%d -- [%d, %d]\n", b, mList[b].x, mList[b].y); */
      /*        } */

      //Step 6.
      /* int Q; */
      /* for (Q = last; Q < UPPER_LIMIT; Q++) */
      /*        { */
      /*          if (prime_q(Q) == 0) */
      /*            { */
      /*              continue; */
      /*            } */
      /*          if (mList[Q].x == 1 && mList[Q].y==1) */
      /*            { */
      /*              break; */
      /*            } */
      /*        } */
      printf ("For q = %d, Q = %d\n",last ,Q);
      if (flag == 0)
	continue;

      // steps 7 and 8
      for (int p = Q; p < UPPER_LIMIT; ++p)
        {
          if (prime_q(p) == 0)
            continue;
          if (mList[p].y == 1 && mList[p].x == 0)
            {
              mList[p].x = 1;
              notP--;
            }
          mList[p].y = 0;
        }

      // OPTMIZATION!
      for (int p = last + 1; p < Q; ++p)
        {
          if (prime_q(p) == 0)
            continue;
          if (mList[p].x == 0 && mList[p].y == 1)
            {
              sum+=p;

              mList[p].x = -2;
            }
        }



      for (int z = 0; z < Q; ++z)
        {
          mList[z].y = 0;
        }
    }

  printf ("sum = %d\n", sum);
  return 0;

  for (i = 0; i < UPPER_LIMIT; ++i)
    {
      if (prime_q(i) == 0)
        continue;
      printf("[x, y] at %d = [%d, %d]\n", i, mList[i].x, mList[i].y);
    }

  /* disableGlobalMemoizationContext(SOME_MEMOIZATION_CONTEXT); */
  /* freeGlobalMemoizationContexts(); */

  return 0;
}
