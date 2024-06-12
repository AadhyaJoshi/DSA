//0-1 knapsack problem using dynamic programming

#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int value;
	int weight;
}item;

//main function for knapsack
void knapsack(item *items,int noi,int maxw,FILE *out)
{
	int matrix[noi+1][maxw+1];
	int keep[noi+1][maxw+1];
	int i,j;
	
	for(i=0;i<=noi;i++)
	{
		for(j=0;j<=maxw;j++)
		{
			matrix[i][j]=0;
			keep[i][j]=0;
		}
	}
	
	for(i=1;i<=noi;i++)
	{
		for(j=1;j<=maxw;j++)
		{
			if(j>=items[i].weight)
			{
				if(matrix[i-1][j]>(items[i].value + matrix[i-1][(j-items[i].weight)]))
				{matrix[i][j]=matrix[i-1][j];}
			
				else
				{
					matrix[i][j]=(items[i].value + matrix[i-1][(j-items[i].weight)]);
					keep[i][j]=1;
				}
			}
		}
	}
	
	/*for(i=0;i<=noi;i++)
	{
		for(j=0;j<=maxw;j++)
		{
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}*/
	
	fprintf(out,"Maximum value of knapsack is %d\n",matrix[noi][maxw]);
	fprintf(out,"Items to be picked are: ");
	
	int k=maxw;
	for(i=noi;i>=1;i--)
	{
		if(keep[i][k]==1)
		{
			fprintf(out,"%d ",i);
			k=k-items[i].weight;
		}
	}
	
}


int main(){

int i;

FILE *inp=fopen("input.txt","r");
FILE *out=fopen("output.txt","w");

int noi;	//number of items
fscanf(inp,"%d",&noi);

int maxw;	//maximum weight of knapsack
fscanf(inp,"%d",&maxw);

item *items=(item*)malloc((noi+1)*sizeof(item));
items[0].value=0;
items[0].weight=0;

for(i=1;i<=noi;i++)
{
	fscanf(inp,"%d",&(items[i].value));
	fscanf(inp,"%d",&(items[i].weight));	
}

knapsack(items,noi,maxw,out);

fclose(inp);
fclose(out);

return 0;
}




