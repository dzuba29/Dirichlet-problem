#include <iostream>
#include <sstream>
#include <chrono>
#include <stdexcept>
#include <omp.h>

#include "functions.h"


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

  Matrix A = Matrix::rand(rows,cols);
  Matrix B = Matrix::rand(rows,cols);
  Matrix C(rows,cols);
  auto initTime = std::chrono::steady_clock::now();

  C=A*B;
  
  auto mulTime = std::chrono::steady_clock::now(); //end



  auto mulDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - initTime);
  auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

  //benchmark(rows, mulDuration.count(), runtimeDuration.count());

  benchmark_to_csv(omp_get_max_threads(), rows, mulDuration.count(), runtimeDuration.count());
  
  return 0;
}
//flags -Wall -Wextra -Wpedantic -fopenmp or 
//#### ssh student-math-03@fujitsu-hpc-02.narfu.ru
//#### Cneltyn2014
