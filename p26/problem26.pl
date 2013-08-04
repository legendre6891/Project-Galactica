#!/usr/bin/perl 
#===============================================================================
#
#         FILE: test.pl
#
#        USAGE: ./test.pl  
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
#      CREATED: 08/15/2011 08:07:48 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;


#&longdiv(1,19,200);
#exit;
my ($D, $longestlen) = (0, 0);
foreach(1..1000) {
	my $len = &longdiv(1, $_, 1000);
	if ($len > $longestlen) {
		$longestlen = $len;
		$D = $_;
	}
}
print "d = $D, length of cycle is $longestlen\n";

# precondition: $num, $denom > 0, $num < $denom
sub longdiv {
	my ($num, $denom, $steps) = @_;
	my @quotients = ();
	my @check = ($num/$denom);
	foreach(1..$steps) {
		push @quotients, my $q = sprintf("%d", 10*$num/$denom);
		#print "Q: $q\n";
		$num = 10*$num - $q*$denom;
		#print "$num\n";
		my $repeat = &indexOf(\@check, $num/$denom);
		if($repeat != -1) {
			#print "Repeats with period " . ($#check + 1 - $repeat);
			return $#check + 1 - $repeat;
		}
		push @check, $num/$denom;
	}
}

sub indexOf {
	my @arr = @{$_[0]};
	my $elt = $_[1];
	for(my $i = 0; $i<=$#arr; ++$i) {
		if ($arr[$i] == $elt) {
			return $i;
		}
	}
	return -1;
}
