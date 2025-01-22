#include "registry.h"
#include "tools.h"


BOOL WriteIntoRegistry(HKEY hkey, LPWSTR path, LPCWSTR subkey, DWORD dwType, void* data){
    HKEY handle;
    LSTATUS result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, path, 0, KEY_SET_VALUE, &handle);
    if(result != ERROR_SUCCESS){
        ShowFailureResponse(GetLastError());
        return FALSE;
    }
    DWORD size;
    if(dwType == REG_SZ) size = wcslen(data) * sizeof(WCHAR);
    else if(dwType == REG_DWORD) size = sizeof(DWORD);
    result = RegSetValueExW(handle, subkey, 0, dwType, data, size);
    if(result != ERROR_SUCCESS){
        ShowFailureResponse(GetLastError());
        RegCloseKey(handle);
        return FALSE;
    }
    RegCloseKey(handle);
    return TRUE;  
}