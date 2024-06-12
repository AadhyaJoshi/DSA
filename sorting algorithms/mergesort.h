
//merge sort

void merge(int arr[],int low,int high,int mid)
{
	int size1=mid-low+1;
	int size2=high-mid;
	
	//making 2 temp arrays for copying data by segment and then merging while sorting
	int temp1[size1],temp2[size2];
	int i,j,k;
	
	
	for(i=0;i<size1;i++)
	{
		temp1[i]=arr[low+i];
	}
	
	for(j=0;j<size2;j++)
	{
		temp2[j]=arr[mid+1+j];
	}
	
	
	i=0,j=0,k=low;
	
	while(i<size1 && j<size2)
	{
		if(temp1[i]<=temp2[j])
		{
			arr[k]=temp1[i];
			i++;
		}
		
		else
		{
			arr[k]=temp2[j];
			j++;
		}
		k++;
	}
	
	//copying remaining elements
	while(i<size1)
	{
		arr[k]=temp1[i];
		k++;
		i++;
	}
	
	while(j<size2)
	{
		arr[k]=temp2[j];
		k++;
		j++;
	}
	
}

void merge_sort(int arr[],int low,int high)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		
		merge_sort(arr,low,mid);
		merge_sort(arr,mid+1,high);
		
		merge(arr,low,high,mid);
	}
}

