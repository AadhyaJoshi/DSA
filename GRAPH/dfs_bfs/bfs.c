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

    newNode = createnode(s);
    newNode->next = G->adj[d];
    G->adj[d] = newNode;
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

//BFS Tarversal
void BFS(graph* G, int startv,FILE *out) {
    // Creating a queue for BFS
    int* queue = (int*)malloc(G->nov * sizeof(int));
    int front = 0, rear = 0;

    //Initially mark the starting vertex as visited and enqueue it
    G->visited[startv] = 1;
    queue[rear++] = startv;

    while (front < rear) {
        int now = queue[front++];
        fprintf(out,"%d->", now);

        //exploring all adjacent vertices of the current vertex
        node* temp = G->adj[now];
        while (temp != NULL) {
            int adjacent = temp->data;
            if (!G->visited[adjacent]) 
            {
                G->visited[adjacent] = 1;
                queue[rear++] = adjacent;
            }
            temp = temp->next;
        }
    }
    free(queue);
}


int main(){

    FILE *inp=fopen("input_dfs_bfs.txt","r");
    FILE *out=fopen("output_bfs.txt","w");

    graph *G=(graph *)malloc(sizeof(graph));
    G=creategraph(G,inp);
    printgraph(G,out);

    fprintf(out,"BFS on graph (starting from vertex 0):\n");
    BFS(G,0,out);

    fclose(out);
    fclose(inp);

    return 0;
}
