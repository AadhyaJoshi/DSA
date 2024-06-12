/*	2022UCP1326 Aadhya Joshi
	
	Description: This is a C program to implement a linked list with the following functionalities:
	creation, traversal, and searching for a particular element.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
} node;

node* newNode();
void insertNode(node* new);
void traverseList();
int searchElement(int n);
int printElement(int n);

node* head=NULL;
                    
node* newNode()
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

void insertNode(node * ptr)
{
    if(head==NULL)
    {
        head=ptr;
        return;
    }

	node* temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
	temp->next=ptr;
	return;
}


void traverseList()
{
    node * temp=head;

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

int searchElement(int x)
{
	node* el=head;
	if(el==NULL)
	{
		return -1;
	}
	int count=0;
	
	while(el!=NULL)
	{
		if(el->data==x)
		{
			return count;
		}	
		count++;
		el=el->next;
	}
	return -1;
}


int printElement(int index)
{
    int count=0;
    node* el=head;
	
    while(el!=NULL)
    {
        if(count==index)
        return el->data;

        count++;
        el=el->next;
    }
    return -1;
}


void main()
{	
	int size,i;
	int val;
	
	printf("Enter the number of values: ");
	scanf("%d",&size);
	
	printf("\n");
	
	for(i=0;i<size;i++)
	{
		int val;
	
		printf("Enter element %d: ",i+1);
		scanf("%d",&val);
			
		node * new=newNode();
        new->data=val;
        new->next=NULL;
              
        insertNode(new);
	}

    printf("\n");

    while(1)
    {
        int x,search,pos;
	    printf("Which operation would you like to perform?\n");
    	printf("PRESS 1: Traverse the linked list and print its elements\n");
	    printf("PRESS 2: Search for an element in the linked list and print its index\n");
    	printf("PRESS 3: Print data value for the position entered by the user\n");
	    printf("PRESS 4: Exit the Program\n");
	
	    scanf("%d",&x);
	
        if(x==4)
        {
            printf("END OF PROGRAM..");
            break;
        }

	    switch(x)
	    {
		case 1:
		traverseList(&head);
		break;
		
		case 2:
        printf("Enter element to be searched: ");
        scanf("%d",&search);

        printf("\n");

		int index = searchElement(search);
		if(index==-1)
			printf("Element not found\n");

		else
			printf("Element found at the index : %d\n", index);
		break;
		
		case 3:
        printf("Enter position: ");
        scanf("%d",&pos);

        printf("\n");

		int value=printElement(pos-1);
        if(value==-1)
			printf("This position does not exist for the defined list.\n");
        else
        printf("Value at given position is %d\n",value);
		break;
	
		default:
		printf("Invalid input\n");
		break;
	    }
    }
}
