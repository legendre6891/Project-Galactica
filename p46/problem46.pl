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

FIRST: foreach(2..10000) {
	my $num = 2*$_ + 1;
	foreach(@primes) {
		if($_ > $num) {
			print "Failed: $num\n";
			last FIRST;
		}
		last if (&isSq(($num-$_)/2));
	}
}

sub isSq {
	my ( $n ) = @_;
	return sqrt($n)!~/\D/;
}
