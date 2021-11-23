#include <iostream>
#include <Windows.h>

using namespace std;

const char libraryName[] = "StringModifyingDll.dll";

int main()
{
	DWORD processId;
	while (true)
	{
		cout << "Enter process id: ";
		cin >> processId;
		HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_CREATE_PROCESS, FALSE, processId);
		if (!hProcess)
		{
			cerr << "Can't access process";
			return -1;
		}
		auto pLoadLibrary = (LPVOID) GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
		LPVOID dllName = (LPVOID) VirtualAllocEx(hProcess, NULL, strlen(libraryName), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (!dllName)
		{
			cerr << "Can't allocate memory for argument";
			return -2;
		}

		SIZE_T written = -1;
		if (!WriteProcessMemory(hProcess,  dllName, libraryName, strlen(libraryName), &written))
		{
			cerr << "Can't write library name, written " << written;
			cin.get();
			return -3;
		}
		auto create_remote_thread_result = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, dllName, 0, NULL);
		if (!create_remote_thread_result)
		{
			cerr << "Can't create thread";
			return -4;
		}
		CloseHandle(hProcess);
	}
}