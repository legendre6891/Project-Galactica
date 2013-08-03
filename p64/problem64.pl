#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem64.pl
#
#        USAGE: ./problem64.pl  
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
#      CREATED: 08/24/2011 07:56:53 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bignum;


foreach(2..13) {
	my @nums = ();
	my $n = sqrt $_;
	while(1) {
		$n = printf("%.10f",1/($n - &floor($n)));
		print "$n\n";
		my $index = &indexOf(\@nums, $n);
		print "$#nums\n";
		if ($index != -1) {
			print "Period is " . $#nums + 1 - $index . "\n";
			last;
		}
		push @nums, $n;
	}
}

sub floor {
	my ( $n ) = @_;
	return sprintf("%d",$n);
}

sub indexOf {
	my @arr = @{$_[0]};
	my $elt = $_[1];
	for(my $i = 0; $i<=$#arr; ++$i) {
		if ($arr[$i] eq $elt) {
			return $i;
		}
	}
	return -1;
}
