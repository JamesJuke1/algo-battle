#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "readfile.h"

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
    if(argc < 2)
    {
        return -1;
    }

    string filename = argv[1];
    auto strings = ReadFile(filename);

    for (int i = 0; i < strings.size(); i += 2)
    {
	string longestSubstring;
	auto length = FindLongestSubstring(strings[i], strings[i + 1], &longestSubstring);

	cout << longestSubstring << std::endl;
    }
    return 0;
}
