#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

/*--Node of list--*/
typedef struct Node
{
	void* value;
	struct Node* next;
} Node;


typedef struct List
{
	Node* head;
	Node* tail;
	int size; 			/* List size */
	size_t nodeSize; 	/* Size of value to allocate for node->value */
} List;

/*--The function create new node--*/ 
Node* CreateNewNode(const size_t size);

/*--Deletes Node--*/
void DeleteNode(Node* po_pNode);

/*--Create New List--*/
void CreateNewList(List* po_pList, const size_t nodeSize);

/*--The function delete all nodes from list--*/ 
void DeleteListNodes(List* po_pList);

/*--Free a pointer to list (deallocate)--*/
void DeleteListPtr(List* po_pList);

/*--Adds node to the end of the list--*/
void AddTail(List* pio_pList, const void* pi_pValue);

/*--Copy list from one to other by value--*/
void CopyList(const List* pi_pDestList, List* po_pSrcList);

/*--Copy list nodes by value--*/
void CopyListNodes(const Node* pi_pBeginNode, const Node* pi_pEndNode, List* po_pSrcList);

#endif
