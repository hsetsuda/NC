#include <windows.h>
#include <stdio.h>
#include <math.h> //add
#include "my_glib.h"

#define N 9   // number of data
//#define N 4   // number of data

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
     
      double x[] = {  35,  19, 10,  3, 0, -3, -10, -19, -35};
      double y[] = { -20, -20, -5, -5, 0, -5,  -5, -20, -20};
      //double x[] = { 0, -10, -20,  35};
      //double y[] = { 0,   0, -20, -20};
      int a, b, j, k;
      double rd = 3.14159/180;
      double m, h, vx, vy, px, py;

      ginit();
      cls(hdc);
      m = 70.0;                 // a side length of equilateral triangle
      h = m * sqrt(3.0) / 2;    // height of equilateral triangle
      window( -m/2, -h/3, m/2, h*2/3);   // window(WX1, WY1, WX2, WY2)

      b = 1;
      for(vy=0.0; vy<=310.0; vy=vy+h)
      {
        a = 1;
        for(vx=50.0; vx<=500.0; vx=vx+m/2)
        {
          view(hdc, vx, vy, vx+m, vy+h);
          for(j=0; j<3; j++)
          {
            for(k=0; k<N; k++)
            {
              px = x[k]*cos(120*j*rd) - y[k]*sin(120*j*rd);
              py = x[k]*sin(120*j*rd) + y[k]*cos(120*j*rd);
              if(a*b==-1)
                py = -py + h/3;   // inverse shadow adjusut
              if(k==0)
                setpoint(px, py);
              else
                moveto(hdc, px, py);
            }
          }
          a = -a;
        }
        b = -b;
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

