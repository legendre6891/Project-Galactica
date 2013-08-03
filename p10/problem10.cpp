#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

bool isPrime(int);

int main()
{
	// find the i-th prime
	long int i = 2000000;
	long int x = 1;
	int count = 0;
	long int sum = 0;
	while (x < i) {
		x++;
		if (isPrime(x)) {
			count++;
			cout << x << endl;
			sum += x;
		}
	}
	cout << "Sum of primes less than " << i << " is " << sum << endl;
	return 0;
	
}

bool isPrime(int a) {
	for (int i = 2; i <= sqrt(a); i++) {
		if (a % i == 0)
			return false;
	}
	return true;
}
