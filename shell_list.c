 #include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "shell_list.h"
#include "sequence.h"

Node *List_Load_From_File(char *filename) {
	// Load file
	FILE * fptr = fopen(filename, "rb");
	if(!fptr) {
		return NULL;
	}
	fseek(fptr, 0, SEEK_END);
	int num_bytes = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	int len = num_bytes / sizeof(long);
	 Node * list_head = NULL;
	 Node * list_tail = NULL;
	
	if(!len) {
		fclose(fptr);
		return NULL;
	}

	//Load each long int
	for(int i = 0; i < len; i++) {
		Node * temp_node = malloc(sizeof(Node));
		fread(&(temp_node -> value), sizeof(long), 1, fptr);
		temp_node -> next = NULL;
		if(!list_tail) {
			list_head = temp_node;
			list_tail = temp_node;
		}
		else {
			list_tail -> next = temp_node;
			list_tail = temp_node;
		}
	}
	fclose(fptr); // close file
	return list_head;
}

int List_Save_To_File(char *filename, Node *List) {
	// Open file
	FILE * fptr = fopen(filename, "wb");
	if(!fptr) {
		return 0;
	}
	long val; // value of node
	int ctr = 0; // size of list
	Node * pointer_node = List;
	while(pointer_node) {
		val = pointer_node -> value;
		fwrite(&val, sizeof(long), 1, fptr);
		pointer_node = pointer_node -> next;
		ctr++;
	}
	fclose(fptr);
	return ctr;
}
 
static Node* getoffset(Node * head, int n)
{
	while(head && n) {
		head = head->next;
		n--;
	}
	return head;
}

Node *List_Shellsort(Node *list, long *n_comp) {
	if(!list) {
		return NULL;
	}
	int size = 0;
	int seq_size;
	Node * pointer_node = list;
	while(pointer_node) {
		pointer_node = pointer_node -> next;
		size++;
	}
	//generate sequence	
	long * seq = Generate_2p3q_Seq(size, &seq_size);
	if(!seq)
		return NULL;
	long k;
	Node* temp;
	Node* leftnode;
	Node* leftprev;
	Node* rightnode;
	Node* rightprev;
	for(int i = seq_size - 1; i > 0; i--) {
		k = seq[i];
		Node* rightprevinit = getoffset(list, k-1);
		Node* rightinit = rightprevinit->next;
		int lastswap = size;
		while(lastswap != k) {
			leftnode = list;
			leftprev = NULL;
			rightnode = rightinit;
			rightprev = rightprevinit;
			int swap = 0;
			int currswaploc = k;			
			for(int j = 0; j < lastswap - k; j++) {
				if((!rightnode) || (!rightprev)){
					break;
				}
				//ctr++;
				(*n_comp)++;
				if(rightnode->value < leftnode->value) {
					swap = 1;
					currswaploc = j + k + 1;
					// if left is not head
					if(leftprev){
						leftprev->next = rightnode;
					}
					rightprev->next = leftnode;
					temp = rightnode->next;
					rightnode->next = leftnode->next;
					leftnode->next = temp;
					// if left is head
					if(!leftprev) {
						list = rightnode;
					}
					temp = rightnode;
					rightnode = leftnode->next;
					leftprev = temp;
					leftnode = leftprev->next;
					rightprev = rightprev->next;
				} else {
					leftnode = leftnode->next;
					rightnode = rightnode->next;
					rightprev = rightprev->next;
					if(leftprev){
						leftprev = leftprev->next;
					} else {
						leftprev = list;
					}
				}
			}
			if(!swap) {
				lastswap = k;
			} else {
				lastswap = currswaploc / k;
			}
		}
	}
	
	// Bubble sort (1-sort)
	
	leftnode = list;
	leftprev = NULL;
	rightnode = leftnode->next;
	while(rightnode){
		(*n_comp)++;
		if(leftnode->value > rightnode->value){
			if(leftprev){
				leftprev->next = rightnode;
			}
			temp = rightnode->next;
			rightnode->next = leftnode;
			leftnode->next = temp;
			
			temp = rightnode;
			rightnode = leftnode;
			leftnode = temp;
			
			if(!leftprev){
				list = leftnode;
			}
		}
		rightnode = rightnode->next;
		leftnode = leftnode->next;
		if(leftprev){
			leftprev = leftprev->next;
		} else {
			leftprev = list;
		}
	}
	
	free(seq);
	return list;
}