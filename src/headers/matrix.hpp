#ifndef __MATRIX_H
#define __MATRIX_H

#include "./basic.h"

template <typename T>
class Matrix {
private:
	unsigned int nRows, nCols;
	std::vector<std::vector<T>> data;
public:
	Matrix(int nRows, int nCols, const T& _default = 0);
	//~Matrix();

	// CRUD
	void edit(unsigned row, unsigned col, const T& value);
	void info(int cellWidth = 3);

	// Access operator: matrixObj(row, col)
	T& operator () (const unsigned int& row, const unsigned int& col);
	const T& operator () (const unsigned int& row, const unsigned int& col) const;

	// mathematical operations
	Matrix<T>& operator + (const Matrix<T>& rhs);
	Matrix<T>& operator - (const Matrix<T>& rhs);
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
}

template <typename T>
void Matrix<T>::edit(unsigned row, unsigned col, const T& value) {
	try {
		// check if row and col out of index range
		if ( (row >= this->nRows) || (col >= this->nCols) ) {
			std::string msg =  "[ERR] Edit failed: (row: " + std::to_string(row) + ", col: " + std::to_string(col) + ") = " + std::to_string(value);
			throw msg;
		}
		this->data.at(row).at(col) = value;
	} catch (std::string msg) {
		std::cout << msg << std::endl;
	}
}

template <typename T>
void Matrix<T>::info(int cellWidth) {
	std::cout << std::string( (cellWidth + 1) * this->nCols, '-') << '-' << std::endl;
	for (int rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
		for (int colIdx = 0; colIdx < this->nCols; ++colIdx) {
			std::cout << std::setw(cellWidth) << this->data.at(rowIdx).at(colIdx) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::string( (cellWidth + 1) * this->nCols, '-') << '-' << std::endl;
}

template <typename T>
T& Matrix<T>::operator () (const unsigned int& row, const unsigned int& col) {
	return this->data.at(row).at(col);
}

template <typename T>
Matrix<T>& Matrix<T>::operator + (const Matrix<T>& rhs) {
	Matrix<T>* sum = new Matrix<T>(rhs.nRows, rhs.nCols); 
	for (unsigned rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
		for (unsigned colIdx = 0; colIdx < this->nCols; ++colIdx) {
			sum->data.at(rowIdx).at(colIdx) = this->data.at(rowIdx).at(colIdx) + rhs.data.at(rowIdx).at(colIdx);
		}
	}
	return *sum;
}

// maybe better to do A + (-B) rather than code all the loops
template <typename T>
Matrix<T>& Matrix<T>::operator - (const Matrix<T>& rhs) {
	Matrix<T>* sum = new Matrix<T>(rhs.nRows, rhs.nCols); 
	for (unsigned rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
		for (unsigned colIdx = 0; colIdx < this->nCols; ++colIdx) {
			sum->data.at(rowIdx).at(colIdx) = this->data.at(rowIdx).at(colIdx) - rhs.data.at(rowIdx).at(colIdx);
		}
	}
	return *sum;
}

#endif