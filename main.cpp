#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Matrix {

public:
  Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_data(rows * cols){}


  size_t rows() const {
    return m_rows;
  }

  size_t cols() const {
    return m_cols;
  }

  double &operator()(size_t row, size_t col){
    return m_data[row * m_cols + col];
  }

 
private:
  size_t m_rows;
  size_t m_cols;
  std::vector<double> m_data;

};


int main(){

	constexpr size_t rows = 4;
	constexpr size_t cols = 4;

	Matrix A(rows, cols);
	Matrix B(rows, cols);
	Matrix C(rows, cols);

	for(size_t i = 0; i < A.rows(); ++i) {
		for(size_t j = 0; j < A.cols(); ++j) {
	 		 A(i,j) = 1;
	 		 B(i,j)=1;
	 		 C(i,j)=0;
		}
	}


	//C=A*B;
	
	
	return 0;
}