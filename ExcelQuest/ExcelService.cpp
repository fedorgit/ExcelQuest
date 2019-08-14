#include "ExcelService.hpp"




// 1. Типы элементов: закрывающиеся, самозакрывающиеся
// 2. 

vector<string> ExcelService::getWorkBookElements(string workbookText)
{
	uint64_t it = 0;
	uint64_t itEnd = 0;
	string tokenStart = "<sheet ";
	string tokenEnd = "/>";

	vector<string> result;

	while ((it = workbookText.find(tokenStart, it)) != string::npos)
	{
		itEnd = workbookText.find(tokenEnd, it);

		string element = workbookText.substr(it, itEnd - it);

		it = itEnd + tokenEnd.length();

		result.push_back(element);
	}

	// TODO: на основе строковых элементов получить сразу Sheet.
	// ...

	return result;
}

// Разбить SharedStrings Tag на элементы.
vector<string> ExcelService::getSharedStringsElements(string sharedStringsText)
{
	vector<string> result = this->getElementsByTagName(sharedStringsText, "t");

	return result;
}

vector<string> ExcelService::getSheetsElements(string sheetsText)
{
	uint64_t it = 0;
	uint64_t itEnd = 0;
	string tokenStart = "<t>";
	string tokenEnd = "</t>";

	vector<string> result;

	while ((it = sheetsText.find(tokenStart, it)) > 0)
	{
		itEnd = sheetsText.find(tokenEnd, it);

		string element = sheetsText.substr(it, itEnd - it);

		result.push_back(element);
	}

	return result;
}

// Получить элементы строк таблицы.
vector<string> ExcelService::getSheetsRowElements(string rowsText)
{
	vector<string> result = this->getElementsByTagName(rowsText, "row");

	return result;
}

vector<Sheet> ExcelService::getSheet(vector<string> sheetElements)
{
	vector<Sheet> result;

	for (string sheetElement : sheetElements) {

		Sheet sheet;
		sheet.name = this->getAttribute(sheetElement, "name");
		sheet.sheetId = this->getAttribute(sheetElement, "sheetId");

		result.push_back(sheet);
	}

	return result;
}

vector<string> ExcelService::getSharedStrings(vector<string> sharedStringsElements)
{
	// <t>Text1</t>
	// <t>Text2</t>
	// <t>  Text3  </t>
	// <t>Text4</t>
	// <t> Text5 </t>
	// <t>  Text6 </t>

	vector<string> result;

	for (string sharedString : sharedStringsElements)
	{
		string shared = this->getElementText(sharedString);
		result.push_back(shared);
	}

	return result;
}

vector<Row> ExcelService::getSheetsRow(vector<string> rowsElements)
{
	vector<Row> result;

	for (string rowElement : rowsElements)
	{
		Row row;

		string crow = this->getElementsByTagName(rowElement, "c")[0];
		row.position = this->getAttribute(crow, "r");
		row.type = this->getAttribute(crow, "t") == "s" ? RowValueEnum::StringType : RowValueEnum::NumberType;
		string cvalue = this->getElementsByTagName(rowElement, "v")[0];
		row.value = this->getElementText(cvalue);

		result.push_back(row);
	}

	return result;
}

// Да кому только в голову пришло давать это в тестовом задании?:)
string ExcelService::getAttribute(string element, string key)
{
	int it;
	int itEnd;

	string result;

	//			|   ||				|
	// <element name=" 283DD2n982b7\" 72 364\" 782n39">
	// <element name=" 283DDD2n982b7 72 364782n39" >
	// <element name="DD 283672n982b7 72 364782n39"/>

	if ((it = element.find(key)) != string::npos)
	{
		it = element.find("=", it);

		it = element.find("\"", it) + 1;

		itEnd = it;

		while ((itEnd = element.find("\"", itEnd)) != string::npos)
		{
			if (element[itEnd - 1] != '\\')
				break;
		}
		result = element.substr(it, itEnd - it);
	}

	return result;
}

// Получить текст элемента.
string ExcelService::getElementText(string element)
{
	int it = 0;
	int itEnd;

	it = element.find("<");
	it = element.find(">", it) + 1;


	itEnd = element.find("<", it);

	string result = element.substr(it, itEnd - it);

	return result;

}

// Получить все элементы по названию тега
// data="<t>Text</t><t>Text2</t>" name = "t" => [<t>Text</t>, <t>Text2</t>]
vector<string> ExcelService::getElementsByTagName(string data, string name)
{
	vector<string> result;

	int it = 0;
	int itEnd;

	// TODO: кол-во открывающих тегов должно совпадать с кол-вом закрывающих тегов.
	//	<row r="1" spans="1:4" x14ac:dyDescent="0.25">
	//		<c r="A1">
	//			<v>1</v>
	//		</c>
	//	</row>

	string tagName = "<" + name;	// + ">"
	string tagNameEnd = "</" + name + ">";

	int countTag = 0;

	while ((it = data.find(tagName, it)) != string::npos)
	{
		countTag++;

		itEnd = data.find(tagNameEnd, it);
		string tag = data.substr(it, itEnd - it + tagNameEnd.length());
		it = itEnd + tagNameEnd.length();

		result.push_back(tag);
	}

	return result;

}

void ExcelService::setArchive(Archive * archive)
{
	this->_archive = archive;
}

ExcelTable ExcelService::extraction()
{
	// 1. Получение названия документа
	// 2. Получение данных от страницах из workbook.xml
	// 3. Получение данных о строках из sharedStrings.xml
	// 4. Получение на основе workbook.xml данных на каждой странице.

	this->_table.name = _archive->getName();

	string workbookText = this->_archive->getDataFromFile(PATH_WORKBOOK);
	vector<string> workBookElements = this->getWorkBookElements(workbookText);
	this->_table.sheets = this->getSheet(workBookElements);

	string sharedStringsText = this->_archive->getDataFromFile(PATH_SHAREDSTRINGS);
	vector<string> sharedStringsElements = this->getSharedStringsElements(sharedStringsText);
	this->_table.sharedStrings = this->getSharedStrings(sharedStringsElements);


	// TODO: доделать.
	for (int i = 0; i < this->_table.sheets.size(); i++) {
		string sheetPath(PATH_SHEET);

		size_t pos = sheetPath.find("[N]");
		sheetPath.replace(pos, 3, to_string(i + 1));
		string sheetsText = this->_archive->getDataFromFile(sheetPath.c_str());
		vector<string> sheetElements = this->getSheetsRowElements(sheetsText);
		vector<Row> rows = this->getSheetsRow(sheetElements);
		for (Row row : rows)
			this->_table.sheets[i].rows.push_back(row);
	}

	return this->_table;
}



ExcelService::ExcelService()
{
}

ExcelService::~ExcelService()
{
}
