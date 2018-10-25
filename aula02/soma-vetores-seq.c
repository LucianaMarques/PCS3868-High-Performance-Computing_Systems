#include <stdio.h>
#define size 1000
#define n_threads 3
#include <stdlib.h>

double a[size][size],b[size][size],c[size][size];

int n_iter;

pthread_t tid[n_threads];

void *inicia_matrizes(void *arg)
{
	int i, j, inicio, fim, k;

	k = *(int *)arg;

	inicio = (k+1)*n_iter;

	fim = inicio+n_iter;

	printf("inicio=%d fim = %d k = %d n_iter=%d\n", inicio,fim, k, n_iter);

	for (i = inicio; i <fim; i++){

		for (j = 0; j < size; j++)
		{
			a[i][j] = 1.5;
			b[i][j] = 2.6;
		}
	}
}


void main()
{  int i,j;
   //inicializa as matrizes
   for (i=0;i<size;i++)
     for (j=0;j<size;j++){
         a[i][j]=1.5;
         b[i][j]=2.6;
     }
   // fim da inicializacao
   // soma de a com b
   for (i=0;i<size;i++)
     for (j=0;j<size;j++)
         c[i][j]=a[i][j]+b[i][j];
   printf("c[0][0]=%f   c[15][20]=%f  c[size-1][size-1]=%f \n",c[0][0],c[15][20],c[size-1][size-1]);
}

        

        
   

