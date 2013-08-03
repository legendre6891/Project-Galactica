#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem69.pl
#
#        USAGE: ./problem69.pl  
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
#      CREATED: 08/24/2011 09:42:03 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;

my $num = 2*3*5*7*11*13*17;
print $num; 
print "\n" . &phi($num);
print "\n";
print $num / &phi($num);
exit;
my ($maxN, $maxRatio) = (0, 0);
foreach(2..1_000_000) {
	my $p = &phi($_);
	print "$_\n";
	if ($_/$p > $maxRatio) {
		$maxN = $_;
		$maxRatio = $_/$p;
	}
}
print "Max ratio is $maxRatio, for n = $maxN\n";

sub phi {
	my ( $n ) = @_;
	my $phi = $n;
	my $prime = 2;
	while($n!=1) {
		if ($n % $prime == 0) {
			$phi /= $prime;
			$phi *= $prime - 1;
			$n /= $prime;
		}
		while($n%$prime==0) {
			$n /= $prime;
		}
		++$prime;
	}
	return $phi;
}
