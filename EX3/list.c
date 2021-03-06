#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "list.h"

typedef struct node_ {
	struct node_* next;
	PElement element;
} Node,*PNode;

typedef struct List_ {
	PNode	head;
	PNode	iterator;
	PNode	current;
	int		elementsNum;
	// Functions:
	clone	clone_fun;
	destroy	destroy_fun;
	compare	compare_fun;
	print	print_fun;
} LIST;

PList ListCreate(clone clFun, destroy deFun, compare coFun, print prFun) {
	PList list = (PList)malloc(sizeof(LIST));
	if (list == NULL) return NULL;
	list->head = NULL;
	list->current = list->head;
	list->iterator = list->head;
	list->elementsNum = 0;
	list->clone_fun = clFun;
	list->destroy_fun = deFun;
	list->compare_fun = coFun;
	list->print_fun = prFun;
	return list;
};	// End of ListCreate.

Result	ListAdd(PList list, PElement old_element) {
	// Check Input:
	if ((list == NULL) || (old_element == NULL)) return FAIL;
	// Create new node:
	PNode	new_node = (PNode)malloc(sizeof(Node));
	if (new_node == NULL) return FAIL;
	// Make a clone of the element:
	new_node->element = list->clone_fun(old_element);
	if (new_node->element == NULL) return FAIL;
	new_node->next = NULL;

	// Enter node to list:
	if (list->elementsNum == 0) {
		list-> head = new_node;
		list->elementsNum++;
		return SUCCESS;
	};

	list->current = list->head;
	while (list->current->next != NULL) {
		list->current = list->current->next;
	};
	list->current->next = new_node;
	list->elementsNum++;
	return SUCCESS;

};	// End of ListAdd


Result	ListRemove(PList list, PElement element) {
	// Check Input:
	if ((list == NULL) || (element == NULL) || (list->head == NULL)) return FAIL;
	list->current = list->head;

	// Check if the element is the first one:
	if (TRUE == list->compare_fun(list->current->element, element)) {
		if (list->iterator == list->current) { list->iterator = list->iterator->next; };
		list->destroy_fun(list->current->element);
		list->head = list->current->next;
		free(list->current);
		list->elementsNum--;
		return SUCCESS;
	};
	list->current = list->current->next;
	PNode prev_node = list->head;
	while (list->current != NULL) {
		if (TRUE == list->compare_fun(list->current->element, element)) {
			if (list->iterator == list->current) { list->iterator = list->iterator->next; }; 
			list->destroy_fun(list->current->element);
			prev_node->next = list->current->next;
			free(list->current);
			list->elementsNum--;
			return SUCCESS;
		};
		prev_node = list->current;
		list->current = list->current->next;
	};
	return FAIL;
};	// End of ListRemove

void ListDestroy(PList list) {
	if (list == NULL) return;
	list->current = list->head;
	while (list->current != NULL) {
		list->destroy_fun(list->current->element);
		list->head = list->current->next;
		free(list->current);
		list->current = list->head;
	};
	free(list);
};	// End of ListDestroy

PElement	ListGetFirst(PList list) {
	if (list == NULL) return NULL;
	list->iterator = list->head;
	if (list->head == NULL) return NULL; // incase List is empty
	return list->head->element;
};	// End of ListGetFirst

PElement	ListGetNext(PList list) {
	if (list == NULL) return NULL;
	if (list->iterator->next == NULL) return NULL;
	list->iterator = list->iterator->next;
	return list->iterator->element;
};	// End of ListGetNext

BOOL		ListCompare(PList list_a, PList list_b) {
	if ((list_a == NULL) || (list_b == NULL)) return FALSE;
	if (list_a->elementsNum != list_b->elementsNum) return FALSE;
	if ((list_a->head == NULL) && (list_b->head == NULL)) return TRUE; // Both have 0 elements.
	list_a->current = list_a->head;
	list_b->current = list_b->head;
	while (list_a->current != NULL) {
		if (FALSE == list_a->compare_fun(list_a->current->element, list_b->current->element)) return FALSE;
		list_a->current = list_a->current->next;
		list_b->current = list_b->current->next;
	};
	return TRUE;	// Every element is equal.

};	// End of ListCompare

void		ListPrint(PList list) {
	if (list == NULL) return;
	list->current = list->head;
	while (list->current != NULL) {
		list->print_fun(list->current->element);
		list->current = list->current->next;
	}
	printf("\n");
};	// End of ListPrint

int 		ListNumElements(PList list){
	//checking input

	if (list == NULL){
		return 0;
	}
	else{
		return list->elementsNum;
	}
}; // End Of ListNumElements

BOOL		ListIsEmpty(PList list){
	if (list == NULL || list->head == NULL) return TRUE; // either list pointer is NULL or list is empty
	return FALSE; // list not empty
}; // End Of ListIsEmpty
