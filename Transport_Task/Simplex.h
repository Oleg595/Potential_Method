#pragma once
#include"Parser.h"

struct Matrix;

class Simplex {
public:
	Simplex(Matrix* A, std::vector<double>* st, std::vector<double>* c);
	double Answer_Func();
	std::vector<double> Answer_Func_Var();
private:
	std::vector<std::pair<std::vector<double>, size_t>> data;//�����������, � ������� ����������, ���������� ����� ������ ����������
	std::vector<double> func;//������, ���������� �������
	std::vector<double> delta;//������ delt
	std::vector<size_t> add_var;
	double answer;//�����
	bool have_ans;
	size_t num_var;
	void Choose(size_t i, size_t min);
	size_t Determine(size_t i);
	size_t Check();
	size_t Num_Var(std::vector<double> vector);
	bool Check_Data();
	void Positive_b();
};