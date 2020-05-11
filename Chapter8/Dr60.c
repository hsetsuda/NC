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
      double rd = 3.14159/180;
      
      double x[] = {  0, 20,   0,  60, 100, 60,  0, -999};
      double z[] = { 40, 60, 100, 120,  60, 20, 40, -999};
      
      double h = 100.0;         // height
      double btx[30], bty[30];  // bottom
      double tpx[30], tpy[30];  // top
      
      double ax =  35 * rd;   // rotation angle around x
      double ay = -60 * rd;         // rotation angle around y
      double az =   0;   // rotation angle around z

      ginit(); 
      cls(hdc);
      window(-320,-200,320,200);
      
      for (k=0;(int)x[k]!=-999;k++)    // bottom plane
      {
          rotate(ax, ay, az, x[k], 0.0, z[k], &btx[k], &bty[k]);
          if (k==0)
          {
            setpoint(btx[k],bty[k]);
          }
          else
          {
            moveto(hdc, btx[k],bty[k]);
          }
      }
      
      n = k;
      for (k=0; k<n; k++)    // top plane
      {
          rotate(ax, ay, az, x[k], h, z[k], &tpx[k], &tpy[k]);
          if (k==0)
          {
            setpoint(tpx[k],tpy[k]);
          }
          else
          {
            moveto(hdc, tpx[k],tpy[k]);
          }
      }

      for(k=0; k<n; k++)
      {
        line(hdc, tpx[k], tpy[k], btx[k], bty[k]);
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
