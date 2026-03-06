#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_ADD   201
#define ID_SUB   202
#define ID_MUL   203
#define ID_DIV   204

HWND hEdit1, hEdit2;

/* ================= Window Procedure ================= */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
                         WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {

    case WM_CREATE:
    {
        CreateWindowW(L"STATIC",L"Please input two numbers",
            WS_VISIBLE | WS_CHILD ,
            35,15,180,25,
            hwnd,NULL,NULL,NULL);

        hEdit1 = CreateWindowW(L"EDIT",L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
            25,50,200,25,
            hwnd,(HMENU)ID_EDIT1,NULL,NULL);

        hEdit2 = CreateWindowW(L"EDIT",L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
            25,85,200,25,
            hwnd,(HMENU)ID_EDIT2,NULL,NULL);

        CreateWindowW(L"BUTTON",L"+",
            WS_VISIBLE | WS_CHILD,
            35,130,35,30,
            hwnd,(HMENU)ID_ADD,NULL,NULL);

        CreateWindowW(L"BUTTON",L"-",
            WS_VISIBLE | WS_CHILD,
            80,130,35,30,
            hwnd,(HMENU)ID_SUB,NULL,NULL);

        CreateWindowW(L"BUTTON",L"*",
            WS_VISIBLE | WS_CHILD,
            125,130,35,30,
            hwnd,(HMENU)ID_MUL,NULL,NULL);

        CreateWindowW(L"BUTTON",L"/",
            WS_VISIBLE | WS_CHILD,
            170,130,35,30,
            hwnd,(HMENU)ID_DIV,NULL,NULL);

        break;
    }

    case WM_COMMAND:
    {
        if(HIWORD(wParam) == BN_CLICKED)
        {
            wchar_t t1[100], t2[100], resultText[200];

            GetWindowTextW(hEdit1,t1,100);
            GetWindowTextW(hEdit2,t2,100);

            double a = _wtof(t1);
            double b = _wtof(t2);
            double result = 0;

            switch(LOWORD(wParam))
            {
                case ID_ADD: result = a+b; break;
                case ID_SUB: result = a-b; break;
                case ID_MUL: result = a*b; break;

                case ID_DIV:
                    if(b==0)
                    {
                        MessageBoxW(hwnd,L"Cannot divide by zero",
                                   L"Error",MB_OK);
                        return 0;
                    }
                    result = a/b;
                    break;
            }

            swprintf(resultText,200,L"%.3f",result);
            MessageBoxW(hwnd,resultText,L"Result",MB_OK);
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, Message, wParam, lParam);
    }

    return 0;
}

/* ================= WinMain ================= */
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE,
                   LPSTR,
                   int nCmdShow)
{
    WNDCLASSEXW wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    wc.hbrBackground = CreateSolidBrush(RGB(57,255,20));

    wc.lpszClassName = L"WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassExW(&wc))
    {
        MessageBoxW(NULL,L"Window Registration Failed!",
                   L"Error!",MB_OK);
        return 0;
    }

    hwnd = CreateWindowExW(
        0,
        L"WindowClass",
        L"My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        250,
        200,
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL)
    {
        MessageBoxW(NULL,L"Window Creation Failed!",
                   L"Error!",MB_OK);
        return 0;
    }

    ShowWindow(hwnd,nCmdShow);

    while(GetMessage(&msg,NULL,0,0)>0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}