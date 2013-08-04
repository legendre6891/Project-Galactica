#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem54.pl
#
#        USAGE: ./problem54.pl  
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
#      CREATED: 08/26/2011 06:45:06 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

sub printHand {
	my @hand = @{$_[0]};
	my %hands = (0 => "High Card",
 	1 => "One Pair",
 	2 => "Two Pairs",
 	3 => "Three of a Kind",
 	4 => "Straight",
 	5 => "Flush",
 	6 => "Full House",
 	7 => "Four of a Kind",
 	8 => "Straight Flush",
 	9 => "Royal Flush" );
	print $hands{$hand[0]} . " " . $hand[1] . "\n";
}




my %order = (A => 14, K => 13, Q => 12, J => 11, T => 10);
foreach(2..9) {
	$order{$_} = $_;
}
#sub pokercmp {
#	my $A = (split('', $a))[0];
#	my $B = (split('', $b))[0];
#	$order{$B} <=> $order{$A};
#}


my @hands = ();
open POKER, "poker.txt";
while(<POKER>) {
	my @arr = split ' ';
	@arr = map {s/(A|K|Q|J|T)/$order{$1}/; $_} @arr;
	my @round = ();
	foreach(@arr) {
		push @round, [substr($_, 0, -1), substr($_, -1, 1)];
	}
	push @hands, [[sort({$b->[0] <=> $a->[0]} @round[0..4])], [sort({$b->[0] <=> $a->[0]} @round[5..9])]];
}
close POKER;

#foreach(0..999) {
#	my $round = $_;
#	print "P1: ";
#	foreach(0..4) {
#		print join('', @{$hands[$round][0][$_]}) . " ";
#	}
#	print " | P2: ";
#	foreach(0..4) {
#		print join('', @{$hands[$round][1][$_]}) . " ";
#	}
#	print "\n";
#}

my $count = 0;
foreach(0..$#hands) {
	my @P1 = &evalHand($hands[$_][0]);
	my @P2 = &evalHand($hands[$_][1]);
	++$count if (($P1[0] > $P2[0]) || (($P1[0] == $P2[0]) && (($P1[1] > $P2[1]) || (($P1[1] == $P2[1]) && ($P1[2] > $P2[2])))));
}
print "$count\n";


# returns an array (a, b, c), where a is the type of hand, b is the rank of a, and c is the high card used for breaking ties
# a: 0 = High Card
# 	 1 = One Pair
# 	 2 = Two Pairs
# 	 3 = Three of a Kind
# 	 4 = Straight
# 	 5 = Flush
# 	 6 = Full House
# 	 7 = Four of a Kind
# 	 8 = Straight Flush
# 	 9 = Royal Flush
# precondition: hand is sorted!
sub evalHand {
	my @hand = @{$_[0]};
	my $high = $hand[0][0];
	# 9, 8
	if (&isFlush(\@hand) && &isStraight(\@hand)) {
		if ($hand[0][0] == 14) {
			return (9, 0, $high);
		} else {
			return (8, $high, $high);
		}
	}
	# 7
	if (($hand[1][0] == $hand[2][0]) && ($hand[2][0] == $hand[3][0]) && (($hand[1][0] == $hand[0][0]) || ($hand[1][0] == $hand[4][0]))) {
		return (7, $hand[1][0], $high);
	}
	# 6
	if ((($hand[0][0] == $hand[1][0]) && ($hand[1][0] == $hand[2][0]) && ($hand[3][0] == $hand[4][0])) || (($hand[0][0] == $hand[1][0]) && ($hand[2][0] == $hand[3][0]) && ($hand[3][0] == $hand[4][0]))) {
		return (6, $hand[2][0], $high);
	}
	# 5
	if (&isFlush(\@hand)) {
		return (5, $high, $high);
	}
	# 4
	if (&isStraight(\@hand)) {
		return (4, $high, $high);
	}
	# 3
	foreach(0..2) {
		return (3, $hand[2][0], $high) if (($hand[$_][0] == $hand[$_+1][0]) && ($hand[$_+1][0] == $hand[$_+2][0]));
	}
	# 2
	if ((($hand[0][0] == $hand[1][0]) && ($hand[2][0] == $hand[3][0])) || (($hand[0][0] == $hand[1][0]) && ($hand[3][0] == $hand[4][0])) || (($hand[1][0] == $hand[2][0]) && ($hand[3][0] == $hand[4][0]))) {
		return (2, $hand[1][0], $high);
	}
	# 1
	foreach(0..3) {
		return (1, $hand[$_][0], $high) if ($hand[$_][0] == $hand[$_+1][0]);
	}
	# 0
	return (0, $high, $high);
}

sub isFlush {
	my @hand = @{$_[0]};
	my $isIt = 1;
	my $suit = $hand[0][1];
	foreach(1..4) {
		$isIt = 0 if ($hand[$_][1] ne $suit);
	}
	return $isIt;
}

sub isStraight {
	my @hand = @{$_[0]};
	my $isIt = 1;
	foreach(1..4) {
		$isIt = 0 if ($hand[$_-1][0] != $hand[$_][0] + 1);
	}
	return $isIt;
}
