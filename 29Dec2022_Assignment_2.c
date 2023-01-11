#include <mpi.h>
#include <stdio.h>
#define N 12


void addition(int *a, int n, int rank){
        int j = *a;
        int sum = 0;
        for(int i=0; i<n; i++){                
                sum = sum + j++;
        }
        printf("Sum is %d in ProcessID %d\n", sum, rank);
        MPI_Send(&sum, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
}

int main(int argc, char** argv) {
        int rank, i;
        int buf, size;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        int array[N];
        int worker;
        int res = 0, sum = 0, r;
        for(i=0; i<N; i++) {
	        array[i] = i + 1;
	}
        if(rank==0){
                int job = 0;
                for(i=1; i<size; i++){
                        MPI_Send(&array[job*(N/(size-1))], N/(size-1), MPI_INT, i, 0, MPI_COMM_WORLD);
                        job++;
                }
                for(int i=1; i<size; i++){
                        MPI_Recv(&sum, 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        res += sum;
                }
                printf("TotalSum=%d\n", res);
        } else {
                MPI_Recv(&worker, N/(size-1), MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                addition(&worker, N/(size-1), rank);
                printf("Process %d received number %d from process 0\n\n\n", rank, worker);
        }             
        MPI_Finalize();
        return 0;
}