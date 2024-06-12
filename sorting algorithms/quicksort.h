//quick sort

int partition(int arr[],int low,int high)
{
	int mid=(low+high)/2;
	
	swap(&arr[mid],&arr[high]);
	
	int pivot=arr[high];
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

void quick_sort(int arr[],int low,int high)
{
	if(low<high)
	{	
		int part=partition(arr,low,high);
	
		quick_sort(arr,low,part-1);
		quick_sort(arr,part+1,high);
	}
	
}
