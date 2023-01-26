#include<mpi.h>
#include<stdio.h>
#define N 10

int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank * 100;
    int buffer[4];
    MPI_Allgather(&value, 1, MPI_INT, &buffer, 1, MPI_INT, MPI_COMM_WORLD);
    printf("My rank is %d and I send %d to rank 0\n", rank, value);
    // MPI_Allgather(&value, 1, MPI_INT, 1, MPI_INT, MPI_COMM_WORLD);
    if(rank==0){
        printf("Value to Gather to process %d: %d, %d, %d, %d.\n", rank, buffer[0], buffer[1], buffer[2], buffer[3]);
    }
    MPI_Finalize();
    return 0;
}