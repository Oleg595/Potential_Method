#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "Potential.h"
#include "ClosedType.h"

class Parser {
public:
	Parser(std::string const&);

	Potential* parse();

	std::vector<int> Production_Points();
	std::vector<int> Consumption_Points();
	Matrix Table();

	~Parser();
private:
	static std::vector<int> create_vector(size_t);

	std::ifstream ifs;

	Matrix table;
	std::vector<int> production_points, consumption_points;
};

struct Grammar {
public:
	const std::string& get_keyword(size_t) const;
	size_t size() const;
protected:
	Grammar(std::vector<std::string>);
private:
	const std::vector<std::string> keywords;
};


struct PotentialGrammar : public Grammar {
public:
	PotentialGrammar();
};

enum KW {
	KW_SIZE = 0,
	KW_PRODACTION,
	KW_CONSUMPTION,
	KW_TABLE,
	KW_NULL
};