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
	return 0;
}


double step(const size_t size){ //шаг 

	return 1.0/(size+1.0);
}



Matrix first_approx_f(const size_t size,const double h){ //первое приближение для f

	Matrix F(size, size);
	for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j)
			{
				F(i, j) = function((i + 1) * h, (j + 1) * h);
			}
		}

	return F;
}


Matrix first_approx_u(const size_t size,const double h){ //первое приближение для u

	Matrix u(size+2, size+2);
	size_t i,j;

	#pragma omp parallel sections private(i,j)
	{
 
	    #pragma omp section
		for (i = 1; i < size + 1; ++i) {
			u(i, 0) = conditions(i * h, 0);
			u(i, size + 1) = conditions(i * h, (size + 1) * h);
		}
		#pragma omp section
		for (j = 0; j < size + 2; ++j) {
			u(0, j) = conditions(0, j * h);
			u(size + 1, j) = conditions((size + 1) * h, j * h);
		}	
	}
		return u;
}

Matrix solve(const size_t size, const double eps) { 

	double h = step(size);

	Matrix F=first_approx_f(size,h);
	Matrix u=first_approx_u(size,h);	

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

Matrix solve_omp(const size_t size, const double eps) { 

	double h = step(size);

	Matrix F=first_approx_f(size,h);
	Matrix u=first_approx_u(size,h);	

	Matrix un=u;

	size_t i,j;
	double max,dm,d,temp;

	omp_lock_t lock;
  	omp_init_lock(&lock);

	do {
	
		max = 0;
		#pragma omp parallel for private(i,j,temp,d,dm) shared(u,max)
		
			for (i = 1; i < size + 1; ++i)
			{	
				dm = 0;
				for (j = 1; j < size + 1; ++j) {

					temp = u(i, j);
					un(i,j) = 0.25 * (u(i-1, j) + u(i+1, j) + u(i, j-1) + u(i, j+1) - h*h*F(i, j));
					d = std::fabs(temp - un(i,j));

					if (dm < d) {
						dm = d;
					}

				omp_set_lock(&lock);
				if ( max < dm ) {
						max = dm;
				}
		      	omp_unset_lock(&lock);
				}
			}
		
		
		

		for (i = 1; i < size + 1; ++i){	

			for (j = 1; j < size + 1; ++j) {

			u(i,j)=un(i,j);

			}

		}
		

		} while (max > eps);

	return u;
}