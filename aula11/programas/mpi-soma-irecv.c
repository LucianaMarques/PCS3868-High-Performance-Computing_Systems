/*
 * EXEMPLO usando Irecv. Esta sendo simulado um processamento enquanto a recepcao dos dados nao finaliza. Para simular uma transmissao em um momento posterior a chamada Irecv pelo receptor foi inserida uma chamada de sleep.
 */

#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(argc, argv)

int			argc;
char			*argv[];

{
	int		n,n_nos, rank;
	MPI_Status	status;
        MPI_Request req;
        int inicio,fim,i,j;
        double soma,soma_sqrt,parcial_sqrt;
        double a[1000][1000];
        int flag;
/*
 * Initialize MPI.
 */
	MPI_Init(&argc, &argv);
/*
 * Error check the number of processes.
 * Determine my rank in the world group.
 * The sender will be rank 0 and the receiver, rank 1.
 */
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        n=1000;
        if (n_nos<2) {
             MPI_Finalize();
             return(0);
           }
printf("INICIO\n");
fflush(stdout);
        inicio=rank*(n/n_nos);
        fim=inicio+(n/n_nos);
        if (rank==0) {
          for(i=0;i<n;i++)
            for(j=0;j<n;j++)
              a[i][j]=4;
              
          for (i=1;i<n_nos;i++)
{
printf("rank 0 antes de Send\n");
fflush(stdout);
            sleep(10);
            MPI_Send(&a[0][0]+(n/n_nos*n*i),n/n_nos*n,MPI_DOUBLE,i,10,MPI_COMM_WORLD);
printf("rank 0 apos Send\n");
fflush(stdout); 
}        }
        else {
printf("rank=%d a[0][0]=%f\n",rank,a[0][0]);
fflush(stdout);
        MPI_Irecv(a,n/n_nos*n,MPI_DOUBLE,0,10,MPI_COMM_WORLD,&req);
printf("apos irecv\n");
fflush(stdout);
        flag=0;
        while (flag==0)
         {
           printf("rank=%d processando enquanto espera termino da recepcao\n",rank);
           fflush(stdout);
           usleep(4000);
           MPI_Test(&req,&flag,&status);
         }
        printf("APOS TERMINO DA RECEPCAO rank=%d a[0][0]=%f\n",rank,a[0][0]);
        fflush(stdout);

        }
        parcial_sqrt=0;
        for(i=0;(i<n/n_nos);i++)
         for(j=0;j<n;j++)
          parcial_sqrt+=sqrt(a[i][j]);
        printf("rank=%d soma_parcial_sqrt=%f\n",rank,parcial_sqrt);
        fflush(stdout);
        if (rank==0) {
           soma_sqrt=parcial_sqrt;
           for(i=1;i<n_nos;i++){
             MPI_Recv(&soma,1,MPI_DOUBLE,MPI_ANY_SOURCE,11,MPI_COMM_WORLD,&status);
             soma_sqrt+=soma;}
           printf("RESULTADO=%f\n",soma_sqrt);
           fflush(stdout); 
           }
        else {
           MPI_Send(&parcial_sqrt,1,MPI_DOUBLE,0,11,MPI_COMM_WORLD);
             }
	MPI_Finalize();
	return(0);
}
