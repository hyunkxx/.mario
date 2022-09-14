#include "pch.h"
#include "mario.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

RECT g_rcClient;
HWND g_hWnd;
HINSTANCE hInst;                              
WCHAR szTitle[MAX_LOADSTRING];                
WCHAR szWindowClass[MAX_LOADSTRING];          

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MARIO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    CCore* pCore = CCore::GetInstance();

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    pCore->Initalize(hInstance, g_hWnd, g_rcClient);

    while (!pCore->IsExit())
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                PostQuitMessage(0);
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            pCore->Process();
        }
    }
    pCore->Release();

    CCore::Destroy();
    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MARIO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   g_rcClient.left = 0;
   g_rcClient.left = 0;
   g_rcClient.right = WIDTH;
   g_rcClient.bottom = HEIGHT;

   AdjustWindowRect(&g_rcClient, WS_OVERLAPPEDWINDOW, false);

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_BORDER,
       CW_USEDEFAULT, 0, g_rcClient.right, g_rcClient.bottom, nullptr, nullptr, hInstance, nullptr);

   SetWindowPos(g_hWnd, NULL, 0, 0, (g_rcClient.right - g_rcClient.left), (g_rcClient.bottom - g_rcClient.top),
       SWP_NOZORDER | SWP_NOMOVE);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}