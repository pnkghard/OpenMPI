/*
Initialise 2 arrays A and B of integers with random
numbers. Size MxN and NxP. M=3, N=4, P=2 to begin
with. Later any random number chosen between 700 to
1100. Parameterise the size.

Third array C is the multiplication of A and B.
Implement with 2 for loops. Outer and Inner. Write,
compile, run and test the program.

Now, use O0 and o2 optimisation and compare its time
taken with and without vectorization. Look at compile logs
to make sure its vectorized.
*/

#include<stdio.h>


int main(){

    int M, N, P, size;

    printf("M  : ");
    scanf("%d", &M);
    printf("N  : ");
    scanf("%d", &N);
    printf("P  : ");
    scanf("%d", &P);
    
    int A[M][N], B[N][P], C[M][P];

    // initializing A and B
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            A[i][j] = rand()%10;
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<P; j++){
            B[i][j] = rand()%12;
        }
    }
    for(int i=0; i<M; i++){
        for(int j=0; j<P; j++){
            C[i][j] = 0;
        }
    }

    // adding array A and B in C
    for(int i=0; i<M; i++){
        for(int j=0; j<P; j++){
            for(int k=0; k<N; k++){
                C[i][j] += A[i][k]*B[k][j];
            } 
        }
    }

    // for printing arrays
    for(int i=0; i<M; i++){
        for(int j=0; j<P; j++){
            printf("%d\t",C[i][j]);
        }
        printf("\n");
    }

    return 0;
}