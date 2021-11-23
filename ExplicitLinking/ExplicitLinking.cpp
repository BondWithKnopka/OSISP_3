#include <iostream>
#include <Windows.h>
#include "../Common/Common.h"

typedef bool (*pReplace)(const char*, const char*);

int main()
{
    HMODULE library = LoadLibraryA("StringModifyingDll.dll");
    pReplace replace = (pReplace)GetProcAddress(library, "ReplaceString");
    ReplaceApp app(replace);
    app.Start();
    FreeLibrary(library);
}