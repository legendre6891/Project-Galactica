#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem36.pl
#
#        USAGE: ./problem36.pl  
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
#      CREATED: 08/21/2011 06:41:52 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $sum = 0;
foreach(1..999999) {
	$sum += $_ if (&isPalindrome($_) && &isPalindrome(sprintf("%b",$_)));
}
print $sum;

sub isPalindrome {
	my ( $num ) = @_;
	return $num eq reverse($num);
}
