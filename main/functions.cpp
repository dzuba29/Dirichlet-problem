#include "functions.h"
#include <fstream>

void benchmark_to_csv(size_t threads, size_t dim, double mulDuration, double runtimeDuration)
{
  std::cout << threads << "," << dim << "," << mulDuration << "," << runtimeDuration << std::endl;
}
