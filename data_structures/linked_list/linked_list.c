#include <stdio.h>
#include <stdlib.h>

#define logger(M, ...) printf("[INFO] (%s:%d) M \n", __FILE__, __LINE__, ##__VA_ARGS__)

typedef struct node {
  void *data;
  struct Node *next, *prev;
} Node;

typedef struct linkedlist {
  Node *head, *tail;
  size_t size;
} LinkedList;

/*
 * constructor for the node
 */
Node* constructNode(void *data) {
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

/*
 * constructor for the LinkedList
 */
LinkedList* constructList() {
  LinkedList *node = malloc(sizeof(LinkedList));
  node->head = NULL;
  node->tail = NULL;
  node->size = 0;
  return node;
}

/*
 * insert a Node at the front of the LinkedList 
 */
void insert(LinkedList *list, void *data) {
  Node *node = constructNode(data);

  if (list->size == 0) {
    list->head = node;
    list->head->next = NULL;
    list->head->prev = NULL;
    list->tail = list->head;
  } else {
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
  }

  list->size++;
}

void show_data(void *data) {
  int val = *(int*)(data);
  printf("data: %d", val);
}

int is_data_equal(void *data1, void *data2) {
  int val1 = *(int*)(data1);
  int val2 = *(int*)(data2);
  return val1 == val2;
}

void show(LinkedList *list) {
  printf("%c", '{');

  Node *temp = list->head;
  while (temp != NULL) {
    // making int value from data
    show_data(temp->data);
    if (temp->next != NULL) printf("%c", ',');
    temp = temp->next;
  }

  printf(" }\n");
}

int remove(LinkedList *list, void *data) {
	Node *temp = list->head;
	while (temp != NULL)
	{
		if (is_data_equal(temp->data, data))
		{
			if (list->size == 1)
				clear(list);
			else if (temp->prev == NULL)
				removeFirst(list);
			else if (temp->next == NULL)
				removeLast(list);
			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				list->size--;
			}
			
			return 0;
		}
		temp = temp->next;
	}

	return 1;
}

void removeFirst(LinkedList *list) {
	if (list->size > 0)
	{
		if (list->size == 1)
			clear(list);
		else
		{
			list->head = list->head->next;
			list->head->prev = NULL;
			list->size--;
		}
	}
}

void removeLast(LinkedList *list) {
	if (list->size > 0)
	{
		if (list->size == 1)
			clear(list);
		else
		{
			list->tail = list->tail->prev;
			list->tail->next = NULL;
			list->size--;
		}
	}
}

int main() {

  int a = 5;
  int b = 7;
  LinkedList *list = constructList();
  insert(list, &a);
  insert(list, &b);
  printf("size: %ld", list->size);
  printf("data equal: %d", is_data_equal(&a, &b));
  show(list);

  return 0;
}
