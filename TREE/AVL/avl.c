//AVL trees are balanced Binary Search Trees
// Balance factor= Height(left subtree) - Height(right subtree)
// Balance factor= {-1,0,1}

//if BF(p)=2 and BF(p->left)=1 ----> LL Rotation
//if BF(p)=2 and BF(p->left)=-1 ----> LR Rotation
//if BF(p)=-2 and BF(p->right)=-1 ----> RR Rotation
//if BF(p)=-2 and BF(p->left)=1 ----> RL Rotation

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    struct Node *left;
    struct Node *right;
    int height;
    int data;
}node;

node *root=NULL;

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

int BalanceFactor(node *p)
{
    return Height(p->left)-Height(p->right);
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

node * createnode(int d)
{
    node *new=(node *)malloc(sizeof(node));
    new->data=d;
    new->left=new->right=NULL;
    new->height=Height(new);
    return new;
}

node * LLRotation(node *p){
    node *pl=p->left;
    node *plr=pl->right;

    pl->right=p;
    p->left=plr;
    p->height=Height(p);
    pl->height=Height(pl);

    if(p==root)
    {
        root=pl;
    }
    return pl;
}

node * LRRotation(node *p)
{
    node *pl=p->left;
    node *plr=pl->right;

    pl->right=plr->left;
    p->left=plr->right;
    
    plr->left=pl;
    plr->right=p;

    p->height=Height(p);
    pl->height=Height(pl);
    plr->height=Height(plr);

    if(p==root)
    {
        root=plr;
    }
    return plr;
}

node * RLRotation(node *p)
{
    node *pr=p->right;
    node *prl=pr->left;

    pr->left=prl->right;
    p->right=prl->left;
    
    prl->right=pr;
    prl->left=p;

    p->height=Height(p);
    pr->height=Height(pr);
    prl->height=Height(prl);

    if(p==root)
    {
        root=prl;
    }
    return prl;
}

node * RRRotation(node *p)
{
    node *pr=p->right;
    node *prl=pr->left;

    p->right=prl;
    pr->left=p;
    p->height=Height(p);
    pr->height=Height(pr);

    if(p==root)
    {
        root=pr;
    }
    return pr;
}

node * Insert(node *p,int x)
{
    node *temp=NULL;

    if(p==NULL)
    {
        node *temp=createnode(x);
        return temp;
    }
    
    if(x<p->data)
    {p->left=Insert(p->left,x);}

    else
    {p->right=Insert(p->right,x);}

    p->height=Height(p);

    if(BalanceFactor(p)==2 && BalanceFactor(p->left)==1)
        return LLRotation(p);
    else if(BalanceFactor(p)==2 && BalanceFactor(p->left)==-1)
        return LRRotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->left)==-1)
        return RRRotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->left)==1)
        return RLRotation(p);
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 0)
        return LLRotation(p);
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 0)
        return RRRotation(p);
    
    return p;
}

node * Delete(node *p, int key) 
{
    if (p == NULL){
        return NULL;
    }
 
    if (p->left == NULL && p->right == NULL){
        if (p == root){
            root = NULL;
        }
        free(p);
        return NULL;
    }
 
    if (key < p->data){
        p->left = Delete(p->left, key);
    } else if (key > p->data){
        p->right = Delete(p->right, key);
    } else {
        node* q;
        if (Height(p->left) > Height(p->right)){
            q = RightPredecessor(p->left);
            p->data = q->data;
            p->left = Delete(p->left, q->data);
        } else {
            q = LeftSuccessor(p->right);
            p->data = q->data;
            p->right = Delete(p->right, q->data);
        }
    }
 
    // Update height
    p->height = Height(p);
 
    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 1) {  // L1 Rotation
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == -1){  // L-1 Rotation
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == -1){  // R-1 Rotation
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 1){  // R1 Rotation
        return RLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 0){  // L0 Rotation
        return LLRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 0){  // R0 Rotation
        return RRRotation(p);
    }
 
    return p;
}

int main(){
    root=Insert(root,50);
    root=Insert(root,20);
    root=Insert(root,10);

    printf("%d ",root->data);
    return 0;
}