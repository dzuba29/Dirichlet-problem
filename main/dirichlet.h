#ifndef __DIRICHLET_H__
#define __DIRICHLET_H__
#include "matrix.h"
Matrix solve(const size_t size, const double eps);
double conditions(const double x,const double y);
double function(const double x, const double y);
#endif // __DIRICHLE_H__