#pragma once
#include <iostream>
#include <string>

typedef bool (*pReplace)(const char* oldString, const char* newString);

class ReplaceApp
{
private:
	const char* _string;
	std::string str;
	pReplace _replace;

public:
	ReplaceApp(const char* string, pReplace replace);
	explicit ReplaceApp(pReplace replace)
		: _replace(replace)
	{
		std::cout << "Enter string: ";
		std::cin >> str;

		_string = str.c_str();
	}

	void Print(std::ostream& out) const;

	void Replace(const char* newString);

	void Start();

	void GetPid(std::ostream& out) const;
};