//Name:  Joshua Rony
//UserID: jrony
//Assignment Name: pa5

#include<stdlib.h>
#include<stdio.h>
#include "List.h"

typedef struct NodeObject{
	
	int data;
	
	struct NodeObject* next; //each of these structs are themselves NodeObjects, and so they have their own struct NodeObject "next", "previous", and "data" attribiutes.
	
	struct NodeObject* previous;

}NodeObject;

typedef NodeObject* Node; 

Node getNewNode(int num){
	
	Node temp = malloc(sizeof(NodeObject));
	
	temp->data = num;
	
	temp->next = NULL;
	
	temp->previous = NULL;
	
	return(temp);
}

typedef struct ListObject{
	
	Node head;
	
	Node tail;
	
	Node cursor;
	
	int length;
	
	int index;

	
} ListObject;



//Constructors-Destructors----------------------------------------------------------------------------------------------------------------------------------

void freeNode(Node *pN){ //Looked at Prof. Tantalo's handouts for this function.  New addition from previous PA2 version of List.  Also had some help writing it.  WORKS SO WELL
	
	if(pN != NULL && *pN != NULL){
		
		free(*pN);
		
		*pN = NULL;
	}
}


List newList(void){
	
	List L;
	
	L = malloc(sizeof(*L));
	L->head = NULL;
	L->tail = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;
	
		
	return(L);
}

void freeList(List *pL){
	
 if(pL != NULL && *pL != NULL){
 
	
 	Node temp = (*pL)->head;
	
	for(int x = 0; x < length((*pL)); x++){
		
		Node temp2 = temp;
		
		temp = temp->next;
		
		freeNode(&temp2);
	}
	
	free(*pL);
	
	*pL = NULL;
	
	}
	
}

//Access functions---------------------------------------------------------------------------------------------------------------------------

int length(List L){
	
	return(L->length);
	
}

int index(List L){
	
	return(L->index);
	
}


int front(List L){
	
	if(L->length < 1){
		
		printf("List module front() function cannot retrieve data element from node in empty List.\n");
		
		exit(1);
	}
	
	else{
	
		return(L->head->data);
		
	}
}

int back(List L){
	
	if(L->length < 1){
		
		printf("List module back() function cannot retrieve data element from node in empty List.\n");
		
		exit(1);
	}
	
	else{
	
	
		return(L->tail->data);
	
	}
}

int get(List L){
	
	if(L->length < 1){
		
		printf("List module get() function cannot retrieve data element from empty List.\n");
		
		exit(1);
	}
	
	if(L->index < 0){
		
		printf("List module get() function cannot retrieve data element from undefined node.\n");
		
		exit(1);
	}  
	
	
	else if(L->cursor != NULL && L->index > -1){
	
		return(L->cursor->data);
		
	}
	
	return(1);
}

int equals(List A, List B){
	
	if(A->length == 0 && B->length == 0){
		
		return(1);
	}
	
	if(A->length != B->length){
		
		return(0);
	}
	
	else{
		
		Node temp = A->head;
		
		Node temp2 = B->head;
		
		for(int x =0; x < A->length; x++){
			
			if(temp->data != temp2->data){
				
				return(0);
			}
			
			temp = temp->next;
			
			temp2 = temp2->next;
		}
	
		
	}
	
	return(1);
}


//Manipulation procedures-------------------------------------------------------------------------------------------------------------------------

void clear(List L){
	
	if(L->length > 0){
		
		if(L->length == 1){
			
			L->head = NULL;
			
			L->tail = NULL;
			
			L->length = 0;
			
			L->cursor = NULL;
			
			L->index = -1;
		}
		
		else{
			
			Node temp = L->head;
			
			for(int x = 0; x < L->length; x++){
				
				Node temp2 = temp;
				
				temp = temp->next;
				
				free(temp2);	
			}
			
			free(temp);
			
			L->head = NULL;
			
			L->tail = NULL;
			
			L->index = -1;
			
			L->length = 0;
			
			L->cursor = NULL;
	
		}
	
	}
}

void moveFront(List L){
	
	if(L->length > 0){
		
		L->cursor = L->head;
		
		L->index = 0;
	}
}

void moveBack(List L){
	
	if(L->length > 0){
		
		L->cursor = L->tail;
		
		L->index = L->length - 1;
	}
}

void movePrev(List L){
	
	if(L->index == 0){
		
		L->cursor = NULL;
		
		L->index = -1;	
			
	}
		
	else if(L->cursor != NULL && L->index > 0){
		
		L->cursor = L->cursor->previous;
		
		L->index = L->index - 1;
	}
	
}

void moveNext(List L){
	
	if(L->cursor != NULL && L->index == L->length - 1){
		
		L->cursor = NULL;
		
		L->index = -1;
	}
	
	else if(L->cursor != NULL && L->index < L->length - 1){
		
		L->cursor = L->cursor->next;
		
		L->index = L->index + 1;
	}
}

void prepend(List L, int num){
	
	if(L == NULL){
		
		printf("List module prepend() function cannot prepend node to undefined List.\n");
		
		exit(1);
	}
	
	Node nuNode = getNewNode(num);
	
	if(L->length == 0){
		
		L->head = nuNode;
		
		L->tail = nuNode;
		
		L->length = 1;
		
	}

	
	else{
		
		if(L->cursor != NULL){
			
			L->index = L->index + 1;
		}
		
		L->head->previous = nuNode;
		
		nuNode->next = L->head;
		
		L->head = nuNode;
		
		L->length = L->length + 1;
	}
	
}

void append(List L, int num){
	
	if(L == NULL){
		
		printf("List module append() function cannot append node to undefined List.\n");
		
		exit(1);
	}
	
	Node nuNode = getNewNode(num);
	
	if(L->length == 0){
	
		L->head = nuNode;
	
	    L->tail = nuNode;
	
		L->length = 1;
	
	}
	
	
	
	
	else{
	
		L->tail->next = nuNode;
	
		nuNode->previous = L->tail;
	
		L->tail = nuNode;
	
		L->length = L->length + 1;		
	}
		
}

void insertBefore(List L, int data){
	
	if(L->length <= 0){
		
		printf("List module insertBefore() function cannot insert element in empty List.\n");
		
		exit(1);
	}
	
	if(L->index < 0){
		
		printf("List module insertBefore() function cannot insert element before undefined node.\n");
		
		exit(1);
	}
	
	if(L->index == 0){
		
		prepend(L, data);

	}
	
	else{
	
		
		Node nuNode = getNewNode(data);
			
		L->cursor->previous->next = nuNode;
		
		nuNode->previous = L->cursor->previous;
		
		nuNode->next = L->cursor;
		
		L->cursor->previous = nuNode;
		
		L->length = L->length + 1;
		
		L->index = L->index + 1;
		
	}
}

void insertAfter(List L, int data){
	
	if(L->length <= 0){
		
		printf("List module insertAfter() function cannot insert element in empty List.\n");
		
		exit(1);
	}
	
	if(L->index < 0){
		
		printf("List module insertAfter() function cannot insert element after undefined node.\n");
		
		exit(1);
		
	}
	
	if(L->index == L->length - 1){
		
		append(L, data);
	}
	
	
	
	else{
		
		Node nuNode = getNewNode(data);
		
		L->cursor->next->previous = nuNode;
		
		nuNode->next = L->cursor->next;
		
		nuNode->previous = L->cursor;
		
		L->cursor->next = nuNode;
		
		L->length = L->length + 1;
	}
	
}

void deleteFront(List L){
	
	if(L->length <= 0){
		
		printf("List module deleteFront() function cannot delete front element from empty List.\n");
		
		exit(1);
	}
	
	else if(L->length == 1){
		
		if(L->index == 0){
			
			L->cursor = NULL;
			
			L->index = -1;
		}
		
		L->length = 0;
		
		freeNode(&L->head);
	}
	
	else{
		
		if(L->cursor != NULL && L->cursor == L->head){
			
			L->cursor = NULL;
			
			L->index = -1;
		}
		
		if(L->cursor != NULL && L->cursor != L->head){
			
			L->index = L->index - 1;
		}
		
		Node temp = L->head;
		
		L->head = L->head->next;
		
		L->head->previous = NULL;
		
		freeNode(&temp);
		
		L->length = L->length - 1;
	
		
	}
	
}

void deleteBack(List L){
	
	if(L->length < 1){
		
		printf("List module deleteBack() function cannot delete back element from empty List.\n");
		
		exit(1);
	}
	
	else if(L->length == 1){
		
		if(L->cursor == L->tail || L->cursor == L->head){
			
			L->cursor = NULL;
			
			L->index = -1;
		}
		
		
		
		freeNode(&L->head);
	
		L->length = 0;
	}
	
	else if(L->length > 1){
		
		if(L->cursor == L->tail){
			
			L->cursor = NULL;
			
			L->index = -1;
		}
		
		Node temp = L->tail;
		
		L->tail = L->tail->previous;
		
		L->tail->next = NULL;
		
		freeNode(&temp);
		
		L->length = L->length - 1;
	
	}
		
}

void delete(List L){
	
	if(L->length == 0){
		
		printf("List module delete() function cannot delete node from empty List.");
		
		exit(1);
	}

	
	if(L->index == 0 && 0 != L->length - 1){//condition 1:  the cursor is at the head of the list, and the list has more than one element in it.
		
		
		Node temp = L->head;
		
		L->head = L->head->next;
		
		L->head->previous = NULL;
		
		freeNode(&temp);
		
		L->length = L->length - 1;
		
		L->cursor = NULL;
		
		L->index = -1;
	}
	
	else if(L->index == L->length - 1 && L->length != 1){ //condition 2: the cursor is at the end of the list, and the list has more than one element in it.
		
		Node temp = L->tail;
		
		L->tail = L->tail->previous;
		
		L->tail->next = NULL;
		
		freeNode(&temp);
		
		L->length = L->length - 1;
		
		L->cursor = NULL;
		
		L->index = -1;
	}
	
	else if(L->index != 0 && L->index != L->length - 1){//condition 3:  the cursor is somewhere in the interior of the list.
		
		Node temp2 = L->cursor;
		
		L->cursor->next->previous = L->cursor->previous;
		
		L->cursor->previous->next = L->cursor->next;
		
		L->cursor = NULL;
		
		freeNode(&temp2);
		
		L->index = -1;
		
		L->length = L->length - 1;
	}
	
	else if(L->length == 1){//condition 4:  the list only has one element in it.
		
		clear(L);
	}
	
}

void Print(List L){
	
	if(length(L) == 0){
		
		printf("Error.  Cannot print contents of empty List.\n");
		
		return;
	}
	
	Node temp = L->head;
	
	for(int x = 0; x < L->length; x++){
		
		printf("%d%s", temp->data, " ");
		
		temp = temp->next;
	}
	
}

//Other operations------------------------------------------------------------------------------------------------------------------------

void printList(FILE* out, List L){
	
	if(L->head == NULL && L->tail == NULL){
		
		printf("List module printList function cannot print contents of empty List.\n");
		
		exit(1);
	}
	
	Node temp = L->head;
	
	for(int x = 0; x < L->length; x++){
		
		fprintf(out, "%d%s", temp->data, " ");
		
		temp = temp->next;
	}
	
	freeNode(&temp);
	
}

List copyList(List L){
	
	List copyList = newList();
	
	if(L->length == 0){
		
		return(copyList);
	}
	
	else{
		
		Node temp = L->head;
		
		for(int x = 0; x < L->length; x++){
			
			append(copyList, temp->data);
			
			temp = temp->next;
		}
		
	}
	
	
	
	return(copyList);
	
}

