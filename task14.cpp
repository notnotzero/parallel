#include <stdio.h>
#include "mpi.h"
#include <iostream>
#define SIZE 1000

using namespace std;

void maximum_element(void *ib, void *ob, int * length, MPI_Datatype *type) {
	int* input = (int*)ib;
	int* output = (int*)ob;
	for (int i = 0; i < *length; i++){
		if (input[i] >= output[i]){
			output[i] = input[i];
		}
	}
		 
}

int main(int argc, char **argv){
	int rank, size, i;
	int a[SIZE];
	int b[SIZE], b_val[SIZE];
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < SIZE; i++) a[i] = i + rank + 1;
	printf("process %d a[0] = %d\n", rank, a[0]);
	MPI_Op_create(&maximum_element, 1, &op);
	MPI_Reduce(a, b, SIZE, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	MPI_Reduce(a, b_val, SIZE, MPI_INT, MPI_MAX , 0, MPI_COMM_WORLD);

	if (rank == 0){
		cout << "b[0] = " << b[0] << endl;
		cout << "b_val[0] = " << b_val[0] << endl;
		int temp = 0;
		for (int i = 0; i < SIZE; i++){
			if (b[i] != b_val[i]){
				cout << "ERROR" << endl;
				break;
			}
			else{
				temp += 1;
			}
		}
		if (temp == SIZE) {
			cout << "Resuts are correct" << endl;
		}
		
}}
	