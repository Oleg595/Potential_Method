#include"Closed_Type.h"

Closed_Type::Closed_Type(std::vector<int> production_points, std::vector<int> consumption_points, Matrix* table) : product_points(production_points),
consum_points(consumption_points) {
	int num1 = 0;
	int num2 = 0;
	for (int i = 0; i < product_points.size(); i++) {
		num1 += product_points[i];
	}
	for (int i = 0; i < consum_points.size(); i++) {
		num2 += consum_points[i];
	}
	if (num1 == num2) {
		data = *(table);
		return;
	}
	if (num1 > num2) {
		ProductMore(num1 - num2, table);
		return;
	}
	ConsumMore(num2 - num1, table);
}

void Closed_Type::ProductMore(int div, Matrix* table) {
	consum_points.push_back(div);
	data = Matrix(table->get_n(), table->get_m() + 1);
	for (size_t i = 0; i < table->get_n(); i++) {
		for (size_t j = 0; j < table->get_m(); j++) {
			data[i][j] = (*table)[i][j];
		}
	}
	for (size_t i = 0; i < table->get_n(); i++) {
		data[i][table->get_m()] = 0;
	}
}

void Closed_Type::ConsumMore(int div, Matrix* table) {
	product_points.push_back(div);
	data = Matrix(table->get_n() + 1, table->get_m());
	for (size_t i = 0; i < table->get_n(); i++) {
		for (size_t j = 0; j < table->get_m(); j++) {
			data[i][j] = (*table)[i][j];
		}
	}
	for (size_t i = 0; i < table->get_m(); i++) {
		data[table->get_n()][i] = 0;
	}
}

std::vector<int> Closed_Type::Production_Points() {
	return product_points;
}

std::vector<int> Closed_Type::Consumption_Points() {
	return consum_points;
}

Matrix Closed_Type::New_Table() {
	return data;
}