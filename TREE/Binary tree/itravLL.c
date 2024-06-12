// program to perform iterative traversal in binary tree

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
    
}node;

//to keep count of nodes in the tree
int nonodes=0;

/*************************************STACK FUNCTIONS****************************************************************/

//maintaining a stack using linked list
typedef struct Stack{
    node *root;
    struct Stack *next;
}snode;

snode *top1=NULL;
snode *top2=NULL;

void push(node *temp,snode **top)
{
    if(*top==NULL)
    {
        *top=(snode*)malloc(sizeof(snode));
        (*top)->root=temp;
        (*top)->next=NULL;
    }

    else
    {
        snode *new=(snode*)malloc(sizeof(snode));
        new->root=temp;
        new->next=*top;
        *top=new;
    }
}

int isempty(snode* top)
{
    if((top)==NULL) return 1;
    return 0;
}

node * pop(snode **top)
{
    node * temp;

    if(isempty(*top))
    printf("Stack underflow!\n");

    else
    {
        temp=(*top)->root;
        snode *del=*top;
        *top=(*top)->next;
        free(del);
    }
    return temp;
}

/*********************************************************************************************************************/

//function to create a tree
node* create(FILE *inp)
{
	node* new=(node*)malloc(sizeof(node));
    nonodes++;
	int value;
	
	fscanf(inp,"%d",&value);
	
	if(value==-1)
	{
		nonodes--;
        return NULL;
	}
	
	new->data=value;
	
	new->left=create(inp);
	new->right=create(inp);
	
	return new;
}

void preorder(node *root,FILE *out)
{
    while(root || !isempty(top1))
    {
        if(root!=NULL)
        {
            fprintf(out,"%d -> ",root->data);
            push(root,&top1);
            root=root->left;
        }

        else
        {
            root=pop(&top1);
            root=root->right;
        }
    }
}

void inorder(node *root,FILE *out)
{
    while(root || !isempty(top1))
    {
        if(root!=NULL)
        {
            push(root,&top1);
            root=root->left;
        }

        else
        {
            root=pop(&top1);
            fprintf(out,"%d -> ",root->data);
            root=root->right;        
        }
    }
}

void postorder(node *root,FILE *out)
{
   		push(root,&top1);
   		
   		while(!isempty(top1))
   		{
   			node *temp=pop(&top1);
   			
   			push(temp,&top2);
   			
   			if(temp->left!=NULL)
   			{push(temp->left,&top1);}
   			
   			if(temp->right!=NULL)
   			{push(temp->right,&top1);}
   			
        }
        
        while(!isempty(top2))
        {
        	node *temp=pop(&top2);
        	fprintf(out,"%d -> ",temp->data);
        }
}

int main(){

	FILE *inp=fopen("input.txt","r");
	FILE *out=fopen("outputI.txt","w");

   	/*creating the tree from input file
    				1
    			   / \
    			  2   3
    			 / \ / \
    			4  5 6  7
    			
    */
    	
    node *root=create(inp);

    fprintf(out,"Preorder traversal: ");
    preorder(root,out);
    fprintf(out,"\n");
    
    fprintf(out,"Inorder traversal: ");
    inorder(root,out);
    fprintf(out,"\n");
    
    fprintf(out,"Postorder traversal: ");
    postorder(root,out);
    fprintf(out,"\n");
    
    fclose(inp);
    fclose(out);

    return 0;
}




