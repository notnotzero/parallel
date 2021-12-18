#include <stdio.h>
#include "mpi.h"
#define NTIMES 100
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	double start, end_;
	string report;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	 

  

	start = MPI_Wtime();
	for ( int j = 0 ; j < NTIMES; j ++){
	if (rank == 9)
	{
		for (i = 1; i < n; i++) {
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,
			         MPI_ANY_TAG, MPI_COMM_WORLD, &status);

		}
	}
	else MPI_Send(&rank, 1, MPI_INT, 9, 0, MPI_COMM_WORLD);
	}
	
	end_ = MPI_Wtime();

	report = "Rank: " + to_string(rank) + ". Time = " + to_string((end_ - start) / NTIMES ) + "; \n";

	cout << report;
	MPI_Finalize();
	return 0;
}