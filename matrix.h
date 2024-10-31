#pragma once
#include <vector>

class matrix
{
public:
	matrix(int rows = 0, int cols = 0);
	void fill(std::vector<double> nums);
	void quad(std::vector<double> nums);
	void fit(std::vector<double> nums, double missing_value = 0);
	void set(int row, int col, double value);
	double get(int row, int col);
	void change_shape(int n_row, int n_col);
	void fit_shape(int n_row, int n_col, double missing_value = 0);
	void print();

private:
	int rows, cols;
	std::vector<std::vector<double>> data;
	int getMaxWidth();
};