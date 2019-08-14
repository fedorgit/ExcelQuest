#ifndef ARCHIVESERVICE_HPP
#define ARCHIVESERVICE_HPP

#include <string>
#include <iostream>
#include <fstream>

#include <zip.h>

using namespace std;

class Archive
{
	// ��������������� ��������� ����
	static string getTextFromZip(string zipName, string pathFileName);
	
private:
	string _zipName;
	struct zip* _zipFile; // ���������� zip �����
	bool _isOpen;

public:
	
	void open(string archiveFileName);
	string getDataFromFile(string pathFileName);
	string getName();
	void close();
	bool isOpen();

	Archive();
	~Archive();
};


#endif

