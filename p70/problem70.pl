#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem70.pl
#
#        USAGE: ./problem70.pl  
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
#      CREATED: 08/25/2011 09:22:36 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my ($N, $minRatio) = (0, 0);
FIRST: foreach(1..10**7) {
	print "$_\n";
	my $phi = $_;
	my $prime = 2;
	while($_!=1) {
		my $n = $_;
		if ($n % $prime == 0) {
			$phi /= $prime;
			$phi *= $prime - 1;
			$n /= $prime;
		} else {
			next;
		}
		if(length($_) != length($phi)) {
			next FIRST;
		}
		while($_%$prime==0) {
			$n /= $prime;
		}
	} continue {
		++$prime;
	}
}

sub phi {
	my ( $n ) = @_;
	my $phi = $n;
	my $prime = 2;
	while($n!=1) {
		if ($n % $prime == 0) {
			$phi /= $prime;
			$phi *= $prime - 1;
			$n /= $prime;
		}
		while($n%$prime==0) {
			$n /= $prime;
		}
		++$prime;
	}
	return $phi;
}
