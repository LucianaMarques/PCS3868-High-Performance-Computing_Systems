#include <stdio.h>
#include <omp.h>
#define n 10

typedef struct {int a; int *proximo;} tipo_lista;

tipo_lista *lista;
tipo_lista *lista_first;

void inicia(int size);
  
void main()
{  
	tipo_lista *prox;
	inicia(n); 
	prox=lista_first;
	#pragma omp parallel num_threads(4)
	{
		#pragma parallel single
		{
			while (prox) {
				lista=prox;
				#pragma omp task firstprivate(lista)
				{				
					printf("%d \n",lista->a);
					sleep(lista->a);
				}
				prox=lista->proximo;
			}
		}
	}
	printf("FIM MAIN\n");
}

void inicia(int size)
{
	int i;
	tipo_lista *lista_anterior;
	lista=(tipo_lista *) malloc(sizeof(tipo_lista));
	lista->a=0; 
	lista_first=lista; 
	for (i=1;i<size;i++)
	{ 
		lista_anterior=lista;
		lista=(tipo_lista *) malloc(sizeof(tipo_lista));
		lista->a=i%5;
		lista_anterior->proximo=lista;
	}
	lista->proximo=(int *) 0; 
} 
