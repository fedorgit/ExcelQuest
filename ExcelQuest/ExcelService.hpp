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

	// Устанавливаем ссылку на текущий архив для получения данных.
	void setArchive(Archive* archive);

	// Извлечение данных из excel.
	ExcelTable extraction();

	// Получить все используемые страницы в excel
	vector<string> getWorkBookElements(string workbookText);

	vector<string> getSheetsRowElements(string rowsText);

	// Получение страниц.
	vector<Sheet> getSheet(vector<string> sheetElements);

	vector<string> getSharedStrings(vector<string> SharedStringsElements);

	// Получить все используемые строки в excel
	vector<string> getSharedStringsElements(string sharedStringsText);

	// Получить все страницы с данными их excel на основе WorkBook.
	vector<string> getSheetsElements(string sheetsText);

	vector<Row> getSheetsRow(vector<string> rowElements);

	// Получить таблицу данных.
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

