#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem48.pl
#
#        USAGE: ./problem48.pl  
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
#      CREATED: 08/17/2011 11:49:42 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $ans = 0;
foreach(1..1000) {
	$ans += &modpower($_, $_, 10000000000);
	$ans %= 10000000000;
}
print $ans;

sub modpower {
	my $ans = 1;
	for(my $i = 0; $i<$_[1]; $i++) {
		$ans *= $_[0];
		$ans %= $_[2];
	}
	return $ans;
}
