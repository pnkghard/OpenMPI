/*
    2.  Using 5 Ranks, add 1000 numbers in an array. Rank 0
        will initilize the array with random numbers. Send 250
        numbers to rank 1 to 4, to be added. Collect back Partial
        sum and get final sum.
*/

#include <mpi.h>
#include <stdio.h>
#define N 1000


void addition(int *a, int n, int rank){
        int j = *a;
        int sum = 0;
        for(int i=0; i<n; i++){                
                sum = sum + j++;
        }
        //printf("Sum is %d in ProcessID %d\n", sum, rank);
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
        }             
        MPI_Finalize();
        return 0;
}