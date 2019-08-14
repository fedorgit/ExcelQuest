#ifndef EXCELDATA_HPP
#define EXCELDATA_HPP

#include <string>

using namespace std;

class ExcelData
{
public:

	string workbook;
	string sharedStrings;
	string sheets;

	ExcelData();
	~ExcelData();
};

#endif

