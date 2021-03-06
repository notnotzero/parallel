#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	int rank;
	MPI_Init(&argc, &argv);
	MPI_File fh;
	MPI_Status status;
	char buf[10];

	MPI_File_open(MPI_COMM_WORLD, "file1.txt", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	MPI_File_write(fh, "bulk1text bulk2text bulk3text bulk4text bulk5text bulk6text ", 60, MPI_CHAR, &status);
	MPI_File_close(&fh);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_File_open(MPI_COMM_WORLD, "file1.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, rank * 5, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	MPI_File_read_all(fh, buf, 5, MPI_CHAR, MPI_STATUS_IGNORE);
	printf("process %d, buf=%s\n", rank, buf);
	MPI_File_close(&fh);
	MPI_Finalize();
}