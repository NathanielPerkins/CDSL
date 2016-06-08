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
//#include "RingBuffer.h"


int testLL(void);

int main (void) {
//	testLL();
	struct node* head = NULL;
	head = malloc(sizeof(struct node));
	float test = 5.5;
	head->data = &test;
	printf("%f",*(float*)head->data);
//	void* point;
//	float k = 5.5;
//	int d = 6;
//	point = d;
//	point = k;
//	printf("%d", point);
	return 1;
}

int testLL(void) {
	struct node* head = NULL;
	head = malloc(sizeof(struct node));
	head->data = 2;
	printf("data = %d\n",(int)head->data);
	int i;
	if (head == NULL){
		return 1;
	}
	head->next = NULL;
	head->data = 1;
	for (i=2;i<6;i++){
		float k = i/3;
		push(head,&k);
	}
	print_list(head);
//	printf("ABOUT TO POP\n");
//	pop(head);
//	printf("POPPED\n");
//	print_list(head);
	pop_start(&head);
	push_start(&head, 20);
	print_list(head);
	delete_list(&head);
	float value = 7.5;
	printf("value = %f\n",value);
//	if(find_value(head,value)==0){
//		printf("Is in the List\n");
//	}
//	else if (find_value(head,value)==1){
//		printf("List does not exist\n");
//	}
//	else if (find_value(head,value)==2){
//		printf("Is not in the List\n");
//	}
//	print_list(head);

	return EXIT_SUCCESS;
}
