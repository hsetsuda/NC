#include <windows.h>
#include <stdio.h>
#include <math.h> //add
#include "my_glib.h"


LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdLine, int nCmdShow)
{
    TCHAR szAppName[] = TEXT("TestApp");
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szAppName;

    if (!RegisterClass(&wc)) return 0;

    hwnd = CreateWindow(
        szAppName, TEXT(""),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        //VX1, VY1,             // look my_glib.c
        //(VX2-VX1), (VY2-VY1), // look my_glib.c
        NULL, NULL,
        hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(   // function catch message from window then do something 
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    
    // devided cace according to event in msg
    switch (uMsg) {
    case WM_PAINT:    // event paint window, UpdateWindow(), RedrawWindow
      hdc = BeginPaint(hwnd, &ps);       // 描画開始
      /* ======== write draw (main)program ===============*/
 
      void rotate(double ax, double ay, double az, double x, double y, double z, double *px, double *py);
      
      int n, k;
      double x, z;
      double px, py;
      double rd = 3.14159/180;
      double y[] = { 180, 140, 100, 60, 20, 10,  4,  0, -999};
      double r[] = { 100,  55,  10, 10, 10, 50, 80, 80, -999};
      double ax = 35 * rd;   // rotation angle around x
      double ay = 0;         // rotation angle around y
      double az = 20 * rd;   // rotation angle around z

      ginit(); 
      cls(hdc);
      window(-320,-100,320,300);
      
      for (k=0;(int)y[k]!=-999;k++)    // rotation track around y
      {
        for(n=0; n<=360; n=n+10)
        {
          x = r[k] * cos(n*rd);
          z = r[k] * sin(n*rd);
          rotate(ax, ay, az, x, y[k], z, &px, &py);
          if (n==0)
          {
            setpoint(px,py);
          }
          else
          {
            moveto(hdc, px,py);
          }
        }
      }

      
      for(n=0; n<=360; n=n+60)        // ridgeline
      {
        for(k=0; (int)y[k]!=-999; k++)
        {
          x = r[k] * cos(n*rd);
          z = r[k] * sin(n*rd);
          rotate(ax, ay, az, x, y[k], z, &px, &py);
          if (k==0)
          {
            setpoint(px,py);
          }
          else
          {
            moveto(hdc, px,py);
          }
        }
      }
      
          

      /* ===========================================  */
      EndPaint(hwnd, &ps);               // 描画終了
        return 0;

    case WM_DESTROY:        // event that delete the window(wParam=0, lParam=0)
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
    // return 0->processing yourself, DefWindowProc->system prcessing
}

void rotate(double ax,double ay,double az,double x,double y,double z,
       double *px,double *py)      // 3D rotation conversion  
{
    double x1,y1,z1,x2,y2;
    x1  =  x*cos(ay) + z*sin(ay);      // around y
    y1  =  y;
    z1  = -x*sin(ay) + z*cos(ay);
    
    x2  =  x1;                         // around x
    y2  = y1*cos(ax) - z1*sin(ax);

    *px = x2*cos(az) - y2*sin(az);     // around z, and conversed point
    *py = x2*sin(az) + y2*cos(az);

}
