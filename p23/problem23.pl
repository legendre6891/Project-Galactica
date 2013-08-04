#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem23.pl
#
#        USAGE: ./problem23.pl  
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
#      CREATED: 08/18/2011 03:44:07 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

open ABUNDANTS, "abundants.txt";
my @abundants = ();
while (<ABUNDANTS>) {
	chomp;
	push @abundants, split " ";
}
close ABUNDANTS;
#print join " ", @abundants;
#print scalar @abundants;
my @sums = ();
for(my $i=0; $i<28122*2; ++$i) {
	push @sums, 0;
}
for(my $i=0; $i<$#abundants; ++$i) {
	for(my $j=0; $j<=$i; ++$j) {
		$sums[$abundants[$i] + $abundants[$j]] = 1;
	}
}

my $fails = 0;
foreach (1..28123) {
	unless ($sums[$_]) {
		$fails += $_;
	}
}
print $fails;

exit;
##stupid solution, requires gigabytes of RAM... -_-
#my @sums = ();
#foreach my $a (1..6965) {
#	foreach my $b ($a..6965) {
#		if ($abundants[$a-1]+$abundants[$b-1]>28123) {
#			next;
#		}
#		push @sums, $abundants[$a-1]+$abundants[$b-1];
#	}
#}
#
#my $totalFail = 0;
#@sums = sort({$a <=> $b} &uniq(@sums));
#print join "\n", @sums;
#foreach (1..$#sums) {
#	foreach ($sums[$_-1]+1..$sums[$_]-1) {
#		$totalFail += $_;
#	}
#}
#print "Total fails sum: $totalFail";
#exit;
#my $totalFails = 0;
#ZEROTH: foreach (1..281) {
#	my $x = $_;
#	FIRST: foreach (@abundants) {
#		my $i = $_;
#		if ($x <  $i) {
#			print "FAILED: $x\n";
#			$totalFails += $x;
#			next ZEROTH;
#		}
#		foreach (@abundants) {
#			my $sum = $_ + $i;
#			if ($sum > $x) {
#				next FIRST;
#			} elsif ($sum == $x) {
#				#print "SUCCESS: $x = $_ + $i\n";
#				next ZEROTH;
#			}
#		}
#	}
#}
#
#print "Sum of all fails: $totalFails";
#
#exit;
#my @abundant = (); # list of abundant numbers
#foreach (14000..14062) {
#	if (&sigma($_) > 2*$_) {
#		push @abundant, $_;
#	}
#}
#
#print join " ", @abundant;

sub sigma {
	my	( $num ) = @_;
	my $ans = 0;
	foreach (2..$num) {
		$ans += $_ if $num % $_ == 0;
	}
	return $ans;
} ## --- end sub sigma

sub uniq {
	    return keys %{{ map { $_ => 1 } @_ }};
	}
