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
	
	double start, end, totalTime;
    	MPI_Init(NULL, NULL);
    	comm = MPI_COMM_WORLD;
    	MPI_Comm_size(comm, &comm_sz);
    	MPI_Comm_rank(comm, &my_rank);
	
    	double fantasyPoints[]= {240.4,239.5,236.1,220.6,187.6,185.1,183.8,179.7,177.5,175.4,168.7,164.6,163.5,163.4,158.0,154.8,151.6,148.8,
    	145.8,142.9,141.7,140.4,138.8,138.6,135.3,133.7,131.2,125.8,124.8,124.2,122.5,120.3,120.2,116.3,115.5,111.0,110.9,108.9,106.2,105.3,
    	105.1,104.9,103.5,99.3,99.0,95.0,94.3,94.0,94.0,93.5,89.4,89.1,88.4,88.0,87.6,87.5,87.1,86.9,86.0,85.7,85.1,84.0,83.4,83.3,83.0,83.0,
    	82.7,82.0,82.0,82.0,82.0,82.0,81.8,81.8,81.7,81.5,81.4,81.0,81.0,81.0,81.0,80.8,80.6,80.4,79.4,79.0,78.9,78.8,78.6,78.1,77.0,77.0,76.3,
    	76.0,75.7,75.0,73.3,73.0,72.0,71.1,71.0,70.0,69.9,69.6,69.4,69.0,69.0,69.0,69.0,68.5,68.5,68.0,68.0,68.0,68.0,67.7,67.6,67.5,66.6,66.4,
    	66.0,65.3,65.0,64.7,64.0,64.0,63.8,63.8,63.0,62.8,62.0,62.0,61.4,61.4,61.1,61.1,61.1,60.4,60.2,60.0,59.7,59.1,58.9,58.0,58.0,57.7,57.4,
    	57.4,57.3,57.3,57.3,57.2,57.0,56.8,56.7,56.3,56.2,55.6,54.9,54.8,54.4,53.9,53.8,53.8,53.5,53.0,52.8,52.4,52.2,52.0,52.0,51.5,51.3,50.7,50.4,
    	50.3,50.0,49.9,49.9,49.0,48.9,48.9,48.6,48.6,48.5,48.3,48.3,48.0,47.3,47.0,47.0,47.0,46.5,46.1,45.8,45.5,45.3,45.2,45.1,44.6,44.5,
    	44.3,44.0,43.9,43.7,43.7,43.6,43.6,43.4,43.4,43.0,43.0,43.0,42.3,42.2,41.7,41.7,41.6,41.2,41.1,41.0,40.3,40.0,40.0,39.6,39.4,39.4,
    	39.1,39.0,38.4,38.2,38.0,37.0,36.0,36.0,35.6,35.3,35.2,35.2,34.9,34.7,34.6,34.4,34.3,34.0,33.9,33.9,33.7,33.6,33.2,33.2,33.0,33.0,
    	32.5,32.0,32.0,31.8,31.6,31.6,31.6,31.3,31.2,31.1,30.8,30.5,30.4,29.9,29.9,29.7,29.0,28.2,28.0,27.9,27.8,27.8,27.5,27.4,27.0,27.0,
    	27.0,26.8,26.8,26.6,26.5,26.3,26.3,26.1,26.0,25.9,25.8,25.8,25.6,25.1,25.0,25.0,24.8,24.8,24.7,24.6,24.4,24.4,24.1,23.8,23.5,23.3,
    	23.2,23.1,23.1,23.0,22.9,22.6,22.5,22.4,22.2,22.0,22.0,21.9,21.4,21.3,21.3,21.2,20.8,20.8,20.7,20.5,20.1,20.0,19.8,19.8,19.7,19.3,
    	19.3,19.0,18.6,18.4,18.4,18.4,18.2,18.1,18.0,18.0,18.0,17.8,17.8,17.4,17.3,17.1,17.0,16.7,16.6,16.1,15.9,15.7,15.6,15.6,15.5,15.3,
    	15.3,15.2,15.2,15.1,15.1,15.0,14.8,14.7,14.7,14.6,14.6,14.6,14.5,14.3,14.1,14.1,13.9,13.6,13.6,13.5,13.5,13.3,13.0,12.9,12.8,12.6,
    	12.4,12.1,12.1,12.0,11.8,11.6,11.6,11.5,11.3,11.3,11.3,11.0,10.9,10.5,10.4,10.1,10.0,9.9,9.9,9.9,9.8,9.7,9.5,9.5,9.4,9.4,9.4,9.3,
    	9.2,9.0,9.0,8.9,8.7,8.7,8.6,8.4,8.4,8.4,8.2,8.1,7.9,7.7,7.6,7.5,7.4,7.4,7.3,7.3,7.3,7.1,7.0,7.0,6.8,6.7,6.7,6.6,6.6,6.5,6.5,6.4,
    	6.3,6.3,6.3,6.3,6.1,6.1,6.1,6.0,5.8,5.6,5.6,5.6,5.5,5.3,5.2,5.1,5.0,5.0,5.0,4.8,4.7,4.6,4.5,4.4,4.1,4.0,4.0,4.0,3.8,3.5,3.3,3.2,
    	3.2,3.2,3.2,3.1,3.1,3.0,2.9,2.8,2.7,2.7,2.7,2.5,2.4,2.3,2.3,2.3,2.3,2.2,2.1,2.1,2.1,2.0,2.0,2.0,2.0,2.0,1.9,1.9,1.8,1.7,1.7,1.6,
    	1.6,1.6,1.6,1.5,1.4,1.3,1.3,1.3,1.3,1.3,1.3,1.2,1.2,1.2,1.2,1.2,1.1,1.1,1.0,1.0,1.0,1.0,1.0,0.9,0.9,0.9,0.9,0.9,0.9,0.8,0.8,0.8,
    	0.7,0.7,0.7,0.7,0.6,0.6,0.6,0.6,0.5,0.5,0.5,0.5,0.5,0.5,0.3,0.3,0.3,0.3,0.3,0.2,0.2,0.2,0.1,0.1,0.1,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
    	0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
    	0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
    	0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,-0.1,-0.5,-0.6,-0.9,-1.0,-1.2,-1.6,-2.0};
	
	size = sizeof(fantasyPoints)/sizeof(fantasyPoints[0]);
	local_size = size/comm_sz;
	double *ar = malloc(local_size*sizeof(double));
	double  *subavgs = NULL;

	start = MPI_Wtime();
	MPI_Scatter(fantasyPoints,local_size,MPI_DOUBLE,ar,local_size,MPI_DOUBLE,0,comm);
	double subavg = MPI_Average(ar,local_size);
	if (my_rank == 0) {
		subavgs = malloc(sizeof(double)* comm_sz);
		assert(subavgs != NULL);
		
  	}		
	//gather the values among the subavg array
	MPI_Gather(&subavg, 1, MPI_DOUBLE, subavgs, 1, MPI_DOUBLE, 0, comm);
	end = MPI_Wtime() - start;

	if (my_rank == 0){
		//calculate the average of the subaverages
        	double avg = MPI_Average(subavgs, comm_sz);
        	printf("Avg of all the teams is %f\n", avg);
		end = MPI_Wtime() - start;
	}
	MPI_Barrier(MPI_COMM_WORLD);
   	MPI_Reduce(&end, &totalTime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(my_rank == 0){
		printf("Total time: %f\n", totalTime);
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
