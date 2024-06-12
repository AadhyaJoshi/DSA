/* 	2022UCP1326 Aadhya Joshi
	This is a C program to implement circular linked list with the following functionalties:
	insertion, deletion, and print.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;

} node;

//globally defining head and tail of CLL
node* head=NULL;
node* tail=NULL;


node* createNode();
void insertatBeginning(node*);
node* insertatEnd(node *,node *);
void insertatN(node*,int);
void delete(int);
void printList(node*);

node* createNode()
{
	node* ptr=(node *)malloc(sizeof(node));

    if(ptr==NULL)
    {
        printf("Memory allocation failed");
        exit(0);
    }

    else
    {
        return ptr;
    }
}

void printList(node* temp)
{
	if(temp==NULL)
	{
		printf("List is empty");
        return ;
    }

    printf("The list is: ");
    printf("%d ",temp->data);
    temp=temp->next;
    while(temp!=head)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

node* insertatEnd(node* head,node * ptr)
{
    if(head==NULL)
    {
        head=ptr;
        tail=ptr;
        ptr->next=head;
        return head;
    }


    else
    {
        tail->next=ptr;
        tail=ptr;
        tail->next=head;  
        return head;
    }

}

void insertatBeginning(node* insert)
{
    node *temp = head;    
    while(temp->next != head)
    {    
        temp = temp->next;
    }
	insert->next=head;
    temp->next=insert;
	head=insert;
}

void insertatN(node* ins,int index)
{
	int count=1;
	node* temp=head;
	
	while(temp->next!=NULL)
	{
		if(count==index-1)
		{
			node *nextitem=temp->next;
			temp->next=ins;			
			ins->next=nextitem;
			break;
		}
		
		else
		{
			count++;
			temp=temp->next;
		}
	}
}

void delete(int value)
{
	node* temp=head;
	
	while(temp->next!=head)
	{
		if(temp->next->data==value)
		{
			node* deletenode=temp->next;
			temp->next=temp->next->next;
	
			deletenode->next=NULL;
			free(deletenode);
			break;
		}
		
		else
		{
			temp=temp->next;
		}
	}
}

void main()
{
	int size,i;
	int val;

	printf("Enter the number of values list: ");
	scanf("%d",&size);

	printf("\n");

    printf("Enter elements for list:\n");
	for(i=0;i<size;i++)
	{
		int val;

		printf("Enter element %d: ",i+1);
		scanf("%d",&val);

		node * new=createNode();
        	new->data=val;
        	new->next=NULL;

        	head=insertatEnd(head,new);
	}

	printf("\n");
	printList(head);

    printf("\n");

    printf("After adding 5 and 2 at the beginning,\n");

    //adding 5 at beginning
    node* ins1=createNode();
    ins1->data=5;
    insertatBeginning(ins1);

    //adding 2 at beginning
    node* ins2=createNode();
    ins2->data=2;
    insertatBeginning(ins2);

    //printing the updated list
    printList(head);

    printf("After adding 10 and 20 at the end,\n");

    //adding 10 at end
    node* ins3=createNode();
    ins3->data=10;
    head=insertatEnd(head,ins3);

    //adding 20 at end
    node* ins4=createNode();
    ins4->data=20;
    head=insertatEnd(head,ins4);

    //printing the updated list
    printList(head);

    printf("After adding 888 at 6th position,\n");

    //adding an elemnet with value 888 at 6th position
    node* ins5=createNode();
    ins5->data=888;
    insertatN(ins5,6);

    //printing the updated list
    printList(head);

    printf("After deleting 5 and 20,\n");

    //removing 5 and 20
    delete(5);
    delete(20);

    //printing the updated list
    printList(head);

    printf("\n");
    printf("END OF PROGRAM..\n");

}