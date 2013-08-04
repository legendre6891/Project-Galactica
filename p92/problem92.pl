#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem92.pl
#
#        USAGE: ./problem92.pl  
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
#      CREATED: 10/08/2011 05:19:25 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $count = 0;
my %seen1 = (1 => 1);
my %seen89 = (89 => 1);
for(my $i=1; $i<=10_000_000; $i++) {
	my $num = $i;
	my %nums = ($num => 1);
	print "$num\n" if ($num%100000==0);
	until($seen89{$num} || $seen1{$num}) {
		my @digits = split '', $num;
		$num = 0;
		foreach(@digits) {
			$num+=$_**2;
		}
		$nums{$num}++;
	}
	if ($seen89{$num}) {
		@seen89{keys %nums} = values %nums;
		$count++;
	} else {
		@seen1{keys %nums} = values %nums;
	}
}
print $count;
