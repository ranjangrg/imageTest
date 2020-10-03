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
	public:
		// class state being public is more convenient
		unsigned int nRows, nCols;
		std::vector<T> data;

		Matrix(int nRows, int nCols);
		Matrix(int nRows, int nCols, const T& _defaultValue);
		Matrix(std::initializer_list<std::initializer_list<T>> rowCol);	// e.g. Matrix<int> ({{1,2}, {3,4}})
		Matrix(std::initializer_list<T> rowOnly); 
		//~Matrix();

		// CRUD
		T& getFirst() const;
		T& get(const unsigned int& rowIdx, const unsigned int& colIdx) const;
		bool addRow(std::vector<T> row);
		bool addRow(std::initializer_list<T> row);
		void edit(unsigned rowIdx, unsigned colIdx, const T& value);
		void info(int cellWidth = 3) const;	// cellWidth = 3 is good enough for signed ints between -999 to 999

		void clear();	// clear the vector data

		// 
		const unsigned int* getDims() const;

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

		// logical operators
		bool& operator == (const Matrix<T>& rhs);
		const bool& operator == (const Matrix<T>& rhs) const;
		bool& operator != (const Matrix<T>& rhs);
		const bool& operator != (const Matrix<T>& rhs) const;
	};
}

namespace Matrix {
	/* 
	===========================================
	| special methods definition for matrices |
	===========================================
	*/
	template <typename T, typename U>
	const bool _compareDims(const Matrix<U>& matA, const Matrix<U>& matB);

	template <typename T>
	Matrix<T>& _addMatrices(const Matrix<T>& lhs, const Matrix<T>& rhs);

	template <typename T, typename U>
	Matrix<T>& _addMatrices(const Matrix<T>& lhs, const Matrix<U>& rhs);

	template <typename T, typename U>
	Matrix<U>& _multiplyMatrixWithScalar(const Matrix<T>& mat, const U& scalarFactor);

	template <typename T>
	Matrix<T>& _convoluteUsingMatrix(const Matrix<T>& mat, const Matrix<T>& kernelMat);

	// special method for Pixel matrix
	template <typename T>
	Matrix<Image::Pixel>& _convoluteUsingMatrix(const Matrix<Image::Pixel>& mat, const Matrix<T>& kernelMat);

	template <typename T, typename U>
	bool _areSame(const Matrix<T>& lhs, const Matrix<U>& rhs);
}

namespace Matrix {
	/* 
	===============================================
	| Class and methods implementation begins now |
	===============================================
	*/
	template <typename T>
	Matrix<T>::Matrix(int nRows, int nCols) {
		this->data.clear();
		this->data.reserve(nRows * nCols);
		this->nRows = nRows;
		this->nCols = nCols;
		for (int idx = 0; idx < (nRows * nCols); ++idx) {
			T defaultValue = T();
			this->data.push_back(defaultValue);
		}
	}

	template <typename T>
	Matrix<T>::Matrix(int nRows, int nCols, const T& _defaultValue) {
		this->data.clear();
		this->data.reserve(nRows * nCols);
		this->nRows = nRows;
		this->nCols = nCols;
		for (int idx = 0; idx < (nRows * nCols); ++idx) {
			this->data.push_back(_defaultValue);
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
				throw constructorBadArgumentException();
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
			throw constructorBadArgumentException();
		}
	}

	template <typename T>
	T& Matrix<T>::getFirst() const {
		if ( (this->nRows + this->nCols) <= 0 ) {
			throw noDataException();
		}
		T value = this->data.at(0);
		T& valueRef = value;
		return valueRef;
	}

	template <typename T>
	T& Matrix<T>::get(const unsigned int& rowIdx, const unsigned int& colIdx) const {
		bool validIdx = (rowIdx < this->nRows) && (colIdx < this->nCols);
		if (!validIdx) {
			throw getException();
		}
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
			throw addRowException();
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
		// check if row and col out of index range 
		if ( 
			(rowIdx < 0) || (colIdx < 0) ||	// not needed probably: should be apparent it is unsigned 
			(rowIdx >= this->nRows) || (colIdx >= this->nCols)
		) {
			throw editException();
		}
		this->data.at((rowIdx * this->nCols) + colIdx) = value;
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
	void Matrix<T>::clear() {
		this->data.clear();
	}

	template <typename T>
	const unsigned int* Matrix<T>::getDims() const{
		unsigned int* size = new unsigned int(2);
		size[0] = this->nRows;
		size[1] = this->nCols;
		return size;
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

	template <typename T>
	bool& Matrix<T>::operator == (const Matrix<T>& rhs) {
		const Matrix<T>& lhs = *this;
		bool areSame = _areSame(lhs, rhs);
		bool& areSameRef = areSame;
		return areSameRef;
	}

	template <typename T>
	bool& Matrix<T>::operator != (const Matrix<T>& rhs) {
		const Matrix<T>& lhs = *this;
		bool areNotSame = !_areSame(lhs, rhs);
		bool& areNotSameRef = areNotSame;
		return areNotSameRef;
	}

}

namespace Matrix {
	/* 
	===============================================
	| special methods implementation for matrices |
	===============================================
	*/

	template <typename T, typename U>
	const bool _compareDims(const Matrix<T>& matA, const Matrix<U>& matB) {
		bool isSameDim = true;
		isSameDim = isSameDim && (matA.nRows == matB.nRows);
		isSameDim = isSameDim && (matA.nCols == matB.nCols);
		return isSameDim;
	}

	template <typename T>
	Matrix<T>& _addMatrices(const Matrix<T>& lhs, const Matrix<T>& rhs) {
		const unsigned int* lhsDims = lhs.getDims();
		const unsigned int* rhsDims = rhs.getDims();
		const unsigned int lhsRows = lhsDims[0], lhsCols = lhsDims[1];		
		const unsigned int rhsRows = rhsDims[0], rhsCols = rhsDims[1];
		Matrix<T>* sum;
		if ( _compareDims(lhs, rhs) ) {
			sum = new Matrix<T>(rhsRows, rhsCols);
			for (unsigned rowIdx = 0; rowIdx < lhsRows; ++rowIdx) {
				for (unsigned colIdx = 0; colIdx < lhsCols; ++colIdx) {
					unsigned idxWithinMatrix = (rowIdx * lhsCols) + colIdx;
					sum->data.at(idxWithinMatrix) = lhs.data.at(idxWithinMatrix) + rhs.data.at(idxWithinMatrix);
				}
			}
		} else {
			throw addException();
		}
		return *sum;
	}

	template <typename T, typename U>
	Matrix<T>& _addMatrices(const Matrix<T>& lhs, const Matrix<U>& rhs) {
		const unsigned int* lhsDims = lhs.getDims();
		const unsigned int* rhsDims = rhs.getDims();
		const unsigned int lhsRows = lhsDims[0], lhsCols = lhsDims[1];		
		const unsigned int rhsRows = rhsDims[0], rhsCols = rhsDims[1];
		Matrix<T>* sum;
		if ( _compareDims(lhs, rhs) ) {
			sum = new Matrix<T>(rhsRows, rhsCols);
			for (unsigned rowIdx = 0; rowIdx < lhsRows; ++rowIdx) {
				for (unsigned colIdx = 0; colIdx < lhsCols; ++colIdx) {
					unsigned idxWithinMatrix = (rowIdx * lhsCols) + colIdx;
					sum->data.at(idxWithinMatrix) = lhs.data.at(idxWithinMatrix) + rhs.data.at(idxWithinMatrix);
				}
			}
		} else {
			throw addException();
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

	// convulate a matrix using another matrix
	template <typename T>
	Matrix<T>& _convoluteUsingMatrix(const Matrix<T>& mat, const Matrix<T>& kernelMat) {
		Matrix<T>* resultantMatrix = new Matrix<T>(mat.nRows, mat.nCols);
		// variable declarations
		T value, valueAtMat, valueAtKernel;
		signed int rowOffset, colOffset, currMatRowIdx, currMatColIdx;
	
		for (unsigned int matRowIdx = 0; matRowIdx < mat.nRows; ++matRowIdx) {
			for (unsigned int matColIdx = 0; matColIdx < mat.nCols; ++matColIdx) {
				// loop through the kernel now
				value = T();
				for (unsigned int kernelRowIdx = 0; kernelRowIdx < kernelMat.nRows; ++kernelRowIdx) {
					for (unsigned int kernelColIdx = 0; kernelColIdx < kernelMat.nCols; ++kernelColIdx) {
						rowOffset = (-1 * int((kernelMat.nRows + 1) / 2)) + 1;
						colOffset = (-1 * int((kernelMat.nCols + 1) / 2)) + 1;
						valueAtKernel = kernelMat.data[kernelRowIdx * kernelMat.nRows + kernelColIdx];
						currMatRowIdx = matRowIdx + kernelRowIdx + rowOffset;
						currMatColIdx = matColIdx + kernelColIdx + colOffset;
						if ( 
							(currMatRowIdx >= 0) && (currMatColIdx >= 0) &&
							(currMatRowIdx < mat.nRows) && (currMatColIdx < mat.nCols)
						) {
							// proceed only if row/col indices are valid(+ve) and within range
							valueAtMat = mat.data[(currMatRowIdx * mat.nRows) + currMatColIdx];
							value = value + (valueAtMat * valueAtKernel);
						}
					}
				}
				resultantMatrix->edit(matRowIdx, matColIdx, value) ;
			}
		}
		return *resultantMatrix;
	}

	// convulate a matrix using another matrix (FIND A BETTER SOLUTION)
	template <typename T>
	Matrix<Image::Pixel>& _convoluteUsingMatrix(const Matrix<Image::Pixel>& mat, const Matrix<T>& kernelMat) {
		Matrix<Image::Pixel>* resultantMatrix = new Matrix<Image::Pixel>(mat.nRows, mat.nCols);
		// variable declarations
		Image::Pixel value, valueAtMat;
		T valueAtKernel;
		signed int rowOffset, colOffset, currMatRowIdx, currMatColIdx;
	
		for (unsigned int matRowIdx = 0; matRowIdx < mat.nRows; ++matRowIdx) {
			for (unsigned int matColIdx = 0; matColIdx < mat.nCols; ++matColIdx) {
				// loop through the kernel now
				Image::Pixel firstPixel = mat.data.at(0);
				value = Image::createPixel(firstPixel.nChannels);
				valueAtMat = Image::createPixel(firstPixel.nChannels);

				for (unsigned int kernelRowIdx = 0; kernelRowIdx < kernelMat.nRows; ++kernelRowIdx) {
					for (unsigned int kernelColIdx = 0; kernelColIdx < kernelMat.nCols; ++kernelColIdx) {
						rowOffset = (-1 * int((kernelMat.nRows + 1) / 2)) + 1;
						colOffset = (-1 * int((kernelMat.nCols + 1) / 2)) + 1;
						valueAtKernel = kernelMat.data[kernelRowIdx * kernelMat.nRows + kernelColIdx];
						currMatRowIdx = matRowIdx + kernelRowIdx + rowOffset;
						currMatColIdx = matColIdx + kernelColIdx + colOffset;
						if ( 
							(currMatRowIdx >= 0) && (currMatColIdx >= 0) &&
							(currMatRowIdx < mat.nRows) && (currMatColIdx < mat.nCols)
						) {
							// proceed only if row/col indices are valid(+ve) and within range
							Image::copyPixels(mat.data[(currMatRowIdx * mat.nRows) + currMatColIdx], valueAtMat);
							value = value + (valueAtMat * valueAtKernel);
						}
					}
				}
				resultantMatrix->edit(matRowIdx, matColIdx, value) ;
			}
		}
		return *resultantMatrix;
	}

	template <typename T, typename U>
	bool _areSame(const Matrix<T>& lhs, const Matrix<U>& rhs) {
		bool areSame = true;
		bool haveSameDims = _compareDims(lhs, rhs);
		if (haveSameDims) {
			for (unsigned int idx = 0; (idx < lhs.data.size()) && areSame; ++idx) {
				areSame = lhs.data[idx] == rhs.data[idx];
			}
		}
		return areSame;
	}

}

#endif