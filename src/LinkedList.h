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
	int data;
	struct node* next;
};

int find_value(struct node* head, int value);
void print_list(struct node* head);
void push(struct node* head, int data);
void push_start(struct node** head, int data);
int pop(struct node* head);
int pop_start(struct node** head);
void delete_list(struct node** head);

#endif /* LINKEDLIST_H_ */
