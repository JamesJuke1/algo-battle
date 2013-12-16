#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

vector<string> const ReadFile(string const &filename)
{
	ifstream fs(filename);
	if(fs.bad())
	{
		cout << "file error" << endl;
		throw std::runtime_error("file error");
	}

	vector<string> contents;
	while(!fs.eof())
	{
		string content;
		getline(fs, content);
		if (content.size() == 0)
		    break;
		contents.push_back(content);
	}

	if(contents.size() % 2 != 0)
	{
		cout << "file format error" << endl;
		throw std::runtime_error("file format error");
	}

	return contents;
}
