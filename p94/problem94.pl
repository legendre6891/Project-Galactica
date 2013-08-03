#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem94.pl
#
#        USAGE: ./problem94.pl  
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
#      CREATED: 08/25/2011 09:49:39 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

print (3*(166_666_666*2+1)+1);
my $sum = 0;
foreach(1..166666666) {
	print "$_\n" if ($_ % 1_000_000 == 0);
	unless($_%3==1) {
		my $h = sqrt(3*$_*$_ + 4*$_ + 1);
		if ($h!~/\D/) {
			$sum += 2*(2*$_ + 1) + 2*$_;
		}
	}
	unless($_%3==2) {
		my $h = sqrt(3*$_*$_ + 2*$_);
		if ($h!~/\D/) {
			$sum += 2*(2*$_ + 1) + 2*$_ + 2;
		}
	}
}
print "$sum\n";
