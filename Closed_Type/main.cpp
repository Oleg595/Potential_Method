#include "Potential.h"
#include "Parser.h"


int main(int argc, char* argv[]) {
	if (argc > 1) {
		Parser parser(argv[1]);
		Potential* potential = parser.parse();
		potential->solve();
		//potential->northwest_corner_method();
	}
	return 0;
}