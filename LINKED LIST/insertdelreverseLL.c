// Online C compiler to run C program online
#include <stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} node;

node* head=NULL;

void Rev(node *q,node *p)
{
    if(p!=NULL)
    {
        Rev(p,p->next);
        p->next=q;
    }

    else
    head=q;
}

int main()
{
    int i,size=5;
    
    for(i=0;i<size;i++)
    {
        node* ptr1=(node*)malloc(sizeof(node));
        ptr1->data=i+1;
        ptr1->next=NULL;
        
        if(head==NULL)
        head=ptr1;
        
        else
        {
            node* temp=head;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
	        temp->next=ptr1;
        }
    }
    

    //insertion at the start
    node *temp=head;
    node* ins=(node*)malloc(sizeof(node));
    ins->data=0;
    ins->next=head;
    head=ins;
    
    //insertion at the end
    node* end=(node*)malloc(sizeof(node));
    end->data=6;
    end->next=NULL;
    
    temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=end;
    
    //insertion in between
    node* bet=(node*)malloc(sizeof(node));
    bet->data=888;
    bet->next=NULL;
    
    temp=head;
    int pos=3;
    int count=1;
    while(temp->next!=NULL)
    {
        if(count==pos-1)
        break;
        
        else{
        temp=temp->next;}
        count++;
    }
    
    bet->next=temp->next;
    temp->next=bet;
    
    //deletion at the beginning
    node* todelete=head;
    head=head->next;
    free(todelete);
    
    //deletion at the end
    temp=head;
    while(temp->next->next!=NULL)
    {temp=temp->next;}
    
    node* todel=temp->next;
    temp->next=NULL;
    free(todel);
    
    //deletion in between
    temp=head;
    count=1;
    pos=2;
    
    while(temp->next!=NULL)
    {
        if(count==pos-1)
        break;
        
        else{
        temp=temp->next;}
        count++;
    }
    node* dell=temp->next;
    temp->next=temp->next->next;
    free(dell);
    
    //reversal of list
    
    /*node* prev=head;
    node* curr=head->next;
    head=head->next;
    prev->next=NULL;
    
    while(head!=NULL)
    {
        head=head->next;
        curr->next=prev;
        prev=curr;
        curr=head;
    }
    head=prev;*/

    //using sliding pointers
    node *r=NULL;
    node *q=NULL;
    node *p=head;

    while(p!=NULL)
    {
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    head=q;

    //using recursion
    p=head;
    q=NULL;
    Rev(q,p);
    
    //printing the list
    temp=head;
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
}