// Online C compiler to run C program online
#include <stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} node;

node* first=NULL;
node *second=NULL;

int main()
{
    int i,size=5;
    
    //linked list 1 containing 0,2,4,6,8
    for(i=0;i<size;i++)
    {
        node* ptr1=(node*)malloc(sizeof(node));
        ptr1->data=i*2;
        ptr1->next=NULL;
        
        if(first==NULL)
        first=ptr1;
        
        else
        {
            node* temp=first;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
	        temp->next=ptr1;
        }
    }

    //linked list 2 containing 1,3,5,7,9
    for(i=0;i<size;i++)
    {
        node* ptr2=(node*)malloc(sizeof(node));
        ptr2->data=i*2+1;
        ptr2->next=NULL;
        
        if(second==NULL)
        second=ptr2;
        
        else
        {
            node* temp=second;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
	        temp->next=ptr2;
        }
    }

    //merging list 1 and 2
    node *third, *last;

    if(first->data<second->data)
    {
        third=last=first;
        first=first->next;
        last->next=NULL;
    }
    else{
        third=last=second;
        second=second->next;
        last->next=NULL;
    }

    while(first!=NULL && second!=NULL)
    {
        if(first->data<second->data)
        {
            last->next=first;
            last=first;
            first=first->next;
            last->next=NULL;
        }

        else{
            last->next=second;
            last=second;
            second=second->next;
            last->next=NULL;
        }
    }

    if(first!=NULL)
    {
        last->next=first;
    }
    else{
        last->next=second;
    }

    //printing the list
    node *temp=third;
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
}