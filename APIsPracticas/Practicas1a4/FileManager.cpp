#include "FileManager.h"
#include <stdio.h>


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

char * FileManager::GetFileContents(const char * filePath)
{
	char* contents = NULL;
	//readonly -> "r"
	FILE*file;
	fopen_s(&file, filePath, "r");
	if (file == NULL)
		return NULL;

	int fileLen = 0;
	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);

	fseek(file, 0, SEEK_SET);
	contents = new char[fileLen + 1];

	fread(contents, 1, fileLen, file);
	contents[fileLen] = '\0';
	fclose(file);
	return contents;
}


template <typename T>
std::vector<T> FileManager::splitString(const std::string & str, char delim)
{
	std::vector<T> elems;
	std::stringstream sstream(str);
	std::string item;

	if (str != "") {
		while (std::getline(sstream, item, delim)) {
			elems.push_back(numberFromString<T>(item));
		}
	}
	return elems;
}

template<typename T>
T FileManager::numberFromString(const std::string & str)
{
	T number;
	std::istringstream stream(str);
	stream >> number;
	return number;
}