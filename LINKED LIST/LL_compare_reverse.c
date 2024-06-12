/* 	2022UCP1326 Aadhya Joshi
	This is a C program to implement two linked list and perform the following
    operations: compare and reverse.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
} node;

node* createNode();
node* insertatEnd(node*,node*);
void printList(node*);
int compareLists(node*,node*,int);
node* reverseList(node*);

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
	    return head;
    }

}

int compareLists(node* head1,node* head2,int size)
{
    int count=0;
    node* comp1=head1;
    node* comp2=head2;

    while(comp1!=NULL && comp2!=NULL)
    {
        if(comp1->data != comp2->data)
        {
            return 0;
            break;
        }

        else
        count++;

        comp1=comp1->next;
        comp2=comp2->next;
    }

    if(count==size)
    return 1;

}

node* reverseList(node* head)
{
    node* prev=head;
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
    head=prev;
    return head;
}

void printList(node* temp)
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

void main()
{
	int size1,size2,i;
	int val;

    node* head1=NULL;
    node* head2=NULL;

	printf("Enter the number of values list1: ");
	scanf("%d",&size1);

	printf("\n");

    printf("Enter elements for list1:\n");
	for(i=0;i<size1;i++)
	{
		int val;

		printf("Enter element %d: ",i+1);
		scanf("%d",&val);

		node * new1=createNode();
        	new1->data=val;
        	new1->next=NULL;

        	head1 = insertatEnd(head1,new1);
	}

	printf("\n");
	printList(head1);

    printf("\n");

    printf("Enter the number of values in list2: ");
	scanf("%d",&size2);

	printf("\n");

    printf("Enter elements for list2:\n");
	for(i=0;i<size2;i++)
	{
		int val;

		printf("Enter element %d: ",i+1);
		scanf("%d",&val);

		node * new2=createNode();
        	new2->data=val;
        	new2->next=NULL;

        	head2=insertatEnd(head2,new2);
	}

	printf("\n");
	printList(head2);

    printf("\n");

    while(1)
    {
        int x,y,output;
	    printf("Which operation would you like to perform?\n");
    	printf("PRESS 1: To compare the given linked lists\n");
	    printf("PRESS 2: Reverse the linked lists\n");
	    printf("PRESS 3: Exit the Program\n");

	scanf("%d",&x);

        if(x==3)
        {
		    printf("END OF PROGRAM..");
		    break;
        }

	    switch(x)
	    {
		    case 1:
		    if(size1==size2)
            {
                output=compareLists(head1,head2,size1);
                if(output==1)
                {
                    printf("Lists are identical\n");
                }
                else
                {
                    printf("Lists are not identical\n");
                }
            }

            else
            {
                printf("Given lists are of different size, hence not comparable\n");
            }
		    printf("\n");
            break;

		    case 2:
       	    head1=reverseList(head1);
            printf("After reversal for list1:\n");
            printList(head1);
            head2 = reverseList(head2);
            printf("After reversal for list2:\n");
            printList(head2);

       	    printf("\n");
		    break;

		    default:
		    printf("Invalid input\n");
		    break;
	    }
    }
}
