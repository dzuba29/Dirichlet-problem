#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "matrix.h"
#include "dirichlet.h"

void benchmark(size_t dim, double mulDuration, double runtimeDuration);
void benchmark_to_csv(int threads, size_t dim, double mulDuration, double runtimeDuration);
void serial_to_csv(const Matrix &matrix);

#endif // __FUNCTIONS_H__