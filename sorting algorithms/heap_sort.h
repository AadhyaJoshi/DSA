
void insert(int *a,int n)
{
    int i = n;
    int temp = a[i];
    while(i > 1 && temp > a[i/2])
    {
        a[i] = a[i/2];
        i = i/2;
    }
    a[i] = temp;
}

void delet(int *a,int n)
{
    int temp;
    int val = a[1];
    a[1] = a[n];
    a[n] = val;
    int i =1;int j = i*2;

    while(j<n-1)
    {
        if(a[j+1]>a[j])
            j = j+1;
        if(a[i] < a[j])
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i = j;
            j = i*2;
        }
        else
            break;
    }

    return;
}

void Heap_Sort(int n,int *a)
{
    int i;
    for(i=n;i>=0;i--)
    {
        a[i+1] = a[i];
    }
    a[0] = 0;
    
    for(i=2;i<=n;i++)
        insert(a,i);
    
    for(i=n;i>=1;i--)
        delet(a,i);
    return;
}