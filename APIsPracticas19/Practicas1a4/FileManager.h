#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class FileManager
{
public:
	FileManager();
	~FileManager();
	char* GetFileContents(const char* filePath);
};

template<typename T>
 T numberFromString(const std::string& str)
{
	T number;
	std::istringstream stream(str);
	stream >> number;
	return number;
}

template <typename T>
 std::vector<T> splitString(const std::string& str, char delim)
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
