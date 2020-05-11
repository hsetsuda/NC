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
     
      int k;
      double leng = 400.0;      // initial value of cross line
      double rd = 3.14159/180;
      double x, y;
      double theta = 54.7;

      ginit();
      cls(hdc);

      setpoint(0, 380);
      setangle(-1*theta);
      for(k=1; k<=10; k++)
      {
        move(hdc, leng);                 // draw cross line
        x = leng * cos(theta*rd);   // x direction length 
        y = leng * sin(theta*rd);   // y direction length
       
        turn(180.0-35.3);           // draw square
        move(hdc, y);
       
        turn(90);
        move(hdc, x);
       
        turn(90);
        move(hdc, y);
       
        turn(90);
        move(hdc, x);

        turn(35.3);
        leng = leng/sqrt(2);
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

