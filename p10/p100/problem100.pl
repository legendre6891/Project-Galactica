#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem100.pl
#
#        USAGE: ./problem100.pl  
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
#      CREATED: 08/26/2011 05:18:09 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bignum;

foreach(707_106_781_187..708_106_781_187) {
	if (&isInt(1/2*(sqrt(1-8*$_+8*$_**2)))) {
			print "$_\n";
			last;
		}
}

sub isInt {
	my ( $n ) = @_;
	my $a = sprintf("%d",$n);
	return $a == $n;
}
