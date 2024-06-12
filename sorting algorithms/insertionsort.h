//function for performing insertion sort
void insertionsort(int a[],int n)
{
	int i,j,key;
	for(i=1;i<n;i++)
	{
		key=a[i];
		j=i-1;
		while(a[j]>key && j>=0)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=key;
	}
}
