#include "Common.h"
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

const size_t MaxStringSize = 4096;

ReplaceApp::ReplaceApp(const char* string, pReplace replace)
{
	_string = string;
	_replace = replace;
}

void ReplaceApp::Print(std::ostream& out) const
{
	out << "String:  " << _string << std::endl;
}

void ReplaceApp::Replace(const char* newString)
{
	cout << "Replace: " << _replace << endl;
	if (_replace)
	{
		_replace(_string, newString);
	}
}

void ReplaceApp::Start()
{
	string command;
	while (true)
	{
		cout << "Enter command (print, pid, replace, quit): ";
		cin >> command;
		if (command == "quit")
		{
			break;
		}
		else if (command == "print")
		{
			Print(cout);
		}
		else if (command == "pid")
		{
			GetPid(cout);
		}
		else if (command == "replace")
		{
			string s;
			cin >> s;
			Replace(s.c_str());
		}
		else
		{
			cout << "Unknown command\n";
		}
	}
}

void ReplaceApp::GetPid(std::ostream& out) const
{
	out << "Pid: " << GetProcessId(GetCurrentProcess()) << std::endl;
}