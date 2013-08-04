#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem40.pl
#
#        USAGE: ./problem40.pl  
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
#      CREATED: 08/21/2011 07:58:21 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $num = 1;
my $count = 0;
my @subs = (1, 10, 100, 1000, 10000, 100000, 1000000);
my $product = 1;
while($#subs>0) {
	my @digits = split '', $num;
	if ($count + @digits >= $subs[0]) {
		$product *= $digits[$subs[0] - $count - 1];
		shift @subs;
	}
	$count += @digits;
	++$num;
}
print $product;
print "\n";
