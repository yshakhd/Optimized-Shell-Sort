#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"

void delete(Node** head);

int main(int argc, char ** argv) {
	if(argc != 4)
		return EXIT_FAILURE;
	int size;
	long comp = 0;

	if(argv[1][1] == 'a') {
		long *array = Array_Load_From_File(argv[2], &size);
		Array_Shellsort(array, size, &comp);
		size = Array_Save_To_File(argv[3], array, size);
		printf("%ld\n", comp);
		if(!array)
			return EXIT_FAILURE;
		free(array);
	}
	else if(argv[1][1] == 'l') {
		Node *list = List_Load_From_File(argv[2]);
		Node *sorted = List_Shellsort(list, &comp);
		size = List_Save_To_File(argv[3], sorted);
		printf("%ld\n", comp);
		if(!list)
			return EXIT_FAILURE;
		delete(&sorted);
	}
	else {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void delete(Node** head) {  
  Node* curr =  *head;
  Node* curr_n;
  while (curr) {
    curr_n = curr -> next;
    free(curr);
    curr = curr_n;
  }
  *head = NULL;
}
