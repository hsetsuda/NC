
/*
 * ------------------------------
 *  function @ glib.h
 *  -----------------------------
 */

#include <windows.h>
#include <math.h>
#include "my_glib.h"

COLORREF color = RGB(0, 0, 255);  // blue

double WX1, WY1, WX2, WY2,      // 
       FACTX, FACTY,          	//   
       ANGLE,               	//   
       LPX, LPY;              	// 
double VX1 = 200, VY1 = 200;
double VX2 = 900, VY2 = 700;      // 
//double VX1, VY1, VX2, VY2;      // 

void window(double x1, double y1, double x2, double y2)
{
	WX1 = x1; WY1 = y1; WX2 = x2; WY2 = y2;
	FACTX = (VX2 - VX1) / (WX2 - WX1);
	FACTY = (VY2 - VY1) / (WY2 - WY1);
}
/*
void view(HDC hdc, double x1, double y1, double x2, double y2)
{
	SetViewportExtEx(hdc, (int)(x2 - x1), (int)(y2 - y1), NULL);
	SetViewportOrgEx(hdc, (int)x1, (int)y1, NULL);
	HRGN hRgn = CreateRectRgn((int)x1, (int)y1, (int)x2 + 1, (int)y2 + 1);
	SelectClipRgn(hdc, hRgn);		// 
	VX1 = x1; VY1 = y1; VX2 = x2; VY2 = y2;
	FACTX = (VX2 - VX1) / (WX2 - WX1);
	FACTY = (VY2 - VY1) / (WY2 - WY1);
}
void Ginit(HDC hdc)
{
	//ghdc = hdc;
	HPEN hPen = CreatePen(PS_SOLID, 1, color);	// 
	SelectObject(hdc, hPen);
	//SelectObject(ghdc, hPen);
	LPX = 0; LPY = 0; ANGLE = 0;
	window(0, 0, 639, 399);
	view(hdc, 0, 0, 639, 399);
}
*/
void cls(HDC hdc)
{
  RECT r;
  GetClipBox(hdc, &r);
  FillRect(hdc, &r, CreateSolidBrush(GetBkColor(hdc)));
}


void line(HDC hdc, double x1, double y1, double x2, double y2)
{
	int px1, py1, px2, py2;
	px1 = (int)((x1 - WX1)*FACTX);
	py1 = (int)((WY2 - y1)*FACTY);
	px2 = (int)((x2 - WX1)*FACTX);
	py2 = (int)((WY2 - y2)*FACTY);
	MoveToEx(hdc, px1, py1, NULL);
	LineTo(hdc, px2, py2);
	LPX = x2; LPY = y2;
}
void pset(HDC hdc, double x, double y)
{
	int px, py;
	px = (int)((x - WX1)*FACTX);
	py = (int)((WY2 - y)*FACTY);
	SetPixel(hdc, px, py,color);	
	LPX = x; LPY = y;
}

void move(HDC hdc, double l)
{
	double x, y, rd = 3.1415927 / 180;
	x = l*cos(rd*ANGLE); y = l*sin(rd*ANGLE);
	line(hdc, LPX, LPY, LPX + x, LPY + y);
}

void moveto(HDC hdc, double x, double y)
{
	line(hdc, LPX, LPY, x, y);
}

void setpoint(double x, double y)
{
  LPX = x;
  LPY = y;
}

