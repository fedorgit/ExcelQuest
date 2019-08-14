#include "Archive.hpp"



// ��������������� ��������� ����
string Archive::getTextFromZip(string zipName, string pathFileName)
{
	struct zip *zip_file; // ���������� zip �����
	struct zip_file *file_in_zip; // ���������� ����� ������ ������
	struct zip_stat file_info;
	struct tm file_time;
	int err; 
	int files_total; 
	int r;
	int file_number;
	char* buffer;

	// ��������� �����.
	zip_file = zip_open(zipName.c_str(), 0, &err);
	if (!zip_file) {
		cout << "Error: can't open file " << zipName << endl;
	}

	// �������� ������ �����:
	// 1. �������� ������ �����.
	// 2. �������� ���������� � ��������� ������� ��� ������.
	// 3. ������� ����.
	//zip_int64_t index_file = zip_name_locate(zip_file, pathFileName.c_str(), 0);

	zip_stat(zip_file, pathFileName.c_str(), 0, &file_info);
	zip_int64_t size_file = file_info.size;
	file_in_zip = zip_fopen(zip_file, pathFileName.c_str(), 0);
	buffer = new char[size_file];
	memset(buffer, 0, size_file);

	if (file_in_zip) {

		// ������ � ����� ���������� ����� � �������
		while ((r = zip_fread(file_in_zip, buffer, size_file)) > 0) {
			//cout << buffer << endl;
		};
		// ��������� ���� ������ ������
		zip_fclose(file_in_zip);
	}
	else {
		cout << "Error: can't open file " << pathFileName << " in zip" << endl;
	};

	string result(buffer);

	delete[] buffer;

	zip_close(zip_file);

	return result;
}



void Archive::open(string archiveFileName)
{
	this->_zipName = archiveFileName;

	int err;						// ��������� ��� �������� ����� ������
	
	// ��������� �����.
	this->_zipFile = zip_open(this->_zipName.c_str(), 0, &err);
	if (!this->_zipFile) {
		cout << "Error: can't open file " << this->_zipName << endl;
		this->_isOpen = false;
	}

}

string Archive::getDataFromFile(string pathFileName)
{

	struct zip_stat fileInfo; // ���������� � �����
	struct zip_file* fileInArchive;	// ���������� ����� ������ ������
	struct tm file_time;
	
	int files_total; // ���������� ������ � ������
	int r;
	int fileNumber;
	char* buffer;
	
	// �������� ������ �����:
	// 1. �������� ������ �����.
	// 2. �������� ���������� � ��������� ������� ��� ������.
	// 3. ������� ����.
	zip_stat(this->_zipFile, pathFileName.c_str(), 0, &fileInfo);
	zip_int64_t sizeFile = fileInfo.size;
	fileInArchive = zip_fopen(this->_zipFile, pathFileName.c_str(), 0);
	buffer = new char[sizeFile];
	memset(buffer, 0, sizeFile);

	if (fileInArchive) {
		// ������ � ����� ���������� ����� � �������
		while ((r = zip_fread(fileInArchive, buffer, sizeFile)) > 0) {
			//cout << "r: " << r << endl;
		};
		// ��������� ���� ������ ������
		zip_fclose(fileInArchive);
	}
	else {
		cout << "Error: can't open file " << pathFileName << " in zip" << endl;
	};


	string result(buffer);

	delete[] buffer;

	return result;

}

string Archive::getName()
{
	return _zipName;
}

void Archive::close()
{
	zip_close(this->_zipFile);
}

bool Archive::isOpen()
{
	return this->_isOpen;
}


Archive::Archive()
{
}

Archive::~Archive()
{
}
