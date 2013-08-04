#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem25.pl
#
#        USAGE: ./problem25.pl  
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
#      CREATED: 08/18/2011 07:09:33 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bignum;

# print fibonnaci numbers up to hard coded number
my ($a, $b, $term, $c) = (0, 1, 1);
while(length($b)<1000) {
	#print $b . " term number $term " . "\n";
	$c = $b;
	$b += $a;
	$a = $c;
	$term++;
}
print "Term number $term has 1000 digits";
