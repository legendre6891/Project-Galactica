#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem51.pl
#
#        USAGE: ./problem51.pl  
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
#      CREATED: 11/11/2011 08:24:06 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $a;
my $num;
my $good = 0;

foreach(10..97) {
	$a = $_;
	if(!&isPrime($a)) {
		next;
	}
	foreach(101..997) {
		my $b = $_;
		if(!&isPrime($b)) {
			next;
		}
	$num = 0;
	foreach(1..9) {
		my $iP = &isPrime("$b" . "$_"x3 . $a);
		$num += $iP;
		print $iP;
	}
	print "   $a   $num";
	if($num >= 8) {
		print " !!";
		$good = 1;
	}
	print "\n";
	}
	
}
print $good;

sub isPrime {
	my ( $num ) = @_;
	return 0 if ($num <= 1);
	foreach(2..sqrt($num)) {
		return 0 if ($num % $_ == 0);
	}
	return 1;
}
