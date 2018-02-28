#include <iostream>
#include <vector>
#include <sstream>
#include <omp.h>
#include <random>
#include <chrono>
#include <stdexcept>


class Matrix {

public:

  Matrix(size_t rows, size_t cols)
      : m_rows(rows)
      , m_cols(cols)
      , m_data(rows * cols)
  {}

  size_t rows() const {
    return m_rows;
  }

  size_t cols() const {
    return m_cols;
  }

  double &operator()(size_t row, size_t col){
    return m_data[row * m_cols + col];
  }

  const double &operator()(size_t row, size_t col) const{
    return m_data[row * m_cols + col];
  }

 
private:
  size_t m_rows;
  size_t m_cols;
  std::vector<double> m_data;
 
};



//linear functions

std::string ToString_Linear(const Matrix &matrix){ //outmatrix

  std::stringstream outStream;

  for (size_t i = 0; i < matrix.rows(); ++i) {

    for (size_t j = 0; j < matrix.cols(); ++j) {

      outStream << matrix(i, j) << " ";
    }
    outStream << std::endl;
  }
return outStream.str();

}







//openmp functions 

void get_random_vector_OpenMp(Matrix &matrix){ //get random numbers


  #pragma omp parallel shared(result)
  {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::normal_distribution<double> dis(1, 2);

    #pragma omp for schedule(static)
    for (size_t i = 0; i < matrix.rows(); ++i) 
    {

      for (size_t j = 0; j < matrix.cols(); ++j) {

       matrix(i, j)=dis(gen);
     }
    }
  }

}

int main(){

	constexpr size_t rows = 100;
	constexpr size_t cols = 100;

  auto time1 = std::chrono::steady_clock::now(); //start

  Matrix A(rows,cols);
  get_random_vector_OpenMp(A);

  std::cout << ToString_Linear(A) << std::endl;

  auto time2 = std::chrono::steady_clock::now(); //end

  auto delta= std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1);

  std::cout<<delta.count()<<std::endl;

	return 0;
}