/*
* -----------------------------------------
*  change glib.h for VisualStudio 2017
*  as for cygwin + win32API
* -----------------------------------------
*/

#pragma once

extern double WX1, WY1, WX2, WY2,      // 
       VX1, VY1, VX2, VY2,      // 
       FACTX, FACTY,          	//   
       ANGLE,               	//   
       LPX, LPY;              	// 
extern HDC hdc;

extern void window(double x1, double y1, double x2, double y2);
extern void view(HDC hdc, double x1, double y1, double x2, double y2);
extern void Ginit(HDC hdc);

extern void cls(HDC hdc);
extern void line(HDC hdc, double x1, double y1, double x2, double y2);

void pset(HDC hdc, double x, double y);

extern void move(HDC hdc, double l);
void moveto(HDC hdc, double x, double y);
extern void setpoint(double x, double y);


#define setangle(a) ANGLE=(double)(a)
#define turn(a) ANGLE=fmod(ANGLE+(a),360.0)

#define ginit() Ginit(hdc)
