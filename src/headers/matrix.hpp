#ifndef __MATRIX_H
#define __MATRIX_H

#include "./basic.h"

template <typename T>
class Matrix {
public:
	int nRows, nCols;
	std::vector<std::vector<T>> data;

	Matrix(int nRows, int nCols, const T& _default = 0);

	void edit(int row, int col, const T& value);
	void info(int cellWidth = 3);
};

template <typename T>
Matrix<T>::Matrix(int nRows, int nCols, const T& _default) {
	this->nRows = nRows;
	this->nCols = nCols;
	for (int rowIdx = 0; rowIdx < nRows; ++rowIdx) {
		std::vector<T> row;
		for (int colIdx = 0; colIdx < nCols; ++colIdx) {
			row.push_back(_default);
		}
		this->data.push_back(row);
	}
	std::cout << "Obj created\n";
}

template <typename T>
void Matrix<T>::edit(int row, int col, const T& value) {
	this->data[row][col] = value;
}

template <typename T>
void Matrix<T>::info(int cellWidth) {
	std::cout << "Printing info ..." << std::endl;
	for (int rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
		for (int colIdx = 0; colIdx < this->nCols; ++colIdx) {
			//std::cout << this->data[rowIdx][colIdx] << " ";
			std::cout << std::setw(cellWidth) << this->data[rowIdx][colIdx] << " ";
		}
		std::cout << std::endl;
	}
}

#endif