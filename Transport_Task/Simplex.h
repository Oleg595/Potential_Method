#pragma once
#include"Parser.h"

struct Matrix;

class Simplex {
public:
	Simplex(Matrix* A, std::vector<double>* st, std::vector<double>* c);
	double Answer_Func();
	std::vector<double> Answer_Func_Var();
private:
	std::vector<std::pair<std::vector<double>, size_t>> data;//неравенства, в которых переменные, выражаются через другие переменные
	std::vector<double> func;//вектор, содержащий функцию
	std::vector<double> delta;//вектор delt
	std::vector<size_t> add_var;
	double answer;//ответ
	bool have_ans;
	size_t num_var;
	void Choose(size_t i, size_t min);
	size_t Determine(size_t i);
	size_t Check();
	size_t Num_Var(std::vector<double> vector);
	bool Check_Data();
	void Positive_b();
};