#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int act_number;
	int start;
	int end;
}activity;

void sortActivityList(activity *acts,int noa)
{
	int i,j;
	activity temp;
	for(i=0;i<noa;i++)
	{
		for(j=0;j<noa-i-1;j++)
		{
			if(acts[j].end>=acts[j+1].end)
			{
				temp=acts[j];
				acts[j]=acts[j+1];
				acts[j+1]=temp;
			}
		}
	}
}

//main function for activity selection using greedy approach
void greedyActivitySelection(activity *acts,int noa,FILE *out)
{
	sortActivityList(acts,noa);
	
	fprintf(out,"Activities to be selected are:\n");
	fprintf(out,"Activity %d (Timings: %d-%d)\n",acts[0].act_number,acts[0].start,acts[0].end);
	int current_end=acts[0].end;
	
	int i;
	for(i=0;i<noa;i++)
	{
		if(acts[i].start>=current_end)
		{
			fprintf(out,"Activity %d (Timings: %d-%d)\n",acts[i].act_number,acts[i].start,acts[i].end);
			current_end=acts[i].end;
		}
	}	
}


int main(){

int i;

FILE *inp=fopen("input.txt","r");
FILE *out=fopen("output_Greedy.txt","w");

int noa;	//number of activities
fscanf(inp,"%d",&noa);

activity *acts=(activity*)malloc((noa)*sizeof(activity));

for(i=0;i<noa;i++)
{
	fscanf(inp,"%d",&(acts[i].act_number));
	fscanf(inp,"%d",&(acts[i].start));
	fscanf(inp,"%d",&(acts[i].end));
}

greedyActivitySelection(acts,noa,out);

fclose(inp);
fclose(out);

return 0;
}





