/* Edward Lee
 * List.c: Substantiates the List header
 */
/*Importation of packages, including the List header file*/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

/*Define the ElementObj that the List uses*/
typedef struct ElementObj{
    int value;
    struct ElementObj* prev;
    struct ElementObj* next;
} ElementObj;

typedef ElementObj* Element;

/*Define the List Object*/
typedef struct ListObj{
    Element front;
    Element cursor;
    int numelements;
} ListObj;

/*Constructor for the Element Object*/
Element newElement(int data){
    Element E = malloc(sizeof(ElementObj));
    E->value = data;
    E->next = NULL;
    E->prev = NULL;
    return(E);
}

/*freeElement: Erases an element and the memory attached to it*/
void freeElement(Element* pE){
    if((*pE!=NULL)&&(pE!=NULL)){
        free(*pE);
        pE = NULL;
    }
}

/*newList: Makes a new List*/
List newList(void){
    List L = malloc(sizeof(ListObj));
    L->front = L->cursor = NULL;
    L->numelements = 0;
    return(L);
}

/*freeList: Frees the memory attached to a List*/
void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

/*length: returns the length of the list*/
int length(List L){
    if(L!=NULL){
        return(L->numelements);
    }else{
        printf("length() error: cannot return length of null list\n");
        exit(1);
        return (0);
    }
}
/*index: returns the index (from 0) of the cursor*/
int index(List L){
    int i = 0;
    if(L==NULL){
        printf("index() error: cannot find the index of a null list\n");
        exit(1);
        return (0);
    }
    if(L->cursor == NULL){
        return (-1);
    }
    Element N = L->front;
    while(N!=L->cursor){
        N = N->next;
        i++;
    }
    return i;
}
/*front: returns the value of the front element*/
int front(List L){
    if(L==NULL){
        printf("front() error: cannot return the front of a null list\n");
        exit(1);
    }
    return(L->front->value);
}
/*back: returns the value of the rearmost element*/
int back(List L){
    if(L==NULL){
        printf("back() error: cannot return the back of a null list\n");
        exit(1);
        return (0);
    }
    Element N = L->front;
    while(N->next!=NULL){
        N=N->next;
    }
    return N->value;
}
/*get: returns the value of the cursor element*/
int get(List L){
    if(L==NULL){
        printf("get() error: cannot return cursor value of null list\n");
        exit(1);
    }
    if(L->cursor==NULL){
        printf("get() error: cannot return cursor value of null cursor\n");
        exit(1);
    }
    Element N = L->front;
    while(N != L->cursor){
        N = N->next;
    }
    return (N->value);
}
/*equals: compares to lists and returns 1 (true) if they are identical*/
int equals(List A, List B){
    if(A==NULL || B==NULL){
        printf("equals() error: cannot compare to a null list\n");
        exit(1);
    }
    if(length(A) != length(B)){
        return (0);
    }
    if((length(A) == 0) && (length(B) == 0)){
        return (1);
    }
    Element N = A->front;
    Element M = B->front;
    while(N!=NULL && M!=NULL){
        if(N->value != M->value){
            return (0);
        }
        N=N->next;
        M=M->next;
    }
    return (1);
}
/*clear: erases all elements in the list*/
void clear(List L){
    if(L!=NULL){
        while(length(L)>0){
            deleteFront(L);
        }
    }
}
/*moveFront: moves the cursor to the front element*/
void moveFront(List L){
    if(L!=NULL){
        L->cursor = L->front;
    }
}
/*moveBack: moves the cursor to the rearmost element*/
void moveBack(List L){
    if(L!=NULL){
        L->cursor = L->front;
        while(L->cursor->next != NULL){
            L->cursor = L->cursor->next;
        }
    }
}
/*movePrev: moves the cursor one element forward*/
void movePrev(List L){
    if(L!=NULL){
        if(L->cursor == NULL){
            printf("moveNext() error: cannot move a null cursor previous\n");
            exit(1);
        }
        if(L->cursor->prev == NULL){
            L->cursor = NULL;
        }else if (L->cursor->prev != NULL){
            L->cursor = L->cursor->prev;
        }
    }
}
/*moveNext: moves the cursor one element down*/
void moveNext(List L){
    if(L!=NULL){
        if(L->cursor == NULL){
            printf("moveNext() error: cannot move a null cursor next\n");
            exit(1);
        }
        if(L->cursor->next == NULL){
            L->cursor = NULL;
        } else if (L->cursor->next != NULL){
            L->cursor = L->cursor->next;
        }
    }
}
/*prepend: adds an element to the front of the list*/
void prepend(List L, int data){
    if(L!=NULL){
        Element E = newElement(data);
        if(length(L) > 0){
            E->next = L->front;
            L->front->prev = E;
        }
        L->front = E;
        L->numelements++;
    }else{
        printf("cannot prepend() to a null list\n");
    }
}
/*append: adds an element to the back of the list*/
void append(List L, int data){
    if(L!=NULL){
        if(length(L) == 0){
            prepend(L, data);
        }else{
            Element E = newElement(data);
            Element F = L->front;
            while(F->next!=NULL){
                F=F->next;
            }
            F->next = E;
            E->prev = F;
            L->numelements++;
        }
    }else{
        printf("cannot append() to a null list\n");
    }
}
/*insertbefore: adds an element immediately preceding the cursor*/
void insertBefore(List L, int data){
    if((L!=NULL)||(L->cursor==NULL)){
        if(index(L) == 0){
            prepend(L, data);
        }else{
            Element E = newElement(data);
            Element F = L->cursor->prev;
            F->next = E;
            E->prev = F;
            E->next = L->cursor;
            L->cursor->prev = E;
            L->numelements++;;
        }
    }else{
        printf("cannot insertBefore to a null list, or a null cursor\n");
    }
}
/*insertafter: inserts an element immediately following the cursor*/
void insertAfter(List L, int data){
    if((L!=NULL)||(L->cursor==NULL)){
        Element E = newElement(data);
        if((length(L)-1)==(index(L))){
            L->cursor->next = E;
            E->prev = L->cursor;
        }else{
            Element F = L->cursor->next;
            F->prev = E;
            E->next = F;;
            L->cursor->next = E;
            E->prev = L->cursor;
        }
        L->numelements++;
    }else{
        printf("cannot insertAfter with a null list or a null cursor\n");
        exit(1);
    }
}
/*deletefront: erases the frontmost element of the list*/
void deleteFront(List L){
    if(L!=NULL){
        if(length(L) == 0){
            printf("deleteFront() error: cannot delete elements from an empty list\n");
            exit(1);
        }else{
            if(index(L)==0){
                L->cursor = NULL;
            }
            if(length(L) == 1){
                Element E = L->front;
                freeElement(&E);
                L->numelements--;
                L->front = NULL;
            }else{
                Element E = L->front;
                L->front = E->next;
                freeElement(&E);
                L->numelements--;
            }
        }
    }
}
/*deleteBack: deletes the hindmost element of the list*/
void deleteBack(List L){
    if(L!=NULL){
        if(length(L) == 0){
            printf("deleteBack() error: cannot delete elements from an empty list\n");
            exit(1);
        }
        if(length(L)==1){
            deleteFront(L);
        }else{
            if(index(L) == (length(L) - 1)){
                L->cursor = NULL;
            }
            Element E = L->front;
            while(E->next != NULL){
                E = E->next;
            }
            Element F = E->prev;
            freeElement(&E);
            F->next = NULL;
            L->numelements--;
        }
    }
}
/*delete: erases the cursor element*/
void delete(List L){
    if(L!=NULL){
        if(length(L) == 0){
            printf("delete() error: cannot delete elements from an empty list\n");
            exit(1);
        }
        if(L->cursor == NULL){
            printf("delete() error: cannot delete cursor element of a null curosr\n");
            exit(1);
        }
        if(index(L) == 0){
            deleteFront(L);
        }else if (index(L) == (length(L)-1)){
            deleteBack(L);
        }else{
            Element A = L->cursor->prev;
            Element B = L->cursor->next;
            A->next = B;
            B->prev = A;
            Element C = L->cursor;
            freeElement(&C);
            L->numelements--;
        }
    }
}
/*printList: prints the list in a readable form*/
void printList(FILE* out, List L){
    if(L!=NULL){
        moveFront(L);
        while(L->cursor != NULL){
            fprintf(out, "%d ", get(L));
            moveNext(L);
        }
    }else{
        printf("cannot print a null list");
        exit(1);
    }
}
/*copyList: copies all the elements of a designated list to a new list*/
List copyList(List L){
    Element N = L->cursor;
    int i = 1;
    if(L!=NULL){
        List A = newList();
        moveFront(L);
        while(i<=length(L)){
            append(A, get(L));
            if(i<length(L)){
                moveNext(L);
            }
            i++;
        }
        L->cursor = N;
        return A;
    }else{
        printf("copyList() error: cannot copy a null list\n");
        exit(1);
        return L;
    }
}
