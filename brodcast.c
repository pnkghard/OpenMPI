#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    int N = atoi(argv[1]);
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    char hostname[MPI_MAX_PROCESSOR_NAME];
    int len;
    MPI_Get_processor_name(hostname, &len);
    int buffer;
    buffer = N;
    
    if(rank==0){
        MPI_Bcast(&buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("I am %s, my rank %d and I am brodcasting %d.\n", hostname, rank, buffer);
    } else {
        printf("I am rank %d and I received %d from rank 0.\n", rank, buffer);
    }
    MPI_Finalize();
    return 0;
}