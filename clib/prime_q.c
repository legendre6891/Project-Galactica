#include "prime_q.h"


int prime_q(unsigned long int n)
{
  mpz_t tester;
  mpz_init(tester);
  
  mpz_set_ui(tester, n);
  int r = mpz_probab_prime_p(tester, 25);


  mpz_clear(tester);

  return r;

}
