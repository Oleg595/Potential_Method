#pragma once
#include<iostream>
#include"Parser.h"
#include"Simplex.h"
#include"ClosedType.h"
#include"Potential.h"

enum LT {
	LT_EQ = 0,
	LT_GT,
	LT_LE,
	LT_ERROR
};

struct Limitations {
public:
	Limitations();
	void add_limitations(std::pair<std::vector<double>, LT>&&);
	std::vector<std::pair<std::vector<double>, LT>> limitations;
};

struct LinearData {
	std::vector<bool> sign;//больше 0?
	std::vector<double> func;//целевая функция
	Limitations system;
};

class ParserSimplex {
public:
	ParserSimplex(std::vector<int>* product_points, std::vector<int>* consum_points, Matrix* table);

	void Get_Answer();

	LinearData get_Data();

private:
	std::vector<double>* func;
	std::vector<double>* b;
	void to_dual(std::vector<double>& function, Limitations& limitations, size_t original_dimension);
	Matrix table;
	int size_n;
	int size_m;
	int new_size_m;

	Limitations dual_limitations;
	std::vector<double> dual_function;

	LinearData line;

	double answer;
	std::vector<double> answer_var;
};