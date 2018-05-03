#include "dirichlet.h"
#include "math.h"

void solve(Matrix &u, Matrix &f,double epsilon, size_t iters, double step){

	double max;
	int iterCnt=0;
	do{
		max=0;
		for (size_t i = 1; i < iters+1; ++i){
			for (size_t j = 1; j < iters+1; ++j){
				double u0=u(i,j);
				u(i,j)=0.25*(u(i-1,j)+u(i+1,j)+u(i,j-1)+u(i,j+1)-step*step*f(i-1,j-1));
				double d=fabs(u(i,j)-u0);
				if (d>max){

					max=d;
				}
			}
		}
		iterCnt++;
	}
	while(max>epsilon);
	std::cout<<"iters:"<<iterCnt<<std::endl;
}



double function(double x, double y){ // правая часть уравнения, пока ноль, yolo

	return x+y;
}
 
double conditions(double x,double y){ //краевые условия

	if(x==0)return 1-2*y;
	if(x==1)return-1+2*y;
	if(y==0)return 1-2*x;
	if(y==1)return-1+2*x;
	else return 0;
}


double step(size_t iters){ //шаг h

	return 1.0/(iters+1);
}

Matrix st_point_f(size_t iters, double step){ // начальное приближение для f

	Matrix f(iters,iters);

	for (size_t i = 0; i < iters; ++i){
			for (size_t j = 0; j < iters; ++j){

				f(i,j) = function((i+1)*step, (j+1)*step);
		}
	}


	return f;
}


Matrix st_point_u(size_t iters,double step){ // начальное приближение для u

	Matrix u(iters+2,iters+2);

	for (size_t i = 1; i < iters+1; ++i){
			for (size_t j = 1; j < iters+1; ++j){

				u(i,j)=0;
				u(i,0)=conditions(i*step,0);
				u(i,iters+1)=conditions(i*step,(iters+1)*step);
				u(0,j)=conditions(0,j*step);
				u(iters+1,j)=conditions((iters+1)*step,j*step); //
		}
	}

	return u;
}
