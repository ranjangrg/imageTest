#ifndef __MATRIX_H
#define __MATRIX_H

#include "./basic.h"

namespace Matrix {
	/*	
	======================================
	| Class, state and method definition |
	======================================
	*/
	template <typename T>
	class Matrix {
	/*
	// class state being public is more convenient
	private:
		unsigned int nRows, nCols;
		// TODO: implement single vector to represent Matrices.
		std::vector<T> data;
	*/
	public:
		// class states
		unsigned int nRows, nCols;
		std::vector<T> data;

		Matrix(int nRows, int nCols, const T& _default = 0);
		Matrix(std::initializer_list<std::initializer_list<T>> rowCol);	// e.g. Matrix<int> ({{1,2}, {3,4}})
		Matrix(std::initializer_list<T> rowOnly); 
		//~Matrix();

		// CRUD
		T& get(const unsigned int& rowIdx, const unsigned int& colIdx) const;
		bool addRow(std::vector<T> row);
		bool addRow(std::initializer_list<T> row);
		void edit(unsigned rowIdx, unsigned colIdx, const T& value);
		void info(int cellWidth = 3) const;	// cellWidth = 3 is good enough for signed ints between -999 to 999

		//
		const unsigned int* getDims() const;
		const bool haveSameDims(const Matrix<T>& otherM) const;

		// Access operator: matrixObj(row, col)
		T& operator () (const unsigned int& rowIdx, const unsigned int& colIdx);
		const T& operator () (const unsigned int& rowIdx, const unsigned int& colIdx) const;

		// mathematical operations
		Matrix<T>& operator + (const Matrix<T>& rhs);
		const Matrix<T>& operator + (const Matrix<T>& rhs) const;
		Matrix<T>& operator - (const Matrix<T>& rhs);
		const Matrix<T>& operator - (const Matrix<T>& rhs) const;

		Matrix<int>& operator * (const int& scalarFactor);
		const Matrix<int>& operator * (const int& scalarFactor) const;
		Matrix<float>& operator * (const float& scalarFactor);
		const Matrix<float>& operator * (const float& scalarFactor) const;
		Matrix<double>& operator * (const double& scalarFactor);
		const Matrix<double>& operator * (const double& scalarFactor) const;
	};
}

namespace Matrix {
	/* 
	===========================================
	| special methods definition for matrices |
	===========================================
	*/
	template <typename T>
	Matrix<T>& _addMatrices(const Matrix<T>& lhs, const Matrix<T>& rhs);

	template <typename T, typename U>
	Matrix<U>& _multiplyMatrixWithScalar(const Matrix<T>& mat, const U& scalarFactor);
}

namespace Matrix {
	/* 
	===============================================
	| Class and methods implementation begins now |
	===============================================
	*/
	template <typename T>
	Matrix<T>::Matrix(int nRows, int nCols, const T& _default) {
		this->data.clear();
		this->data.reserve(nRows * nCols);
		this->nRows = nRows;
		this->nCols = nCols;
		for (int idx = 0; idx < (nRows * nCols); ++idx) {
			this->data.push_back(_default);
		}
	}

	template <typename T>
	Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> rowCol) {
		this->nRows = 0;
		bool validData = (rowCol.size() > 0) ? true : false; // check for rows
		if (validData) {
			bool isFirstRow = true;
			unsigned int currColSize = this->nCols;
			unsigned int prevColSize = currColSize;
			try {
				this->data.clear();
				for (std::initializer_list<T> row : rowCol) {
					currColSize = row.size();

					// code below is run, only on the FIRST iteration/loop
					if (isFirstRow) {
						prevColSize = currColSize;
						this->nCols = currColSize;
						isFirstRow = false;
					}

					// try to catch data with irregular column lengths
					if (currColSize != prevColSize) { throw -1; }

					// populate this->data
					for (T col : row) { this->data.push_back(col); }

					this->nRows++;
					prevColSize = currColSize;
				}
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
			this->data = std::vector<T>{rowOnly};
			this->nRows = 1;
			this->nCols = rowOnly.size();
		} else {
			std::cerr << "[ERR] Invalid row data: Empty row." << std::endl;
		}
	}

	template <typename T>
	T& Matrix<T>::get(const unsigned int& rowIdx, const unsigned int& colIdx) const {
		T value = this->data.at((rowIdx * this->nCols) + colIdx);
		T& valueRef = value;
		return valueRef;
	}

	template <typename T>
	bool Matrix<T>::addRow(std::vector<T> row) {
		bool isAddSuccessful = true;
		try {
			// only if column count matches
			if ( row.size() != this->nCols ) { throw -1; }
			this->data.insert(this->data.end(), row.begin(), row.end());
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
	void Matrix<T>::edit(unsigned rowIdx, unsigned colIdx, const T& value) {
		try {
			// check if row and col out of index range 
			if ( 
				(rowIdx < 0) || (colIdx < 0) ||	// not needed probably: should be apparent it is unsigned 
				(rowIdx >= this->nRows) || (colIdx >= this->nCols)
			) {
				std::string msg =  "[ERR] Matrix edit failed! (row: " + std::to_string(rowIdx) + ", col: " + std::to_string(colIdx) + ") = " + std::to_string(value);
				throw msg;
			}
			this->data.at((rowIdx * this->nCols) + colIdx) = value;
		} catch (std::string msg) {
			std::cerr << msg << std::endl;
		}
	}

	template <typename T>
	void Matrix<T>::info(int cellWidth) const {
		bool matrixIsNotEmpty = (this->nCols > 0) && (this->nRows > 0);
		if (matrixIsNotEmpty) {
			std::cout << std::string( (cellWidth + 1) * this->nCols, '-') << '-' << std::endl; // only for printing lines
			for (int rowIdx = 0; rowIdx < this->nRows; ++rowIdx) {
				for (int colIdx = 0; colIdx < this->nCols; ++colIdx) {
					std::cout << std::setw(cellWidth) << this->data.at((rowIdx * this->nCols) + colIdx) << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::string( (cellWidth + 1) * this->nCols, '-') << '-' << std::endl; // only for printing lines
		}
	}

	template <typename T>
	const unsigned int* Matrix<T>::getDims() const{
		unsigned int* size = new unsigned int(2);
		size[0] = this->nRows;
		size[1] = this->nCols;
		return size;
	}

	template <typename T>
	const bool Matrix<T>::haveSameDims(const Matrix<T>& otherM) const{
		bool isSameDim = true;
		isSameDim = isSameDim && (this->nRows == otherM.nRows);
		isSameDim = isSameDim && (this->nCols == otherM.nCols);
		return isSameDim;
	}

	template <typename T>
	T& Matrix<T>::operator () (const unsigned int& rowIdx, const unsigned int& colIdx) {
		return this->get(rowIdx, colIdx);
	}

	template <typename T>
	Matrix<T>& Matrix<T>::operator + (const Matrix<T>& rhs) {
		const Matrix<T>& lhs = *this;
		Matrix<T>& sum = _addMatrices(lhs, rhs);
		return sum;
	}

	// basically doing A + (-B)
	template <typename T>
	Matrix<T>& Matrix<T>::operator - (const Matrix<T>& rhs) {
		const Matrix<T>& lhs = *this;
		Matrix<T>& productMatrix = _multiplyMatrixWithScalar(rhs, -1);
		Matrix<T>& diff = _addMatrices(lhs, productMatrix);
		return diff;
	}

	template <typename T>
	Matrix<int>& Matrix<T>::operator * (const int& scalarFactor) {
		const Matrix<T>& lhs = *this;
		Matrix<int>& productMatrix = _multiplyMatrixWithScalar(lhs, scalarFactor);
		return productMatrix;
	}

	template <typename T>
	Matrix<float>& Matrix<T>::operator * (const float& scalarFactor) {
		const Matrix<T>& lhs = *this;
		Matrix<float>& productMatrix = _multiplyMatrixWithScalar(lhs, scalarFactor);
		return productMatrix;
	}

	template <typename T>
	Matrix<double>& Matrix<T>::operator * (const double& scalarFactor) {
		const Matrix<T>& lhs = *this;
		Matrix<double>& productMatrix = _multiplyMatrixWithScalar(lhs, scalarFactor);
		return productMatrix;
	}

}

namespace Matrix {
	/* 
	===============================================
	| special methods implementation for matrices |
	===============================================
	*/

	template <typename T>
	Matrix<T>& _addMatrices(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		const unsigned int* lhsDims = lhs.getDims();
		const unsigned int* rhsDims = rhs.getDims();
		const unsigned int lhsRows = lhsDims[0], lhsCols = lhsDims[1];		
		const unsigned int rhsRows = rhsDims[0], rhsCols = rhsDims[1];
		Matrix<T>* sum;
		std::cout << "(0, 0): " << lhs.get(0, 0) << std::endl;
		if ( lhs.haveSameDims(rhs) ) {
			sum = new Matrix<T>(rhsRows, rhsCols);
			for (unsigned rowIdx = 0; rowIdx < lhsRows; ++rowIdx) {
				for (unsigned colIdx = 0; colIdx < lhsCols; ++colIdx) {
					unsigned idxWithinMatrix = (rowIdx * lhsCols) + colIdx;
					sum->data.at(idxWithinMatrix) = lhs.data.at(idxWithinMatrix) + rhs.data.at(idxWithinMatrix);
				}
			}
		} else {
			std::string msg = "[ERR] Matrix Addition failed! Dimensions not same!";
			std::cerr << msg << std::endl;
			sum = new Matrix<T>(0, 0);
		}
		return *sum;
	}

	template <typename T, typename U>
	Matrix<U>& _multiplyMatrixWithScalar(const Matrix<T>& mat, const U& scalarFactor) {
		Matrix<U>* productMatrix = new Matrix<U>(mat.nRows, mat.nCols);
		for (unsigned int idx = 0; idx < (mat.data).size() ; ++idx) {
			productMatrix->data.at(idx) = mat.data.at(idx) * scalarFactor;
		}
		return *productMatrix;
	}

}

#endif