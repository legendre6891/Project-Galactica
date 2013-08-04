#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem47.pl
#
#        USAGE: ./problem47.pl  
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
#      CREATED: 08/25/2011 11:34:58 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $count = 0;
FIRST: foreach(134_043..200_000) {
	my @factors = &primeFactors($_);
	if (scalar(@factors) >= 4) {
		++$count;
	} else {
		$count = 0;
	}
	if ($count == 4) {
		print "$_\n";
		last;
	}
}

sub primeFactors {
	my ($n) = @_;
	my $prime = 2;
	my @factors = ();
	while($n!=1) {
		if ($n%$prime==0) {
			push @factors, $prime;
			$n /= $prime;
		}
		while($n%$prime==0) {
			$n /= $prime;
		}
		++$prime;
	}
	return @factors;
}
