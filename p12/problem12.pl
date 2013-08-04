#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem12.pl
#
#        USAGE: ./problem12.pl  
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
#      CREATED: 08/17/2011 07:00:52 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;


#build list of triangle numbers, up to 50th one
my @numsToTest = ();
push(@numsToTest, &trinum($_)) foreach (11501..14500);
foreach (@numsToTest) {
	
	
	my $num = $_;
	#print "Enter a number: ";
	#chomp($num = <STDIN>);
	
	my @factors = ();
	my $x = 1;
	my $divisors = 1;
	do {
		$x++;
		my @tmp = ($x, 0);
		while($num % $x == 0) {
			$tmp[1]++;
			$num /= $x;
		}
		if ($tmp[1] != 0) {
			push @factors, [ @tmp ];
		}
		$divisors *= $tmp[1] + 1;
	} while($num != 1);
	
	print "Current number: $_\n";
	foreach (@factors) {
		print join(" ^ ", @$_);
		print "\n";
	}

	print "Number of divisors: $divisors";
	if ($divisors > 500) {
		print "\nThe number you seek is $_";
		exit;
	}
	print "\n";
}

sub trinum {
	my	( $num )	= @_;
	return $num*($num+1)/2;
} ## --- end sub trinum
