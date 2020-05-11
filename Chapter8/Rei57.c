#include <windows.h>
#include <stdio.h>
#include <math.h> //add
#include "my_glib.h"

double ANGLE; // add
int n;  // add

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

      void mirror(int flag, double m, double *dat);  // symetrical movement
      void draw(HDC hdc, double *dat);
      
      double a[] = {11, 
        0,80,  5,75, 17,80, 20,60, 15,55, 0,55,
        0,20, 10,40, 20,40, 10,20,  0,20};

      ginit();
      cls(hdc);
      window(-160, -100, 160, 100);

      draw(hdc, a);

      mirror(1, 0.0, a);
      draw (hdc, a);

      mirror(0, 0.0, a);
      draw (hdc, a);

      mirror(1, 0.0, a);
      draw (hdc, a);

      EndPaint(hwnd, &ps);               // 描画終了
        return 0;

    case WM_DESTROY:        // event that delete the window(wParam=0, lParam=0)
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
    // return 0->processing yourself, DefWindowProc->system prcessing
}

void mirror(int flag, double m, double *dat)  // symetrical movement
{
  for(int i=1; i<=2*dat[0]; i=i+2)  // dat[0] : nubmer of data
  {
    if(flag==1) // y-symetrical movement 
    {
      dat[i] = 2*m-dat[i];
    }
    if(flag==0) // x-symetrical movement 
    {
      dat[i+1] = 2*m-dat[i+1];
    }
  }
}

void draw(HDC hdc, double *dat)
{
  setpoint(dat[1], dat[2]);        // initial point
  for(int i=3; i<=2*dat[0]; i=i+2)
    moveto(hdc, dat[i], dat[i+1]);
}
