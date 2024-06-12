//bucket sort

#include<stdlib.h>
#include<stdio.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
}node;


node* insertnode(node*,int);
void bucket_sort(int *,int);
node* sortgivenbucket(node*);


node* insertnode(node* head,int value)
{
    node* new=(node*)malloc(sizeof(node));

    new->data=value;
    new->next=NULL;

    if(head==NULL)
    {
        head=new;
        return head;
    }

    //inserting while sorting
    node *temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=new;
    return head;
}

node* sortgivenbucket(node *head) 
{  
    node *current = head; 
    node *nextnode = NULL;  
    int temp;  
          
    if(head==NULL) 
    {  
        return head;  
    }  
        
    else 
    {  
        while(current!= NULL) 
        {  
            nextnode=current->next;       
            while(nextnode!=NULL) 
            {
                if(current->data>nextnode->data) 
                {  
                    temp = current->data;  
                    current->data = nextnode->data;  
                    nextnode->data = temp;  
                }  
                nextnode=nextnode->next;  
            }  
            current=current->next;  
        }      
    }  
    return head;
} 


void bucket_sort(int *arr,int size)
{
    //finding max element
    int max=arr[0];
    int i;
    for(i=0;i<size;i++)
    {
        if(arr[i]>max)
        max=arr[i];
    }

    //let number of buckets be 6
    int num=6;

    //creating buckets
    node **buckets;
    buckets = (node **)malloc(num*sizeof(node *));

    for(i=0;i<num;i++) 
    {
        buckets[i] = NULL;
    }

    //filling the buckets
    for(i=0;i<size;i++) 
    {
        if(arr[i]!=max)
        {
            int value=(arr[i]*num)/max;
            buckets[value]=insertnode(buckets[value],arr[i]);
        }
    }
   
    //adding max element to last bucket
    buckets[num-1]=insertnode(buckets[num-1],max);

    //sorting elements of each bucket
    for(i=0;i<num;i++) 
    {
        buckets[i]=sortgivenbucket(buckets[i]);
    }

    //Putting sorted elements on initial array
    int j;
    for (i=0,j=0;i<num;i++) 
    {
        node *temp1;
        temp1=buckets[i];
        while(temp1) 
        {
            arr[j++] = temp1->data;
            temp1=temp1->next;
        }
  }

}
