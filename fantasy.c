#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <pthread.h> 
int size;
double sum, avg2;
void serialAverage(double ar[]);
void MPI_Average(int, MPI_Comm, double[]);
void average(double);
int my_rank;


int main(void)
{
	int comm_sz, local_size;
	double * local_ar;
	MPI_Comm comm;
    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);
    MPI_Barrier(comm);

	double start=0, finish=0, loc_elapsed=0, time=0;
	double fantasyPoints[]= {14.4,15.3,15.8,15.8,16.4,16.8,16.8,17.4,17.6,17.7,17.9,18.3,
							18.4,19.4,19.5,19.6,19.7,20,20.1,20.2,20.6,20.9,20.9,21,21.2,
							21.5,21.7,21.7,23.4,26.3,27.6};
	
	size = sizeof(fantasyPoints)/sizeof(fantasyPoints[0]);
	local_size = size/comm_sz;
	local_ar=malloc(local_size*sizeof(double));
	MPI_Scatter(fantasyPoints,local_size, MPI_DOUBLE, local_ar,local_size, MPI_DOUBLE,0, comm);
	//serialAverage(fantasyPoints);
	MPI_Average(local_size, comm, local_ar);
	MPI_Finalize();
      return(0);
}

void serialAverage(double fantasyPoints[])
{
	double sum=0;
	for(int i=0; i<size; ++i)
	{
		sum+=fantasyPoints[i];
	}
	double avg=sum/size;
	printf("%s", "The average for the fantasy teams is " );
	printf("%f\n",avg);

}
void MPI_Average(int local_size, MPI_Comm comm, double ars[])
{
	unsigned long long* Ar;
    Ar = malloc(size*sizeof(double));
	MPI_Allgather(ars, local_size, MPI_DOUBLE, Ar, local_size, MPI_DOUBLE, comm);
	//printf("%d\n",local_size );
	for(int i=0; i < local_size; ++i)
	{
		average(ars[i]);
	}
	printf("%s\n", "The average is " );
	printf("%f\n", avg2);

}
void average(double value)
{
	sum+=value;
	avg2 = sum/size;

}