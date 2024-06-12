//this algorithm is applicable for solving shortest path problems having negative weights as well

#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef struct Node
{
    int data;
    struct Node* next; 
}node;

typedef struct Edge {
    int source;
    int destination;
    int weight;
}defedge;

typedef struct Graph {
    int nov;
    int noe;
    defedge* edge;
    node **adj;
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
    G->edge=(defedge *)malloc(e*sizeof(defedge));

    int edge_count=0;
    for (i = 0; i<n; i++)
    {
        G->adj[i] = NULL;
    }

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
                G->edge[edge_count].weight=value;
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

void print_distance(int dist[], int V,FILE *out) 
{
    fprintf(out,"Vertex   Min distance from source\n");
    
    for (int i = 0; i < V; i++) {
        if (dist[i] == __INT_MAX__)
            fprintf(out,"%d \t\t INFINITY\n", i);
        else
            fprintf(out,"%d \t\t %d\n", i, dist[i]);
    }
}

void relax(int *parent,int *dist,int u,int v,int w)
{
    if (dist[u] != __INT_MAX__ && dist[u] + w < dist[v])
    {
        dist[v] = dist[u] + w;
        parent[v]=u;
    }   
}

// Bellman-Ford algorithm
void Bellman_Ford(graph *G, int source,FILE *out) {
    int V = G->nov;
    int E = G->noe;
    int dist[V];
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = __INT_MAX__;
        parent[i]=-1;
    }
        
    dist[source] = 0;
    parent[source]=-1;

    for (int i = 1; i <= G->nov - 1; i++) 
    {
        for(int j=0;j<E;j++) 
        {
            int u = G->edge[j].source;
            int v = G->edge[j].destination;
            int w = G->edge[j].weight;
            relax(parent,dist,u,v,w);
        }
    }

    //condition for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = G->edge[i].source;
        int v = G->edge[i].destination;
        int w = G->edge[i].weight;
        if (dist[u] + w < dist[v]) 
        {
            fprintf(out,"Graph contains negative-weight cycle\n");
            return;
        }
    }
    print_distance(dist,V,out);
}

int main() {

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_BF.txt","w");

    graph *G=(graph *)malloc(sizeof(graph));
    G=creategraph(G,inp);
    printgraph(G,out);

    int source;
    fscanf(inp,"%d",&source);
    Bellman_Ford(G,source,out);

    fclose(out);
    fclose(inp);

    return 0;
}