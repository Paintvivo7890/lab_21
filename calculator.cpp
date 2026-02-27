#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_ADD   201
#define ID_SUB   202
#define ID_MUL   203
#define ID_DIV   204

HWND hEdit1, hEdit2;

/* ================= Window Procedure ================= */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
                         WPARAM wParam, LPARAM lParam) {

	int id = LOWORD(wParam);
	int code = HIWORD(wParam);

    switch(Message) {

    case WM_CREATE:
    {
		CreateWindow("STATIC","PLease input two numbers",
			WS_VISIBLE | WS_CHILD ,
			35,15,180,25,
			hwnd,NULL,NULL,NULL);
        
        hEdit1 = CreateWindow("EDIT","",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
            25,50,200,25,
            hwnd,(HMENU)ID_EDIT1,NULL,NULL);

        hEdit2 = CreateWindow("EDIT","",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
            25,85,200,25,
            hwnd,(HMENU)ID_EDIT2,NULL,NULL);

        
        CreateWindow("BUTTON","+",
            WS_VISIBLE | WS_CHILD,
            35,130,35,30,
            hwnd,(HMENU)ID_ADD,NULL,NULL);

        CreateWindow("BUTTON","-",
            WS_VISIBLE|WS_CHILD,
            80,130,35,30,
            hwnd,(HMENU)ID_SUB,NULL,NULL);

        CreateWindow("BUTTON","*",
            WS_VISIBLE|WS_CHILD,
            125,130,35,30,
            hwnd,(HMENU)ID_MUL,NULL,NULL);

        CreateWindow("BUTTON","/",
            WS_VISIBLE|WS_CHILD,
            170,130,35,30,
            hwnd,(HMENU)ID_DIV,NULL,NULL);

        break;
    }
    
	case WM_COMMAND:
{
    int id = LOWORD(wParam);
    int code = HIWORD(wParam);

    if(code == BN_CLICKED)
    {
        char t1[100], t2[100], resultText[200];

        GetWindowText(hEdit1,t1,100);
        GetWindowText(hEdit2,t2,100);

        double a = atof(t1);
        double b = atof(t2);
        double result = 0;

        switch(id) {
            case ID_ADD: result = a+b; break;
            case ID_SUB: result = a-b; break;
            case ID_MUL: result = a*b; break;

            case ID_DIV:
                if(b==0){
                    MessageBox(hwnd,"Cannot divide by zero",
                               "Error",MB_OK);
                    return 0;
                }
                result = a/b;
                break;
        }

        sprintf(resultText,"%.3f",result);
        MessageBox(hwnd,resultText,"Result",MB_OK);
    }
    break;
}

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* ================= WinMain ================= */
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE,
                   LPSTR,
                   int nCmdShow) {

    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    wc.hbrBackground = CreateSolidBrush(RGB(57, 255, 20));//RGB(0,180,255)

    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)){
        MessageBox(NULL,"Window Registration Failed!",
                   "Error!",MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        0,
        "WindowClass",
        "My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        250,
        200,
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL){
        MessageBox(NULL,"Window Creation Failed!",
                   "Error!",MB_OK);
        return 0;
    }

    ShowWindow(hwnd,nCmdShow);

    while(GetMessage(&msg,NULL,0,0)>0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}