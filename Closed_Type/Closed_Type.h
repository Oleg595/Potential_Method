#pragma once
#include<iostream>
#include<vector>
#include"Matrix.h"

class Closed_Type {
public:
	Closed_Type(std::vector<int> production_points, std::vector<int> consumption_points, Matrix* table);
	std::vector<int> Production_Points();//���������� ����� ���������� ����� � ������� ��������
	std::vector<int> Consumption_Points();//���������� ����� ����������� � ������� ����������
	Matrix New_Table();//���������� ����� ������� ��������� ���������
private:
	std::vector<int> product_points;//���������� ����� � ������� ��������
	std::vector<int> consum_points;//����������� � ������� ����������
	Matrix data;//������������� ������� ��������� ���������
	void ProductMore(int div, Matrix* table);
	void ConsumMore(int div, Matrix* table);
};