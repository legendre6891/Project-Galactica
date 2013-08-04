#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem67.pl
#
#        USAGE: ./problem67.pl  
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
#      CREATED: 08/19/2011 07:19:35 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;


my @triangle = ();
open(NUMBERS, "p67_nums.txt");
while (<NUMBERS>) {
	push(@triangle, [ split ]);
}
close(NUMBERS);

#test print: SUCCESS
#foreach my $row (@triangle) {
#	print join(" ", @$row) . "\n";
#}

#strategy: push up from the bottom
for(my $row = $#triangle-1; $row >= 0; --$row) {
	foreach my $col (0..$row) {
		my $a = $triangle[$row+1][$col];
		my $b = $triangle[$row+1][$col+1];
		$triangle[$row][$col] += ($a > $b) ? $a : $b;
	}
}
print "Maximal sum is $triangle[0][0]" . "\n";
