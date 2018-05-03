#ifndef __DIRICHLET_H__
#define __DIRICHLET_H__
#include "matrix.h"
double function( double x, double y);
double conditions( double x, double y);
double step( size_t iters);
Matrix st_point_f(size_t iters, double step);
Matrix st_point_u( size_t iters, double step);
void solve(Matrix &u,Matrix &f, double epsilon, size_t iters, double step);
#endif // __DIRICHLE_H__