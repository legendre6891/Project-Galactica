#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem52.pl
#
#        USAGE: ./problem52.pl  
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
#      CREATED: 08/26/2011 05:40:24 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

foreach(1..1_000_000) {
	my $x = $_;
	next if (length($x) != length(6*$x));
	if (&sortDigits($x) eq &sortDigits($x*2) && &sortDigits($x) eq &sortDigits($x*3) && &sortDigits($x) eq &sortDigits($x*4) && &sortDigits($x) eq &sortDigits($x*5) && &sortDigits($x) eq &sortDigits($x*6)) {
		print $x;
		last;
	}
}

sub sortDigits {
	my ( $n ) = @_;
	return join('', sort({$a <=> $b} split('', $n)));
}
