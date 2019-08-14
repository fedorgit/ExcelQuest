#ifndef UNZIPSERVICE_HPP
#define UNZIPSERVICE_HPP

#include <string>

#include <zip.h>

using namespace std;

class UnzipService
{
public:

	string getTextFromFile(string fileName);

	UnzipService();
	~UnzipService();
};


#endif

