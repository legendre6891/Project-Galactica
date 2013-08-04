#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem39.pl
#
#        USAGE: ./problem39.pl  
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
#      CREATED: 08/26/2011 02:31:00 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use POSIX qw/ceil floor/;

my $maxCount = 0;
my $maxPerim = 0;
foreach my $perim (1..1000) {
	my $count = 0;
	foreach(ceil($perim/3)..floor($perim/2-0.1)) {
		my $c = $_;
		foreach(1..floor(($perim-$_)/2)) {
			my $a = $_;
			my $b = $perim - $a - $c;
			if ($a**2 + $b**2 == $c**2) {
				++$count;
			}
		}
		if ($count > $maxCount) {
			$maxPerim = $perim;
			$maxCount = $count;
		}
	}
}
print "p = $maxPerim with $maxCount solutions\n";
