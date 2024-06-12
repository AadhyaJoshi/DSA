//ith order stats for a given array using deterministic selection, and selecting median of medians as pivot

#include<stdio.h>
#include<stdlib.h>

int select(int *,int,int,int);
int median_of_medians(int *,int,int);

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

int insertionsort(int *a,int low,int high)
{
	int i,j,key;
	for(i=low+1;i<=high;i++)
	{
		key=a[i];
		j=i-1;
		while(a[j]>key && j>=low)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=key;
	}
}

/*partition L into subsets S[i] of five elements each
        (there will be n/5 subsets total).

    for (i = 1 to n/5) do
        x[i] = select(S[i],3)

    M = select({x[i]}, n/10)
*/

int median_of_medians(int *arr,int low,int high)
{
	int size=high-low+1;
	int start=low;
	int *b=(int*)malloc(size*sizeof(int));

	for(int i=0;i<size;i++){ b[i]=arr[low+i]; }

	int nog; //number of groups
    if(size % 5 == 0) {nog = size/5;}
    else nog = size/5+1;

	int *medians=(int*)malloc(nog*sizeof(int));
	for(int i=0;i<nog-1;i++)
	{
		medians[i]=select(b,start,start+4,start+3);
		start=start+5;
	}
	medians[nog-1]=select(b,start,high,(high+start)/2+1);

	return select(medians,0,nog-1,size/10+1);
}

int partition_mom(int arr[],int low,int high)
{	
    int median=median_of_medians(arr,low,high);
	int pivot=arr[median];
	swap(&arr[median],&arr[high]);
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

int select(int *arr,int low,int high,int i)
{
    if(high-low+1<=10){
		insertionsort(arr,low,high);
		return arr[i-1];
	}

    int q=partition_mom(arr,low,high);
    int k=q-low+1;

    if(i==k) return arr[q];
    else if(i<k) return select(arr,low,q-1,i);
    else return select(arr,q+1,high,i-k);
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

    int res=select(arr,0,size-1,i);

    fprintf(out,"%dth smallest element is %d\n",i,res);
    fclose(inp);
    fclose(out);
}