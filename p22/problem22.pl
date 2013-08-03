#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem22.pl
#
#        USAGE: ./problem22.pl  
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
#      CREATED: 08/18/2011 01:38:45 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @names = ();
open NAMES, "names.txt";
while ( <NAMES> ) {
	chomp;
	push @names, split ",";
}
close NAMES;

@names = map {substr($_, 1, -1)} @names;
@names = sort @names;

#print $_ . "\n" foreach (@names);

my $total = 0;
for my $x (0..$#names) {
	my $name = $names[$x];
	my @chars = split '', $name;
	my $score = 0;
	foreach my $char (@chars) {
		$score += ord($char) - 64;
		print $score. " $x\n";
	}
	$score *= $x + 1;
	$total += $score;
}
print "Total score is $total";
print "\nLines: $#names";
