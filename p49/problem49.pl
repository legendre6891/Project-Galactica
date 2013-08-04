#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem49.pl
#
#        USAGE: ./problem49.pl  
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
#      CREATED: 08/26/2011 04:31:42 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

# make primes, using sieve
my %primes;
my @primes = ();
my $lim = 9999;
my @nums = ();
foreach(2..$lim) {
	$nums[$_-2] = 0;
}
foreach(2..$lim) {
	if ($nums[$_-2]==0) {
		$primes{$_} = 1;
		push @primes, $_;
		my $val = 2*$_;
		while($val <= $lim) {
			++$nums[$val-2];
			$val+=$_;
		}
	}
}

# 1228
foreach(0..668) {
	my $b = $_;
	foreach(0..$b-1) {
		my $a = $primes[$_];
		my $c = 2*$primes[$b] - $a;
		my $b = $primes[$b];
		if ((&sortDigits($a) eq &sortDigits($b)) && (&sortDigits($a) eq &sortDigits($c))) {
			if ($primes{$c}) {
				print "$a$b$c\n";
			}
		}
	}
}

foreach(669..1228) {
	my $b = $_;
	foreach($b+1..$#primes) {
		my $c = $primes[$_];
		my $a = 2*$primes[$b] - $c;
		my $b = $primes[$b];
		if ((&sortDigits($a) eq &sortDigits($b)) && (&sortDigits($a) eq &sortDigits($c))) {
			if ($primes{$a}) {
				print "$a$b$c\n";
			}
		}
	}
}


sub sortDigits {
	my ( $n ) = @_;
	return join('', sort({$a <=> $b} split('', $n)));
}
