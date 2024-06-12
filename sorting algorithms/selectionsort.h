//function for performing selection sort

void selectionsort(int a[],int n)
{
	int i,j,min=0;
	for(i=0;i<n;i++)
	{
		int min=i;
		for(j=i+1;j<n;j++)
		{
			if(a[j]<a[min])
			{
				min=j;
				swap(&a[i],&a[min]);
			}
		}
	}
}
