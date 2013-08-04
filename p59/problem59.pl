#!/usr/bin/perl 
#===============================================================================
#
#         FILE: problem59.pl
#
#        USAGE: ./problem59.pl  
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
#      CREATED: 10/08/2011 08:51:59 PM
#     REVISION: ---
#===============================================================================

use strict;
use warnings;
use integer;

my @enc;
open CIPHER, "cipher1.txt";
while(<CIPHER>) {
	chomp $_;
	push @enc, split ',',$_; 
	print join ' ', @enc;
	print $#enc;
}
close CIPHER;
exit;

my %enc_freq = %{&countFreq(\@enc)};
exit;
printf("%11s%11s","Value","Freq");
print "\n";
my $ptit=0;
foreach(keys(%enc_freq)) {
#	$enc_frkq{$_} = 0 unless($enc_freq{$_});
	if ($ptit) {
		print "\n\n\$_: $_ Value: " . "\n\n";
		$ptit=0;
	}
	if ($enc_freq{$_} == 77) {
		$ptit=1;
	}
	print(ord($_) . " $_, $enc_freq{$_}");
	print "\n";
}

#assumed key != 'zzz'
sub nextKey {
	my $key = $_[0];
	my @letters = split '',$key;
	my @nums = map {ord($_) - 97} @letters;
	$nums[2]++;
	my $carry = $nums[2]/26;
	$nums[2]%=26;
	$nums[1]+=$carry;
	$carry = $nums[1]/26;
	$nums[1]%=26;
	$nums[0]+=$carry;
	@nums = map {$_ + 97} @nums;
	$key = '';
	$key .= chr $_ foreach(@nums);
	return $key;
}

sub countFreq {
	my @vals = @{$_[0]};
	my %freq;
	foreach(@vals){
		$freq{$_}++;
	}
	print join " ", keys %freq;
	return \%freq;
}
