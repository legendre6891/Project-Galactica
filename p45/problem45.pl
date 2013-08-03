#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem45.pl
#
#        USAGE: ./problem45.pl  
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
#      CREATED: 08/22/2011 04:28:50 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $n = 143;
while() {
	++$n;
	last if (&isPent(&Hn($n)));
}
print &Hn($n);


sub isTriangle {
	my	( $T )	= @_;
	return ((1/2*(-1 + sqrt(1+8*$T))) !~ /\D/) ? 1 : 0;
} ## --- end sub isTriangle

sub isPent {
	my	( $P )	= @_;
	return ((1/6*(1+sqrt(1+24*$P))) !~ /\D/) ? 1 : 0;
} ## --- end sub isPent

sub Hn {
	my ( $n ) = @_;
	return $n*(2*$n-1);
}

