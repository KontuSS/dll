#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct doubly_linked_list_t* dll_create()
{
    struct doubly_linked_list_t *dll = malloc(sizeof(struct doubly_linked_list_t));
    if (dll==NULL) return NULL;
    dll->head=NULL;
    dll->tail=NULL;
    return dll;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value)
{
    if(dll ==NULL || (dll->tail== NULL && dll->head!= NULL) || (dll->tail!= NULL && dll->head== NULL)) return 1;
    struct node_t *new = malloc(sizeof(struct node_t));
    if (new==NULL) return 2;
    new->data=value;
    new->next = NULL;
    if (dll->tail==NULL)
    {
        new->prev=NULL;
        dll->head=new;
    }
    else
    {
        dll->tail->next=new;
        new->prev=dll->tail;
    }
    dll->tail=new;
    return 0;
}
int dll_push_front(struct doubly_linked_list_t* dll, int value)
{
    if(dll ==NULL || (dll->tail== NULL && dll->head!= NULL) || (dll->tail!= NULL && dll->head== NULL)) return 1;
    struct node_t *new = malloc(sizeof(struct node_t));
    if (new==NULL) return 2;
    new->data=value;
    new->prev = NULL;
    if (dll->head==NULL)
    {
        new->next=NULL;
        dll->tail=new;
    }
    else
    {
        dll->head->prev=new;
        new->next=dll->head;
    }
    dll->head=new;
    return 0;
}
int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL)
    {
        if (err_code!=NULL) *err_code=1;
        return -1;
    }
    int retVal = dll->head->data;
    struct node_t *newHead = dll->head->next;
    free(dll->head);
    dll->head=newHead;
    if (dll->head==NULL) dll->tail=NULL;
    else dll->head->prev=NULL;
    if (err_code!=NULL) *err_code=0;
    return retVal;

}
int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL)
    {
        if (err_code!=NULL) *err_code=1;
        return -1;
    }
    int retVal = dll->tail->data;
    struct node_t *newTail = dll->tail->prev;
    free(dll->tail);
    dll->tail=newTail;
    if (dll->tail==NULL) dll->head=NULL;
    else dll->tail->next=NULL;
    if (err_code!=NULL) *err_code=0;
    return retVal;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL)
    {
        if (err_code!=NULL) *err_code=1;
        return -1;
    }
    if (err_code!=NULL) *err_code=0;
    return dll->tail->data;
}
int dll_front(const struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL)
    {
        if (err_code!=NULL) *err_code=1;
        return -1;
    }
    if (err_code!=NULL) *err_code=0;
    return dll->head->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL) return NULL;
    return dll->head;
}
struct node_t* dll_end(struct doubly_linked_list_t* dll)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL) return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll)
{
    if(dll==NULL || (dll->tail== NULL && dll->head!= NULL) || (dll->tail!= NULL && dll->head== NULL)) return -1;
    if (dll->tail==NULL && dll->head==NULL) return 0;
    int count = 0;
    struct node_t *counter = dll->head;
    while (counter!=NULL)
    {
        count++;
        counter=counter->next;
    }
    return count;
}
int dll_is_empty(const struct doubly_linked_list_t* dll)
{
    if(dll==NULL || (dll->tail== NULL && dll->head!= NULL) || (dll->tail!= NULL && dll->head== NULL)) return -1;
    if (dll->tail==NULL && dll->head==NULL) return 1;
    return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL)
    {
        if (err_code!=NULL) *err_code=1;
        return -1;
    }

    int size = dll_size(dll);
    if ((int)index>=size) return 1;

    unsigned int count = 0;
    struct node_t *counter = dll->head;
    while (count<index)
    {
        count++;
        counter=counter->next;
    }
    if (err_code!=NULL) *err_code=0;
    return counter->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value)
{
    if (dll==NULL) return 1;
    unsigned int size = dll_size(dll);
    if (index>size) return 1;

    struct node_t *new = malloc(sizeof(struct node_t));
    if (new==NULL) return 2;
    new->data=value;
    new->next=NULL;
    new->prev=NULL;

    if (dll->head==NULL)
    {
        dll->head=new;
        dll->tail=new;
    }
    else if (index==0)
    {
        new->next=dll->head;
        dll->head->prev=new;
        dll->head=new;
    }
    else if (index==size)
    {
        new->prev=dll->tail;
        dll->tail->next=new;
        dll->tail=new;
    }
    else
    {
        unsigned int count = 0;
        struct node_t *counter = dll->head;
        while (count<index)
        {
            count++;
            counter=counter->next;
        }
        struct node_t *move = counter->prev;
        new->prev = move;
        move->next=new;
        new->next=counter;
        counter->prev=new;
    }
    return 0;
}
int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if (dll == NULL || dll->head == NULL || dll->tail == NULL)
    {
        if (err_code) *err_code = 1;
        return -1;
    }
    unsigned int size = dll_size(dll);
    if (index>=size)
    {
        if (err_code) *err_code = 1;
        return -1;
    }
    int retval;
    if (index==0)
    {
        struct node_t *move = dll->head;
        retval = move->data;
        dll->head=move->next;

        if (dll->head==NULL) dll->tail=NULL;
        else dll->head->prev=NULL;

        free(move);
        if (err_code!=NULL) *err_code=0;
        return retval;
    }
    else if (index==size-1)
    {
        struct node_t *move = dll->tail;
        retval = move->data;
        dll->tail=move->prev;
        dll->tail->next=NULL;

        free(move);
        if (err_code!=NULL) *err_code=0;
        return retval;
    }
    else// ABDCQE
    {
        unsigned int count = 0;
        struct node_t *counter = dll->head;
        while (count<index)
        {
            count++;
            counter=counter->next;
        }

        struct node_t *move = counter->prev;
        move->next = counter->next;
        counter->next->prev = move;
        retval = counter->data;
        free(counter);
        if (err_code!=NULL) *err_code=0;
        return retval;
    }
}

void dll_clear(struct doubly_linked_list_t* dll)
{
    if (dll == NULL || dll->head == NULL || dll->tail == NULL) return;
    struct node_t *clear = dll->head;
    while (clear!=NULL)
    {
        struct node_t *next = clear->next;
        free(clear);
        clear = next;
    }
    dll->head=NULL;
    dll->tail=NULL;
}

void dll_display(const struct doubly_linked_list_t* dll)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL ) return;
    struct node_t *display = dll->head;
    for (int i = 0; display ; ++i)
    {
        printf("%d ", display->data);
        display=display->next;
    }
}
void dll_display_reverse(const struct doubly_linked_list_t* dll)
{
    if(dll == NULL || dll->head == NULL || dll->tail==NULL ) return;
    struct node_t *display = dll->tail;
    for (int i = 0; display ; ++i)
    {
        printf("%d ", display->data);
        display=display->prev;
    }
}