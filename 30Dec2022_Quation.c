#include <mpi.h>
#include <stdio.h>
#define N 10

int main(int argc, char** argv) {
        int rank, size;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        int array[N];
        int n;
        if(rank==0){
            for(int i=0; i<N; i++){
                array[i] = i + 1;
            }
            MPI_Send(&array[0], N, MPI_INT,1, 0, MPI_COMM_WORLD);
            printf("%d Address send by processID %d \n", &array[0], rank);
        }else{
            MPI_Recv(&n, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int i=0; i<N; i++){
                printf("ProcessID=%d\tArray[%d]=%d\n", rank, i, n++);
            }
        }      
        MPI_Finalize();
        return 0;
}