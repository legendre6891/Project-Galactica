#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem34.pl
#
#        USAGE: ./problem34.pl  
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
#      CREATED: 08/17/2011 01:31:19 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $finalsum = 0;

for(my $i = 10; $i <2200000; $i++) {
	my @array = split('',$i);
	my $sum = 0;
	$sum += &factorial($_) foreach (@array);
	if ($i == $sum) {
		print $i . "\n";
		$finalsum += $i;
	}
}

print $finalsum; 

sub factorial {
	my ($num) = @_;
	my $ans = 1;
	for(my $i = 1; $i<=$num; $i++) {
		$ans *= $i;
	}
	return $ans;
}
