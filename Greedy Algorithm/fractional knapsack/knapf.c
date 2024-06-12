#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int value;
	int weight;
	float ratio;
}item;

int getmax_ratio(item *items,int noi)
{
	int i;
	int max=0;
	for(i=1;i<=noi;i++)
	{
		if(items[i].ratio>items[max].ratio)
		{max=i;}
	}
	return max;
}

//main function for fractional knapsack
void fractional_knapsack(item *items,int noi,float maxw,FILE *out)
{
	float max_value=0;
	
	fprintf(out,"Items to be picked are:\n");
	
	int pick;
	while(maxw>0)
	{
		pick=getmax_ratio(items,noi);
		if(maxw>=items[pick].weight)
		{
			fprintf(out,"1 whole item no.%d\n",pick);
			maxw=maxw-items[pick].weight;
			max_value+=items[pick].value;
			items[pick].ratio=0;
		}
		
		else
		{
			fprintf(out,"Fraction of item no.%d\n",pick);
			max_value+=maxw*(items[pick].ratio);
			maxw=0;
		}
	}
		
	fprintf(out,"Maximum value of knapsack is %f\n",max_value);
	
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
items[0].ratio=0;

for(i=1;i<=noi;i++)
{
	fscanf(inp,"%d",&(items[i].value));
	fscanf(inp,"%d",&(items[i].weight));
	items[i].ratio=	(items[i].value)/(items[i].weight);
}

fractional_knapsack(items,noi,maxw,out);

fclose(inp);
fclose(out);

return 0;
}




