#
#===============================================================================
#
#         FILE: PermUtils.pm
#
#  DESCRIPTION: 
#
#        FILES: ---
#         BUGS: ---
#        NOTES: ---
#       AUTHOR: Brian Tu (), 
#      COMPANY: 
#      VERSION: 1.0
#      CREATED: 08/21/2011 06:35:10 PM
#     REVISION: ---
#===============================================================================

package PermUtils;

use strict;
use warnings;


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
