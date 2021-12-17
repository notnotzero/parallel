#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;


int main(int argc, char** argv)
{
    long int N = atoi(argv[1]);
    double* arr = new double[N];
    double true_max_ = 0;
    int test_runs_number = 20;

    for(int i = 0; i < N; i++)
    {
        arr[i] = (double(rand()) / RAND_MAX);
        true_max_ = max(true_max_, arr[i]);
    }

    for(int i = 1; i <= 10; i++)
    {
        double total_time = 0;

        for(int j = 0; j < test_runs_number; j++)
        {
            double max_ = arr[0];
            double begin = omp_get_wtime();

            #pragma omp parallel for num_threads(i) reduction(max:max_)
            for(int idx = 0; idx < N; idx++)
                max_ = max(max_, arr[idx]);

            double exec_time = (double)(omp_get_wtime() - begin);

            if (max_ == true_max_)
                total_time += exec_time;
            else
                total_time -= 1000;

        }
        cout << "Number of threads:" << i << "; Time: " << total_time / test_runs_number  << endl;
    }
    return 0;
}