#include<stdio.h>
#include<stdlib.h>

/***************************GRAPH CREATION*******************************/

typedef struct Node
{
    int data;
    struct Node* next; 
}node;

typedef struct Edge {
    int source;
    int destination;
}defedge;

typedef struct Graph {
    int nov;
    int noe;
    defedge* edge;
    node **adj;
    int *visited;
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
    G->noe=e;
    G->adj=(node **)malloc(n*sizeof(node *));
    G->edge=(defedge *)malloc(G->noe*sizeof(defedge));
    G->visited=(int *)malloc(n*sizeof(int));

    for (i = 0; i<n; i++)
    {
        G->adj[i] = NULL;
        G->visited[i]=0;
    }
	
	int edge_count=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fscanf(inp,"%d",&value);
            if(value!=0)
            {
                makeedge(G,i,j);
                G->edge[edge_count].source=i;
                G->edge[edge_count].destination=j;
                edge_count++;
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
void DFS_visit(graph* G, int vertex,defedge ignore,FILE *out)
{
    G->visited[vertex] = 1;
    node* temp =G->adj[vertex];
    while (temp != NULL) 
    {
        int adjacent = temp->data;
        if (!G->visited[adjacent] && ((vertex!=ignore.source || adjacent!=ignore.destination) && (vertex!=ignore.destination || adjacent!=ignore.source))) 
        {
            DFS_visit(G,adjacent,ignore,out);
        }
        temp=temp->next;
    }
}

//DFS Traversal
void detect_bridge(graph* G,FILE *out) {
    int count=0;
    for(int i=0;i<G->noe;i++)
    {
        count=0;
        for(int k=0;k<G->nov;k++)
        {G->visited[k]=0;}
        for(int j=0;j<G->nov;j++)
        {
            if(G->visited[j]==0)
            {
                count++;
                DFS_visit(G,j,G->edge[i],out);
            }
        }
        if(count>1)
        fprintf(out,"%d->%d ",G->edge[i].source,G->edge[i].destination);
    }
}

int main(){

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_b.txt","w");

    graph *G=(graph *)malloc(sizeof(graph));
    G=creategraph(G,inp);
    printgraph(G,out);

    fprintf(out,"Bridges(s) is/are: ");
    detect_bridge(G,out);

    fclose(out);
    fclose(inp);

    return 0;
}






 	
