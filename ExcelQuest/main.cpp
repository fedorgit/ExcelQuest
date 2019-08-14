#include <iostream>
#include <fstream>
#include <codecvt>
#include <cstdlib>
#include <ctime>
#include <locale>

#include <zip.h>

#include "Archive.hpp"
#include "ExcelService.hpp"
#include "ExcelData.hpp"

typedef unsigned char byte;

// Архитектура приложения
// 
// Sheet
//
// Book
// 
using namespace std;

int main(int argc, char *argv[])
{
	// [0]: Получаем аргументы.
	// TODO: в ParametrHelper
	if (argc != 3)
	{
		cout << "Invalid number of parameters: " << argc << endl;
		system("pause");
		return -1;
	}

	string inputFileName = argv[1];
	string outputFileName = argv[2];

	if (std::string::npos == inputFileName.find(".xlsx")) {
		cout << "Invalid file format" << endl;
		system("pause");
		return -2;
	}
		


	// [1]: Работа с zip архивом
	Archive archive;
	archive.open(inputFileName);
	if (!archive.isOpen()) {
		cout << "Could not open file" << endl;
		system("pause");
		return -3;
	}

	// [2]: Получение кастомных данных в Xml
	ExcelService excelService;
	excelService.setArchive(&archive);
	ExcelTable excelTable = excelService.extraction();

	archive.close();
	

	// [3]: Вывод данных в другой фаил (формат не указан?)
	std::ofstream out;        // поток для записи
	out.open(outputFileName); // окрываем файл для записи
	if (out.is_open())
	{
		out << excelTable.getReport();
	}

	

	return 0;
}