#include <windows.h>
#ifdef SECONDTDLL_EXPORTS
#define SECONDDLL_API __declspec(dllexport)
#else
#define SECONDDLL__API __declspec(dllimport)
#endif

#ifdef _c
extern "C"
{
#endif
	SECONDDLL__API  BOOLEAN __cdecl GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
	SECONDDLL__API  BOOLEAN __cdecl GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
	SECONDDLL__API VOID __cdecl Execute();
#ifdef _c
};
#endif