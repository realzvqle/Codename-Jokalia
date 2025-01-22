#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED




#include <Windows.h>

VOID InstallerError(LPWSTR ErrorMessage);
VOID ShowFailureResponse(DWORD errorCode);
VOID BlueScreenSystem();
BOOL CheckIfAdministrator();
BOOL CheckIfRan();
void* AllocateVirtualMemory(size_t size);
BOOL FreeVirtualMemory(void* memory);
VOID ShutdownSystem();
VOID RestartSystem();
BOOL CheckIfWindows10OrGreater();
#endif