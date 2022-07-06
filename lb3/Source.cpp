#include <windows.h>
#include <ctime>

using namespace std;

HINSTANCE hInst;
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Zyablitsev Kelchevskiy";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
    int nCmdShow)
{
    srand(time(NULL));
    MSG msg;

    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)WndProc; 
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW-1); 
    wcex.lpszMenuName = NULL; 
    wcex.lpszClassName = szWindowClass; 
    wcex.hIconSm = NULL;
    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    hInst = hInstance; 
    hWnd = CreateWindow(szWindowClass,
        szTitle, 
        WS_OVERLAPPEDWINDOW,
        0, 
        0, 
        500, 
        250, 
        NULL, 
        NULL, 
        hInstance,
        NULL); 
    if (!hWnd) 
    {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd); 
    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HICON hIcon = (HICON)LoadImage( 
        NULL,      
        "icon1.ico",   
        IMAGE_ICON,    
        0,              
        0,           
        LR_LOADFROMFILE |  
        LR_DEFAULTSIZE | 
        LR_SHARED 
    );

    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    static TCHAR ch;
    HBRUSH hbr = CreateSolidBrush(RGB(100, 150, 100));
    static HWND twnd[12];
    static LPDRAWITEMSTRUCT drw;
    HWND tt;

    TEXTMETRIC tm;
    RECT rect;
    POINT pt[3];
    int cx, cy;
    static bool flag[3] = { 0,0,0 };
    static char buff1[50];
    static char buff2[50];
    static char buff3[50];

    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 10:
            GetWindowText(twnd[9], buff1, 12);
            SetWindowText(twnd[0], buff1);
            
            InvalidateRect(hWnd, NULL, 1);
            break;
        case 11:
            GetWindowText(twnd[10], buff2, 12);
            SetWindowText(twnd[1], buff2);
            
            InvalidateRect(hWnd, NULL, 1);
            break;
        case 12:
            GetWindowText(twnd[11], buff3, 12);
            SetWindowText(twnd[2], buff3);
            InvalidateRect(hWnd, NULL, 1);
            break;
        case 7:
            ShowWindow(twnd[0], SendMessage(twnd[6], BM_GETCHECK, 1, 0));
            break;
        case 8:
            ShowWindow(twnd[1], SendMessage(twnd[7], BM_GETCHECK, 1, 0));
            break;
        case 9:
            ShowWindow(twnd[2], SendMessage(twnd[8], BM_GETCHECK, 1, 0));
            break;
        case 4:
            break;
        }
        break;
    case WM_DRAWITEM:
        drw = (LPDRAWITEMSTRUCT)lParam;
        FillRect(drw->hDC, &drw->rcItem,
            (HBRUSH)GetStockObject(WHITE_BRUSH));
        FrameRect(drw->hDC, &drw->rcItem,
            (HBRUSH)GetStockObject(BLACK_BRUSH));
        cx = (drw->rcItem.right - drw->rcItem.left) / 2;
        cy = (drw->rcItem.bottom - drw->rcItem.top) / 2;

        if (drw->itemState & ODS_SELECTED) {
            FillRect(drw->hDC, &drw->rcItem,
                CreateSolidBrush(RGB(220, 220, 220)));
            FrameRect(drw->hDC, &drw->rcItem,
                (HBRUSH)GetStockObject(BLACK_BRUSH));
        }

        switch (drw->CtlID) {
        case 1:
            SetBkMode(drw->hDC, TRANSPARENT);
            hdc = GetDC(hWnd);
            SelectObject(drw->hDC, hbr);
            if (SendMessage(twnd[3], BM_GETCHECK, 1, 0)) {
                DrawIconEx(drw->hDC, 10, 10, hIcon, 32, 32, 0, NULL, DI_NORMAL);
            }
            else DrawText(drw->hDC, buff1, -1, &drw->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            break;
        case 2:
            SetBkMode(drw->hDC, TRANSPARENT);
            hdc = GetDC(hWnd);
            SelectObject(drw->hDC, hbr);
            if (SendMessage(twnd[4], BM_GETCHECK, 1, 0)) {
                DrawIconEx(drw->hDC, 10, 10, hIcon, 32, 32, 0, NULL, DI_NORMAL);
            }
            else DrawText(drw->hDC, buff2, -1, &drw->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            break;
        case 3:
            SetBkMode(drw->hDC, TRANSPARENT);
            hdc = GetDC(hWnd);
            SelectObject(drw->hDC, hbr);
            if (SendMessage(twnd[5], BM_GETCHECK, 1, 0)) {
                DrawIconEx(drw->hDC, 10, 10, hIcon, 32, 32, 0, NULL, DI_NORMAL);
            }
            else DrawText(drw->hDC, buff3, -1, &drw->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            break;

        }

        break;
    case WM_CREATE:
        twnd[3] = CreateWindow("button", "Icon", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 20, 170, 55, 13, hWnd, (HMENU)4, hInst, NULL);
        twnd[4] = CreateWindow("button", "Icon", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 160, 170, 55, 13, hWnd, (HMENU)5, hInst, NULL);
        twnd[5] = CreateWindow("button", "Icon", WS_CHILD | BS_AUTORADIOBUTTON | WS_VISIBLE, 300, 170, 55, 13, hWnd, (HMENU)6, hInst, NULL);

        twnd[6] = CreateWindow("button", buff3, WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 20, 120, 13, 13, hWnd, (HMENU)7, hInst, NULL);
        twnd[7] = CreateWindow("button", buff3, WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 160, 120, 13, 13, hWnd, (HMENU)8, hInst, NULL);
        twnd[8] = CreateWindow("button", buff3, WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, 300, 120, 13, 13, hWnd, (HMENU)9, hInst, NULL);
        SendMessage(twnd[6], BM_SETCHECK, 1, 0);
        SendMessage(twnd[7], BM_SETCHECK, 1, 0);
        SendMessage(twnd[8], BM_SETCHECK, 1, 0);

        twnd[9] = CreateWindow("edit", buff1, WS_CHILD | WS_VISIBLE, 20, 60, 80, 20, hWnd, (HMENU)10, hInst, NULL);
        twnd[10] = CreateWindow("edit", buff2, WS_CHILD | WS_VISIBLE, 160, 60, 80, 20, hWnd, (HMENU)11, hInst, NULL);
        twnd[11] = CreateWindow("edit", buff3, WS_CHILD | WS_VISIBLE, 300, 60, 80, 20, hWnd, (HMENU)12, hInst, NULL);

        twnd[0] = CreateWindow("button", buff1, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 40, 100, 100, 50, hWnd, (HMENU)1, hInst, NULL);
        twnd[1] = CreateWindow("button", buff2, WS_CHILD | BS_OWNERDRAW | WS_VISIBLE, 180, 100, 100, 50, hWnd, (HMENU)2, hInst, NULL);
        twnd[2] = CreateWindow("button", buff3, WS_CHILD | BS_OWNERDRAW | WS_VISIBLE, 320, 100, 100, 50, hWnd, (HMENU)3, hInst, NULL);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rt); 

        EndPaint(hWnd, &ps); 
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
