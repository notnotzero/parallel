#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <iostream>

#define tag1 1
#define tag2 2

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int rank, n, i;

    double start_, end_, time_;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N = 10;
  

    for (int message_length = 1; message_length <= 1000000; message_length *= 10) {
        int* A_warm = (int*)malloc(message_length * sizeof(int));
        int* A = (int*)malloc(message_length * sizeof(int));

        if (rank == 0){
            start_ = MPI_Wtime();
            
        }

        // Warm-up loop
		for(int i=1; i<=5; i++){
			if(rank == 0){
				MPI_Send(A_warm, N, MPI_DOUBLE, 1, tag1, MPI_COMM_WORLD);
				MPI_Recv(A_warm, N, MPI_DOUBLE, 1, tag2, MPI_COMM_WORLD, &status);
			}
			else if(rank == 1){
				MPI_Recv(A_warm, N, MPI_DOUBLE, 0, tag1, MPI_COMM_WORLD, &status);
				MPI_Send(A_warm, N, MPI_DOUBLE, 0, tag2, MPI_COMM_WORLD);
			}
		}

        free(A_warm);

        for (int i = 1; i <= N; i++) {

            if (rank == 0) {
                MPI_Send(A, message_length, MPI_INT, 1, tag1, MPI_COMM_WORLD);
                MPI_Recv(A, message_length, MPI_INT, 1, tag2, MPI_COMM_WORLD, &status);

            } else if (rank == 1) {
                MPI_Recv(A, message_length, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
                MPI_Send(A, message_length, MPI_INT, 0, tag2, MPI_COMM_WORLD);
            }
        }

        if (rank == 0) {
            end_ = MPI_Wtime();
            time_ = end_ - start_;

            long int num_B = sizeof(int) * message_length;
            long int B_in_GB = 1 << 20;


            double num_GB = (double)num_B / (double)B_in_GB;
            double bandwidth = num_GB * 2.0 * (double)N / time_;
            std::cout << "message_length = " << message_length << "; Bandwidth = " << sizeof(int) * bandwidth  << "MB/s\n ";

            // printf("Bandwidth for message_length = %d is %f MB/s\n", message_length, sizeof(int) * bandwidth);
        }

        free(A);

    }

    if (rank == 0){
        start_ = MPI_Wtime();
    }

    for (int i = 1; i <= N; i++) {
        if (rank == 0) {
            MPI_Send(&i, 0, MPI_INT, 1, tag1, MPI_COMM_WORLD);
            MPI_Recv(&i, 0, MPI_INT, 1, tag2, MPI_COMM_WORLD, &status);

        } else if (rank == 1) {
            MPI_Recv(&i, 0, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
            MPI_Send(&i, 0, MPI_INT, 0, tag2, MPI_COMM_WORLD);
        }

    }

    if (rank == 0) {
            end_ = MPI_Wtime();
            time_ = end_ - start_;

            std::cout << "latency is " << time_ / (2 * N) << std::endl;
    }

    MPI_Finalize();
    return 0;
}