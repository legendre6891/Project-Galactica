#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem60.pl
#
#        USAGE: ./problem60.pl  
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
#      CREATED: 08/27/2011 02:30:08 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;


my @primes = ();
my %primes = ();
my $lim = 2_000_000;
my @nums = ();
foreach(2..$lim) {
	$nums[$_-2] = 0;
}
foreach(2..$lim) {
	if ($nums[$_-2]==0) {
		push @primes, $_ if ($_<5000);
		$primes{$_} = 1;
		my $val = 2*$_;
		while($val <= $lim) {
			++$nums[$val-2];
			$val+=$_;
		}
	}
}
delete $primes{2};
shift @primes; # get rid of 2;

my $num = 5;
foreach(0..$#primes-$num+1) {
	my $a1 = $primes[$_];
	my $a1_n = $_;
	foreach($a1_n+1..$#primes-$num+2) {
		my $a2 = $primes[$_];
		my $a2_n = $_;
		foreach($a2_n+1..$#primes-$num+3) {
			my $a3 = $primes[$_];
			my $a3_n = $_;
			foreach($a3_n+1..$#primes-$num+4) {
				my $a4 = $primes[$_];
				my $a4_n = $_;
				foreach($a4+1..$#primes-$num+5) {
					my $a5 = $primes[$_];
					my $a5_n = $_;
					my $works = 1;
					foreach(1..5) {
						my $n = $_;
						foreach(1..5) {
							next if ($_ == $n);
							my $x = eval("\$a$n.\$a$_");
							$works = 0 unless ($primes{$x});
						}
					}
					if ($works) {
						print "$a1, $a2, $a3, $a4, $a5";
						exit;
					}
				}
			}
			
		}
	}
}
