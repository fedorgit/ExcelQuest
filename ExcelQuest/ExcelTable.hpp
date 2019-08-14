#ifndef EXCELTABLE_HPP
#define EXCELTABLE_HPP

#include <vector>

#include "Sheet.hpp"
#include "RowValueEnum.hpp"

using namespace std;

class ExcelTable
{
public:

	// �������� �������
	string name;

	// �������� �������
	vector<Sheet> sheets;

	// ����� ����� � �������.
	vector<string> sharedStrings;

	// ����� �� ������ �������.
	string getSharedStringById(int id);

	// ����� �� ������ �������.
	string getReport();

	ExcelTable();
	~ExcelTable();
};


#endif

