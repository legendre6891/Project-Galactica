#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem58.pl
#
#        USAGE: ./problem58.pl  
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
#      CREATED: 08/24/2011 07:39:57 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $denom = 1;
my $num = 0;
my $len;
foreach(1..15000) {
	$len = 2*$_+1;
	my $sq = $len**2;
	++$num if &isPrime($sq-($len-1));
	++$num if &isPrime($sq - 2*($len-1));
	++$num if &isPrime($sq - 3*($len-1));
	$denom += 4;
	last if ($num/$denom <.1);
}
print "FINAL: $len\n";

sub isPrime {
	my ( $num ) = @_;
	return 0 if ($num <= 1);
	foreach(2..sqrt($num)) {
		return 0 if ($num % $_ == 0);
	}
	return 1;
}
