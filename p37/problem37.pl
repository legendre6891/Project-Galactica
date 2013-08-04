#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem37.pl
#
#        USAGE: ./problem37.pl  
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
#      CREATED: 08/21/2011 06:56:08 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;


open(PRIMES, "p37_primes.txt");
my @primes = ();
while(<PRIMES>) {
	chomp;
	push @primes, $_;
}
close PRIMES;

my $sum = 0;
my $count = 0;
FIRST: foreach(@primes) {
	#my @digits = split '', $_;
	#@digits = @digits[1..$#digits-1];
	#foreach(@digits) {
	#	next FIRST if ($_ % 2 == 0);
	#}
	#next unless (&isPrime(substr($_,0,1)) && &isPrime(substr($_,-1,1)));
	#if (&isPrime($_)) {
		#print "$_\n";
		#check <-
		my $_Copy = $_;
		do {
			chop $_Copy;
			unless (&isPrime($_Copy)) {
				next FIRST;
			}
		} while(length($_Copy) > 1);
		#check ->
		$_Copy = $_;
		do {
			$_Copy = substr($_Copy,1);
			unless (&isPrime($_Copy)) {
				next FIRST;
			}
		} while(length($_Copy) > 1);
		print "$_ is such a prime\n";
		$sum += $_;
		++$count;
		last if ($count == 11);
	#}
}
print "Sum is $sum\n";


sub isPrime {
	my ( $num ) = @_;
	return 0 if $num == 1;
	foreach(2..sqrt($num)) {
		return 0 if $num % $_ == 0;
	}
	return 1;
}
