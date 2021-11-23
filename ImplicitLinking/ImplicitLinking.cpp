#include <iostream>
#include "../Common/Common.h"
#include "../StringModifyingDll/StringModifyingDll.h"

const char a[] = "Hello!";
using namespace std;

int main()
{
    ReplaceApp app(ReplaceString);
    app.Start();
}