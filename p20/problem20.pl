#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem20.pl
#
#        USAGE: ./problem20.pl  
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
#      CREATED: 08/16/2011 10:16:59 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bignum;

my $fac = 1;
$fac *= $_ foreach (1..100);
my @digits = split '', $fac;
my $sum = 0;

for (@digits) {
	$sum += $_;
}

print $sum;
