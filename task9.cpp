#include <stdio.h>

#include <stdlib.h>
#include <iostream>
#include "mpi.h"

const int SIZE = 1000000;
const int V_SIZE = 1000000;

using namespace std;
int main(int argc, char *argv[]) {

    MPI_Init(NULL, NULL);
    int rank, pr_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &pr_size);


    int helper[V_SIZE];
    int number[V_SIZE / pr_size];
    int temps[pr_size];

    if (rank == 0) {
        for (int i = 0; i < V_SIZE; i++)
        number[i] = 1;

    }

    double start_time = MPI_Wtime();
    MPI_Scatter(number, V_SIZE / pr_size, MPI_INT, &helper, V_SIZE / pr_size, MPI_INT, 0, MPI_COMM_WORLD);
    long int temp = 0;

    for (int i = 0; i < V_SIZE / pr_size; i++) {

        temp = temp + helper[i];

    }

    MPI_Gather(&temp, 1, MPI_INT, &temps, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    long int result = 0;

    if (rank == 0) {
        result = 0;
        for (int i = 0; i < pr_size; i++) {
            result += temps[i];
    }
    cout << "#######################" << endl;
    cout << " # Cascade algorithm #" << endl;
    cout << "#######################" << endl;

    cout << "Result: " << result << endl;
    double execution_time = MPI_Wtime() - start_time;
    cout << "Time: " << execution_time << endl << endl << endl;

    }

    temp = 0;
    result = 0;

    start_time = MPI_Wtime();
    MPI_Scatter(number, V_SIZE / pr_size, MPI_INT, &helper, V_SIZE / pr_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < V_SIZE / pr_size; i++) {
        temp = temp + helper[i];
    }
    
    MPI_Reduce(&temp, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {


        cout << "#######################" << endl;
        cout << " # MPI Reduce algorithm #" << endl;
        cout << "#######################" << endl;

        cout << "Result: " << result << endl;
        double execution_time = MPI_Wtime() - start_time;
        cout << "Time: " << execution_time << endl;
        cout << "Number of processes: " << pr_size << endl;
        

    }

MPI_Finalize();

return 0;

}