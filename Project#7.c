
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct listNode {
	int value;
	struct listNode* next;
} Node;

typedef struct list {
	Node* head;
} List;

typedef struct arrStack {
	int* stack;
	int size;
	int top;
} ArrStack;

typedef struct listStack {
	Node* head;
} ListStack;


typedef struct listQueue {
	Node* head;
} ListQueue;

// Linear version
void removeEveryOther(List* l) {
	if (l == NULL || l->head == NULL) {
		return;
	}
	Node* a = l->head;
	Node* temp;
	while (a != NULL && a->next != NULL) {
		temp = a->next;
		a->next = temp->next;
		free(temp);
		a = a->next;
	}
}

// Recursive Version
void removeAlternate(Node* head) {
	if (head == NULL)
		return;
	Node* next = head->next;
	if (next == NULL) 
		return;
	head->next = next->next;
	free(next);
	removeAlternate(head->next);
}


void ArrStackPush(ArrStack* theStack, int value) {
	if (theStack->top >= (theStack->size - 1)) {
		printf("The stack is full.  New value not added.\n");
	}
	else {
		theStack->top++;
		theStack->stack[theStack->top] = value;
	}
}

int ArrStackPop(ArrStack* theStack) {
	int returnVal = -999;

	if (theStack->top <= -1) {
		printf("No entries on the stack.\n");
	}
	else
	{
		returnVal = theStack->stack[theStack->top];
		theStack->top--;
	}
	return returnVal;
}

void ArrStackPrint(ArrStack* theStack) {

	for (int i = 0; i <= theStack->top; i++)
		printf("%d  ", theStack->stack[i]);

	printf("\n");
}

// Question 3) Implement a stack (stack structure, push function, pop function) using a list.

void ListStackPush(ListStack* theStack, int value) {

	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->value = value;
	newNode->next = NULL;

	if (theStack->head == NULL) {
		theStack->head = newNode;
	}
	else {
		newNode->next = theStack->head;
		theStack->head = newNode;
	}
}

int ListStackPop(ListStack* theStack) {
	int returnVal = -999;
	Node* tmp;

	if (theStack->head == NULL) {
		printf("No entries on the stack.\n");
	}
	else
	{
		returnVal = theStack->head->value;
		tmp = theStack->head;
		theStack->head = tmp->next;
		free(tmp);
	}
	return returnVal;
}

void ListStackPrint(ListStack* theStack) {

	Node* currNode;

	currNode = theStack->head;

	while (currNode != NULL) {
		printf("%d  ", currNode->value);
		currNode = currNode->next;
	}

	printf("\n");
}

// Question 4) Implement a queue (queue structure, enqueue function, dequeue function) using a list.

void ListEnqueue(ListQueue* theQueue, int value) {

	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->value = value;
	newNode->next = NULL;

	Node* tail;

	// If there is no queue, just add the data.
	if (theQueue->head == NULL) {
		theQueue->head = newNode;
	}
	// Otherwise, add node to the tail of the queue.
	else {
		// First need to find the last node.
		tail = theQueue->head;

		while (tail->next != NULL)
			tail = tail->next;

		// Found the tail, so add the new node.
		tail->next = newNode;
	}
}

int ListDequeue(ListQueue* theQueue) {
	int returnVal = -999;
	Node* tmp;

	if (theQueue->head == NULL) {
		printf("No entries on the queue.\n");
	}
	else
	{
		returnVal = theQueue->head->value;
		tmp = theQueue->head;
		theQueue->head = tmp->next;
		free(tmp);
	}
	return returnVal;
}

void ListQueuePrint(ListQueue* theQueue) {

	Node* currNode;

	currNode = theQueue->head;

	while (currNode != NULL) {
		printf("%d  ", currNode->value);
		currNode = currNode->next;
	}

	printf("\n");
}

void PrintList(List* l) {
	Node* currNode;

	if (l != NULL) {
		currNode = l->head;

		while (currNode != NULL) {
			printf("%d  ", currNode->value);
			currNode = currNode->next;
		}
		printf("\n");
	}
}


void main() {
	int i;
	List l;
	ArrStack aStack;
	ListStack lStack;
	ListQueue lQueue;
	Node* newNode;
	Node* current;
	newNode = (Node*)malloc(sizeof(Node));
	l.head = newNode;
	current = newNode;
	current->value = 0;

	for (int x = 1; x < 10; x++) {
		newNode = (Node*)malloc(sizeof(Node));
		newNode->value = x;
		newNode->next = NULL;
		current->next = newNode;
		current = newNode;
	}

	printf("List Before: ");
	PrintList(&l);
	removeEveryOther(&l);
	printf("List After: ");
	PrintList(&l);

	aStack.stack = (int*)malloc(sizeof(int) * 10);
	aStack.size = 10;
	aStack.top = -1;
	lStack.head = NULL;
	lQueue.head = NULL;

	for (i = 0; i < aStack.size; i++) {
		ArrStackPush(&aStack, i);
		ListStackPush(&lStack, i);
		ListEnqueue(&lQueue, i);
	}

	printf("Array Stack: ");
	ArrStackPrint(&aStack);
	printf("List Stack: ");
	ListStackPrint(&lStack);
	printf("List Queue: ");
	ListQueuePrint(&lQueue);

	while (aStack.top > -1) {
		printf("Array Stack Pop: %d\n", ArrStackPop(&aStack));
	}

	i = ListStackPop(&lStack);
	while (i > -1) {
		printf("List Stack Pop: %d\n", i);
		i = ListStackPop(&lStack);
	}

	i = ListDequeue(&lQueue);
	while (i > -1) {
		printf("List Queue Dequeue: %d\n", i);
		i = ListDequeue(&lQueue);
	}

	free(aStack.stack);
}