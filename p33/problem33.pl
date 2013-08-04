#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem33.pl
#
#        USAGE: ./problem33.pl  
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
#      CREATED: 08/20/2011 11:37:26 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

foreach(1..9) {
	my $a = $_;
	foreach(1..9) {
		my $c = $_;
		if ((10*$a*$c) % (9*$c+$a) == 0) {
			my $b = 10*$a*$c/(9*$c+$a);
			print "$a$b/$c$a = $b/$c\n" if $b/$c!=1;
		}
	}
}
