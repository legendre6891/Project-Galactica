#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem73.pl
#
#        USAGE: ./problem73.pl  
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
#      CREATED: 08/24/2011 10:23:30 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @denoms = (8, 5, 7);
FIRST: while() {
	my @newD = ();
	push @newD, $denoms[0];
	foreach(1..$#denoms) {
		my $sum = $denoms[$_-1] + $denoms[$_];
		if ($sum <= 12000) {
			push @newD, $sum;
		}
		push @newD, $denoms[$_];
	}
	if ($#newD == $#denoms) {
		last FIRST;
	}
	@denoms = @newD;
	print @denoms . "\n";
}
print @denoms . "\n";
