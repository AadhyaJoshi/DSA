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
    G->edge=(defedge *)malloc(e*sizeof(defedge));
    G->visited=(int *)malloc(n*sizeof(int));

    int edge_count=0;
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

void relax(int *dist,int u,int v,int w)
{
    if (dist[u] != __INT_MAX__ && dist[u] + w < dist[v])
        dist[v] = dist[u] + w;
}

void Enqueue_priority(int *Q,int *dist,int *front,int *rear,int adjacent)
{
    Q[*rear++] = adjacent;
    int i,j,key;
	for(i=*front+1;i<*rear;i++)
	{
		key=dist[i];
		j=i-1;
		while(dist[Q[j]]>key && j>=0)
		{
			Q[j+1]=Q[j];
			j--;
		}
		Q[j+1]=key;
	}
}

void Dijkstra(graph *G, int source, FILE *out)
{
    int V = G->nov;
    int E = G->noe;
    int dist[V];
    int *Q=(int *)malloc(G->nov*sizeof(int));
    int front=0,rear=0;

    for (int i = 0; i < V; i++)
    {
        dist[i] = __INT_MAX__;
    }
    dist[source] = 0;

    Q[rear++]=source;

    while (front < rear) {
        int now = Q[front++];
        //fprintf(out,"%d->", now);

        //exploring all adjacent vertices of the current vertex
        node* temp = G->adj[now];
        while (temp != NULL) 
        {
            int adjacent = temp->data;
            //fprintf(out,"%d ", adjacent);
            if (!G->visited[adjacent]) 
            {
                G->visited[adjacent] = 1;
                for(int j=0;j<E;j++)
                {
                    if(G->edge[j].source==now && G->edge[j].destination==adjacent)
                    {
                        //fprintf(out,"%d ",G->edge[j].weight);
                        relax(dist,now,adjacent,G->edge[j].weight);
                        Enqueue_priority(Q,dist,&front,&rear,adjacent);
                        //fprintf(out,"%d ",Q[front]);
                        break;
                    }
                }
                //Q[rear++] = adjacent;
            }
            temp = temp->next;
        }
    }
    free(Q);
    print_distance(dist,V,out);
}

int main(){

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_dj.txt","w");

    graph *G=(graph *)malloc(sizeof(graph));
    G=creategraph(G,inp);
    printgraph(G,out);

    int source;
    fscanf(inp,"%d",&source);
    Dijkstra(G,source,out);

    fclose(out);
    fclose(inp);

    return 0;
}
