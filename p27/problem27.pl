#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem27.pl
#
#        USAGE: ./problem27.pl  
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
#      CREATED: 08/19/2011 10:19:49 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;


my @primes = &listPrimes(300);
my $polyn = '$n**2 + $a*$n + $b';
my ($A, $B, $N) = (0, 0, 0);
foreach(-999..999) {
	my $a = $_;
	foreach(@primes) {
		my $b = $_;
		my $n = 0;
		while(&isPrime(eval($polyn))) {
			++$n;
		}
		if ($n > $N) {
			$A = $a;
			$B = $b;
			$N = $n;
			print "a: $a, b: $b, n: $n\n";
		}
	}
}
print "RESULT a: $A, b: $B, n: $N, ab: " . $A*$B . "\n";

sub listPrimes {
	my ( $numToList ) = @_;
	my @primes = ();
	my $num = 2;
	while($num < 1000) {
		push @primes, $num if &isPrime($num);
		++$num;
	}
	return @primes;
}

sub isPrime {
	my ($num) = @_;
	return 0 if $num<0;
	foreach(2..sqrt($num)) {
		return 0 if $num % $_ == 0;
	}
	return 1;
}
