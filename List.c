#include "List.h"
#include <string.h>

Node* CreateNewNode(const size_t size)
{
	Node* p = (Node*) malloc(sizeof(Node));
	p->value = malloc(size);
	p->next = NULL;

	return p;
}

void DeleteNode(Node* p)
{
	free(p->value);
	free(p);
}

void CreateNewList(List* pList, const size_t size)
{
	pList->size = 0;
	pList->head = NULL;
	pList->tail = NULL;
	pList->nodeSize = size;
}

void DeleteListNodes(List* pList)
{
	Node* p = pList->head; /* start point */
	while(p != NULL)
	{
		Node* next = p->next;
		DeleteNode(p);
		p = next;
	}
}

void DeleteListPtr(List* pList)
{
	free(pList);
}

void AddTail(List* pList, const void* value)
{
	Node* p = CreateNewNode(pList->nodeSize);
	memcpy(p->value, value, pList->nodeSize); /* copy data */

	pList->size++;
	if(pList->head == NULL)
	{
		pList->head = pList->tail = p;
	}
	else
	{
		pList->tail->next = p;
		pList->tail = p;
	}
	
}

void CopyList(const List* list1, List* list2)
{
	CopyListNodes(list1->head, list1->tail, list2);
}

void CopyListNodes(const Node* start, const Node* end, List* list)
{
	Node* p = (Node*) start;
	while(p != end->next)
	{
		AddTail(list, p->value);
		p = p->next;
	}
}
