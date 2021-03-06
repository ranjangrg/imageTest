#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <iostream>
#include <exception>	// for custom exceptions

namespace Matrix {
	struct constructorBadArgumentException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Matrix] Matrix(): Bad AND/OR incomplete argument data.\n";
		}
	};

	struct editException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Matrix] edit(rowIdx, colIdx) failed! Invalid index values.\n"; 
		}
	};

	struct addRowException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Matrix] addRow(row) failed! Possible that number of cols don't match.\n";
		}
	};

	struct getException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Matrix] get(rowIdx, colIdx) failed! Check if indices are within range.\n";
		}
	};

	struct dimensionsNotSameException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Matrix] Dimensions not same!";
		}
	};

	struct noDataException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Matrix] No data within matrix!";
		}
	};

	// TODO: maybe have this nested with dimensionsNotSameException()
	struct addException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Matrix] Add failed! Dimensions not same!";
		}
	};
}

namespace Image {
	struct pixelChannelCountNotSameException : public std::exception {
		const char * what() const throw() {
			return "\n[ERR] [Pixel] Pixels don't have same number of channels. Operation failed.";
		}
	};
}

#endif