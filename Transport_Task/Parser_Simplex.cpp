#include"Parser_Simplex.h"

Parser_Simplex::Parser_Simplex(std::vector<int>* product_points, std::vector<int>* consum_points, Matrix* tab) {
	size_n = tab->get_n();
	size_m = tab->get_m();

	ClosedType* cl_t = new ClosedType(PotentialParams{ (*product_points), (*consum_points), (*tab) });// (*product_points), (*consum_points), tab);

	std::vector<int> production_points = cl_t->Production_Points();
	std::vector<int> consumption_points = cl_t->Consumption_Points();
	Matrix matr = cl_t->New_Table();

	new_size_m = matr.get_m();

	std::cout << std::endl;
	matr.print();

	table = Matrix(matr.get_m() + matr.get_n(), matr.get_m() * matr.get_n());
	b = new std::vector<double>;
	func = new std::vector<double>;

	for (int i = 0; i < production_points.size(); i++) {
		double time_doub = (double)production_points[i];
		b->push_back(time_doub);
		for (int j = 0; j < table.get_m(); j++) {
			if (j / consumption_points.size() == i) {
				table[i][j] = 1;
			}
			else {
				table[i][j] = 0;
			}
		}
	}
	for (int i = production_points.size(); i < matr.get_n() + matr.get_m(); i++) {
		b->push_back((double)consumption_points[i - production_points.size()]);
		for (int j = 0; j < table.get_m(); j++) {
			if (j % consumption_points.size() == i - production_points.size()) {
				table[i][j] = 1;
			}
			else {
				table[i][j] = 0;
			}
		}
	}
	std::cout << std::endl;
	for (int i = 0; i < matr.get_n(); i++) {
		for (int j = 0; j < matr.get_m(); j++) {
			func->push_back(matr[i][j]);
		}
	}

	Simplex* simp = new Simplex(&table, b, func);
	answer = simp->Answer_Func();
	answer_var = simp->Answer_Func_Var();
}

void Parser_Simplex::Get_Answer() {
	std::cout << std::endl;
	std::cout << "F(x) = " << answer << std::endl;
	for (size_t i = 0; i < size_n; i++) {
		std::cout << std::endl;
		for (size_t j = 0; j < size_m; j++) {
			std::cout << 'x' << i + 1 << j + 1 << " = " << answer_var[i * new_size_m + j] << ' ';
		}
	}
}