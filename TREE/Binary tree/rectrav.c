// program for recursive preorder, postorder and inorder traversals

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
    
}node;

node* create(FILE *inp)
{
	node* new=(node*)malloc(sizeof(node));
	int value;
	
	fscanf(inp,"%d",&value);
	
	if(value==-1)
	{
		return NULL;
	}
	
	new->data=value;
	
	new->left=create(inp);
	new->right=create(inp);
	
	return new;
}

void preorder(node *root,FILE *out)
{
    if(root==NULL){return;}
    fprintf(out,"%d -> ",root->data);
    preorder(root->left,out);
    preorder(root->right,out);
}

void inorder(node *root,FILE *out)
{
    if(root==NULL){return;}
    inorder(root->left,out);
    fprintf(out,"%d -> ",root->data);
    inorder(root->right,out);
}

void postorder(node *root,FILE *out)
{
    if(root==NULL){return;}
    postorder(root->left,out);
    postorder(root->right,out);
    fprintf(out,"%d -> ",root->data);
}

int main(){
	
	FILE *inp=fopen("input.txt","r");
	FILE *out=fopen("outputR.txt","w");
    
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





