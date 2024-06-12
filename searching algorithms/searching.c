#include<stdio.h>
#include<stdlib.h>

//sorting for binary and interpolation searches
void insertion_sort(int arr[],int size)
{
	int j,i=0;
	
	for(i=1;i<size;i++)
	{		
		int key=arr[i];
		j=i-1;
		while(key<arr[j] && j>=0)
		{
			arr[j+1]=arr[j];
			j=j-1;
		}
		arr[j+1]=key;
	}
	
}

//linear search
int linear_search(int *arr,int size,int el)
{
    for(int i=0;i<size;i++)
    {
        if(el==arr[i])
        {
            return i;
        }
    }
    return -1;
}

//binary search
int binary_search(int low,int high,int el,int *arr)
{	
	int mid= low+((high-low)/2);
	if(low<high)
	{		
		if(el==arr[mid])
		{
            return mid;
		}
		
		if(el>arr[mid])
		{
			return binary_search(mid+1,high,el,arr);
		}
		
		if(el<arr[mid])
		{	
			return binary_search(low,mid-1,el,arr);
		}
	}

	else
	return -1;
}

//ternary search
int ternary_search(int low,int high,int el,int *arr)
{
	int mid1= low+((high-low)/3);
	int mid2= high-((high-low)/3);
	if(low<high)
	{		
		if(el==arr[mid1]) {return mid1;}

		else if(el==arr[mid2]) {return mid2;}
		
		else if(el<arr[mid1]) {
			high=mid1-1;
			return ternary_search(low,high,el,arr);
			}
		
		else if(el>arr[mid2]) {
			low=mid2+1;
			return ternary_search(low,high,el,arr);
			}

		else {
			low=mid1+1;
			high=mid2-1;
			return ternary_search(low,high,el,arr);
			}
	}

	else
	return -1;
}


void main()
{
	int size,i,x;
	
	FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output.txt","w");

	if(out==NULL || inp==NULL)
    {
        printf("Cannot open file!");
        return;
    }

	fscanf(inp,"%d",&size);
	int *arr=(int *)malloc(size*sizeof(int));

    int el,index;
	fscanf(inp,"%d",&el);

	int n=0;
    while(fscanf(inp,"%d",&arr[n])!=EOF)
    {n++;}

		while(1)
		{
			printf("\n");
			
			printf("Would you like to locate an element?\n");
            printf("PRESS 1: Yes, using linear search\n");
			printf("PRESS 2: Yes, using binary search\n");
            printf("PRESS 3: Yes, using ternary search\n");
			printf("PRESS 0: To exit program\n");
			scanf("%d",&x);
			printf("\n");
			
			if(x==0)
			{
				printf("End of program, have a nice day!\n");
				break;
			}
            printf("\n");
			
            switch(x)
            {

            case 1:
                fprintf(out,"Using linear search,\n");
				index=linear_search(arr,size,el);
				
				if(index==-1)
				fprintf(out,"Element not found\n");
				
				else
				fprintf(out,"Element found at %dth position\n",index+1);
            break;

			case 2:
                insertion_sort(arr,size);
                fprintf(out,"Array is sorted..\n");
				fprintf(out,"Using binary search,\n");
				index=binary_search(0,size-1,el,arr);
				
				if(index==-1)
				fprintf(out,"Element not found\n");
				
				else
				fprintf(out,"Element found at %dth position\n",index+1);
            break;
				
			case 3:
                insertion_sort(arr,size);
                fprintf(out,"Array is sorted..\n");
				fprintf(out,"Using ternary search,\n");
				index=ternary_search(0,size-1,el,arr);
				
				if(index==-1)
				fprintf(out,"Element not found\n");
				
				else
				fprintf(out,"Element found at %dth position\n",index+1);
			break;
			
			default:
			printf("Invalid input, please enter again\n");
            break;	
            }		
		}
	fclose(inp);
    fclose(out);
}