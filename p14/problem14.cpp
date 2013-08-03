#include <iostream>
using namespace std;

int main () 
{
	int length;
	int longest = 0;
	long int num;
	int num_orig;
	int num_biggest;
	for (long int i=1; i<1000000; i++) {
		num_orig = i;
		length = 0;
		cout << i;
		num = i;
		while(num != 1) {
			if (num % 2 == 0)
				num /= 2;
			else
				num = 3*num + 1;
			length++;
		}
		cout << "   " << length;
		if (length > longest) {
			longest = length;
			num_biggest = num_orig;
			cout << "  !!";
		}
		cout << endl;
	}
	cout << "Longest chain starts with " << num_biggest << " and has length " << longest << endl;
	
	return 0;
}
