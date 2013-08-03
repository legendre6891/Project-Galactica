#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem71.pl
#
#        USAGE: ./problem71.pl  
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
#      CREATED: 08/24/2011 10:17:54 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my ($n, $d) = (2, 5);
while($d+7<=1000000) {
	$n += 3;
	$d += 7;
}
print "$n/$d";
