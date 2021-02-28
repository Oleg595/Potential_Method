#pragma once
#include <vector>
#include <queue>
#include "Matrix.h"
#include"Closed_Type.h"

struct PotentialParams {
	std::vector<int> production_points;
	std::vector<int> consumption_points;
	Matrix table;
};

// ����� ������ �����������
class Potential {
public:
	Potential(PotentialParams const&);

	void northwest_corner_method();   // ����� ������-��������� ����
	std::vector<int> solve();   // ������� ������

	~Potential();
private:
	bool is_optimal_plan(size_t&, size_t&) const;   // �������� ������������� �����
	bool is_optimal_plan(std::vector<int> const&, std::vector<int> const&, size_t&, size_t&) const;   // �������� ������������� �����
	size_t points_in_plan() const;   // ���������� ��� � �����


	std::vector<int> production_points;   // ���������� ����� � ������� ��������
	std::vector<int> consumption_points;   // ����������� � ������� ����������
	Matrix table;   // ������� ��������� ���������
	Matrix plan;   // ���� ���������
};