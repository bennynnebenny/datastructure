#include <stdio.h>
#include <stdlib.h>

struct tnode 
{
    int x;
    struct tnode *next;
    struct tnode *prev;
} *head, *tail;

void push_front(int value) 
{
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));

    node->x = value;
    node->prev = NULL;
    node->next = head;

    if(head == NULL) 
    {
        head = tail = node;
    }else 
    {
        head->prev = node;
        head = node;
    }

}

void push_back(int value) 
{
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));

    node->x = value;
    node->next = NULL;

    if(tail == NULL) 
    {
        head = tail = node;
        node->prev = NULL;
    }else 
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }

}

void push_mid(int value, int searchKey) 
{
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));

    node->x = value;

    if(head == NULL)
    {
        head = tail = node;
        node->next = node->prev = NULL;
    }else 
    {
        struct tnode *curr = head;

        while(curr != NULL && curr->x != searchKey) 
        {
            curr = curr->next;
        }

        if(curr == NULL) 
        {
            printf("Data %d not found\n", searchKey);
            free(node);
        }else 
        {
            node->next = curr->next;
            node->prev = curr;

            if(curr->next != NULL) 
            {
                curr->next->prev = node;
            }else 
            {
                tail = node;
            }

            curr->next = node;

        }
    }
}

void del_front() 
{
    if (head == NULL) 
    {
        printf("No data to delete\n");
        return;
    }

    struct tnode *temp = head;

    head = head->next;

    if(head != NULL) 
    {
        head->prev = NULL;
    }else 
    {
        tail = NULL;
    }

    free(temp);

}

void del_back() 
{
    if(tail == NULL) 
    {
        printf("No data to delete\n");
        return;
    }

    struct tnode *temp = tail;

    tail = tail->prev;

    if(tail != NULL)
    {
        tail->next = NULL;
    }else 
    {
        head = NULL;
    }

    free(temp);

}

void del_mid(int value)
{
    if(head == NULL) 
    {
        printf("No data to delete\n");
        return;
    }

    struct tnode *curr = head;

    while(curr != NULL && curr->x != value) 
    {
        curr = curr->next;
    }

    if(curr == NULL) 
    {
        printf("Data %d not found\n", value);
        return;
    }

    if(curr == head) 
    {
        del_front();
    }else if(curr == tail) 
    {
        del_back();
    }else 
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
    }

}

void printList()
{
    struct tnode *curr = head;

    while(curr != NULL) 
    {
        printf("%d ", curr->x);
        curr = curr->next;
    }

    printf("\n");
    
}

int main() 
{
    push_front(76);
    push_front(90);
    push_front(45);
    printList();
    push_mid(60, 76);
    printList();
    del_front();
    printList();
    del_back();
    printList();
    del_mid(60);
    printList();
    return 0;
}