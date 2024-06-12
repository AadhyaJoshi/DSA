#include<stdio.h>
#include<stdlib.h>

/***************************GRAPH CREATION*******************************/

typedef struct Node
{
    int data;
    struct Node* next; 
}node;

typedef struct Graph
{
    int nov;
    node **adj;
    int* visited;
}graph;

node *createnode(int d)
{
    node *new=(node*)malloc(sizeof(node));
    new->data=d;
    new->next=NULL;

    return new;
}

void makeedge(graph* G, int s, int d) {
    //making an edge from source s to destination d
    node* newNode = createnode(d);
    newNode->next = G->adj[s];
    G->adj[s] = newNode;
}

graph* creategraph(graph *G,FILE *inp)
{
    node *temp;
    int n,e;
    int i,j,value;
    fscanf(inp,"%d",&n);
    fscanf(inp,"%d",&e);
    G->nov=n;
    G->adj=(node **)malloc(n*sizeof(node *));
    G->visited = (int*)malloc((G->nov)* sizeof(int));

    for (i = 0; i<n; i++)
    {
        G->adj[i] = NULL;
        G->visited[i]=0;
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fscanf(inp,"%d",&value);
            if(value!=0)
            {
                makeedge(G,i,j);
            }
        }
    }
    return G;
}

void printgraph(graph *G,FILE *out)
{
    fprintf(out,"Representation of graph using adjacency list:\n");
    int i,j;
    for(i=0;i<(G->nov);i++)
    {
        fprintf(out,"%d",i);
        node *temp=G->adj[i];
        while(temp)
        {
            fprintf(out,"->%d",temp->data);
            temp=temp->next;
        }
        fprintf(out,"\n");
    }
    fprintf(out,"\n");
}

/**************************GRAPH CREATION ENDS****************************/

//DFS visit
void DFS_visit(graph* G, int vertex,int ignore,FILE *out)
{
    G->visited[vertex] = 1;

    node* temp =G->adj[vertex];
    while (temp != NULL) {
        int adjacent = temp->data;
        if (!G->visited[adjacent] && adjacent!=ignore) {
            DFS_visit(G,adjacent,ignore,out);
        }
        temp=temp->next;
    }
}

//DFS Traversal
void articulation_point(graph* G,FILE *out) {
    int count=0;
    for(int i=0;i<G->nov;i++)
    {
        count=0;
        for(int k=0;k<G->nov;k++)
        {G->visited[k]=0;}
        for(int j=0;j<G->nov;j++)
        {
            if(G->visited[j]==0 && i!=j)
            {
                count++;
                DFS_visit(G,j,i,out);
            }
        }
        if(count>1)
        fprintf(out,"%d ",i);
    }
}

int main(){

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_ap.txt","w");

    graph *G=(graph *)malloc(sizeof(graph));
    G=creategraph(G,inp);
    printgraph(G,out);

    fprintf(out,"Articulation point(s) is/are: ");
    articulation_point(G,out);

    fclose(out);
    fclose(inp);

    return 0;
}
