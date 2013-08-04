#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem50.pl
#
#        USAGE: ./problem50.pl  
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
#      CREATED: 08/22/2011 05:37:03 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @primes = ();
open PRIMES, "p50_primes.txt";
while(<PRIMES>) {
	chomp;
	push @primes, $_;
}
close PRIMES;

my $maxsum = 0;
my $maxlen = 0;
FIRST: foreach(2..40_000) {
	my $len = $_;
#	print "LENGTH: $len\n";
	my $sum = 0;
	foreach(1..$len-1) {
		$sum += $primes[$_-1];
	}
	$sum += $primes[-1];
	
	my $count = 0;
	foreach(0..$#primes-$len+1) {
		$sum -= $primes[$_-1];
		$sum += $primes[$_+$len-1];
		if ($sum > 999999) {
			if ($_ == 0) {
				last FIRST;
			} else {
				next FIRST;
			}
		}
		++$count if (&isPrime($sum));
		if ((&isPrime($sum)) && $len > $maxlen) {
#			print "PRIME: $maxsum, COUNT: $len\n";
			$maxlen = $len;
			$maxsum = $sum;
		}
	}
}
print "$maxsum\n";

sub isPrime {
	my ( $num ) = @_;
	return 0 if ($num <= 1);
	foreach(2..sqrt($num)) {
		return 0 if ($num % $_ == 0);
	}
	return 1;
}
