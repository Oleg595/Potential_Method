#include "Matrix.h"

Matrix Matrix::create_matrix(size_t n, size_t m) {
	return Matrix(n, m);
}

Matrix::Matrix() : n{ 0 }, m{ 0 }, matrix{ nullptr } {}

Matrix::Matrix(size_t n, size_t m = 0) : n{ n }, m{ m == 0 ? n : m } {
	matrix = new int* [n];
	for (size_t i = 0; i < n; ++i) {
		matrix[i] = new int[m];
		for (size_t j = 0; j < m; ++j) {
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(Matrix const& other) : Matrix(other.n, other.m) {
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

Matrix::Vector::Vector(int* vector) : vector{ vector } {}

std::vector<double> Matrix::Gauss(std::vector<double> b) {
	for (size_t i = 0; i < n; i++) {
		size_t str = m;
		for (size_t j = 0; j < m; j++) {
			if (fabs(matrix[i][j]) > pow(10, -5)) {
				str = j;
				break;
			}
		}
		if (str == m) {
			if (b[i] == 0) {
				continue;
			}
			else {
				return b;
			}
		}
		for (size_t j = 0; j < m; j++) {
			if (j != str)
				matrix[i][j] /= matrix[i][str];
		}
		b[i] /= matrix[i][str];
		matrix[i][str] = 1.;
		for (size_t j = 0; j < n; j++) {
			if (j != i) {
				for (size_t q = 0; q < m; q++) {
					if (q != str)
						matrix[j][q] -= matrix[j][str] * matrix[i][q];
				}
				b[j] -= matrix[j][str] * b[i];
				matrix[j][str] = 0.;
			}
		}
	}
	return b;
}

Matrix& Matrix::operator=(Matrix other) {
	std::swap(matrix, other.matrix);
	std::swap(n, other.n);
	std::swap(m, other.m);
	return *this;
}

int& Matrix::Vector::operator[](size_t index) {
	return vector[index];
}

int const& Matrix::Vector::operator[](size_t index) const {
	return vector[index];
}

Matrix::Vector Matrix::operator[](size_t index) {
	return Vector(matrix[index]);
}

Matrix::Vector Matrix::operator[](size_t index) const {
	return Vector(matrix[index]);
}

void Matrix::print() const {
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

size_t Matrix::get_n() const {
	return n;
}

size_t Matrix::get_m() const {
	return m;
}

Matrix Matrix::get_transposed() const {
	Matrix AT(m, n);
	for (size_t i = 0; i < m; ++i) {
		for (size_t j = 0; j < n; ++j) {
			AT[i][j] = matrix[j][i];
		}
	}
	return AT;
}

Matrix::~Matrix() {
	for (size_t i = 0; i < n; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}