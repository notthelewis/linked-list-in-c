/*
	C program to build and maniuplate linked-list data structures
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node * next;
} node_t;

/* Function definitions */
void print_list(node_t * head);
void push_to_start(node_t ** head, int val);
void push_to_end(node_t	* head, int val);
int pop_first(node_t ** head);
int pop_last(node_t * head);
int count_list_len(node_t ** head);
int remove_by_index(node_t ** head, int n);

/* Print the contents of the list */
void print_list(node_t * head)
{
	node_t * current = head;
	while (current != NULL) {
		printf("%d\n", current->val);
		current = current->next;
	}
}

/* Add int to end of list */
void push_to_end(node_t * head, int val)
{
	node_t * current = head; 
	while (current-> next != NULL) {
		current = current-> next;
	}

	current->next = (node_t *) malloc(sizeof(node_t));
	current->next->val = val;
	current->next->next = NULL;
}

void push_to_start(node_t ** head, int val) {
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

int pop_first(node_t ** head)
{
	int retval = -1;
	node_t * next_node = NULL;

	if (*head == NULL) {
		return -1;
	}

	next_node = (*head)->next;
	retval = (*head)->val;
	free(*head);
	*head = next_node;

	return retval;
}

int pop_last(node_t * head)
{
	int retval = 0;
	/*If there's only one item, remove it*/
	if (head->next == NULL){
		retval = head->val;
		free(head);
		return retval;
	}

	/* get to the second to last node in the list */
	node_t * current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}

	/*Current points to second to last item of the list, remove current ->next*/
	retval = current->next->val;
	free(current->next);
	current->next = NULL;

	return retval;
}

int count_list_len(node_t ** head)
{
	int i = 0;
	int c = 0;
	node_t * current = *head; 
	while (current != NULL) {
		c++;
		current = current->next;
	}

	return c;
}

int remove_by_index(node_t ** head, int n)
{
	int i = 0;
	int retval = -1;
	node_t * current = *head;
	node_t * temp_node = NULL;

	int list_len = count_list_len(&current);

	if (n > list_len)
		printf("Out of bounds search");

	if (n == 0) {
		return pop_first(&current);
	}

	for (i = 0; i < n-1; i++) {
		if (current->next == NULL) {
			return -1;
		}
		current = current->next;
	}

	temp_node = current->next;
	retval = temp_node->val;
	current->next = temp_node->next;
	free(temp_node);

	return retval;
}

int main()
{
	node_t * head = NULL;
	head = (node_t *) malloc(sizeof(node_t));
	if (head == NULL) {
		return 1;
	}

/* Allocate 3 values to the linked list  */
	head->val = 1;
	head->next = (node_t *) malloc(sizeof(node_t));

	head->next->val = 2;
	head->next->next = (node_t *) malloc(sizeof(node_t));

	head->next->next->val = 3;
	head->next->next->next = NULL;

	printf("Initial... \n");
	print_list(head);

	printf("push to start \n");
	push_to_start(&head, 3);
	print_list(head);

	printf("push to end \n");
	push_to_end(head, 4);
	print_list(head);

	printf("pop first \n");
	pop_first(&head);
	print_list(head);

	printf("pop last \n");
	pop_last(head);
	print_list(head);

	printf("Remove 3rd \n");
	remove_by_index(&head, 2);
	print_list(head);

	free(head);
}
