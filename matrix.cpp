#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <string>

matrix::matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {};

void matrix::fill(std::vector<double> nums) {
	if (nums.size() > rows * cols) {
		std::cout << "Too many elements, cannot fit all of them in matrix" << std::endl;
		return;
	}

	if (nums.size() < rows * cols) {
		std::cout << "Too few elements" << std::endl;
		return;
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			data[i][j] = nums[(i * cols) + j];
		}
	}
}

void matrix::quad(std::vector<double> nums) {
	if (nums.size() % 2 != 0) {
		std::cout << "Odd number of elements, last of them not going to be in matrix" << std::endl;
		nums.pop_back();
	}

	int n = nums.size() / 2;
	rows = n;
	cols = n;
	data.resize(n);

	for (auto& row : data) {
		row.resize(n);
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			data[i][j] = nums[(i * cols) + j];
		}
	}
}

void matrix::fit(std::vector<double> nums, double missing_value) {
	if (nums.size() > rows * cols) std::cout << "Too many elements, not all of them will be in matrix" << std::endl;

	if (nums.size() < rows * cols) {
		std::cout << "Too few elements, remaining elements in matrix will be " << missing_value << std::endl;
		while (nums.size() < rows * cols) nums.push_back(missing_value);
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			data[i][j] = nums[(i * cols) + j];
		}
	}
}

void matrix::set(int row, int col, double value) {
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		data[row][col] = value;
	}
	else {
		std::cout << "Element outside the matrix" << std::endl;
	}
}

double matrix::get(int row, int col) {
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		return data[row][col];
	}
	else {
		std::cout << "Element outside the matrix" << std::endl;
		return NULL;
	}
}

void matrix::change_shape(int n_row, int n_col) {
	if (rows * cols > n_row * n_col) {
		std::cout << "New matrix size is less then previos" << std::endl;
		return;
	}
	
	if (rows * cols < n_row * n_col) {
		std::cout << "New matrix size is bigger then previos" << std::endl;
		return;
	}

	std::vector<double> numbers;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			numbers.push_back(data[i][j]);
		}
	}

	rows = n_row;
	cols = n_col;

	data.resize(rows);

	for (auto& row : data) {
		row.resize(cols);
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			data[i][j] = numbers[(i * cols) + j];
		}
	}
}

void matrix::fit_shape(int n_row, int n_col, double missing_value) {
	std::vector<double> numbers;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			numbers.push_back(data[i][j]);
		}
	}

	if (rows * cols > n_row * n_col) {
		std::cout << "New matrix size is less then previos, not all elements will be in matrix" << std::endl;
	}

	if (rows * cols < n_row * n_col) {
		std::cout << "New matrix size is bigger then previos, remaining elements will be " << missing_value  << std::endl;
		while (numbers.size() < n_row * n_col) numbers.push_back(missing_value);
	}

	rows = n_row;
	cols = n_col;

	data.resize(rows);

	for (auto& row : data) {
		row.resize(cols);
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			data[i][j] = numbers[(i * cols) + j];
		}
	}
}

int matrix::getMaxWidth(){
	int maxNumber = data[0][0];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (std::abs(data[i][j]) > std::abs(maxNumber)) {
				maxNumber = data[i][j];
			}
		}
	}
	return std::to_string(maxNumber).length() + 2;
}

void matrix::print(){
	const int fieldWidth = getMaxWidth();

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << std::setw(fieldWidth) << data[i][j];
		}
		std::cout << std::endl;
	}
}