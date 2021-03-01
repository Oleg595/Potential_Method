#pragma once
#include<iostream>
#include<vector>
#include"Matrix.h"

class Closed_Type {
public:
	Closed_Type(std::vector<int> production_points, std::vector<int> consumption_points, Matrix* table);
	std::vector<int> Production_Points();//возвращает новое количество груза в пунктах хранения
	std::vector<int> Consumption_Points();//возвращает новую потребность в пунктах назначения
	Matrix New_Table();//возвращает новую таблицу стоимости перевозок
private:
	std::vector<int> product_points;//количество груза в пунктах хранения
	std::vector<int> consum_points;//потребность в пунктах назначения
	Matrix data;//соответствует таблице стоимости перевозок
	void ProductMore(int div, Matrix* table);
	void ConsumMore(int div, Matrix* table);
};