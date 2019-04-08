#include <windows.h>
#ifdef FIRSTDLL_EXPORTS
#define FIRSTDLL_API __declspec(dllexport)
#else
#define FIRSTDLL__API __declspec(dllimport)
#endif

#ifdef _c
extern "C"
{
#endif
	FIRSTDLL__API  BOOLEAN __cdecl GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
	FIRSTDLL__API  BOOLEAN __cdecl GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
	FIRSTDLL__API VOID __cdecl Execute();
#ifdef _c
};
#endif