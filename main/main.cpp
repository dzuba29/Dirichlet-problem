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

  //Matrix A = Matrix::rand(rows,cols);
  //Matrix B = Matrix::rand(rows,cols);
  //Matrix C(rows,cols);

  double st=step(rows); // get steps
  double eps=0.001;

  Matrix f(rows,cols);
  f=st_point_f(rows,st);

  Matrix u(rows+2,cols+2);
  u=st_point_u(rows,st);


  auto initTime = std::chrono::steady_clock::now();

  //C=A*B;
  
  solve(u,f,eps,rows,st);

  auto mulTime = std::chrono::steady_clock::now(); //end

   std::cout << ToString(u) << std::endl;

  auto mulDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - initTime);
  auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

  //benchmark(rows, mulDuration.count(), runtimeDuration.count());

  //benchmark_to_csv(omp_get_max_threads(), rows, mulDuration.count(), runtimeDuration.count());
  
  return 0;
}
//flags -Wall -Wextra -Wpedantic -fopenmp or 
//#### ssh student-math-03@fujitsu-hpc-02.narfu.ru
//#### Cneltyn2014
