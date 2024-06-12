//merging k sorted arrays

#include<stdio.h>
#include<stdlib.h>

//print array function
void printarray(FILE *out,int *arr,int size)
{
	for(int i=0;i<size;i++)
	{fprintf(out,"%d ",arr[i]);}
	fprintf(out,"\n");
}

//making a structure of array input as k arrays
typedef struct Array{
    int size;
    int *ptr;
}array;

//merging 2 arrays at a time
int* merge(int *a,int *b,int s1,int s2)
{
    int *res=(int *)malloc((s1+s2)*sizeof(int));

    int i=0; //index of a array
    int j=0; //index of b array
    int k=0; //index of res array

    while(i<s1 && j<s2)
    {
        if(a[i]<b[j])
        {
            res[k]=a[i];
            i++;
        }

        else{
            res[k]=b[j];
            j++;
        }
        k++;
    }

    while(i<s1)
    {
        res[k]=a[i];
        i++;
        k++;
    }

    while(j<s2)
    {
        res[k]=b[j];
        j++;
        k++;
    }

    return res;
}

int main(){

    int num;

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output.txt","w");

    fprintf(out,"Merging k sorted arrays, final array is:\n");

	if(out==NULL || inp==NULL)
    	{
        printf("Cannot open file!");
        return 0;
    	}

    //taking input from file for k i.e. the number of sorted arrays
    fscanf(inp,"%d",&num);
    //creating k number of structures, each having a size and ptr to an array
    array list[num];

    for(int i=0;i<num;i++)
    {   
        fscanf(inp,"%d",&list[i].size);

        list[i].ptr=(int *)malloc((list[i].size)*sizeof(int));

        for(int j=0;j<list[i].size;j++)
        {
            fscanf(inp,"%d",&list[i].ptr[j]);
        }
    }

    int *res;
    int sumsize=0;

    res=merge(list[0].ptr,list[1].ptr,list[0].size,list[1].size);
    sumsize=list[0].size+list[1].size;

    for(int l=2;l<num;l++)
    {
        int *temp=merge(list[l].ptr,res,list[l].size,sumsize);
        res=temp;
        sumsize=sumsize+list[l].size;
    }

    printarray(out,res,sumsize);

    fclose(inp);
    fclose(out);

    return 0;
}
