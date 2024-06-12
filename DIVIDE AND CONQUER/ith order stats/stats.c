//ith order stats for a given array

#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

int partition_random(int arr[],int low,int high)
{	
    int randind=(rand() % (high-low+1))+low;
	int pivot=arr[randind];
	swap(&arr[randind],&arr[high]);
	int j,i=-1;
	
	for(j=0;j<high;j++)
	{
		if(arr[j]<=pivot)
		{
			i++;
			swap(&arr[j],&arr[i]);
		}
	}
	swap(&arr[i+1],&arr[high]);
	return i+1;		
}

int randomised_select(int *arr,int low,int high,int i)
{
    if(low==high) return arr[low];

    int q=partition_random(arr,low,high);
    int k=q-low+1;

    if(i==k) return arr[q];
    else if(i<k) return randomised_select(arr,low,q-1,i);
    else return randomised_select(arr,q+1,high,i-k);
}

int main(){

    FILE* inp=fopen("input.txt","r");
    FILE* out=fopen("output.txt","w");

    if(out==NULL || inp==NULL)
    	{
        printf("Cannot open file!");
        return 0;
    	}
	
	int size;
	fscanf(inp,"%d",&size);
	int *arr=(int *)malloc(size*sizeof(int));

    int i;
    fscanf(inp,"%d",&i);

	int n=0;
    while(fscanf(inp,"%d",&arr[n])!=EOF)
    {n++;}

    int res=randomised_select(arr,0,size-1,i);

    fprintf(out,"%dth smallest element is %d\n",i,res);
    fclose(inp);
    fclose(out);
}