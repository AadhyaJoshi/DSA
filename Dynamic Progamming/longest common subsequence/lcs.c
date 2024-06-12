//least common subsequence problem using dynamic programming

#include<stdio.h>
#include<stdlib.h>

void find_LCS(int noc1,int *first,int noc2,int *second,FILE *out)
{
    int i,j,k=0;
    int dp[noc1+1][noc2+1];
    char direction[noc1+1][noc2+1];

    for(i=1;i<=noc1;i++)
    {
    	dp[i][0] = 0;
    	direction[i][0]='n';
    }

    for(i=1;i<=noc2;i++)
    {
    	dp[0][i] = 0;
    	direction[0][i]='n';
    }

    for(i=1;i<=noc1;i++)
    {
        for(j=1;j<=noc2;j++)
        {
            if(first[i]==second[j])
            {
                dp[i][j]=dp[i-1][j-1] + 1;
                direction[i][j]='c';
            }
            else if(dp[i-1][j]>=dp[i][j-1])
            {
                dp[i][j]=dp[i-1][j];
                direction[i][j]='u';
            }
            else{
                dp[i][j]=dp[i][j-1];
                direction[i][j]='s';
            }
        }
    }
    
    fprintf(out,"Longest common subsequence is of %d characters\n",dp[noc1][noc2]);
    /*for(i=1;i<=noc1;i++)
    {
        for(j=1;j<=noc2;j++)
        {
        	fprintf(out,"%d ",dp[i][j]);
        }
        fprintf(out,"\n");
     }*/
    
    fprintf(out,"Subsequence is: ");
    i=noc1;
    j=noc2;
    
    while(i!=0 && j!=0)
    {
    	if(direction[i][j]=='c')
    	{
    		fprintf(out,"%d",first[i]);
            i=i-1;
    		j=j-1;
    	}
    	
    	else if(direction[i][j]=='u')
    	{i=i-1;}
    	
    	else
    	{j=j-1;}	
    }
   
}

int main(){

int i;

FILE *inp=fopen("input.txt","r");
FILE *out=fopen("output.txt","w");

int noc1;	//number of characters in first sequence
fscanf(inp,"%d",&noc1);

int first[noc1+1];
for(i=1;i<=noc1;i++)
{
	fscanf(inp,"%d",&first[i]);
}

int noc2;	//number of characters in second sequence
fscanf(inp,"%d",&noc2);

int second[noc2+1];
for(i=1;i<=noc2;i++)
{
	fscanf(inp,"%d",&second[i]);
}

find_LCS(noc1,first,noc2,second,out);

fclose(inp);
fclose(out);

return 0;
}


