#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem28.pl
#
#        USAGE: ./problem28.pl  
#
#  DESCRIPTION: Calculates sum along both main diagonals of a 1001x1001 spiral 
#
#      OPTIONS: ---
# REQUIREMENTS: ---
#         BUGS: ---
#        NOTES: ---
#       AUTHOR: Brian Tu (), 
#      COMPANY: 
#      VERSION: 1.0
#      CREATED: 08/18/2011 09:36:52 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $sum = 0;
for(my $i=1; $i<=1001; $i+=2) {
	$sum += $i*$i*4 - ($i-1)*6;
}
print "Sum requested is $sum";
