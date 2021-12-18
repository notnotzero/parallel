#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

double** malloc_array(int n)
{
	double** matrix = new double*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];
	return matrix;
}

void free_array(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void rand_matrix(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = double(rand()) / RAND_MAX + 2;
}


bool mult_check(double** matrix_1, double** matrix_2, int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            if(matrix_1[i][j] != matrix_2[i][j]){
                cout << i << ';' << j << ';' << matrix_1[i][j] << ';' << matrix_2[i][j];
                return false;

            }

        }

    return true;
}

void print_matrix(double** matrix, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int main(int argc, char** argv)
{
	const int N = atoi(argv[1]);
	double** A, **B, **C, **C_val;

	A = malloc_array(N);
	B = malloc_array(N);
	C = malloc_array(N);
	C_val = malloc_array(N);

	rand_matrix(A, N);
	rand_matrix(B, N);
    for (int p = 0; p < N; p++)
    		for (int o = 0; o < N; o++){
			    C[p][o] = 0.0;
    }
     for (int p = 0; p < N; p++)
    		for (int o = 0; o < N; o++){
			    C_val[p][o] = 0.0;
            }
	double t;

// ijk 
    cout << "ijk" << endl;

	t = omp_get_wtime();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				C_val[i][j] += A[i][k] * B[k][j];
	double baseline_ijk = omp_get_wtime() - t;
    cout << "baseline time " << baseline_ijk << endl;

    for(int n_threads = 2; n_threads <= 10; n_threads++)
    {
        for (int p = 0; p < N; p++)
    		for (int o = 0; o < N; o++){
			    C[p][o] = 0.0;
            }
        
        int i, j, k;
        t = omp_get_wtime();
        #pragma omp parallel for num_threads(n_threads) shared(A, B, C) private(i, j, k)
            for (i = 0; i < N; i++)
                for (j = 0; j < N; j++)
                    for (k = 0; k < N; k++)
                        C[i][j] += A[i][k] * B[k][j];
        double ijk_parallel_time = omp_get_wtime() - t;

        if(!mult_check(C, C_val, N))
            cout << "Error, matrix is not equal;" << endl;
        cout << "Threads: " << n_threads << "; Parallel time: " << ijk_parallel_time << "; Eficiency: " << baseline_ijk / ijk_parallel_time << endl;
    }
	cout <<  endl;

// jki
    cout << "jki multiplication" << endl;

	 for (int p = 0; p < N; p++)
    		for (int o = 0; o < N; o++){
			    C[p][o] = 0.0;
            }
	t = omp_get_wtime();
	for (int j = 0; j < N; j++)
		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				C[i][j] += A[i][k] * B[k][j];
	double baseline_jki = omp_get_wtime() - t;

    cout << "baseline time " << baseline_jki << endl;


    for(int n_threads = 2; n_threads <= 10; n_threads++)
    {
        int i, j, k;
        for (int p = 0; p < N; p++)
    		for (int o = 0; o < N; o++){
			    C[p][o] = 0.0;
            }
        t = omp_get_wtime();
        #pragma omp parallel for num_threads(n_threads) shared(A, B, C) private(i, j, k)
            for (j = 0; j < N; j++)
                for (k = 0; k < N; k++)
                    for (i = 0; i < N; i++)
                        C[i][j] += A[i][k] * B[k][j];
        double t_jki_parallel = omp_get_wtime() - t;

        if(!mult_check(C, C_val, N))
            cout << "Error, matrix is not equal;" << endl;
        cout << "Threads: " << n_threads << "; Parallel time: " << t_jki_parallel << "; Eficiency: " << baseline_jki / t_jki_parallel << endl;

    }

	cout <<  endl;

// ikj
    cout << "ikj multiplication" << endl;

	 for (int p = 0; p < N; p++)
    		for (int o = 0; o < N; o++){
			    C[p][o] = 0.0;
            }
	t = omp_get_wtime();
	for (int i = 0; i < N; i++)
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++)
				C[i][j] += A[i][k] * B[k][j];
	double baseline_ikj = omp_get_wtime() - t;
    cout << "baseline time " << baseline_ikj << endl;


    for(int n_threads = 2; n_threads <= 10; n_threads++)
    {
        int i, j, k;
         for (int p = 0; p < N; p++)
    		for (int o = 0; o < N; o++){
			    C[p][o] = 0.0;
            }
        t = omp_get_wtime();
        #pragma omp parallel for num_threads(n_threads) shared(A, B, C) private(i, j, k)
            for (i = 0; i < N; i++)
                for (k = 0; k < N; k++)
                    for (j = 0; j < N; j++)
                        C[i][j] += A[i][k] * B[k][j];
        double t_ikj_parallel = omp_get_wtime() - t;



        if(!mult_check(C, C_val, N))
            cout << "Error, matrix is not equal;" << endl;
        cout << "Threads: " << n_threads << "; Parallel time: " << t_ikj_parallel << "; Eficiency: " << baseline_ikj / t_ikj_parallel << endl;

    }
    cout <<  endl;


	free_array(A, N);
	free_array(B, N);
	free_array(C, N);
    free_array(C_val, N);
	return 0;
}