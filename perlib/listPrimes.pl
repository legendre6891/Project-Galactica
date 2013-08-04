#!/usr/bin/perl 
#===============================================================================
#
#         FILE: listPrimes.pl
#
#        USAGE: ./listPrimes.pl  
#
#  DESCRIPTION: 
#
#      OPTIONS: ---
# REQUIREMENTS: ---
#         BUGS: ---
#        NOTES: ---
#       AUTHOR: Brian Tu (), 
#      COMPANY: 
#      VERSION: 1.0
#      CREATED: 08/20/2011 08:29:43 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @primes = &listPrimes(50);
# listPrimes( $num, $mode )
# mode = 0 is list first $num primes
#      = 1 is list primes until $num;
sub listPrimes {
	my ($num) = @_;
	my @primes = (2..$num);
	foreach(0..$num-1) {
		last if $_ > $#primes;
		my $prime = $primes[$_];
		@primes = grep {!&multipleOf($_, $prime)} @primes;
		unshift @primes, $prime;
	}
	return @primes;
}

sub multipleOf {
	my ($num, $mod) = @_;
	return 0 if $mod == 0;
	return ($num % $mod == 0) ? 1 : 0;
}
