#pragma once
#include<iostream>
#include"Parser.h"
#include"Simplex.h"
#include"ClosedType.h"
#include"Potential.h"

class Parser_Simplex {
public:
	Parser_Simplex(std::vector<int>* product_points, std::vector<int>* consum_points, Matrix* table);

	void Get_Answer();

private:
	std::vector<double>* func;
	std::vector<double>* b;
	Matrix table;
	int size_n;
	int size_m;
	int new_size_m;

	double answer;
	std::vector<double> answer_var;
};