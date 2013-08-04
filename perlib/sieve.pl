# sieve
my @primes;
my $lim = 1_000;
my @nums = ();
foreach(2..$lim) {
	$nums[$_-2] = 0;
}
foreach(2..$lim) {
	if ($nums[$_-2]==0) {
		push @primes, $_;
		my $val = 2*$_;
		while($val <= $lim) {
			++$nums[$val-2];
			$val+=$_;
		}
	}
}
print scalar(@primes) . "\n";
