#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem55.pl
#
#        USAGE: ./problem55.pl  
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
#      CREATED: 08/17/2011 02:03:13 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use bignum;

my $master = 0;
for(my $i = 1; $i<10000; $i++) {
	my $num = $i;
	my $counter = 0;
	REVERSAL: {do {
		print $num . " + " . reverse($num) . " = ";
		$num += reverse($num);
		print $num . "\n";
		$counter++;
		if ($counter >= 50) {
			$master++;
			print "FAILED\n";
			last REVERSAL;
		}
	} while ($num != reverse($num)); }
	print "Palindrome after $counter steps \n\n";
}

print "Number of Lychrel numbers: $master";
