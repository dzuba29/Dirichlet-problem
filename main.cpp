#include <iostream>
#include <vector>
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

  const double &operator()(size_t row, size_t col) const{
    return m_data[row * m_cols + col];
  }

 
 
private:
  size_t m_rows;
  size_t m_cols;
  std::vector<double> m_data;

};

std::string ToString(const Matrix &matrix){

  std::stringstream outStream;
  for (size_t i = 0; i < matrix.rows(); ++i) {

    for (size_t j = 0; j < matrix.cols(); ++j) {

      outStream << matrix(i, j) << " ";
    }
    outStream << std::endl;
  }
return outStream.str();

}

int main(){

	constexpr size_t rows = 4;
	constexpr size_t cols = 4;

  Matrix A(rows,cols);
  ToString(A);

	return 0;
}