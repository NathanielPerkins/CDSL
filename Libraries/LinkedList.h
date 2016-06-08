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
#include <stdint.h>

//typedef int data_t;

struct node {
	void *data;
	struct node* next;
};

int find_value(struct node* head, void* value);
struct node sll_init(void* value);
void print_list(struct node* head);
void push(struct node* head, void* data);
void push_start(struct node** head, void* data);
void* pop(struct node* head);
void* pop_start(struct node** head);
void delete_list(struct node** head);

#endif /* LINKEDLIST_H_ */
