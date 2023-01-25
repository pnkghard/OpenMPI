#include<mpi.h>
#include<stdio.h>
#define N 10

int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank * 100;
    
    if(rank==0){
        int buffer[size];
        MPI_Gather(&value, 1, MPI_INT, buffer, 1, MPI_INT, rank, MPI_COMM_WORLD);
        printf("Value to Gather from process %d: %d, %d, %d, %d.\n", rank, buffer[0], buffer[1], buffer[2], buffer[3]);
    } else {
        printf("My rank is %d and I send %d to rank 0\n", rank, value);
        MPI_Gather(&value, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}