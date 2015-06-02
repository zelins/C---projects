#pragma once
#include <fstream>

#define DefaultFileName "default.txt"

class BaseDataManager
{
protected:
	char *FileName;
public:
	virtual void Save() const = 0;
	virtual void Load() = 0;
	BaseDataManager() : FileName(new char[strlen(DefaultFileName) + 1])
	{
		strcpy_s(FileName, strlen(DefaultFileName) + 1, DefaultFileName);
	}
	BaseDataManager(const char *path) : FileName(new char[strlen(path) + 1])
	{
		strcpy_s(FileName, strlen(path) + 1, path);
	}
	virtual ~BaseDataManager()
	{
		delete[] FileName;
	}
};