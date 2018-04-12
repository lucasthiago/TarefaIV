#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** ler(const char *nomeArq, int *d) {
	int i, j, dim;
	double **L, a;
	FILE *arq;
    
    arq = fopen(nomeArq, "r");
	i = fscanf(arq,"%d",&dim);
	L = malloc( dim*sizeof(double *));
	for( i = 0 ; i < dim ; i++ )
		L[i] = (double *) malloc((dim+1)*sizeof(double));
	
	i=j=0;
	while (fscanf(arq,"%lf",&a) != EOF) {
		L[i][j] = a;
		j++;
		if (j == dim+1) {
			j = 0;
			i++;
		}
	}
	*d=dim;
	return L;
}

void imprime(double **N, int var){
	
	int i, j;
	
	for(i=0;i<var;i++) {
		for(j=0;j<var+1;j++) { 
			printf("%5.2lf\t",N[i][j]);
		}	  
		puts("");
	}
}

void pivoteamento(double **M, int dim)
{
	double aux1, lamb;
	int i, j, k, aux2, o;
	
	puts("\nMatriz Pivoteada\n\n");
	
	for(i=0; i<dim; i++)
	{
		aux2=i;
		
		for(j=i+1; j<dim; j++)
		{
			if(fabs(M[aux2][i])<fabs(M[j][i]))
				aux2 = j;
		}
		
		
		o=i;
		
		if(aux2>i)
		{
			for(k=o; k<dim+1; k++)
			{
				aux1=M[aux2][k];
				M[aux2][k] = M[o][k];
				M[o][k] = aux1;
			}
		}
		
			
		for(j=i; j<dim-1; j++)
		{
			lamb=M[j+1][i]/M[i][i];
			for(k=i; k<dim+1; k++)
				M[j+1][k]-=(lamb) * M[i][k];
		}
		imprime(M, dim);
		puts(" ");
	}	
	
}



void subsreversa (double **M, double *raizes, int dim)
{
	int i, j, pos=0, e=0;
	double soma=0;
	
	
	for(i=dim-1; i>=0; i--)
	{
		raizes[i] = M[i][dim];
		
		for(j=dim; j>=i+1; j--)
			raizes[i]-=M[i][j]*raizes[j];
			
		raizes[i]/=M[i][i];
	}
}
	
	

		

int main(int argc, char **argv) {
	double **M;

	double *raizes;

	int i, dim;
	
	M=ler(argv[1], &dim);

	imprime(M,dim);
	pivoteamento(M, dim);
	imprime(M,dim);
	
	raizes = malloc(dim*sizeof(double));
	subsreversa(M,raizes,dim);
	
	puts("Raizes");
	
	for(i=0; i<dim; i++)
		printf("%5.3lf\t", raizes[i]);
		
	printf("\n\n\n\n");
	

	return 0;
}
