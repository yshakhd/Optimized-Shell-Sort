#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "shell_array.h"
#include "sequence.h"

long *Array_Load_From_File(char *filename, int *size) {
	FILE * fptr = fopen(filename, "rb");
	if(!fptr){
		return NULL;
	}
	fseek(fptr, 0, SEEK_END);
	int num_bytes = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	int len = num_bytes / sizeof(long);
	*size = len;
	if(!len) {
		fclose(fptr);	
		return NULL;
	}
	long * seq = malloc(num_bytes);
	fread(seq, sizeof(long), len, fptr);

	fclose(fptr);
	return seq;
}

int Array_Save_To_File(char *filename, long *array, int size) {
	FILE * fptr = fopen(filename, "wb");
	if(!fptr) {
		return 0;
	}
	int ctr = fwrite(array, sizeof(long), size, fptr);
	fclose(fptr);
	return ctr;
}

void Array_Shellsort(long *array, int size, long *n_comp) {
	if(!array)
		return;
	int seq_size;
	long comp = 0;
	long * seq = Generate_2p3q_Seq(size, &seq_size);
	for(int i = seq_size - 1; i >= 0; i--) {
		for(int j = seq[i]; j < size; j++) {
			long temp = array[j];
			int k = j;
			while (k >= seq[i] && array[k - seq[i]] > temp) {
				array[k] = array[k - seq[i]];
				k = k - seq[i];
				comp++;
			}
			array[k] = temp;
		}
	}
	*n_comp = comp;
	free(seq);
}
