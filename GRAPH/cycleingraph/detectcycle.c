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
        G->visited[i]=-1;
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
int cyclecount=0;
void DFS_visit(graph* G, int vertex,FILE *out)
{
    G->visited[vertex] = 0;
    //fprintf(out,"%d ", vertex);
    time++;
    G->start[vertex]=time;

    node* temp =G->adj[vertex];
    while (temp != NULL) {
        int adjacent = temp->data;
        if (G->visited[adjacent]==-1) {
            DFS_visit(G,adjacent,out);
        }
        else if(G->visited[adjacent]==0){
            cyclecount++;
            break;
        }
        temp=temp->next;
    }
    time++;
    G->finish[vertex] = time;
    G->visited[vertex] = 1;
}

//DFS Traversal
void DFS(graph* G,FILE *out) {
    for(int i=0;i<G->nov;i++)
    {
        if(G->visited[i]==-1)
        {
            DFS_visit(G,i,out);
        }
    }
    if(cyclecount>0)
    fprintf(out,"Cycle present");

    else
    fprintf(out,"Cycle not present");
}

void find_cycles(graph* G,FILE *out)
{
    DFS(G,out);
    fprintf(out,"\n");
}

int main(){

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_cycle.txt","w");

    graph *G=(graph *)malloc(sizeof(graph));
    G=creategraph(G,inp);
    printgraph(G,out);

    find_cycles(G,out);

    fclose(out);
    fclose(inp);

    return 0;
}
