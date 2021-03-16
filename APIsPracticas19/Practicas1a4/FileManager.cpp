#include "FileManager.h"


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
