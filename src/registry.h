#ifndef REGISTRY_H_INCLUDED
#define REGISTRY_H_INCLUDED



#include <windows.h>


BOOL WriteIntoRegistry(HKEY hkey, LPWSTR path, LPCWSTR subkey, DWORD dwType, void* data);

#endif