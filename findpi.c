#include<stdio.h>
#include<math.h>


#define N 999999

int main(){
	int i;
	double area, pi;
	double dx, y, x;
	
	dx = 1.0/N;
	x = 0.0;
	area = 0.0;
	
	for(i=0;i<N;i++){
		y = sqrt(1-x*x);
		area += y*dx;  
		x += dx;
	}
	
	pi = 4.0*area;
	printf("\n Value of pi is = %0.9f\n\n", pi);
	
}