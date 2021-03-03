#pragma once
#include <iostream>
#include<vector>

class Matrix {
private:
	struct Vector;
public:
	Matrix();
	Matrix(size_t, size_t);
	Matrix(Matrix const&);

	std::vector<double> Gauss(std::vector<double> b);
	void Change_Str(size_t i, size_t j);
	void Change_Col(size_t i, size_t j);

	static Matrix create_matrix(size_t, size_t);

	Matrix& operator=(Matrix);
	Vector operator[](size_t);
	Vector operator[](size_t) const;

	size_t get_n() const;
	size_t get_m() const;
	Matrix get_transposed() const;

	void print() const;

	~Matrix();
private:
	struct Vector {
		Vector(int*);
		int& operator[](size_t);
		int const& operator[](size_t) const;
	private:
		int* vector;
	};

	int** matrix;
	size_t n, m;
};