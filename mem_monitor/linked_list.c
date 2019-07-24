/* 
 * This file is part of the Navi Singh's experiments 
 * (https://github.com/xxxx or http://xxx.github.io).
 *
 * Copyright (c) 2019 Navjot Singh.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Navjot Singh
 * Email: navisinghnz9@gmail.com
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"


//
// NOTE:
// The linked list implementation was taken from
// https://gist.github.com/KevinTyrrell/9f4d13107b32d2ad0421a7881fcd1199
// and customized as per needs of this project
//

static struct Node {
	void *data;
	struct Node *next, *prev;
};

struct LinkedList {
	struct Node *head, *tail;
	size_t _size;
};

// Constructor for the Node.
static struct Node* constructNode(void *data) {
	struct Node *temp = malloc(sizeof(struct Node));
	temp->data = data;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

// Constructor for the LinkedList.
struct LinkedList* constructList() {
	struct LinkedList *temp = malloc(sizeof(struct LinkedList));
	temp->head = NULL;
	temp->tail = NULL;
	temp->_size = 0;
	return temp;
}

// Locates a Node within the LinkedList based on the index.
static struct Node* find(struct LinkedList *list, unsigned int index) {
	if (index > list->_size)
		fprintf(stderr, "%s%d%s%d%c\n",
			"Error: Index Out of Bounds. Index was '",
			index, "\' but size is ", list->_size, '.');
	else if (list->_size > 0)
		if (index == 0)
			return list->head;
		else if (index == list->_size - 1)
			return list->tail;
		else {
			struct Node *temp;

			if ((double)index / list->_size > 0.5) {
				// Seek from the tail.
				temp = list->tail;
				for (unsigned int i = list->_size - 1; i > index; i--)
					temp = temp->prev;
			} else {
				// Seek from the head.
				temp = list->head;
				for (unsigned int i = 0; i < index; i++)
					temp = temp->next;
			}

			return temp;
		}

	return NULL;
}

// Inserts a Node at the front of the LinkedList.
void add(struct LinkedList *list, void *data) {
	struct Node *inserted = constructNode(data);

	if (list->_size == 0) {
		list->head = inserted;
		list->head->next = NULL;
		list->head->prev = NULL;
		list->tail = list->head;
	} else {
		inserted->next = list->head;
		list->head->prev = inserted;
		list->head = inserted;
	}

	list->_size++;
}

// Inserts a Node at a given index inside the LinkedList.
int addAt(struct LinkedList *list, unsigned int index, void *data) {
	if (index > list->_size) {
		fprintf(stderr, "%s%d%s%d%c\n",
			"Error: Index Out of Bounds. Index was '",
			index, "\' but size is ", list->_size, '.');
		return 1;
	} else if (index == 0)
		add(list, data);
	else if (index == list->_size)
		addLast(list, data);
	else {
		struct Node *temp = find(list, index),
			*added = constructNode(data);
		added->prev = temp->prev;
		added->next = temp;
		temp->prev->next = added;
		temp->prev = added;
		list->_size++;
	}

	return 0;
}

// Inserts a Node at the end of the LinkedList.
// O(1) complexity.
void addLast(struct LinkedList *list, void *data)
{
	if (list->_size == 0){
		add(list, data);
  } else {
		struct Node *added = constructNode(data);
		added->prev = list->tail;
		list->tail->next = added;
		list->tail = added;
		list->_size++;
	}
}

// Clear the LinkedList of Nodes.
// O(1) complexity.
void clear(struct LinkedList *list) {
	list->head = NULL;
	list->tail = NULL;
	list->_size = 0;
}

// Remove's a Node at a given index.
int removeAt(struct LinkedList *list, unsigned int index) {
	if (index >= list->_size) {
		fprintf(stderr, "%s%d%s%d%c\n",
			"Error: Index Out of Bounds. Index was '",
			index, "\' but size is ", list->_size, '.');
		return 1;
	}
	else if (index == 0)
		removeFirst(list);
	else if (index == list->_size - 1)
		removeLast(list);
	else
	{
		struct Node *temp = find(list, index);
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		list->_size--;
	}

	return 0;
}

// Remove's the first Node whose data matches the parameter, if it exists.
int remove(struct LinkedList *list, void *data) {
	struct Node *temp = list->head;
	while (temp != NULL)
	{
		if (temp->data == data)
		{
			if (list->_size == 1)
				clear(list);
			else if (temp->prev == NULL)
				removeFirst(list);
			else if (temp->next == NULL)
				removeLast(list);
			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				list->_size--;
			}
			
			return 0;
		}
		temp = temp->next;
	}

	return 1;
}

// Remove's the first Node in the LinkedList.
// O(1) complexity.
void removeFirst(struct LinkedList *list)
{
	if (list->_size > 0)
	{
		if (list->_size == 1)
			clear(list);
		else
		{
			list->head = list->head->next;
			list->head->prev = NULL;
			list->_size--;
		}
	}
}

// Remove's the last Node in the LinkedList.
// O(1) complexity.
void removeLast(struct LinkedList *list) {
	if (list->_size > 0)
	{
		if (list->_size == 1)
			clear(list);
		else
		{
			list->tail = list->tail->prev;
			list->tail->next = NULL;
			list->_size--;
		}
	}
}

// Prints out the LinkedList to the terminal window.
// O(n) complexity.
void print(struct LinkedList *list) {
	printf("%c", '{');

	struct Node *temp = list->head;
	while (temp != NULL)
	{
		printf(" %s", temp->data);
		if (temp->next != NULL)
			printf("%c", ',');
		temp = temp->next;
	}

	printf(" }\n");
}

// Copies a given LinkedList and returns the cloned version.
// O(n) complexity.
struct LinkedList* clone(struct LinkedList *list) {
	if (list == NULL)
		return NULL;

	struct LinkedList *copy = constructList();
	struct Node *head = list->head;

	while (head != NULL) {
		addLast(copy, head->data);
		head = head->next;
	}

	return copy;
}
