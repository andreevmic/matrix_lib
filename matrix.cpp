#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

matrix::matrix(int rows, int cols)
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {}

/**
 * Fills the matrix with values from a vector.
 *
 * @param nums Vector of values to fill the matrix.
 * If the size of the vector does not match the size of the matrix,
 * an error message will be displayed.
 */
void matrix::fill(std::vector<double> nums) {
    if (nums.size() != rows * cols) {
        std::cout << "Incorrect number of elements. Expected " << rows * cols << ", got " << nums.size() << std::endl;
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = nums[(i * cols) + j];
        }
    }
}

/**
 * Sets a square matrix from a vector of values.
 *
 * @param nums Vector of values to fill the square matrix.
 * If the number of values is odd, the last element will be ignored.
 */
void matrix::quad(std::vector<double> nums) {
    if (nums.size() % 2 != 0) {
        nums.pop_back(); // Remove the last element
    }

    int n = nums.size() / 2;
    rows = n;
    cols = n;
    data.assign(n, std::vector<double>(n)); // Use assign to allocate memory and initialize

    fill(nums); // Fill the matrix
}

/**
 * Fills the matrix with values, allowing for a value for missing elements.
 *
 * @param nums Vector of values to fill the matrix.
 * @param missing_value Value used to fill missing elements
 * if the size of the vector is less than the size of the matrix.
 */
void matrix::fit(std::vector<double> nums, double missing_value) {
    if (nums.size() < rows * cols) {
        std::cout << "Too few elements. Filling with " << missing_value << std::endl;
        nums.resize(rows * cols, missing_value); // Fill missing elements
    }
    else if (nums.size() > rows * cols) {
        std::cout << "Too many elements. Only the first " << (rows * cols) << " will be used." << std::endl;
        nums.resize(rows * cols); // Trim excess elements
    }

    fill(nums); // Fill the matrix
}

/**
 * Sets a value in the specified cell of the matrix.
 *
 * @param row Row number (index).
 * @param col Column number (index).
 * @param value Value to set.
 * If the specified indices are out of bounds,
 * an error message will be displayed.
 */
void matrix::set(int row, int col, double value) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        data[row][col] = value;
    }
    else {
        std::cout << "Element outside the matrix" << std::endl;
    }
}

/**
 * Gets the value from the specified cell of the matrix.
 *
 * @param row Row number (index).
 * @param col Column number (index).
 * @return Value in the specified cell of the matrix.
 * If the specified indices are out of bounds,
 * an error message is displayed and 0 is returned.
 */
double matrix::get(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return data[row][col];
    }
    else {
        std::cout << "Element outside the matrix" << std::endl;
        return 0.0; // Return 0 instead of NULL for double
    }
}

/**
 * Changes the size of the matrix, preserving data.
 *
 * @param n_row New number of rows.
 * @param n_col New number of columns.
 * If the new size does not match the previous size,
 * an error message will be displayed.
 */
void matrix::change_shape(int n_row, int n_col) {
    if (rows * cols != n_row * n_col) {
        std::cout << "New matrix size does not match previous size." << std::endl;
        return;
    }

    std::vector<double> numbers;
    for (const auto& row : data) {
        numbers.insert(numbers.end(), row.begin(), row.end());
    }

    rows = n_row;
    cols = n_col;
    data.assign(n_row, std::vector<double>(n_col));

    fill(numbers); // Fill the new matrix
}

/**
 * Changes the size of the matrix, filling missing elements with a specified value.
 *
 * @param n_row New number of rows.
 * @param n_col New number of columns.
 * @param missing_value Value to fill missing elements.
 */
void matrix::fit_shape(int n_row, int n_col, double missing_value) {
    std::vector<double> numbers;
    for (const auto& row : data) {
        numbers.insert(numbers.end(), row.begin(), row.end());
    }

    if (numbers.size() < n_row * n_col) {
        std::cout << "New matrix size is larger than previous. Filling with " << missing_value << std::endl;
        numbers.resize(n_row * n_col, missing_value);
    }

    rows = n_row;
    cols = n_col;
    data.assign(n_row, std::vector<double>(n_col));

    fill(numbers); // Fill the new matrix
}

/**
 * Finds the maximum width of an element in the matrix for formatted output.
 *
 * @return Field width for the largest number in the matrix.
 */
int matrix::getMaxWidth() const {
    int maxNumber = data[0][0];
    for (const auto& row : data) {
        for (double num : row) {
            maxNumber = std::max(maxNumber, static_cast<int>(std::abs(num)));
        }
    }
    return std::to_string(maxNumber).length() + 2;
}

/**
 * Prints the matrix to the console with formatting.
 */
void matrix::print() const {
    const int fieldWidth = getMaxWidth();
    for (const auto& row : data) {
        for (double value : row) {
            std::cout << std::setw(fieldWidth) << value;
        }
        std::cout << std::endl;
    }
}
