#include<iostream>
#include"mpi.h"
#define SIZE 1000000


using namespace std;
int main(int argc, char** argv) {
    int vector1[SIZE];
    int vector2[SIZE];
    int start, end_;
    int result = 0;
    MPI_Init(&argc, &argv);
    int rank, n, i, message;

    MPI_Status status;

     
    
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank== 0){
        int sub_results_buffer;
        for( int i = 0; i < SIZE; i++) {
            vector1[i] = 1;
            vector2[i] = 1;
        }
        start = 0;
        end_ = start + SIZE / n + SIZE % n;
        for(int i = 1; i < n; i++) {
            start = end_;
            end_ = min(start + SIZE / n, SIZE);
            MPI_Send(&vector1[start], end_-start, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Send(&vector2[start], end_-start, MPI_INT, i, 2, MPI_COMM_WORLD);
        }
        start = 0;
        end_ = start + SIZE / n + SIZE % n;
        for(int i = start; i < end_; i++)
            result += vector1[i] * vector2[i];
        for(int i= 1; i < n; i++){
            MPI_Recv(&sub_results_buffer, SIZE / n, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
            result += sub_results_buffer;
        }
        cout<<"Result: "<< result << endl;
    }
    else{
        MPI_Recv(&vector1, SIZE / n, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&vector2, SIZE / n, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        for(int i = 0; i < SIZE / n; i++){
            result += vector1[i] * vector2[i];
        }
        MPI_Send(&result, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
        }
        MPI_Finalize();
    // delete[] vector1;
    // delete[] vector2;

    return 0;
}