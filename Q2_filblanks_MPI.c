#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"

int main(int argc, char** argv){
    int width[50], height[50], area[50], perimeter[50];
    int width_local[10], height_local[10], area_local[10], perimeter_local[10];
    int i=0;
    int myid, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if(size!=5){
        MPI_Finalize();
        printf("This program works only with 5 Processes. Exiting.....\n");
        exit(0);
    }

    if(myid==0){
        for(i=0; i<50; i++){
            width[i]=i;
            height[i]=i;
        }
    }

    MPI_Scatter(&width, 10, MPI_INT, &width_local, 10, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&height, 10, MPI_INT, &height_local, 10, MPI_INT, 0, MPI_COMM_WORLD);

    for(i=0; i<10; i++){
        area_local[i] = width_local[i] * height_local[i];
        perimeter_local[i] = 2 * (width_local[i] + height_local[i]);
    }

    MPI_Gather(&area_local, 10, MPI_INT, &area, 10, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(&perimeter_local, 10, MPI_INT, &perimeter, 10, MPI_INT, 0, MPI_COMM_WORLD);

    if(myid==0){
        printf("\nArea : \n");
        for(i=0; i<50; i++){
            printf("\t%d", area[i]);
        }
        printf("\n\nPerimeter : \n");
        for(i=0; i<50; i++){
            printf("\t%d", perimeter[i]);
        }
    }
    printf("\n");

    MPI_Finalize();
}