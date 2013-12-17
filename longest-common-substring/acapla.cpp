#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "readfile.h"

using namespace std;

inline int FindLongestSubstring(const string& x, const string& y, string* outLongestSubstring)
{
	int sizeX = x.size();
	int sizeY = y.size();
	const string* px = &x;
	const string* py = &y;
	int sslength = sizeX;
	int lslength = sizeY;
	if(sizeX > sizeY)
	{
		swap(px, py);
		swap(sslength, lslength);
	}

	const string& ss = *px;
	const string& ls = *py;

	int longest = 0;
	int longestBegin = 0;

	//ss:abcdefg
	//ls:      123456789	this is negative offset = -6
	//ss:        abcdefg
	//ls:123456789			this is positive offset = 4
	for(int offset = -(sslength - 1); offset < lslength - longest; ++offset)
	{
		int currentLongest = 0;
		int currentLength = 0;
		const int startIndexSS = offset < 0 ? -offset : 0;
		const int startIndexLS = offset < 0 ? 0 : offset;

		for(int iss = startIndexSS, ils = startIndexLS; iss < sslength && ils < lslength; ++iss, ++ils)
		{
			if(ss[iss] != ls[ils])
			{
				if(currentLength > longest)
				{
					currentLongest = currentLength;
					longest = currentLongest;
					longestBegin = ils - currentLength;
				}

				currentLength = 0;
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
		}
	}

	if(longest != 0)
	{
		*outLongestSubstring = ls.substr(longestBegin, longest);
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
