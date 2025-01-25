#ifndef GDI_H_INCLUDED
#define GDI_H_INCLUDED



#include "tools.h"


void SetupGDIElements();
HDC GDIReturnDC();
int GDIReturnStockScreenX();
int GDIReturnStockScreenY();
int GDIReturnDPIX();
int GDIReturnDPIY();
int GDIReturnScreenX();
int GDIReturnScreenY();
void FreeGDIElements();
VOID MalDrawText(HDC dc, float x, float y, int size, WCHAR* text, COLORREF color);
void RenderSquares(HDC dc, int x, int y, HGDIOBJ color, HGDIOBJ acolor, HGDIOBJ bcolor);
#endif