#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem31.pl
#
#        USAGE: ./problem31.pl  
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
#      CREATED: 08/26/2011 01:47:58 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $count = 0;
foreach(0..1) { # 200p
	my $p200 = $_;
	foreach(0..(200-200*$p200)/100) {
		my $p100 = $_;
		foreach(0..(200-200*$p200-100*$p100)/50) {
			my $p50 = $_;
			foreach(0..(200-200*$p200-100*$p100-50*$p50)/20) {
				my $p20 = $_;
				foreach(0..(200-200*$p200-100*$p100-50*$p50-20*$p20)/10) {
					my $p10 = $_;
					foreach(0..(200-200*$p200-100*$p100-50*$p50-20*$p20-10*$p10)/5) {
						my $p5 = $_;
						foreach(0..(200-200*$p200-100*$p100-50*$p50-20*$p20-10*$p10-5*$p5)/2) {
							my $p2 = $_;
							++$count;
							print "200*$p200 + 100*$p100 + 50*$p50 + 20*$p20 + 10*$p10 + 5*$p5 + 2*$p2 = " . (200*$p200 + 100*$p100 + 50*$p50 + 20*$p20 + 10*$p10 + 5*$p5 + 2*$p2);
							print "\n";
						}
					}
				}
			}
		}
	}
}

print "$count\n";
