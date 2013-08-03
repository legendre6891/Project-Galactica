#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem35.pl
#
#        USAGE: ./problem35.pl  
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
#      CREATED: 08/20/2011 11:52:36 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @arr = &listPrimes(50);
print join " ", @arr;
exit;
open(PRIMES, "p35_primes.txt");
my @primes = ();
while(<PRIMES>) {
	chomp;
	push @primes, $_;
}
close PRIMES;

my %seen = ();
foreach(@primes) {
	if(exists $seen{$_}){
		next;
	}
	my @cur = ($_);
	my @digits = split //, $_;
	my $num;
	do {
		push(@digits, shift(@digits));
		$num = join '', @digits;
		if($num == $_) {
			++$seen{$_} foreach (@cur);
			next;
		}
	} while(&isPrime($num));
}
print "Number of cyclic primes: " . keys %seen;

sub listPrimes {
	my ( $numToList ) = @_;
	my @primes = ();
	my $num = 2;
	while($num < $numToList) {
		push @primes, $num if &isPrime($num);
		++$num;
	}
	return @primes;
}

sub isPrime {
	my ($num) = @_;
	return 0 if $num<0;
	foreach(2..sqrt($num)) {
		return 0 if $num % $_ == 0;
	}
	return 1;
}
