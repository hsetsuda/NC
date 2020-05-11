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
      
      // tree curve no.2

      void ctree(HDC hdc, int n, double x0, double y0, double leng, double angle);

      int n = 9;                    // branch dimention number
      double x0 = 0.0, y0 = 50.0;   // root position
      double leng = 100.0;          // branch length
      double angle = 90.0;          // branch direction

      ginit();
      cls(hdc);
      window( -640, -400, 640, 400);

      ctree(hdc, n, x0, y0, leng, angle);
      
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

void ctree(HDC hdc, int n, double x0, double y0, double leng, double angle)
{   // tree curve recursive function
  double rd = 3.14159/180;
  int k;

  if(n==0)
  {
    return;
  }

  setpoint(x0, y0);
  setangle(angle);
  for(k=1; k<=4; k++)   // draw square
  {
    turn(90);
    move(hdc, leng);
  }

  ctree( hdc, n-1, 
         x0 + leng * cos((angle-45)*rd) / sqrt(2.0),
         y0 + leng * sin((angle-45)*rd) / sqrt(2.0),  
         leng/sqrt(2.0), angle-45
        );
  ctree( hdc, n-1, 
         x0 + leng * cos((angle+45)*rd) * sqrt(2.0),
         y0 + leng * sin((angle+45)*rd) * sqrt(2.0),  
         leng/sqrt(2.0), angle+45
        );
}

