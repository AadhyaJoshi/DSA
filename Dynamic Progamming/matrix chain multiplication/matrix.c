//matrix chain multiplication

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//struct which stores answers to be returned
typedef struct matrixchain{
	int **m;
	int **s;
	int *p;
}mat;

//function for matrix chain multiplication
mat * matrix_chain_mult(mat *answer,int nom)
{
	int i,j,l,k,q;
	
	for(i=1;i<=nom;i++)
	{answer->m[i][i]=0;}
	
	for(l=2;l<=nom;l++)
	{
		for(i=1;i<=(nom-l+1);i++)
		{
			j=i+l-1;
			answer->m[i][j]=INFINITY;
			
			for(k=i;k<=j-1;k++)
			{
				q=answer->m[i][k]+answer->m[k+1][j]+((answer->p[i-1])*(answer->p[k])*(answer->p[j]));
				if(q<answer->m[i][j])
				{
					answer->m[i][j]=q;
					answer->s[i][j]=k;
				}
			}
		}
	}
	
	return answer;
}


int main(){

int i,j,temp;

FILE *inp=fopen("input.txt","r");
FILE *out=fopen("output.txt","w");

int nom;	//number of matrices
fscanf(inp,"%d",&nom);

//memory allocation of struct
mat *answer=(mat*)malloc(sizeof(mat));

answer->m=(int **)malloc((nom+1)*sizeof(int *));
for(i=0;i<nom+1;i++)
{answer->m[i]=(int *)malloc((nom+1)*sizeof(int));}

answer->s=(int **)malloc((nom+1)*sizeof(int *));
for(i=0;i<nom+1;i++)
{answer->s[i]=(int *)malloc((nom+1)*sizeof(int));}

answer->p=(int *)malloc((nom+1)*sizeof(int));
for(i=0;i<nom+1;i++)
{	
	fscanf(inp,"%d",&(answer->p[i]));
	fscanf(inp,"%d",&temp);
}
answer->p[nom]=temp;

//calling matrix chain multiplication
mat *final=matrix_chain_mult(answer,nom);

/*for(i=1;i<=nom;i++)
{
	for(j=1;j<=nom;j++)
	{

		fprintf(out,"%d ",final->s[i][j]);
	}
	fprintf(out,"\n");
}

for(i=1;i<=nom;i++)
{
	for(j=1;j<=nom;j++)
	{

		fprintf(out,"%d ",final->m[i][j]);
	}
	fprintf(out,"\n");
}*/

fprintf(out,"Minimum number of multiplications are: %d ",final->m[1][nom]);

fclose(inp);
fclose(out);

return 0;
}






