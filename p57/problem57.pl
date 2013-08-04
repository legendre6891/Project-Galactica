#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem57.pl
#
#        USAGE: ./problem57.pl  
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
#      CREATED: 08/26/2011 06:33:10 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bigint;

my $count = 0;
my ($num, $denom) = (1, 1);
my ($numPrev, $denomPrev) = (1, 0);
foreach(1..1_000) {
	my $tmp = $num;
	$num = 2*$num + $numPrev;
	$numPrev = $tmp;
	$tmp = $denom;
	$denom = 2*$denom + $denomPrev;
	$denomPrev = $tmp;
	if (length($num)>length($denom)) {
		++$count;
	}
}
print "$count\n";
