//all sorting algorithms

#include<stdio.h>
#include "swap.h"
#include "bubblesort.h"
#include "selectionsort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "countsort.h"
#include "radixsort.h"
#include "bucketsort.h"

void printarray(int* arr,int size,FILE *out)
{	
	int i;
	
	for(i=0;i<size;i++)
	{
		fprintf(out,"%d ",arr[i]);
	}
	fprintf(out,"\n");
}

int main(){

    int input,size;

    FILE *inp=fopen("input.txt","r");
    FILE *out=fopen("output.txt","w");

    if(out==NULL || inp==NULL)
    {
        printf("Cannot open file!");
        return 0;
    }

    fscanf(inp,"%d",&size);
	int arr[size];

    int n=0;
    while(fscanf(inp,"%d",&arr[n])!=EOF)
    {n++;}

    while(1)
    {
        printf("Which sorting algorithm would you like to use?\n");
        printf("PRESS 1: Bubble sort\n");
        printf("PRESS 2: Selection sort\n");
        printf("PRESS 3: Insertion sort\n");
        printf("PRESS 4: Quick sort\n");
        printf("PRESS 5: Merge sort\n");
        printf("PRESS 6: Radix sort\n");
        printf("PRESS 7: Bucket sort\n");
        printf("PRESS 8: Count sort\n");
        printf("PRESS 0: To exit\n");
        scanf("%d",&input);

        if(input==0)
        {
            printf("END OF PROGRAM..\n");
            break;
        }

        switch(input)
        {
            case 1:
            bubblesort(arr,size);
            fprintf(out,"Using bubble sort:\n");
            printarray(arr,size,out);
            break;

            case 2:
            selectionsort(arr,size);
            fprintf(out,"Using selection sort:\n");
            printarray(arr,size,out);
            break;

            case 3:
            insertionsort(arr,size);
            fprintf(out,"Using insertion sort:\n");
            printarray(arr,size,out);
            break;

            case 4:
            quick_sort(arr,0,size);
            fprintf(out,"Using quick sort:\n");
            printarray(arr,size,out);
            break;

            case 5:
            merge_sort(arr,0,size);
            fprintf(out,"Using merge sort:\n");
            printarray(arr,size,out);
            break;

            case 6:
            radix_sort(arr,size);
            fprintf(out,"Using radix sort:\n");
            printarray(arr,size,out);
            break;

            case 7:
            bucket_sort(arr,size);
            fprintf(out,"Using bucket sort:\n");
            printarray(arr,size,out);
            break;

            case 8:
            counting_sort(arr,size);
            fprintf(out,"Using count sort:\n");
            printarray(arr,size,out);
            break;

            default:
            printf("Invalid Input, Please enter again.\n");
            break;
        }
    }
    fclose(inp);
    fclose(out);

    return 0;
}