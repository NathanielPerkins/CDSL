/*
 * LinkedList.h
 *
 *  Created on: 06/06/2016
 *      Author: nathanjp
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

void print_list(struct node* head);
void push(struct node* head, int data);
int pop(struct node* head);
int delete_list(struct node** head);
#endif /* LINKEDLIST_H_ */
