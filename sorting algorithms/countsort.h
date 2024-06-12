//counting sort

#include<stdlib.h>

void counting_sort(int arr[],int size)
{
    //finding max element
    int max=arr[0];
    int i;
    for(i=0;i<size;i++)
    {
        if(arr[i]>max)
        max=arr[i];
    }

    //preparing frequency array
    int *count=(int *)malloc((max+1)*sizeof(int));
    for(i=0;i<max+1;i++)
    {
        count[i]=0;
    }

    for(i=0;i<size;i++)
    {
        count[arr[i]]++;
    }

    //preparing cummulative array
    for(i=1;i<max+1;i++)
    {
        count[i]=count[i]+count[i-1];
    }

    //defining a temporary array to store sorted array
    int temp[size];

    for(i=size-1;i>=0;i--)
    {
        if(count[arr[i]]!=0)
        {
            count[arr[i]]--;
            temp[count[arr[i]]]=arr[i];
        }
        
    }

    //copying all elements of temp array to original array
    for(i=0;i<size;i++)
    {
        arr[i]=temp[i];
    }
}
