#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem17.pl
#
#        USAGE: ./problem17.pl  
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
#      CREATED: 08/17/2011 10:06:05 AM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

# 10 = ten
# 101 = one hundred and one
# 140 one hundred and forty
# 542 five hundred and forty two

#print "enter any number: ";
#chomp(my $num = <STDIN>);
#print "\n";

my $wordlen = 0;
my $word;
for (my $num = 1; $num < 1000; $num++) {
# split number up into digits
	my @digits = split '', $num;
# CHECK: print $_ . " " foreach @digits;
	
# word size defs
	my @units = ("", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine");
#$units[$_] = length($units[$_]) foreach (0..9);
	my @tens = ("", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety");
#$tens[$_] = length($tens[$_]) foreach (0..9);
	my @hundreds = ("", "onehundred", "twohundred", "threehundred", "fourhundred", "fivehundred", "sixhundred", "sevenhundred", "eighthundred", "ninehundred");
	if (scalar @digits == 3) {
		if (($digits[1] == 0) && ($digits [2] == 0)) {
			$word = $hundreds[$digits[0]];
		} else {
			$word =  $hundreds[$digits[0]] . "and" . &teens($digits[1], $digits[2]); 
		}
	} elsif (scalar @digits == 2) {
		$word =  &teens($digits[0], $digits[1]);
	} elsif (scalar @digits == 1) {
		$word =  $units[$digits[0]];
	}
	print $word . "\n";
	$wordlen += length($word);
}

print $wordlen;


sub teens {
	my @units = ("", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine");
#$units[$_] = length($units[$_]) foreach (0..9);
	my @tens = ("", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety");
#$tens[$_] = length($tens[$_]) foreach (0..9);

	unless ($_[0] == 1) {
		return $tens[$_[0]] . $units[$_[1]];
	} else {
		return(("ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen")[$_[1]]);
	}
}
