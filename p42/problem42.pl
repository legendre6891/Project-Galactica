#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem42.pl
#
#        USAGE: ./problem42.pl  
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
#      CREATED: 08/22/2011 12:00:44 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use List::Util qw(sum);


my %tris = map {$_ => 0} &genTri;
my @words = ();
open WORDS, "words.txt";
while(<WORDS>) {
	chomp;
	$_ = substr $_, 1, -1;
	push @words, $_;
}
close WORDS;
my $count = 0;
foreach(@words) {
	my @letters = split '', $_;
	@letters = map {ord($_) - 64} @letters;
	if(exists $tris{sum(@letters)}) {
		++$count;
	}
}
print "Number of triangle words: $count\n";



sub genTri {
	my @tris = ();
	my $num = 1;
	my $tri;
	do {
		$tri = $num*($num+1)/2;
		push @tris, $tri;
		++$num;
	} while($tri<=416);
	pop @tris;
	return @tris;
}
