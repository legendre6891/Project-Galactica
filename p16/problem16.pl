#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem16.pl
#
#        USAGE: ./problem16.pl  
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
#      CREATED: 08/16/2011 10:09:50 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bignum;

my $num = 2**1000;
my @digits = split '', $num;
my $sum = 0;

for (@digits) {
	$sum += $_;
}

print $sum;
