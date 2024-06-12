//program to determine minimum spanning tree using kruskals algorithm

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
    int source;
    int destination;
    int weight;
}edge;

typedef struct 
{
    int nov;
    int noe;
    edge *edges;
}graph;

void creategraph(graph *G, FILE *inp){

    fscanf(inp,"%d",&(G->nov));
    fscanf(inp,"%d",&(G->noe));

    G->edges=(edge*)malloc(G->noe*sizeof(edge));

    int temp;
    int edgecount=0;
    for(int i=0;i<G->nov;i++)
    {
        for(int j=0;j<G->nov;j++)
        {
            fscanf(inp,"%d",&temp);
            if(temp!=0)
            {
                G->edges[edgecount].source=i;
                G->edges[edgecount].destination=j;
                G->edges[edgecount].weight=temp;
                edgecount++;
            }
        }
    }
}

void printgraph(graph *G, FILE *out)
{
    fprintf(out,"Given graph contains edges:\n");
    for(int i=0;i<G->noe;i++)
    {
        fprintf(out,"(%d %d), ",G->edges[i].source,G->edges[i].destination);
    }
    fprintf(out,"\n\n");
}

void printMST(int *included,graph *G,FILE *out)
{
    fprintf(out,"Edges included in MST of given graph are:\n");
    
    int sum=0;
    for(int i=0;i<G->noe;i++)
    {
        if(included[i]==1){
            fprintf(out,"(%d %d) of weight %d\n",G->edges[i].source,G->edges[i].destination,G->edges[i].weight);
            sum+=G->edges[i].weight;
        }
    }
    fprintf(out,"Total min weight= %d", sum);
}

//to find the parent of a vertex (used in disjoint set)
int findParent(int* parent, int vertex) {
    if (parent[vertex] == -1)
        return vertex;
    return findParent(parent, parent[vertex]);
}

//to perform union of two sets (used in disjoint set)
void unionSets(int* parent, int vertex1, int vertex2) {
    int parent1 = findParent(parent, vertex1);
    int parent2 = findParent(parent, vertex2);
    parent[parent1] = parent2;
}

//to sort edges according to weights in increasing order
void sort_edges(graph *G)
{
	int i,j;
    edge temp;
	for(i=0;i<G->noe-1;i++)
	{
		for(j=0;j<G->noe-i-1;j++)
		{
			if(G->edges[j].weight>G->edges[j+1].weight)
			{
				temp=G->edges[j];
                G->edges[j]=G->edges[j+1];
                G->edges[j+1]=temp;
			}
		}
	}
}


void find_MST_kruskals(graph *G,FILE *out)
{
    int included[G->noe]; //to keep track of edges included in MST corresponding to edges array
    int parent[G->nov]; //to keep track of parent

    sort_edges(G);
    
    //initialize parent array
    for (int i=0;i<G->nov;i++)
        parent[i] = -1;
    //initially no edge is contained in MST
    for (int i=0;i<G->noe;i++)
        included[i] = 0;
    
    int i = 0;
    //inlcuding the egde w minimum weight
    included[i]=1;

    for(i=1;i<G->noe;i++)
    {
        int sourceParent = findParent(parent, G->edges[i].source);
        int destinationParent = findParent(parent, G->edges[i].destination);

        //if including this edge does not create a cycle, include it in MST
        if (sourceParent != destinationParent) {
            included[i]=1;
            unionSets(parent, sourceParent, destinationParent);
        }
    }
    printMST(included,G,out);
}

int main()
{
    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_kruskals.txt","w");

    graph G;
    creategraph(&G,inp);
    printgraph(&G,out);
    find_MST_kruskals(&G,out);

    return 0;
}