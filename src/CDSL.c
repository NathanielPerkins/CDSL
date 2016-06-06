/*
 ============================================================================
 Name        : CDSL.c
 Author      : Nathan Perkins
 Version     :
 Copyright   : No Copyright
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


int main(void) {
	struct node* head = NULL;
	head = malloc(sizeof(struct node));
	int i;
	if (head == NULL){
		return 1;
	}
	head->next = NULL;
	head->data = 1;
	for (i=2;i<6;i++){
		push(head,i);
	}
	print_list(head);
	printf("ABOUT TO POP\n");
	pop(head);
	printf("POPPED\n");
	print_list(head);
	delete_list(&head);
	print_list(head);
	return EXIT_SUCCESS;
}


