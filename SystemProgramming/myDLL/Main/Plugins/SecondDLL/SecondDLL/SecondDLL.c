#include"SecondDLL.h"
#include <stdio.h>
#include <string.h> 
#include <tlhelp32.h>

extern BOOLEAN __cdecl GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)
{
	LPSTR name = "Alex";
	int i = 0;
	DWORD sizeName = (DWORD)strlen(name);
	while (i < sizeName && i < dwBufferSize)
	{
		buffer[i] = name[i];
		++i;
	}
	*pdwBytesWritten = i;
	if (i == sizeName)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

extern BOOLEAN __cdecl GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)
{
	LPSTR description = "Retrieves information about the disk C, including the amount of free space on the disk";
	int i = 0;
	DWORD sizeDName = (DWORD)strlen(description);
	while (i < sizeDName && i < dwBufferSize)
	{
		buffer[i] = description[i];
		++i;
	}
	*pdwBytesWritten = i;
	if (i == sizeDName)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

extern VOID __cdecl Execute()
{
	LPCSTR  lpRootPathName = "C:";
	DWORD sectorsPerCluster;
	DWORD bytesPerSector;
	DWORD numberOfFreeClusters;
	DWORD totalNumberOfClusters;
	GetDiskFreeSpaceA(
		lpRootPathName,
		&sectorsPerCluster,
		&bytesPerSector,
		&numberOfFreeClusters,
		&totalNumberOfClusters
	);
	printf("Information about disk C \n");
	printf("Number of sectors per cluster %d \n", sectorsPerCluster);
	printf("Number of bytes per sector %d \n", bytesPerSector);
	printf("Total number of free clusters on the disk %d \n", numberOfFreeClusters);
	printf("Total number of clusters on the disk %d \n", totalNumberOfClusters);
}