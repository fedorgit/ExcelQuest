#ifndef ROW_HPP
#define ROW_HPP

#include <string>

#include "RowValueEnum.hpp"

using namespace std;

class Row
{
public:

	int row;
	string position;
	RowValueEnum type;
	string value;

	Row();
	~Row();
};

#endif

