#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem43.pl
#
#        USAGE: ./problem43.pl  
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
#      CREATED: 08/22/2011 12:28:24 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $count = 0;
my $sum = 0;
open(PERMS, "p43_perms.txt");
while(<PERMS>) {
	chomp;
	if (substr($_, 1, 3) % 2 == 0 &&
		substr($_, 2, 3) % 3 == 0 &&
		substr($_, 3, 3) % 5 == 0 &&
		substr($_, 4, 3) % 7 == 0 &&
		substr($_, 5, 3) % 11 == 0 &&
		substr($_, 6, 3) % 13 == 0 &&
		substr($_, 7, 3) % 17 == 0) {
		++$count;
		$sum += $_;
	}
}
close PERMS;
print "Numbers with the property: $count\n";
print "Sum: $sum\n";


sub next_permutation {
	my ( $ref ) = @_;
	my @given = @$ref;
	my $size = $#given;
	if ($size == 0) {
		return 0;
	}
	my $tail = $size;
	#find tail
	while($given[$tail-1] >= $given[$tail]) {
		--$tail;
		if ($tail == 0) {
			return 0;
		}
	}
	my $next = $tail-1;
	my $swap;
	for($swap = $size; $swap >= $tail; --$swap) {
		last if($given[$next] < $given[$swap]);
	}
	#swap $next and $swap
	my $tmp = $given[$swap];
	$given[$swap] = $given[$next];
	$given[$next] = $tmp;
	@$ref = (@given[0..$next], reverse(@given[$tail..$size]));
	return 1;
}
