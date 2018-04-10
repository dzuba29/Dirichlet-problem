#include "functions.h"

void benchmark(size_t dim, double mulDuration, double runtimeDuration) {
  std::cout.setf(std::ios::fixed);
  std::cout.precision(5);
  std::cout << "║   " << dim << "║   "<< mulDuration << "║   "<< runtimeDuration<< std::endl;
}

void benchmark_to_csv(int threads, size_t dim, double mulDuration, double runtimeDuration) {
  std::cout << threads << "," << dim << "," << mulDuration << "," << runtimeDuration << std::endl;
}