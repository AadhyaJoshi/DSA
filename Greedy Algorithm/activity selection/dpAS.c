#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int act_number;
	int start;
	int end;
}activity;

typedef struct{
    int count;
    int finish;
    activity** activities;
}list;

void sortActivityList(activity *acts,int noa)
{
	int i,j;
	activity temp;
	for(i=0;i<noa;i++)
	{
		for(j=0;j<noa-i-1;j++)
		{
			if(acts[j].start>=acts[j+1].start)
			{
				temp=acts[j];
				acts[j]=acts[j+1];
				acts[j+1]=temp;
			}
		}
	}
}

//main function for activity selection using dynamic programming
void dpActivitySelection(activity *acts,int noa,FILE *out)
{
	sortActivityList(acts,noa);
	int i;
	
    list* answer[noa];
    for(i=0;i<noa;i++)
    {
        answer[i]=(list*)malloc(sizeof(list));
        answer[i]->activities = (activity**)malloc(noa*sizeof(activity*));
        for(int j=0;j<noa;j++)
        {
           answer[i]->activities[j]=(activity*)malloc(sizeof(activity));
        }
        answer[i]->count = 0;
        answer[i]->finish = 0;
    }

    for(i=0;i<noa;i++)
    {
        int index = 0;
        for(int j=0;j<i;j++)
        {
            if(answer[j]->finish <= acts[i].start && answer[j]->count > answer[i]->count)
            {
                answer[i] = answer[j];
                index = answer[j]->count;
            }
        }
        answer[i]->count++;
        answer[i]->activities[index]->start = acts[i].start;
        answer[i]->activities[index]->end = acts[i].end;
        answer[i]->activities[index]->act_number = acts[i].act_number;
        answer[i]->finish = acts[i].end;

    }

    int max=0;
    int max_index=0;
    for (int i=0;i<noa;i++) 
    {
        if (answer[i]->count>max) 
        {
            max = answer[i]->count;
            max_index=i;
        }
    }

    fprintf(out,"Max number of activities: %d\n",max);
    	
	fprintf(out,"Activities to be selected are:\n");
    
    for(int i=0;i<max;i++)
    {
        fprintf(out,"Activity %d (Timings: %d-%d)\n",answer[max_index]->activities[i]->act_number,answer[max_index]->activities[i]->start,answer[max_index]->activities[i]->end);
    }
}


int main(){

int i;

FILE *inp=fopen("input.txt","r");
FILE *out=fopen("output_dp.txt","w");

int noa;	//number of activities
fscanf(inp,"%d",&noa);

activity *acts=(activity*)malloc((noa)*sizeof(activity));

for(i=0;i<noa;i++)
{
	fscanf(inp,"%d",&(acts[i].act_number));
	fscanf(inp,"%d",&(acts[i].start));
	fscanf(inp,"%d",&(acts[i].end));
}

dpActivitySelection(acts,noa,out);

fclose(inp);
fclose(out);

return 0;
}

