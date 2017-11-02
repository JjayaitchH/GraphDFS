//Jesus Hernandez
//jherna83
//PA5
//List.c
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj
{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
}NodeObj;

typedef NodeObj* Node;


typedef struct ListObj
{
    Node head;
    Node tail;
    Node cursor;
    int index;
    int length;
}ListObj;

//~~~Constructors~~~

//creates new List
List newList(void)
{
    List L;
    L = malloc(sizeof(ListObj));
    L -> head = NULL;
    L -> tail = NULL;
    L -> cursor = NULL;
    L -> length = 0;
    L -> index = -1;

    return L;
}

//create new node, set everything to NULL or 0
Node newNode(int data)
{
    Node n = malloc(sizeof(NodeObj));
    n -> data = data;
    n -> next = NULL;
    n -> prev = NULL;
    return (n);
}

//~~~End Constructors~~~

//~~~Destructors~~~

//frees individual node
void freeNode(Node* pN)
{
    if(pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

//free the entire list
void freeList(List* pL)
{
    if(pL != NULL && *pL != NULL)
    {
        while(length(*pL) != 0)
        {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;        
    }
}

//~~~End Destructors~~~

//return the length of List
int length(List L)
{
    return L -> length;
}

//return the current index of 
//cursor
int index(List L)
{
    return L-> index;
}

//return front node data
//pre: length() > 0
int front(List L)
{
    if(length(L) > 0)
    {
        return L -> head -> data;
    }
    else
    {
        printf("List Error at front(): the length of the list must be greater than 0\n");
        exit(1);
    }
}

//return back node data
int back(List L)
{
    if(length(L) > 0)
    {
        return L -> tail -> data;
    }
    else
    {
        printf("List Error at back(): the length of the list must be greater than 0\n");
        exit(1);
    }
}

//return data of cursor
//pre:length() > 0 and index() >= 0
int get(List L)
{
    if(length(L) > 0 && index(L) >= 0)
    {
        return L -> cursor -> data;
    }
    else
    {
        printf("List Error at get(): the length must be greater then 0 and the index greater than or equal to 0\n");
        exit(1);
    }
}

//checks to see if both lists
//being compared are the same
int equals(List A, List B)
{
    int eq = 0;
    Node n = NULL;
    Node m = NULL;

    if(A == NULL || B == NULL)
    {
        printf("List Error: calling equals() on NULL referene\n");
        exit(1);
    }
    eq = (A -> length == B -> length);
    
    n = A -> head;
    m = B -> head;

    while(eq != 0 && n != NULL)
    {
        eq = (n -> data == m -> data);
        n = n -> next;
        m = m -> next;
    }
    return eq;
}

//clear the list
void clear(List L)
{
    Node temp = L -> head; //temp will run through the list

    while(temp != NULL)
    {
        Node hold = temp; //hold on to node to free it while temp moves next
        temp = temp -> next;
        freeNode(&hold);
    }
    L -> index = -1;
    L -> length = 0;
    L -> head = NULL;
    L -> tail = NULL;
    L -> cursor = NULL;
    freeNode(&temp);
}

//move cursor to the front
void moveFront(List L)
{
    if(length(L) != 0)
    {
        L -> cursor = L-> head;
        L -> index = 0;
    }
}

//move cursor to the back
void moveBack(List L)
{
    if(length(L) != 0)
    {
        L -> cursor = L -> tail;
        L -> index = length(L) - 1;
    }
}

//move cursor towards front of list
//if cursor is at front, it becomes undefined
//otherwise nothing is done
void movePrev(List L)
{
    if(L -> cursor != NULL && L -> cursor -> prev != NULL)
    {
        L -> cursor = L -> cursor -> prev;
        L -> index--;
    }
    else if(L -> cursor == L -> head)
    {
        L -> cursor = NULL;
        L -> index = -1;
    }
}

//move cursor towards front of list
//if cursor is at front, it becomes undefined
//otherwise nothing is done
void moveNext(List L)
{
    if((L -> cursor != NULL) && (L -> cursor -> next != NULL))
    {
        L -> cursor = L -> cursor -> next;
        L -> index++;
    }
    else if(L -> cursor == L -> tail)
    {
        L -> cursor = NULL;
        L -> index = -1;
    }
}

//add new node to front of list
void prepend(List L, int data)
{
    Node temp = newNode(data);

    if(length(L) == 0)
    {
        L -> head = temp;
        L -> tail = temp;
        L -> length++;
    }
    else
    {
        L -> head -> prev = temp;
        temp -> next = L -> head;
        L -> head = temp;
        L -> length++;

        if(L -> cursor != NULL) //MAYBE
        {
            L -> index++;
        }
    }

}

//add new node to back of list
void append(List L, int data)
{
    Node temp = newNode(data);

    if(length(L) == 0)
    {
        L -> head = temp;
        L -> tail = temp;
        L -> length = 1;
        //printf("works: length: %d\n", L -> length);
    }
    else
    {
        L -> tail -> next = temp;
        temp -> prev = L -> tail;
        L -> tail = temp;
        L -> length++;
        //printf("works: length: %d\n", L -> length);
    }
}

//insert new node befor cursor
void insertBefore(List L, int data)
{
    //if breaks bring malloc back up here

    if(length(L) > 0 && index(L) >= 0)
    {
        //if cursor is head prepend instead
        if(L -> cursor == L -> head)
        {
            prepend(L, data);
            //L -> index++;
        }
        else
        {
            Node temp = newNode(data);
            temp -> prev = L -> cursor -> prev;
            L -> cursor -> prev -> next = temp;
            temp -> next = L -> cursor;
            L -> cursor -> prev = temp;

            L -> index++;
            L -> length++;
        }
    }
    else
    {
        printf("List Error on insertBefore(): the length must be greater than 0 and index greater than or equal to 0\n");
        exit(1);
    }
}

//insert node after cursor
void insertAfter(List L, int data)
{
    //if breaks, bring malloc back up here

    if(length(L) > 0 && index(L) >= 0)
    {
        //if cursor is tail just append
        if(L -> cursor == L -> tail)
        {
            append(L, data);
        }
        else
        {
            Node temp = newNode(data);
            temp -> next = L -> cursor -> next;
            L -> cursor -> next -> prev = temp;
            temp -> prev = L -> cursor;
            L -> cursor -> next = temp;

            L -> length++;
        }
    }
    else if(length(L) < 0)
    {
        printf("List Error at insertAfter(): the length must be greater than 0\n");
        exit(1);
    }
    else if(index(L) < 0)
    {
        printf("List Error at insertAfter(): the index is undefined\n");
        exit(1);
    }
}

//deletes front element
//pre: length > 0
void deleteFront(List L)
{
    if(length(L) == 0)
    {
        printf("List Error at deleteFront(): the length must be greater than 0\n");
        exit(1);
    }
    if(length(L) > 1)
    {
        Node temp = L -> head;
        L -> head = L -> head -> next;
        L -> head -> prev = NULL; //MAYBE

        L -> index--;
        L -> length--;

        freeNode(&temp);
    }
    else
    {
        Node temp = L -> head;
        L -> head = NULL;
        L -> tail = NULL;

        L -> length--;
        freeNode(&temp);
    }
}

//deletes the back element
//pre: length() > 0
void deleteBack(List L)
{
    if(length(L) == 0)
    {
        printf("List Error at deleteBack(): the length must be greater than 0\n");
        exit(1);
    }
    if(length(L) > 1)
    {
        if(L -> cursor == L -> tail)
        {
            L -> index = -1;
            L -> cursor = NULL;
        }

        Node temp = L -> tail;
        L -> tail = L -> tail -> prev;
        
        L -> length--;
        freeNode(&temp);
    } 
    else
    {
        Node temp = L -> tail;
        L -> head = NULL;
        L -> tail = NULL;

        L -> length--;
        freeNode(&temp);
    }
}

//delete element cursor is pointinig to
//make cursor undefined
//pre: length() > 0 and index() > 0
void delete(List L)
{
    if(length(L) > 0 && index(L) >= 0)
    {
        if(L -> cursor == L -> head)
        {
            deleteFront(L);
        }
        else if(L -> cursor == L -> tail)
        {
            deleteBack(L);
        }
        else
        {
            Node temp = L -> cursor;

            L -> cursor -> next -> prev = L -> cursor -> prev;
            L -> cursor -> prev -> next = L -> cursor -> next;
            L -> length--;
            freeNode(&temp);
        }
        L -> cursor = NULL;
        L -> index = -1;
    }
    else
    {
        printf("List Error at delete(): the length must be grater than 0 and index must be greater than or equal to 0 \n");
        exit(1);
    }
}

//coppy list into a new list
List copyList(List L)
{
    List nL = newList();
    Node temp = L -> head;

    while(temp != NULL)
    {
        append(nL, temp -> data);  //call append to create new list
        temp = temp -> next;
    }

    return nL;
}

//prints out the list
void printList(FILE* out, List L)
{
    Node n = NULL;

    if(L == NULL)
    {
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }

    for(n = L -> head; n != NULL; n = n -> next)
    {
        fprintf(out, "%d ", n -> data);
    }
}