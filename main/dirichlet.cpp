#include "dirichlet.h"
#include <cmath>


double function(const double x, const double y){ // правая часть уравнения

	return 0;
}
 
double conditions(const double x,const double y){ //краевые условия

	if(x==0)return exp(y)+y*y*(1-exp(1))-1;
	if(x==1)return y;
	if(y==0)return 0;
	if(y==1)return x;
	else return 0;
	return 0;
}


double step(const size_t size){ //шаг для сетки

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
	

	for (size_t i = 1; i < size + 1; ++i) {
		u(i, 0) = conditions(i * h, 0);
		u(i, size + 1) = conditions(i * h, (size + 1) * h);
	}
	for (size_t j = 0; j < size + 2; ++j) {
		u(0, j) = conditions(0, j * h);
		u(size + 1, j) = conditions((size + 1) * h, j * h);
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

Matrix solve_omp(size_t size, const double eps) { 

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
		#pragma omp parallel for shared(u,size,max) private(i,j,temp,d,dm) 
		
			for (i = 1; i < size + 1; ++i)
			{	
				dm = 0;
				for (j = 1; j < size + 1; ++j) {

					temp = u(i, j);
					un(i,j) = 0.25 * (u(i-1, j) + u(i+1, j) + u(i, j-1) + u(i, j+1) - h*h*F(i-1, j-1));
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

Matrix solve_omp2(size_t size, const double eps) {

	double h=step(size);
	Matrix u_mat=first_approx_u(size,h);
	Matrix f_mat=first_approx_f(size,h);
	double max, u0, d;
	size_t j=0;
	std::vector<double> mx(size+1);
	do
	{

		for (size_t k = 1; k < size+1; k++) {
			mx[k] = 0;
			#pragma omp parallel for shared(u_mat, size, max) private(j, u0, d) schedule(static, 1)
			for (size_t i = 1; i < k+1; i++) {
				j = k + 1 - i;
				u0 = u_mat(i, j);
				u_mat(i, j) = 0.25 * (u_mat(i-1, j) +u_mat(i+1, j) + u_mat(i, j-1) + u_mat(i, j+1) - h*h*f_mat(i-1, j-1));
				d = std::fabs(u_mat(i, j) - u0);
				if (d > mx[i]) mx[i] = d;
			}
		}
		for (size_t k = size-1; k > 0; k--) {
			#pragma omp parallel for shared(u_mat, size, max) private(j, u0, d) schedule(static, 1)
			for (size_t i = size-k+1; i < size+1; i++){
				j = 2*size - k - i + 1;
				u0 = u_mat(i, j);
				u_mat(i, j) = 0.25 * (u_mat(i-1, j) +u_mat(i+1, j) + u_mat(i, j-1) + u_mat(i, j+1) - h*h*f_mat(i-1, j-1));
				d = std::fabs(u_mat(i, j) - u0);
				if (d > mx[i]) mx[i] = d;				
			}
		}
		max = 0;
		for (size_t i = 1; i < size+1; i++) {
			if (mx[i] > max) max = mx[i];
		}
	} while (max > eps);
	return u_mat;
}