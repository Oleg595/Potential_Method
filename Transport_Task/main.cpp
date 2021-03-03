#include "Potential.h"
#include "Parser.h"
#include"Parser_Simplex.h"


int main(int argc, char* argv[]) {
	if (argc > 1) {
		Parser parser(argv[1]);
		Potential* potential = parser.parse();
		std::vector<int> optimal = potential->solve();
		Parser_Simplex* par_simplex = new Parser_Simplex(&parser.Production_Points(), &parser.Consumption_Points(), &parser.Table());
		par_simplex->Get_Answer();
		std::cout << "\nOptimal:\n";
		for (auto elem : optimal) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
		std::cout << "Min value: " << potential->objective_function(optimal) << std::endl;

		delete potential;
	}
	return 0;
}