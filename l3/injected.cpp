#include <Windows.h>
#include <iostream>
#include "../Common/Common.h"

using namespace std;

int main()
{
	cout << "Pid: " << GetProcessId(GetCurrentProcess()) << std::endl << "Type anything after DLL injection" << endl;
	cin.get();
	auto hLib = GetModuleHandleA("StringModifyingDll.dll");
	pReplace replace = (pReplace)GetProcAddress(hLib, "ReplaceString");
	ReplaceApp app(replace);
	app.Start();
	app.Print(cout);
	cin.get();
}