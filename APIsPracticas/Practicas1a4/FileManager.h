#pragma once
#include <vector>
class FileManager
{
public:
	FileManager();
	~FileManager();
	char* GetFileContents(const char* filePath);
	template <typename T>
	std::vector<T> splitString(const std::string& str, char delim);

	template <typename T>
	T numberFromString(const std::string& str);

};