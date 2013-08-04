#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem79.pl
#
#        USAGE: ./problem79.pl  
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
#      CREATED: 08/25/2011 09:42:29 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my @nums = ();
open KEYLOG, "keylog.txt";
while(<KEYLOG>) {
	chomp;
	push @nums, $_;
}
close KEYLOG;
my %seen = ();
foreach(@nums) {
	my @digits = split '', $_;
	foreach(@digits) {
		++$seen{$_};
	}
}
print scalar(keys(%seen)) . "\n";
