#pragma once

#ifndef __STRINGMODIFYINGDLL_H
#define __STRINGMODIFYINGDLL_H

#define STRINGMODIFYINGDLLAPI __declspec(dllimport)

#else
#define STRINGMODIFYINGDLLAPI __declspec(dllexport)

#endif // !__STRINGMODIFYINGDLL_H

extern "C" bool STRINGMODIFYINGDLLAPI ReplaceString(const char* oldValue, const char* newValue);
