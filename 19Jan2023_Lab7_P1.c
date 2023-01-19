#include <mpi.h>
#include <stdio.h>
#define N 1000


void addition(int *a, int n, int rank){
        int j = *a;
        int sum = 0;
        MPI_Win win;
        for(int i=0; i<n; i++){                
                sum = sum + j++;
        }
        printf("Sum is %d in ProcessID %d\n", sum, rank);
        MPI_Win_create(&sum,sizeof(int),sizeof(int),MPI_INFO_NULL, MPI_COMM_WORLD, &win);
        MPI_Win_free(&win);
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

        MPI_Win win;
        
        if(rank==0){
                for(i=0; i<N; i++) {
                    array[i] = 1 + i;
                }
                MPI_Win_create(NULL,0,1,MPI_INFO_NULL,MPI_COMM_WORLD,&win);
                int job = 0;
                for(i=1; i<size; i++){
                        MPI_Win_lock(MPI_LOCK_SHARED,i,0,win);
                        MPI_Put(&array[job*(N/(size-1))],N/(size-1),MPI_INT,i,0,N/(size-1),MPI_INT,win);
                        MPI_Win_unlock(i,win);
                        job++;
                }
                MPI_Win_free(&win);
                MPI_Win_create(NULL,0,1,MPI_INFO_NULL,MPI_COMM_WORLD,&win);
                for(int i=1; i<size; i++){
                        MPI_Win_lock(MPI_LOCK_SHARED,i,0,win);
			            MPI_Get(&sum,1,MPI_INT,i,0,1,MPI_INT,win);
			            MPI_Win_unlock(i,win);
                        res += sum;
                }
                MPI_Win_free(&win);
                printf("TotalSum=%d\n", res);
        } else {
            MPI_Win_create(&worker,(N/(size-1))*sizeof(int),sizeof(int),MPI_INFO_NULL, MPI_COMM_WORLD, &win);
		    MPI_Win_free(&win);
            addition(&worker, N/(size-1), rank);
        }             
        MPI_Finalize();
        return 0;
}