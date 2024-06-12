/* 	2022UCP1326 Aadhya Joshi
	This is a C program to implement doubly linked list with the following functionalties:
	insertion, deletion, and traversal.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
	struct Node* prev;
} node;

//globally defining head of DLL
node* head=NULL;


node* createNode();
void insertatBeginning(node*);
node* insertatEnd(node *,node *);
void insertatN(node*,int);
void deleteatbeginning();
void deleteatEnd();
void delete(int);
void traversal(node*);

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

void traversal(node* temp)
{
	if(temp==NULL)
	{
		printf("List is empty");
        return ;
    }

    printf("The list is: ");

    while(temp!=NULL)
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
        return head;
    }


    else
    {
	node* temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
	    temp->next=ptr;
	    ptr->prev=temp;
	    return head;
    }

}

void insertatBeginning(node* insert)
{
	insert->next=head;
	head->prev=insert;
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
			ins->prev=temp;
			nextitem->prev=ins;
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


void deleteatbeginning()
{
	node* toDel=head;
	head=head->next;
	toDel->next=NULL;
	head->prev=NULL;
	free(toDel);
}

void deleteatEnd()
{
	node* temp=head;
	while(temp->next->next!=NULL)
	{
		temp=temp->next;
	}
	node *del=temp->next;
	temp->next=NULL;
	del->prev=NULL;
	free(del);
}

void delete(int value)
{
	node* temp=head;
	
	while(temp->next!=NULL)
	{
		if(temp->data==value)
		{
			node* deletenode=temp;
			temp->prev->next=temp->next;
			temp->next->prev=temp->prev;
			
			deletenode->next=NULL;
			deletenode->prev=NULL;
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
        	new->prev=NULL;

        	head=insertatEnd(head,new);
	}

	printf("\n");
	traversal(head);

    printf("\n");
    
    while(1)
    {
        int x,value,value2,value3,pos,del;
	printf("Which operation would you like to perform?\n");
    	printf("PRESS 1: Insert an element at the beginning of the DLL\n");
    	printf("PRESS 2: Insert an element at the end of the DLL\n");
    	printf("PRESS 3: Insert an element at an index of the DLL\n");
	printf("PRESS 4: Delete an element from the beginning of the DLL\n");
	printf("PRESS 5: Delete an element from the end of the DLL\n");
	printf("PRESS 6: Delete an element from DLL\n");
	printf("PRESS 0: Exit the Program\n");
	
	scanf("%d",&x);
	
        if(x==0)
        {
        	traversal(head);
		printf("END OF PROGRAM..");
		break;
        }

	    switch(x)
	    {
		case 1:		
		printf("Enter value: ");
		scanf("%d",&value);
		printf("\n");
		
		node* ins=createNode();
		ins->data=value;
		ins->prev=NULL;
		
		insertatBeginning(ins);
		printf("\n");
		
		traversal(head);
		break;
		
		case 2:
       	printf("Enter value: ");
		scanf("%d",&value2);
		printf("\n");
		
		node* insend=createNode();
		insend->data=value2;
		
		head=insertatEnd(head,insend);
		printf("\n");
       	
		traversal(head);
		break;
		
		case 3:
		printf("Enter value: ");
		scanf("%d",&value3);
		printf("\n");
		
		printf("Enter index: ");
		scanf("%d",&pos);
		printf("\n");
		
		node* insbet=createNode();
		insbet->data=value3;
		
		insertatN(insbet,pos);
		printf("\n");
		
		traversal(head);
		break;
		
		case 4:
		deleteatbeginning();
		traversal(head);
		break;
			
		case 5:
		deleteatEnd();
		traversal(head);
		break;
		
		case 6:
		printf("Enter value to be deleted: ");
		scanf("%d",&del);
		printf("\n");
		
		delete(del);
		
		traversal(head);
		break;
		
		default:
		printf("Invalid input\n");
		break;
	    }
    }
    
}






