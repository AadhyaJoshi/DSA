//this sort is similar to insertion sort
//difference is that it inserts an element which is at a gap of n/2 from the start
//it continues till gap=1

void Shellsort(int *arr,int n)
{
    int gap,i,j;

    for(gap=n/2;gap>1;gap/=2)
    {
        for(i=gap;i<n;i++)
        {
            int key=arr[i];
            j=i-gap;

            while(j>0 && arr[j]>key)
            {
                arr[j+gap]=arr[j];
                j=j-gap;
            }
            arr[j+gap]=key;
        }
    }
}