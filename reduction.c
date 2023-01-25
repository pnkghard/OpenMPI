#include<mpi.h>
#include<stdio.h>
#define N 10

int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank * 100;
    int result = 0;
    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank==0)
        printf("my rank is %d Sum of all rank is %d.\n", rank, result);
    MPI_Finalize();
    return 0;
}