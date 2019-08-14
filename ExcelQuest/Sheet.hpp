#ifndef SHEET_HPP
#define SHEET_HPP

#include <cstring>
#include <vector>

#include "Row.hpp"

using namespace std;

class Sheet
{

private:
	

public:

	string name;
	string sheetId;
	vector<Row> rows;

	Sheet();
	~Sheet();
};

#endif

