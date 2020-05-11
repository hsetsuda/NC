#include <windows.h>
#include <math.h> //add
#include "my_glib.h"

void rotate(double,double,double,double,double,double,double *,double *);

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
     

void main(void)
{

    struct {
        int f;
        double x,y,z;
    } a[]
    ={-1,80,50,100,   1,0,50,100,   1,0,0,100,    1,80,0,100,
      1,80,0,0,       1,80,50,0,    1,80,50,100,  1,80,0,100,
      -1,0,50,100,    1,0,50,0,     1,0,0,0,      1,0,0,100,
      -1,0,50,0,      1,80,50,0,    -1,0,0,0,     1,80,0,0,
      -1,0,50,100,    1,40,80,100,  1,80,50,100,  -1,0,50,0,
      1,40,80,0,      1,80,50,0,    -1,40,80,100, 1,40,80,0,
      -1,50,72,100,   1,50,90,100,  1,65,90,100,  1,65,61,100,
      1,65,61,80,     1,65,90,80,   1,50,90,80,   1,50,90,100,
      -1,65,90,100,   1,65,90,80,   -1,50,90,80,  1,50,72,80,
      1,65,61,80,     -1,50,72,100, 1,50,72,80,   -999,0,0,0  };
    int k;
    double ax =  20 * 3.14159/180,
           ay = -45 * 3.14159/180,
           az =   0 * 3.14159/180,
           px,py;

    //ginit(); 
    //cls(hdc);
    window(-160,-100,160,100);
    //window(-400,-400,0,0);

    for (k=0;a[k].f!=-999;k++)
    {
        rotate( ax, ay, az, a[k].x, a[k].y, a[k].z, &px, &py);
        if (a[k].f==-1)          //
            setpoint(px,py);
        else
            moveto(hdc, px,py);
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
       double *px,double *py)      // 
{
    double x1,y1,z1,x2,y2;
    x1  =  x*cos(ay) + z*sin(ay);        // 
    y1  =  y;
    z1  = -x*sin(ay) + z*cos(ay);
    x2  =  x1;                         // 
    y2  = y1*cos(ax) - z1*sin(ax);
    *px = x2*cos(az) - y2*sin(az);     // 
    *py = x2*sin(az) + y2*cos(az);

}
