//program to determine minimum spanning tree using prims algorithm

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct 
{
    int nov;
    int noe;
    int **weight;
}graph;

void creategraph(graph *G, FILE *inp){

    fscanf(inp,"%d",&(G->nov));
    fscanf(inp,"%d",&(G->noe));
    G->weight=(int **)malloc(G->nov*sizeof(int *));

    for(int i=0;i<G->nov;i++)
    {
        G->weight[i]=(int *)malloc(G->nov*sizeof(int));
    }

    for(int i=0;i<G->nov;i++)
    {
        for(int j=0;j<G->nov;j++)
        {
            fscanf(inp,"%d",&(G->weight[i][j]));
        }
    }
}

void printgraph(graph *G, FILE *out)
{
    fprintf(out,"Given graph is:\n");
    for(int i=0;i<G->nov;i++)
    {
        for(int j=0;j<G->nov;j++)
        {
            fprintf(out,"%d ",(G->weight[i][j]));
        }
        fprintf(out,"\n");
    }
    fprintf(out,"\n");
}

void printMST(int *parent,int *min_weight,graph *G,FILE *out)
{
    fprintf(out,"Edges included in MST of given graph are:\n");
    for(int i=1;i<G->nov;i++)
    {
        fprintf(out,"(%d %d) of weight %d\n",i,parent[i],G->weight[i][parent[i]]);
    }

    int sum=0;
    for(int i=0;i<G->nov;i++)
    {
        sum+=min_weight[i];
    }
    fprintf(out,"Total min weight= %d", sum);
}

int pick_min_adj(int *min_weight,int *included,int nov)
{
    int min_w=INFINITY;
    int min;
 
    for (int i=0;i<nov;i++)
    {
        if (included[i]==0 && min_weight[i]<min_w)
            min_w= min_weight[i],min=i;
    }
 
    return min;
}

void find_MST_prims(graph *G,FILE *out)
{
    int included[G->nov]; //to keep track of vertices included in MST
    int min_weight[G->nov]; //to keep track of min weights associated with a vertex
    int parent[G->nov]; //to track parents in MST

    for(int i=0;i<G->nov;i++)
    {
        min_weight[i]=INFINITY;
        included[i]=0;
    }

    //to select first vertex
    parent[0]=-1;
    min_weight[0]=0;

    for(int i=0;i<G->nov;i++)
    {
        int temp=pick_min_adj(min_weight,included,G->nov);
        included[temp]=1;

        for (int j=0;j<G->nov;j++)
        {
            if (G->weight[i][j]!=0 && included[j]==0 && G->weight[i][j]<min_weight[j])
            {
                parent[j]=i;
                min_weight[j]=G->weight[i][j];
            }
        }
    }
    
    printMST(parent,min_weight,G,out);
}

int main()
{
    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output_prims.txt","w");

    graph G;
    creategraph(&G,inp);
    printgraph(&G,out);
    find_MST_prims(&G,out);

    return 0;
}