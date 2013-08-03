#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem44.pl
#
#        USAGE: ./problem44.pl  
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
#      CREATED: 08/26/2011 04:15:24 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

# populate hash with pentagonal numbers
my $up = 10000;
my %hash1 = (); # N -> P_n
my %hash2 = (); # P_n -> N
foreach(1..$up) {
	my $P = &pent($_);
	$hash1{$_} = $P;
	$hash2{$P} = $_;
}
FIRST: foreach(1..$up-1) {
	my $diff = $_;
	foreach($diff+1..$up) {
		if($hash2{$hash1{$_} + $hash1{$_-$diff}} && $hash2{$hash1{$_} - $hash1{$_-$diff}}) {
			print $hash1{$_} - $hash1{$_-$diff};
			last FIRST;
		}
	}
}

sub pent {
	my ( $n ) = @_;
	return $n*(3*$n - 1)/2;
}
