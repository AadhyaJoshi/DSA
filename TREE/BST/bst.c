//binary search tree is a binary tree in which left child is smaller than parent and right child is greater than parent

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    struct Node *left;
    struct Node *right;
    int data;
}node;

node *root=NULL;

node * createnode(int d)
{
    node *new=(node *)malloc(sizeof(node));
    new->data=d;
    new->left=new->right=NULL;
    return new;
}

int Height(node *p)
{
    if(p==NULL)
    {
        return 0;
    }
    int x=Height(p->left);
    int y=Height(p->right);

    if(x>y) return x+1;
    else return y+1;
}

node * RightPredecessor(node *p)
{
    while(p!=NULL && p->right!=NULL)
    {
        p=p->right;
    }
    return p;
}

node * LeftSuccessor(node *p)
{
    while(p!=NULL && p->left!=NULL)
    {
        p=p->left;
    }
    return p;
}

void Insert(int x)
{
    node *p=root;
    node *prev=NULL;

    if(p==NULL)
    {
        node *temp=createnode(x);
        root=temp;
        return;
    }

    while(p!=NULL)
    {
        prev=p;
        if(x<p->data)
        {
            p=p->left;
        }
        else
        {
            p=p->right;
        }
    }
    node *temp=createnode(x);

    if(x<prev->data)
    {
        prev->left=temp;
    }
    else prev->right=temp;
    return;
 
}

node * Delete(node *p,int x)
{
    if(p==NULL)
    {
        return NULL;
    }

    if(p->left==NULL && p->right==NULL)
    {
        if(p==root){root=NULL;}
        free(p);
        return NULL;
    }

    node *temp;

    if(x<p->data)
    p->left=Delete(p->left,x);

    else if(x>p->data)
    p->right=Delete(p->right,x);

    else
    {
        if(Height(p->left)>Height(p->right))
        {
            temp=RightPredecessor(p->left);
            p->data=temp->data;
            p->left=Delete(p->left,temp->data);
        }

        else{
            temp=LeftSuccessor(p->right);
            p->data=temp->data;
            p->right=Delete(p->right,temp->data);
        }
    }
}

void inorder(node *p)
{
    if(p==NULL){return;}
    inorder(p->left);
    printf("%d ",p->data);
    inorder(p->right);
}

int main(){

    Insert(10);
    Insert(8);
    Insert(66);
    Insert(36);
    Insert(2);
    Insert(9);
    inorder(root);
    printf("\n");

    Delete(root,10);
    inorder(root);

    return 0;
}
