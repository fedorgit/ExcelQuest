#include "ExcelTable.hpp"



string ExcelTable::getSharedStringById(int id)
{
	return this->sharedStrings[id];
}

string ExcelTable::getReport()
{
	string result = "Input: " + this->name + "\n";
	string value;

	for (Sheet sheet : this->sheets)
	{
		result += "-Sheet: " + sheet.name + "\n";

		for (Row row : sheet.rows)
		{
			value = row.type == RowValueEnum::NumberType ? row.value : this->getSharedStringById(std::atoi(row.value.c_str()));
			result += "--" + row.position + ": " + value + "\n";
		}

	}

	return result;
}

ExcelTable::ExcelTable()
{
}


ExcelTable::~ExcelTable()
{
}
