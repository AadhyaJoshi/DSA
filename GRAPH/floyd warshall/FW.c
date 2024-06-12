#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node;

typedef struct graph
{
    int nov;
    node **adj;
    int **weight;
} graph;

node *createNode(int d)
{
    node *p = (node *)malloc(sizeof(node));
    p->data = d;
    p->next = NULL;
    return p;
}

void insertNode(node *s, node *p)
{
    node *temp = s;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = p;
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

void createGraph(graph *g, FILE *inp, FILE * out)
{
    fscanf(inp, "%d", &g->nov);
    g->adj = (node **)malloc((g->nov) * sizeof(node *));
    g->weight = (int **)malloc((g->nov) * sizeof(int *));
    int i, j, temp;
    for (i = 0; i < g->nov; i++)
    {
        g->weight[i] = (int *)malloc((g->nov) * sizeof(int));
    }
    node *t;
    for (i = 0; i < g->nov; i++)
    {
        t = createNode(i);
        g->adj[i] = t;
    }

    for (i = 0; i < g->nov; i++)
    {
        for (j = 0; j < g->nov; j++)
        {
            fscanf(inp, "%d", &temp);
            if (temp != 0)
            {
                g->weight[i][j] = temp;
                t = createNode(j);
                insertNode(g->adj[i], t);
            }
            else if (i != j && temp == 0)
            {
                g->weight[i][j] = 10000;
            }
            else
            {
                g->weight[i][j] = 0;
            }
        }
    }
    printgraph(g,out);
    
}

void FW(graph *g, FILE *inp, FILE *out)
{
    int current[g->nov][g->nov];
    int previous[g->nov][g->nov];
    int parent[g->nov][g->nov];
    int i, j, k;
    for (i = 0; i < g->nov; i++)
    {
        for (j = 0; j < g->nov; j++)
        {
            current[i][j] = 10000;
            previous[i][j] = g->weight[i][j];
            if(g->weight[i][j] != 10000 && g->weight[i][j] != 0)
            {
                parent[i][j] = i;
            }
            else parent[i][j] = 0;
        }
    }
    for (k = 0; k < g->nov; k++)
    {
        for (i = 0; i < g->nov; i++)
        {
            for (j = 0; j < g->nov; j++)
            {
                if (previous[i][j] > previous[i][k] + previous[k][j])
                {
                    current[i][j] = previous[i][k] + previous[k][j];
                    parent[i][j] = k;
                }
                else
                {
                    current[i][j] = previous[i][j];
                }
            }
        }
      
        for (i = 0; i < g->nov; i++)
        {
            for (j = 0; j < g->nov; j++)
            {
                previous[i][j] = current[i][j];
                current[i][j] = 10000;
            }
        }
    }

    fprintf(out,"The shortest path is :\n");
    for (i = 0; i < g->nov; i++)
    {
        for (j = 0; j < g->nov; j++)
        {
            fprintf(out, "%d ", previous[i][j]);
        }
        fprintf(out, "\n");
    }
    
    fprintf(out,"\nThe shortest path is via:\n");
    for (i = 0; i < g->nov; i++)
    {
        for (j = 0; j < g->nov; j++)
        {
            fprintf(out, "%d ", parent[i][j]);
        }
        fprintf(out, "\n");
    }
}

int main()
{
    FILE *inp = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    graph g;
    createGraph(&g, inp, out);
    FW(&g, inp, out);
    return 0;
}



