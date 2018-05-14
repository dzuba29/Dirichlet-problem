#include "dirichlet.h"
#include <cmath>


double function(const double x, const double y){ // правая часть уравнения

	return 0;
}
 
double conditions(const double x,const double y){ //краевые условия

	if(x==0)return  1-2*y;
	if(x==1)return -1+2*y;
	if(y==0)return  1-2*x;
	if(y==1)return -1+2*x;
	else return 0;
}


double step(const size_t iters){ //шаг 

	return 1.0/(iters+1.0);
}



Matrix first_approx(){


}

Matrix solve(const size_t size, const double eps) {

	Matrix F(size, size);
	Matrix u(size+2, size+2);
	

	double h = step(size);

	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j)
			F(i, j) = function((i + 1) * h, (j + 1) * h);
	}

	for (size_t i = 1; i < size + 1; ++i) {
		u(i, 0) = conditions(i * h, 0);
		u(i, size + 1) = conditions(i * h, (size + 1) * h);
	}

	for (size_t j = 0; j < size + 2; ++j) {
		u(0, j) = conditions(0, j * h);
		u(size + 1, j) = conditions((size + 1) * h, j * h);
	}

	double max;
	do {
		
		max = 0;
		for (size_t i = 1; i < size + 1; ++i)
			for (size_t j = 1; j < size + 1; ++j) {
				double u0 = u(i, j);
				double temp = 0.25 * (u(i-1, j) + u(i+1, j) + u(i, j-1) + u(i, j+1) - h*h*F(i - 1, j - 1));
				u(i, j) = temp;
				double d = std::fabs(temp - u0);

				if (d > max) {
					max = d;
				}
			}
		} while (max > eps);
	return u;
}