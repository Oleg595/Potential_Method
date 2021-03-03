#include"Parser_Simplex.h"

ParserSimplex::ParserSimplex(std::vector<int>* product_points, std::vector<int>* consum_points, Matrix* tab) {
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
		//double time_doub = (double)production_points[i];
		std::pair<std::vector<double>, LT> time_pair;
		b->push_back(production_points[i]);
		for (int j = 0; j < table.get_m(); j++) {
			if (j / consumption_points.size() == i) {
				time_pair.first.push_back(1.);
				table[i][j] = 1;
			}
			else {
				time_pair.first.push_back(0.);
				table[i][j] = 0;
			}
		}
		time_pair.first.push_back((double)production_points[i]);
		time_pair.second = LT::LT_EQ;
		line.system.add_limitations(std::move(time_pair));
	}
	for (int i = production_points.size(); i < matr.get_n() + matr.get_m(); i++) {
		b->push_back((double)consumption_points[i - production_points.size()]);
		std::pair<std::vector<double>, LT> time_pair;
		for (int j = 0; j < table.get_m(); j++) {
			if (j % consumption_points.size() == i - production_points.size()) {
				time_pair.first.push_back(1.);
				table[i][j] = 1;
			}
			else {
				time_pair.first.push_back(0.);
				table[i][j] = 0;
			}
		}
		time_pair.first.push_back((double)consumption_points[i- production_points.size()]);
		time_pair.second = LT::LT_EQ;
		line.system.add_limitations(std::move(time_pair));
	}
	std::cout << std::endl;
	for (int i = 0; i < matr.get_n(); i++) {
		for (int j = 0; j < matr.get_m(); j++) {
			func->push_back(matr[i][j]);
		}
	}

	for (int i = 0; i < table.get_m(); i++) {
		line.sign.push_back(true);
	}

	line.func = (*func);


	/*Limitations time_lim;
	for (int i = 0; i < table.get_n(); i++) {
		std::vector<double> time_vec;
		for (int j = 0; j < table.get_m(); j++) {
			time_vec.push_back(table[i][j]);
		}
		time_vec.push_back((*b)[i]);
		time_lim.add_limitations({ time_vec, LT::LT_EQ });
	}

	to_dual(*func, time_lim, table.get_n());

	Matrix time_Matrix = Matrix(dual_limitations.limitations[0].first.size() - 1, dual_limitations.limitations.size());
	std::vector<double> time_b;
	for (int i = 0; i < dual_limitations.limitations[0].first.size() - 1; i++) {
		for (int j = 0; j < dual_limitations.limitations.size(); j++) {
			time_Matrix[i][j] = dual_limitations.limitations[i].first[j];
		}
		time_b.push_back(dual_limitations.limitations[i].first[dual_limitations.limitations[0].first.size() - 1]);
	}

	time_Matrix.print();*/

	Simplex* simp = new Simplex(&table, b, func);
	answer = simp->Answer_Func();
	answer_var = simp->Answer_Func_Var();

	/*Simplex* dual_simp = new Simplex(&time_Matrix, &time_b, &dual_function);
	answer = dual_simp->Answer_Func();
	answer_var = dual_simp->Answer_Func_Var();*/
}

LinearData ParserSimplex::get_Data() {
	return line;
}

void ParserSimplex::Get_Answer() {
	std::cout << std::endl;
	if (answer_var.size() == 0) {
		std::cout << "No answer" << std::endl;
		return;
	}
	std::cout << "F(x) = " << answer << std::endl;
	for (size_t i = 0; i < size_n; i++) {
		std::cout << std::endl;
		for (size_t j = 0; j < size_m; j++) {
			std::cout << 'x' << i + 1 << j + 1 << " = " << answer_var[i * new_size_m + j] << ' ';
		}
	}
}

Limitations::Limitations() {}

void Limitations::add_limitations(std::pair<std::vector<double>, LT>&& limitation) {
	limitations.push_back(limitation);
}

void ParserSimplex::to_dual(std::vector<double>& function, Limitations& limitations, size_t original_dimension) {
	dual_function = std::vector<double>(limitations.limitations.size());

	for (size_t i = 0; i < dual_function.size(); ++i) {
		if (limitations.limitations[i].second == LT::LT_LE) {
			for (size_t j = 0; j < original_dimension + 1; ++j) {
				limitations.limitations[i].first[j] *= -1;
			}
		}
	}

	for (size_t i = 0; i < dual_function.size(); ++i) {
		dual_function[i] = limitations.limitations[i].first[original_dimension];
	}

	for (size_t i = 0; i < original_dimension; ++i) {
		std::vector<double> new_limitation(dual_function.size() + 1);
		for (size_t j = 0; j < dual_function.size(); ++j) {
			new_limitation[j] = limitations.limitations[j].first[i];
		}
		new_limitation[dual_function.size()] = function[i];
		dual_limitations.add_limitations({ new_limitation, LT::LT_EQ });
	}

	std::swap(dual_function, function);
	std::swap(dual_limitations, limitations);
}