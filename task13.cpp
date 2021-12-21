  
#include <cstdlib>
#include "mpi.h"
#include <string>
#include <iostream>

#define SIZE 500

using namespace std;
int main(int argc, char **argv)
{
	int rank, channels;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &channels);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }

	MPI_Barrier(MPI_COMM_WORLD);

	double start_ = MPI_Wtime();
	for (int i = 0; i < SIZE; i++){
        for (int k = 0; k < SIZE; k++){
		    for (int j = 0; j < SIZE; j++){
	            C[i][j] += A[i][k] * B[k][j];
	        }
	    }
	}
	double end_ = MPI_Wtime();
	string LOG  = "Proccess : " + std::to_string(rank) + "\nTime: " + to_string(end_ - start_) + "\n" + "######################" + "\n";
	cout << LOG;
	MPI_Finalize();
}