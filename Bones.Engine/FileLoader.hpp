#pragma once 

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include "core_types.h"

using namespace std;

class FileLoader final
{
public:
	FileLoader() {}

	string ReadFileToString(const string& filePath);
	stringstream ReadFileToStringStream(const string& filePath);
};