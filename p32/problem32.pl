#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem32.pl
#
#        USAGE: ./problem32.pl  
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
#      CREATED: 08/18/2011 10:41:57 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use integer;

my $finalSum = 0;
FIRST: foreach(1000..9999) {
	my $num = $_;
	foreach my $c (2..sqrt($num)) {
		if ($num % $c == 0) {
			my $d = $num/$c;
			#check for panitigality
			my @digits = split('', $c . $d . $num);
			@digits = sort {$a <=> $b} @digits;
			if ((scalar(@digits)== 9) && ($digits[0]!=0) && (scalar(&uniq(@digits) == 9))) {
				#print "$num = $c X $d". "\n";
				$finalSum += $num;
				next FIRST;
			}
		}
	}
}
print "Sum of all such numbers is $finalSum\n";


sub uniq {
	    return keys %{{ map { $_ => 1 } @_ }};
	}
