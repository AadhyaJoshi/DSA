#include<stdio.h>
#include<stdlib.h>

int time=0;

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
    int *finish;
    int *start;
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
    int n;
    int i,j,value;
    fscanf(inp,"%d",&n);
    G->nov=n;
    G->adj=(node **)malloc(n*sizeof(node *));
    G->visited = (int*)malloc((G->nov)* sizeof(int));
    G->finish = (int*)malloc((G->nov)* sizeof(int));
    G->start = (int*)malloc((G->nov)* sizeof(int));

    for (i = 0; i<n; i++)
    {
        G->adj[i] = NULL;
        G->visited[i]=0;
        G->finish[i]=0;
        G->start[i]=0; 
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

graph * transposegraph(graph * G){

    int i,t;
    node *new;

    graph *trans=(graph*)malloc(sizeof(graph));
    trans->nov=G->nov;
    trans->adj=(node **)malloc((trans->nov)*sizeof(node *));
    trans->visited = (int*)malloc((trans->nov)* sizeof(int));
    trans->finish = (int*)malloc((trans->nov)* sizeof(int));
    trans->start = (int*)malloc((trans->nov)* sizeof(int));

    for (i=0; i<trans->nov; i++)
    {
        trans->adj[i] = NULL;
        trans->visited[i]=0;
        trans->finish[i]=0;
        trans->start[i]=0;
    }

    for(i=0;i<G->nov;i++){
        node * temp=G->adj[i];

        while(temp)
        {
            t=temp->data;
            new=createnode(i);
            makeedge(trans,t,i);
            temp=temp->next;
        }
    }

    return trans;
    
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
void DFS_visit(graph* G, int vertex,FILE *out)
{
    G->visited[vertex] = 1;
    fprintf(out,"%d ", vertex);
    time++;
    G->start[vertex]=time;

    node* temp =G->adj[vertex];
    while (temp != NULL) {
        int adjacent = temp->data;
        if (!G->visited[adjacent]) {
            DFS_visit(G,adjacent,out);
        }
        temp=temp->next;
    }
    time++;
    G->finish[vertex] = time;
}

//DFS Traversal
void DFS(graph* G,FILE *out) {
    for(int i=0;i<G->nov;i++)
    {
        if(G->visited[i]==0)
        {
            DFS_visit(G,i,out);
        }
    }
    fprintf(out,"\n");
}

int max_finish(graph *G)
{
    int max=0;
    int i;
    for(i=0;i<G->nov;i++)
    {
        if(G->finish[i] > G->finish[max])
            max=i;
    }
    G->finish[max] = 0;
    return max;
}

void DFS_transpose(graph *G,FILE *out)
{
    int i,max=0;
    graph *trans=transposegraph(G);
    printgraph(trans,out);

    fprintf(out,"Strongly connected components are:\n");

    for(i=0;i<G->nov;i++)
    {
        int max = max_finish(G);

        if(trans->visited[max]==0){
        DFS_visit(trans,max,out);
        fprintf(out,"\n");
        G->finish[max]=0;
    }
    }
}

void strongly_connected(graph* G,FILE *out)
{
    fprintf(out,"DFS on graph:\n");
    DFS(G,out);
    fprintf(out,"\n");

    fprintf(out,"Transpose ");
    DFS_transpose(G,out);
}

int main(){

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_scc.txt","w");

    graph *G=(graph *)malloc(sizeof(graph));
    G=creategraph(G,inp);
    printgraph(G,out);

    strongly_connected(G,out);

    fclose(out);
    fclose(inp);

    return 0;
}
