#include<mpi.h>
#include<stdio.h>
#define N 10

int main(int argc, char** argv){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank * 100;
    int result[size];
    MPI_Alltoall(&value, 1, MPI_INT, &result, 1, MPI_INT, MPI_COMM_WORLD);
    if(rank==0){
        for(int i=0; i<size; i++){
            printf("from rank %d received %d.\n", i, result[i]);
        }
    }
    MPI_Finalize();
    return 0;
}