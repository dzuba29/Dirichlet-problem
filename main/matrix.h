#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <vector>
#include <iostream>
#include <string>


std::vector<double> get_random_OpenMp(size_t size);
class Matrix {

public:

  Matrix(size_t rows, size_t cols)
  : m_rows(rows)
  , m_cols(cols)
  , m_data(rows * cols)
  {}


  inline size_t rows() const {
    return m_rows;
  }

  inline size_t cols() const {
    return m_cols;
  }

  inline double &operator()(size_t row, size_t col){
    return m_data[row * m_cols + col];
  }

  inline const double &operator()(size_t row, size_t col) const{
    return m_data[row * m_cols + col];
  } 

  Matrix operator * (const Matrix& matrix);

  static Matrix rand(size_t rows,size_t cols){

    return Matrix(rows,cols,get_random_OpenMp(rows*cols));

  }

private:

  Matrix(size_t rows, size_t cols,const std::vector<double> &data)
  : m_rows(rows)
  , m_cols(cols)
  , m_data(data)
  {}

  size_t m_rows;
  size_t m_cols;
  std::vector<double> m_data;

};

std::string ToString(const Matrix &matrix);
std::string ToCSV(const Matrix &matrix,const double time);
Matrix MultLinear(const Matrix &A,const Matrix &B);
Matrix MultOpenMp(const Matrix &A,const Matrix &B);
Matrix MultOpenMp2(const Matrix &A,const Matrix &B);
std::vector<double> get_random_OpenMp(size_t size);
#endif // __MATRIX_H__