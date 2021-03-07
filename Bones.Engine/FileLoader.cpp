#include "FileLoader.hpp"
#include "emscripten_include.h"

string FileLoader::ReadFileToString(const string& filePath)
{
	string content;
	ifstream fileStream;
	try {
		fileStream.open(filePath);

		// more efficient way to read file
		// first set end position
		fileStream.seekg(0, ios::end);
		// reserve string space till the end
		content.reserve(fileStream.tellg());
		// set start of file positions
		fileStream.seekg(0, ios::beg);

		// add to string
		content.assign((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
	}
	catch (const ifstream::failure& e)
	{
		cout << "Error reading file: " << filePath << endl;
		cout << e.what() << endl;
		fileStream.close();
	}
	catch (const out_of_range& e)
	{
		cout << "Error reading file: " << filePath << endl;
		cout << e.what() << endl;
	}
	catch (const exception& e)
	{
		cout << "Error reading file: " << filePath << endl;
		cout << e.what() << endl;
	}

	fileStream.close();

	return content;
}

stringstream FileLoader::ReadFileToStringStream(const string& filePath)
{
	stringstream stream;
	ifstream fileStream;
	try
	{
		fileStream.open(filePath);
		stream << fileStream.rdbuf();
	}
	catch (const ifstream::failure& e)
	{
		cout << "Error reading file: " << filePath << endl;
		cout << e.what() << endl;
	}
	catch (const exception& e)
	{
		cout << "Error reading file: " << filePath << endl;
		cout << e.what() << endl;
	}
	fileStream.close();
	return stream;
}

#if EMSCRIPTEN_RUNTIME

using namespace emscripten;

EMSCRIPTEN_BINDINGS(FileLoader)
{
	class_<FileLoader>("FileLoader")
		.constructor()
		.function("ReadFileToString", &FileLoader::ReadFileToString);
}

#endif 