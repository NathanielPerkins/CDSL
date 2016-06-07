/*
 * LinkedList.c
 *
 *  Created on: 06/06/2016
 *      Author: nathanjp
 */
#include "LinkedList.h"

void print_list(struct node* head) {
    struct node* current = head;
    if (head == NULL){
    	printf("List Empty\n");
    }
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void push(struct node* head, int data){
	struct node* current = head;
	while (current->next != NULL){
		current = current->next;
	}
	current->next = malloc(sizeof(struct node));
	current->next->data = data;
	current->next->next = NULL;
}

void push_start(struct node** head, int data){
	struct node* oldHead = *head;
	struct node* newHead = malloc(sizeof(struct node));
	newHead->data = data;
	newHead->next = oldHead;
	*head = newHead;
}

int find_value(struct node* head,int value){
	if(head == NULL){
		return 1; //return 1 = no linked list
	}
	struct node* current = head;
	while(current != NULL){
		if(current->data == value){
			return 0; // exit success, it's in the list
		}
		current = current->next;
	}
	return 2; //return 2 = not in array
}

int pop(struct node* head){
	if (head == NULL) return -1;
	int data;
	struct node* current = head;
	struct node* prev = NULL;
	if(head->next == NULL){
		data = head->data;
		free(head);
		return data;
	}
	while(current->next != NULL){
		prev = current;
		current = current->next;
	}
	prev->next = NULL;
	data = current->data;
	free(current);
	return data;
}

int pop_start(struct node** head){
	if (*head == NULL){
		return -1;
	}
	struct node* next;
	next = (*head)->next;
	int data;
	data = (*head)->data;
	*head = next;
	return data;
}

void delete_list(struct node** head){
	struct node *next, *deleteMe;
	deleteMe = *head;
	while (deleteMe) {
		next = deleteMe->next;
		free(deleteMe);
		deleteMe = next;
	}
	*head = NULL;
}


