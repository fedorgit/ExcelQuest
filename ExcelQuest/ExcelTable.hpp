#ifndef EXCELTABLE_HPP
#define EXCELTABLE_HPP

#include <vector>

#include "Sheet.hpp"
#include "RowValueEnum.hpp"

using namespace std;

class ExcelTable
{
public:

	// Название таблицы
	string name;

	// Страницы таблицы
	vector<Sheet> sheets;

	// Набор строк в таблице.
	vector<string> sharedStrings;

	// Отчет по данным таблицы.
	string getSharedStringById(int id);

	// Отчет по данным таблицы.
	string getReport();

	ExcelTable();
	~ExcelTable();
};


#endif

