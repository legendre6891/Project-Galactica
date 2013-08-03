#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem19.pl
#
#        USAGE: ./problem19.pl  
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
#      CREATED: 08/18/2011 06:11:29 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use integer;

#print &dow(2000, 1, 01);
my $count = 0;
#exit;
foreach(1901..2000) {
	my $year = $_;
	foreach(1..12) {
		$count++ if (&dow($year, $_, 1)==0);
	}
}
print "$count Sundays fell on the first of the month from 1/1/1901 to 12/31/2000)";


# Day of week function, works only if 1900 < year 
# year, month, day
sub dow {
	my	( $y, $m, $d )	= @_;
	my @months = (0, 1, 4, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5);
	$y -= 1900;
	$y -= 1 if $m < 3;
	return ($y/4 - $y/100 + ($y+300)/400 + $y +  $months[$m] + $d)%7;
} ## --- end sub dow
