/*
    1.  Write a Hello World Program, for 5 MPI ranks. All ranks
        print Hello World, with hostname.
*/

#include<mpi.h>
#include<stdio.h>
#define N 10

int main(int argc, char** argv) {
        int pid;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
        printf("Hello World! and rank %d on hostname cdac-acts\n", pid);    
        MPI_Finalize();
        return 0;
}