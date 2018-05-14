#include <iostream>
#include <sstream>
#include <chrono>
#include <stdexcept>
#include <omp.h>

#include "functions.h"
#include "matrix.h"
#include "dirichlet.h"

int main(int argc, char* argv[]){

  auto startTime = std::chrono::steady_clock::now();


  size_t rows=10;
  size_t cols=10;

  if (argc > 1){
    std::istringstream ss(argv[1]);
    int dim;
    if (!(ss >> dim)){
      throw std::invalid_argument("Wrong ARGV");
    } else {
      rows = dim;
      cols = dim;
    }
  } 


  Matrix A=solve(999, 0.0001);
  auto runTime= std::chrono::steady_clock::now(); //end


  auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(runTime - startTime);

  
  return 0;
}
//ssh student-math-03@fujitsu-hpc-02.narfu.ru
//Cneltyn2014
