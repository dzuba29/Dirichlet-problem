#include "dirichlet.h"


void start_point(){

	return;
}

void function(){

	return;
}

void solve(const Matrix &u,const Matrix &st_point,double epsilon,double iters,double step){

	double max;
	do{
		max=0
		for (size_t i = 1; i < iters+1; ++i){
			for (size_t j = 1; j < iters+1; ++j){

				double u0=u(i,j);
				u(i,j)=0.25*(u(i-1,j)+u(i+1,j)+u(i,j-1)+u(i,j+1)-step*step*st_point(i-1,j-1));
				double d=abs(u(i,j)-u0);
				if (d>max){

					max=d;
				}

			}

		}


	}
	while(max>epsilon)
}