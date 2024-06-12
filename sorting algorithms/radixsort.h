//radix sort

void countingsort(int arr[],int size,int exponent)
{   
    //finding max element
    int max=(arr[0]/exponent)%10;
    int i;
    for(i=1;i<size;i++)
    {
        if(((arr[i]/exponent)%10)>max)
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
        count[(arr[i]/exponent)%10]++;
    }

    //preparing cummulative array
    for(i=1;i<10;i++)
    {
        count[i]=count[i]+count[i-1];
    }

    //defining a temporary array to store sorted array
    int temp[size];

    for(i=size-1;i>=0;i--)
    {
        temp[count[(arr[i]/exponent)%10]-1]=arr[i];   
        count[(arr[i]/exponent)%10]--;
    }

    //copying all elements of temp array to original array
    for(i=0;i<size;i++)
    {
        arr[i]=temp[i];
    }
}

void radix_sort(int arr[],int size)
{
    //finding max element
    int max=arr[0];
    int i;
    for(i=0;i<size;i++)
    {
        if(arr[i]>max)
        max=arr[i];
    }

    //exponent indicates the power of 10
    for(int exponent=1;max/exponent>0;exponent=exponent*10)
    {
        countingsort(arr,size,exponent);
    }
}
