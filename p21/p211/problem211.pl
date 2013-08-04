#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem221.pl
#
#        USAGE: ./problem221.pl  
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
#      CREATED: 12/28/2011 11:05:32 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bignum;

foreach(101..500) {
	my $a = $_;
	foreach(1..10) {
		my $b = &sig2($a,$_);
		print $b if (&isSq($b));
	}
}

sub sig2 {
	my ( $p, $k ) = @_;
	return ($p**(2*($k+1)) - 1) / ($p*$p - 1);
}

sub isSq {
	no bignum;
	my ( $n ) = @_;
	return (sqrt($n) == int(sqrt($n)));
}
