#include "gdi.h"



HDC dc;
int x;
int y;
int dpiX;
int dpiY;
int screenx;
int screeny; 


void SetupGDIElements(){
    dc = GetDC(NULL);
    x = GetSystemMetrics(SM_CXSCREEN);
    y = GetSystemMetrics(SM_CXSCREEN);
    dpiX = GetDeviceCaps(dc, LOGPIXELSX);
    dpiY = GetDeviceCaps(dc, LOGPIXELSY);
    screenx = x * dpiX;
    screeny = y * dpiY;
}

HDC GDIReturnDC(){
    return dc;
}

int GDIReturnStockScreenX(){
    return x;
}

int GDIReturnStockScreenY(){
    return y;
}

int GDIReturnDPIX(){
    return dpiX;
}

int GDIReturnDPIY(){
    return dpiY;
}

int GDIReturnScreenX(){
    return screenx;
}

int GDIReturnScreenY(){
    return screeny;
}


void FreeGDIElements(){
    DeleteDC(dc);
}

static HFONT CreateStanderdFont(int fontsize) {
	return CreateFontW(
		-MulDiv(fontsize, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72),
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Microsoft JhengHei Light"
	);
}



VOID MalDrawText(HDC dc, float x, float y, int size, WCHAR* text, COLORREF color) {
	SetTextColor(dc, color);
	SetBkMode(dc, TRANSPARENT);
	HANDLE hFont = CreateStanderdFont(size);
	if (hFont) {
		SelectObject(dc, hFont);
		TextOutW(dc, x, y, text, wcslen(text));
		DeleteObject(hFont);
	}
	else {
		ShowFailureResponse(GetLastError());
	}
}


void RenderSquares(HDC dc, int x, int y, HGDIOBJ color, HGDIOBJ acolor, HGDIOBJ bcolor){
    SelectObject(dc, color);
    PatBlt(dc, x / 2, y / 2, 90, 90, PATINVERT);
    Sleep(10);
    SelectObject(dc, acolor);
    PatBlt(dc, x / 2, y / 2, 90, 90, PATINVERT);
    Sleep(10);
    SelectObject(dc, bcolor);
    PatBlt(dc, x / 2, y / 2, 90, 90, PATINVERT);
    Sleep(10);
}