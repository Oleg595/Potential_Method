#pragma once
#include<iostream>
#include<vector>
#include"Matrix.h"
#include "Potential.h"

class ClosedType {
public:
	ClosedType(PotentialParams const&);
	
	PotentialParams const& get_params() const;

	std::vector<int> Production_Points();//���������� ����� ���������� ����� � ������� ��������
	std::vector<int> Consumption_Points();//���������� ����� ����������� � ������� ����������
	Matrix New_Table();//���������� ����� ������� ��������� ���������

	~ClosedType();
private:
	void product_more(int, Matrix const& table);
	void consum_more(int, Matrix const& table);

	PotentialParams params;
};