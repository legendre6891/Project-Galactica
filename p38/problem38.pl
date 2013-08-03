#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem38.pl
#
#        USAGE: ./problem38.pl  
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
#      CREATED: 08/25/2011 12:56:41 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

FIRST: foreach(1..49_999) {
	my $n = $_;
	my $pan = "";
	foreach(1..9) {
		$pan = $pan . ($n * $_);
		if ($pan =~ /(.).*\1|0/) {
			next FIRST;
		}
		if ($pan =~ /[1-9]{9}/) {
			print "$pan: $n\n";
			next FIRST;
		}
	}
}
