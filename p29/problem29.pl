#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem29.pl
#
#        USAGE: ./problem29.pl  
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
#      CREATED: 08/18/2011 07:24:07 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bigint;

my @nums = ();
for(my $a=2; $a<=100; $a++) {
	for(my $b=2; $b<=100; $b++) {
		push(@nums, $a**$b);
	}
}
#print join "\n", @nums;
#exit;
@nums = &uniq(@nums);
print "Number of distinct terms is " . ($#nums + 1);

sub uniq {
	    return keys %{{ map { $_ => 5 } @_ }};
	}
