//longest increasing subsequence in an array

#include<stdio.h>
#include<stdlib.h>

void find_LIS(int *arr,int size,FILE *out)
{
    int lis[size];
    int keep[size];

    for(int i=0;i<size;i++)
    {
        lis[i]=1;
        keep[i]=0;
    }

    for(int i=1;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {keep[k]=0;}

        keep[i]=1;
        for(int j=0;j<i;j++)
        {
            if(arr[i]>arr[j] && lis[i]<lis[j]+1)
            {
                lis[i]=lis[j]+1;
                keep[j]=1;
            }
        }
    }

    if(arr[0]>arr[1])
    {
        keep[0]=0;
        keep[1]=1;
    }

    fprintf(out,"Longest increasing subsequence of the given array is of %d elements\n",lis[size-1]);
    fprintf(out,"Elements are: ");
    for(int i=0;i<size;i++)
    {
        if(keep[i]==1)
        fprintf(out,"%d ",arr[i]);
    }
}

int main()
{
    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output.txt","w");

    int size;
    fscanf(inp,"%d",&size);
    int arr[size];

    int i=0;
    while(fscanf(inp,"%d",&arr[i])!=EOF)
    {i++;}

    find_LIS(arr,size,out);

    fclose(inp);
    fclose(out);
    return 0;
}