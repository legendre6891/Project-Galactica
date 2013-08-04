#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem30.pl
#
#        USAGE: ./problem30.pl  
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
#      CREATED: 08/18/2011 10:13:33 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @goodNums = ();
foreach my $a (2..999999) {
	my @digits = split '', $a;
	my $theSum = &sum(map {$_**5} @digits);
	if ($a == $theSum) {
		push @goodNums, $a;
	}
}
print join "\n", @goodNums;
print "\nThe sum of these numbers is " . &sum(@goodNums);


# sums and returns the elements of an array
sub sum {
	my $sum = 0;
	$sum += $_ foreach @_;
	return $sum;
}
