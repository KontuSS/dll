#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "doubly_linked_list.h"

int main()
{
    struct doubly_linked_list_t *dll = dll_create();
    if (dll==NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    int choice, err;
    while (1)
    {
        printf("Co chcesz zrobic?");
        if (scanf("%d", &choice)!=1)
        {
            printf("Incorrect input");
            if(dll_is_empty(dll)==0) dll_clear(dll);
            free(dll);
            return 1;
        }

        if (choice==1)
        {
            int val;
            printf("Podaj liczbe");
            if (scanf("%d", &val)!=1)
            {
                printf("Incorrect input");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 1;
            }
            if (dll_push_back(dll, val)==2)
            {
                printf("Failed to allocate memory");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 8;
            }
        }
        else if (choice==2)
        {
            int view;
            if (dll_is_empty(dll)==1) printf("List is empty\n");
            else
            {
                view = dll_pop_back(dll, &err);
                printf("%d\n", view);
            }
        }
        else if (choice==3)
        {
            int val;
            printf("Podaj liczbe");
            if (scanf("%d", &val)!=1)
            {
                printf("Incorrect input");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 1;
            }
            if (dll_push_front(dll, val)==2)
            {
                printf("Failed to allocate memory");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 8;
            }
        }
        else if (choice==4)
        {
            int view;
            if (dll_is_empty(dll)==1) printf("List is empty\n");
            else
            {
                view = dll_pop_front(dll, &err);
                printf("%d\n", view);
            }
        }
        else if (choice==5)
        {
            int index, val;
            printf("Podaj wartosc: ");
            if (scanf("%d", &val)!=1)
            {
                printf("Incorrect input");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 1;
            }
            printf("Podaj index");
            if (scanf("%d", &index)!=1)
            {
                printf("Incorrect input");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 1;
            }
            int er = dll_insert(dll, index, val);
            if (er==1)
            {
                printf("Index out of range\n");
                continue;
            }
            if (er==2)
            {
                printf("Failed to allocate memory");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 8;
            }
        }
        else if (choice==6)
        {
            if (dll_is_empty(dll)==1)
            {
                printf("List is empty\n");
                continue;
            }
            printf("Podaj index");
            int index;
            if (scanf("%d", &index)!=1)
            {
                printf("Incorrect input");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 1;
            }
            int retVal = dll_remove(dll, index, &err);
            if (err==1)
            {
                printf("Index out of range\n");
                continue;
            }
            printf("%d\n", retVal);
        }
        else if (choice==7)
        {
            if (dll_is_empty(dll)==1)
            {
                printf("List is empty\n");
                continue;
            }
            printf("%d\n", dll_back(dll, &err));
        }
        else if (choice==8)
        {
            if (dll_is_empty(dll)==1)
            {
                printf("List is empty\n");
                continue;
            }
            printf("%d\n", dll_front(dll, &err));
        }
        else if (choice==9)
        {
            dll_is_empty(dll)? printf("1\n"): printf("0\n");
        }
        else if (choice==10)
        {
            printf("%d\n", dll_size(dll));
        }
        else if (choice==11)
        {
            dll_clear(dll);
        }
        else if (choice==12)
        {
            if (dll_is_empty(dll)==1)
            {
                printf("List is empty\n");
                continue;
            }
            int index, retVal;
            printf("Podaj index: ");
            if (scanf("%d", &index)!=1)
            {
                printf("Incorrect input");
                if(dll_is_empty(dll)==0) dll_clear(dll);
                free(dll);
                return 1;
            }
            retVal = dll_at(dll, index, &err);
            if (err==1)
            {
                printf("Index out of range\n");
                continue;
            }
            printf("%d\n", retVal);
        }
        else if (choice==13)
        {
            if (dll_is_empty(dll)==1)
            {
                printf("List is empty\n");
                continue;
            }
            dll_display(dll);
            printf("\n");
        }
        else if (choice==14)
        {
            if (dll_is_empty(dll)==1)
            {
                printf("List is empty\n");
                continue;
            }
            dll_display_reverse(dll);
            printf("\n");
        }
        else if (choice==0) break;
        else
        {
            printf("Incorrect input data\n");
            continue;
        }
    }
    if(dll_is_empty(dll)==0) dll_clear(dll);
    free(dll);
    return 0;
}