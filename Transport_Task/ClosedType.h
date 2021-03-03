#pragma once
#include<iostream>
#include<vector>
#include"Matrix.h"
#include "Potential.h"

class ClosedType {
public:
	ClosedType(PotentialParams const&);
	
	PotentialParams const& get_params() const;

	std::vector<int> Production_Points();//возвращает новое количество груза в пунктах хранения
	std::vector<int> Consumption_Points();//возвращает новую потребность в пунктах назначения
	Matrix New_Table();//возвращает новую таблицу стоимости перевозок

	~ClosedType();
private:
	void product_more(int, Matrix const& table);
	void consum_more(int, Matrix const& table);

	PotentialParams params;
};