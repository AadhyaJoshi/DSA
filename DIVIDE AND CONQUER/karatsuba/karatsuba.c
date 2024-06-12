//karatsuba's algorithm for large integer multiplication

#include<stdio.h>
#include<math.h>

int sizeofnum(int num)
{
    int count=0;

    while(num>0)
    {
        count++;
        num=num/10;
    }
    return count;
}

long long karatsuba(long int num1,long int num2)
{
    if(num1<10 || num2<10) return num1*num2;
    
    int n;

	if(sizeofnum(num1)>sizeofnum(num2)) 
	n=sizeofnum(num1);
	
	else
  	n=sizeofnum(num2);

    n=n/2;
    long long power=pow(10,n);
    long long a= num1/power;
    long long c= num2/power;
    long long b= num1%power;
    long long d= num2%power;

    long long ac= karatsuba(a,c);
    long long bd= karatsuba(b,d);
    long long e= karatsuba(a+b,c+d)-ac-bd;

    long long res= (long long)pow(10,2*n)*ac + (long long)pow(10,n)*e +bd;
    return res;
    
}

int main(){

    long long num1,num2,res;

    FILE* inp=fopen("input.txt","r");
    FILE* out=fopen("output.txt","w");

    fscanf(inp,"%lld",&num1);
    fscanf(inp,"%lld",&num2);

    res=karatsuba(num1,num2);
    fprintf(out,"%lld",res);

    fclose(inp);
    fclose(out);

    return 0;
}
