sub isPrime {
	my ( $num ) = @_;
	return 0 if ($num <= 1);
	foreach(2..sqrt($num)) {
		return 0 if ($num % $_ == 0);
	}
	return 1;
}
