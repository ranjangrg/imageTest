#ifndef __MATRIX_H
#define __MATRIX_H

#include "./basic.h"

/*	
======================================
| Class, state and method definition |
======================================
*/
template <typename T>
class Matrix {
private:
	unsigned int nRows, nCols;
	std::vector<std::vector<T>> data;
public:
	Matrix(int nRows, int nCols, const T& _default = 0);
	Matrix(std::initializer_list<std::initializer_list<T>> rowCol);
	Matrix(std::initializer_list<T> rowOnly);
	//~Matrix();

	// CRUD
	bool addRow(std::vector<T> row);
	bool addRow(std::initializer_list<T> row);
	void edit(unsigned row, unsigned col, const T& value);
	void info(int cellWidth = 3);

	//
	const unsigned int* getDims();
	const bool haveSameDims(const Matrix<T>& otherM);

	// Access operator: matrixObj(row, col)
	T& operator () (const unsigned int& row, const unsigned int& col);
	const T& operator () (const unsigned int& row, const unsigned int& col) const;

	// mathematical operations
	Matrix<T>& operator + (const Matrix<T>& rhs);
	Matrix<T>& operator - (const Matrix<T>& rhs);
};

/* 
===============================================
| Class and methods implementation begins now |
===============================================
*/
template <typename T>
Matrix<T>::Matrix(int nRows, int nCols, const T& _default) {
	this->data.clear();
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
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> rowCol) {
	bool validData = (rowCol.size() > 0) ? true : false;
	if (validData) {
		bool isFirstRow = true;
		unsigned int currColSize = this->nCols;
		unsigned int prevColSize = currColSize;
		try {
			this->data.clear();
			std::vector<std::vector<T>> data;
			for (auto row : rowCol) {
				currColSize = row.size();
				if (isFirstRow) {
					prevColSize = currColSize;
					isFirstRow = false;
				}
				// try to catch data with irregular column lengths
				if (currColSize != prevColSize) { throw -1; }
				
				data.push_back(row);
				prevColSize = currColSize;
			}
			this->data = data;
			this->nRows = data.size();
			this->nCols = data.at(0).size();
		} catch (int e) {
			this->data.clear();
			this->nRows = 0;
			this->nCols = 0;
			std::cerr << "[ERR] Bad data (as argument) for Matrix constructor." << std::endl;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> rowOnly) {
	bool validData = (rowOnly.size() > 0) ? true : false;
	if (validData) {
		this->data.clear();
		this->data.push_back(rowOnly);
		this->nRows = 1;
		this->nCols = rowOnly.size();
	} else {
		std::cerr << "[ERR] Invalid row data: Empty row." << std::endl;
	}
}

template <typename T>
bool Matrix<T>::addRow(std::vector<T> row) {
	bool isAddSuccessful = true;
	try {
		// only if column count matches
		if ( row.size() != this->nCols ) { throw -1; }
		this->data.push_back(row);
		this->nRows++;
	} catch (...) {
		isAddSuccessful = false;
		std::cerr << "[ERR] Matrix: Adding row failed! Columns count doesn't match." << std::endl;
	}
	return isAddSuccessful;
}

template <typename T>
bool Matrix<T>::addRow(std::initializer_list<T> row) {
	std::vector<T> rowVector = row;
	bool isAddSuccessful = this->addRow(rowVector);	
	return isAddSuccessful;
}

template <typename T>
void Matrix<T>::edit(unsigned row, unsigned col, const T& value) {
	try {
		// check if row and col out of index range
		if ( (row >= this->nRows) || (col >= this->nCols) ) {
			std::string msg =  "[ERR] Matrix edit failed! (row: " + std::to_string(row) + ", col: " + std::to_string(col) + ") = " + std::to_string(value);
			throw msg;
		}
		this->data.at(row).at(col) = value;
	} catch (std::string msg) {
		std::cerr << msg << std::endl;
	}
}

template <typename T>
void Matrix<T>::info(int cellWidth) {
	bool matrixIsNotEmpty = (this->nCols > 0) && (this->nRows > 0);
	if (matrixIsNotEmpty) {
		std::cout << std::string( (cellWidth + 1) * this->nCols, '-') << '-' << std::endl;
		for (int rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
			for (int colIdx = 0; colIdx < this->nCols; ++colIdx) {
				std::cout << std::setw(cellWidth) << this->data.at(rowIdx).at(colIdx) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::string( (cellWidth + 1) * this->nCols, '-') << '-' << std::endl;
	}
}

template <typename T>
const unsigned int* Matrix<T>::getDims() {
	unsigned int* size = new unsigned int(2);
	size[0] = this->nRows;
	size[1] = this->nCols;
	return size;
}

template <typename T>
const bool Matrix<T>::haveSameDims(const Matrix<T>& otherM) {
	bool isSameDim = true;
	isSameDim = isSameDim && (this->nRows == otherM.nRows);
	isSameDim = isSameDim && (this->nCols == otherM.nCols);
	return isSameDim;
}

template <typename T>
T& Matrix<T>::operator () (const unsigned int& row, const unsigned int& col) {
	return this->data.at(row).at(col);
}

template <typename T>
Matrix<T>& Matrix<T>::operator + (const Matrix<T>& rhs) {
	Matrix<T>* sum;
	if ( this->haveSameDims(rhs) ) {
		sum = new Matrix<T>(rhs.nRows, rhs.nCols);
		for (unsigned rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
			for (unsigned colIdx = 0; colIdx < this->nCols; ++colIdx) {
				sum->data.at(rowIdx).at(colIdx) = this->data.at(rowIdx).at(colIdx) + rhs.data.at(rowIdx).at(colIdx);
			}
		}		
	} else {
		std::string msg = "[ERR] Matrix Addition failed! Dimensions not same!";
		std::cerr << msg << std::endl;
		sum = this; 
	}

	return *sum;
}

// maybe better to do A + (-B) rather than code all the loops
template <typename T>
Matrix<T>& Matrix<T>::operator - (const Matrix<T>& rhs) {
	Matrix<T>* diff;
	// Testing try catch (maybe good for more than one exception)
	// currently try-catch maynot be a good idea 
	try {
		if ( this->haveSameDims(rhs) ) {
			diff = new Matrix<T>(rhs.nRows, rhs.nCols); 
		} else {
			throw "[ERR] Matrix Difference failed! Dimensions not same!";
		}
		Matrix<T>* diff = new Matrix<T>(rhs.nRows, rhs.nCols); 
		for (unsigned rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
			for (unsigned colIdx = 0; colIdx < this->nCols; ++colIdx) {
				diff->data.at(rowIdx).at(colIdx) = this->data.at(rowIdx).at(colIdx) - rhs.data.at(rowIdx).at(colIdx);
			}
		}
	} catch (const char* msg) {
		std::cerr << msg << std::endl;
		diff = this; 
	}
	return *diff;
}

#endif