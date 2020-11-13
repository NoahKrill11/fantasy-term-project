#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <pthread.h> 
#include <assert.h>
int size;
double sum;
void serialAverage(double ar[]);
double MPI_Average(double *ar, int local_size);
int my_rank;


int main(void)
{
	int my_rank, local_size, comm_sz;
	MPI_Comm comm;
    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    double fantasyPoints[]= {14.4,15.3,15.8,15.8,16.4,16.8,16.8,17.4,17.6,17.7,17.9,18.3,
							18.4,19.4,19.5,19.6,19.7,20,20.1,20.2,20.6,20.9,20.9,21,21.2,
							21.5,21.7,21.7,23.4,26.3,27.6};
	size = sizeof(fantasyPoints)/sizeof(fantasyPoints[0]);
	
	local_size = size/comm_sz;
	double *ar = malloc(local_size*sizeof(double));
	MPI_Scatter(fantasyPoints,local_size,MPI_DOUBLE,ar,local_size,MPI_DOUBLE,0,comm);
	double subavg = MPI_Average(ar,local_size);

	double  *subavgs = NULL;
	if (my_rank==0)
	{
		subavgs = malloc(sizeof(double)* comm_sz);
		assert(subavgs != NULL);
	}
	MPI_Gather(&subavg, 1, MPI_DOUBLE, subavgs, 1, MPI_DOUBLE, 0, comm);

	if (my_rank == 0) {
    double avg = MPI_Average(subavgs, comm_sz);
    printf("Avg of all the teams is %f\n", avg);
  }
	MPI_Finalize();
      return(0);
}

double MPI_Average(double *ar, int local_size)
{
	double sum=0;
	int i;
	for(i=0; i < local_size; ++i)
	{
		sum+=ar[i];
	}
	return sum/local_size;
}
