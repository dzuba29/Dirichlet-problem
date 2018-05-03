#include "functions.h"
#include <fstream>

void benchmark(size_t dim, double mulDuration, double runtimeDuration) {
  std::cout.setf(std::ios::fixed);
  std::cout.precision(5);
  std::cout << "║   " << dim << "║   "<< mulDuration << "║   "<< runtimeDuration<< std::endl;
}

void benchmark_to_csv(size_t threads, size_t dim, double mulDuration, double runtimeDuration) {
  std::cout << threads << "," << dim << "," << mulDuration << "," << runtimeDuration << std::endl;
}

void serial_to_csv(const Matrix &matrix){


 	std::fstream file;
	file.open("surface.txt");
	for (size_t i = 0; i < matrix.rows(); ++i) {

	    for (size_t j = 0; j < matrix.cols(); ++j) {

	      file<< matrix(i, j) << ",";
	    }
	    file<< std::endl;
	}
	file.close();
	
}