#include <windows.h>
#include <stdio.h>
#include <math.h> //add
#include "my_glib.h"

double ANGLE; // add
double adj = 0;

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
      /* write draw program */
      
      void multi(double, double, double *, double *);
      void rotate(double, double *, double *);
     
      double x[] = {0, 100, 100,   0, 0};
      double y[] = {0,   0, 200, 200, 0};
      int j, k;
      int n = 5;

      ginit();
      cls(hdc);
      window(-320, -200, 320, 200);
      // window(WX1, WY1, WX2, WY2)

      for(j=0; j<12; j++)
      {
        for(k=0; k<n; k++)
        {
          multi(.8, .8, &x[k], &y[k]);
          rotate(30, &x[k], &y[k]);
          if(k==0)
          {
            setpoint(x[k], y[k]);
          }
          else
          {
            moveto(hdc, x[k], y[k]);
          }
        }
      }

      EndPaint(hwnd, &ps);               // 描画終了
        return 0;

    case WM_DESTROY:        // event that delete the window(wParam=0, lParam=0)
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
    // return 0->processing yourself, DefWindowProc->system prcessing
}

void multi(double factx, double facty, double *x, double *y)
{
  *x = factx * (*x);
  *y = facty * (*y);
}
void rotate(double deg, double *x, double *y)
{
  double dx, dy;
  double rd = 3.14159 / 180;
  
  dx = (*x) * cos(deg*rd) - (*y) * sin(deg*rd);
  dy = (*x) * sin(deg*rd) + (*y) * cos(deg*rd);
  *x = dx;
  *y = dy;
}
