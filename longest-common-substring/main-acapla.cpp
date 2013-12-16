#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

inline int FindLongestSubstring(const string& x, const string& y, string* outLongestSubstring)
{
	auto sizeX = x.size();
	auto sizeY = y.size();
	if(sizeX > sizeY)
	{
		std::swap(const_cast<string&>(x), const_cast<string&>(y));
		std::swap(sizeX, sizeY);
	}

	int longest = 0;
	auto longestBegin = 0;

	for(auto offset = 0; offset <= sizeY - sizeX; ++offset)
	{
		int currentLongest = 0;
		int currentLength = 0;
		for(auto i = 0; i < sizeX; ++i)
		{
			if(x[i] != y[offset + i])
			{
				currentLength = 0;
				break;
			}
			else
			{
				++currentLength;
			}
		}

		if(currentLength != 0)
		{
			currentLongest = max(currentLength, currentLongest);
			longest = max(longest, currentLongest);
			longestBegin = offset;
		}
	}

	if(longest != 0)
	{
		*outLongestSubstring = y.substr(longestBegin, longest);
	}
	else
	{
		*outLongestSubstring = "";
	}

	return longest;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
    {
        return -1;
    }

    string s1 = argv[1];
    string s2 = argv[2];

	string longestSubstring;
	auto length = FindLongestSubstring(s1, s2, &longestSubstring);

	cout << "substring length: " << length << std::endl
              << longestSubstring << std::endl;
	//ifstream fs("123.txt");
	//if(fs.bad())
	//{
	//	cout << "file error" << endl;
	//	char useless;
	//	cin >> useless;
	//	return -1;
	//}

	//vector<string> contents;
	//while(!fs.eof())
	//{
	//	string content;
	//	getline(fs, content);
	//	auto p = content.find(',');
	//	contents.push_back(content.substr(0, p));
	//	p += sizeof(',');
	//	contents.push_back(content.substr(p, content.size() - p));
	//}

	//fs.close();

	//if(contents.size() % 2 != 0)
	//{
	//	cout << "file format error" << endl;
	//	char useless;
	//	cin >> useless;
	//	return -1;
	//}

	//for(vector<string>::size_type i = 0; i < contents.size(); i += 2)
	//{
	//	cout << FindLongestSubstring(contents[i], contents[i + 1]) << endl;
	//}

	return 0;
}