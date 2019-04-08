#include <windows.h>
#ifdef FUNCTIONALDLL_EXPORTS
#define FUNCTIONALTDLL_API __declspec(dllexport)
#else
#define FUNCTIONALDLL__API __declspec(dllimport)
#endif

#ifdef _c
extern "C"
{
#endif
	FUNCTIONALDLL__API DWORD __stdcall Dialog();
#ifdef _c
};
#endif