#!/usr/bin/perl 
#===============================================================================
#
#         FILE: next_permutation.pl
#
#        USAGE: ./next_permutation.pl  
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
#      CREATED: 08/19/2011 12:41:30 PM
#     REVISION: ---
#===============================================================================
use strict;
use warnings;


my @arr = (1..7);
my @perms = ();
do {
	push @perms, join('', @arr);
} while(&next_permutation(\@arr));

@perms = reverse @perms;
my $num;
foreach $num (@perms) {
	if (&isPrime($num)) {
		print "$num is prime!\n";
		last;
	}
}

sub next_permutation {
	my ( $ref ) = @_;
	my @given = @$ref;
	my $size = $#given;
	if ($size == 0) {
		return 0;
	}
	my $tail = $size;
	#find tail
	while($given[$tail-1] >= $given[$tail]) {
		--$tail;
		if ($tail == 0) {
			return 0;
		}
	}
	my $next = $tail-1;
	my $swap;
	for($swap = $size; $swap >= $tail; --$swap) {
		last if($given[$next] < $given[$swap]);
	}
	#swap $next and $swap
	my $tmp = $given[$swap];
	$given[$swap] = $given[$next];
	$given[$next] = $tmp;
	@$ref = (@given[0..$next], reverse(@given[$tail..$size]));
	return 1;
}

sub isPrime {
	my ( $num ) = @_;
	foreach(2..sqrt($num)) {
		return 0 if $num % $_ == 0;
	}
	return 1;
}
