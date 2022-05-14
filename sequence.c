#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

long *Generate_2p3q_Seq(int n, int *seq_size) {
	if (n < 1) {
		*seq_size = 0;
		//return NULL;
	}
	long * seq = malloc(sizeof(long) * n);
	if (!seq) {
		*seq_size = 0;
		return NULL;
	}
	int ctr = 1;
	seq[0] = 1;
	int idx2 = 0, idx3 = 0;
	while (seq[ctr-1] < n) {
		long fact2 = seq[idx2] * 2;
		long fact3 = seq[idx3] * 3;
		if (fact2 < fact3) 
			seq[ctr] = fact2;
		else
			seq[ctr] = fact3;
		idx2 += (fact2 <= fact3);
		idx3 += (fact2 >= fact3);
		ctr++;
	}
	*seq_size = ctr - 1;
	return seq;
}
