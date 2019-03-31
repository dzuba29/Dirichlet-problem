#include <iostream>
#include <sstream>
#include <chrono>
#include <stdexcept>

#include "functions.h"
#include "matrix.h"
#include "dirichlet.h"

int main(int argc, char *argv[])
{

  size_t N = 99; //size
  double eps = 0.001;

  if (argc > 1)
  {
    std::istringstream ss(argv[1]);
    size_t iters;
    if (!(ss >> iters))
    {
      throw std::invalid_argument("Wrong ARGV");
    }
    else
    {
      N = iters;
    }
  }

  auto startTime = std::chrono::steady_clock::now();

  // Matrix u = solve_omp2(N, eps);

  auto runTime = std::chrono::steady_clock::now();
  auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(runTime - startTime);

  // std::cout << ToCSV(u, runtimeDuration.count()) << std::endl;
  return 0;
}

