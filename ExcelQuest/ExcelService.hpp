#ifndef EXCELSERVICE_HPP
#define EXCELSERVICE_HPP

#include <string>
#include <vector>

#include "ExcelConfig.hpp"
#include "ExcelTable.hpp"
#include "Sheet.hpp"
#include "Archive.hpp"

#include "RowValueEnum.hpp"


using namespace std;

class ExcelService
{
private:
	string _xmlText;
	//XmlAttribute attributes[];	// TODO: or vector and map

	// Element -> ParentId, ChildrensId[], Attribute:Value[] , Text 
	// 
	ExcelTable _table;

	Archive* _archive;

public:

	// ������������� ������ �� ������� ����� ��� ��������� ������.
	void setArchive(Archive* archive);

	// ���������� ������ �� excel.
	ExcelTable extraction();

	// �������� ��� ������������ �������� � excel
	vector<string> getWorkBookElements(string workbookText);

	vector<string> getSheetsRowElements(string rowsText);

	// ��������� �������.
	vector<Sheet> getSheet(vector<string> sheetElements);

	vector<string> getSharedStrings(vector<string> SharedStringsElements);

	// �������� ��� ������������ ������ � excel
	vector<string> getSharedStringsElements(string sharedStringsText);

	// �������� ��� �������� � ������� �� excel �� ������ WorkBook.
	vector<string> getSheetsElements(string sheetsText);

	vector<Row> getSheetsRow(vector<string> rowElements);

	// �������� ������� ������.
	ExcelTable getTableData();

	// TODO: XmlHelper
	string getAttribute(string element, string key);

	// TODO: XmlHelper
	vector<string> getElementsByTagName(string data, string name);

	// TODO: XmlHelper
	string getElementText(string element);


	//Sheet[] sheets getShets();
	// workbook.xml -> sharedString.xml -> sheet1.xml
	//                                     sheet2.xml
	//									   sheet3.xml									

	ExcelService();
	~ExcelService();
};

#endif

