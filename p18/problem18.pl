#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem18.pl
#
#        USAGE: ./problem18.pl  
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
#      CREATED: 08/19/2011 06:33:55 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @triangle = ();
open(NUMBERS, "p18_nums.txt");
while (<NUMBERS>) {
	push(@triangle, [ split ]);
}
close(NUMBERS);

#test print: SUCCESS
#foreach my $row (@triangle) {
#	print join(" ", @$row) . "\n";
#}
my $biggest = 0;
my @biggestpath = ();
for(my $pathnum=0; $pathnum<=2**14-1; ++$pathnum) {
	my $sum = 0;
	my ( $row, $col ) = (0, 0);
	my @path = split('', sprintf("%014b", $pathnum));
	$sum += $triangle[0][0];
	foreach(@path) {
		++$row;
		if($_ == 1) {
			++$col;
		}
		$sum += $triangle[$row][$col];
	}
	if($sum > $biggest) {
		$biggest = $sum;
		@biggestpath = @path;
	}
}
print "Biggest sum is $biggest" . "\n";
print "The path is " . join " ", @biggestpath;
