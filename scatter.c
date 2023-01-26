#include<mpi.h>
#include<stdio.h>
#define N 10

int main(int argc, char** argv){
    int rank, size;
    int buffer[4] = {0, 100, 200, 300};
    int value;
    // MPI parallel resion start
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // initialization end
    MPI_Scatter(buffer, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0){          
        printf("Value to scatter from process %d: %d, %d, %d, %d.\n", rank, buffer[0], buffer[1], buffer[2], buffer[3]);
    }
    printf("My rank is %d and I received %d from rank 0.\n", rank, value);

    MPI_Finalize();
    // MPI parallel reasion end

    return 0;
}