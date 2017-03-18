#pragma once
#include <fstream>
#include <cassert>

class HasFile
{
private:
	std::string _path;
	std::fstream _file;
public:
	HasFile(std::string path) : _path(path)
	{
		assert(_path.size() != 0);
		_file = std::fstream(_path, std::ios::in);
		assert(_file.good() == true);
	}
	~HasFile()
	{
		_file.close();
	}
	std::fstream& GetFile() { return _file; }
};
