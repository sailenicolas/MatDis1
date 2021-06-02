// mat3dis.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "mat3dis.h"
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <strsafe.h>
#include <CommCtrl.h>
#define MAX_LOADSTRING 100
#define ADD_TEXT 4
#define IDC_LISTBOX_EXAMPLE 1999
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ListBoxExampleProc(HWND, UINT, WPARAM, LPARAM);

HWND hEdit, hOut;
HWND hListBox; // Handle for list box control
typedef struct
{
    TCHAR achName[MAX_PATH];
    TCHAR achPosition[12];
    int nGamesPlayed;
    int nGoalsScored;
} Player;

Player Roster[] =
{
    {TEXT("->"), TEXT("Midfield"), 18, 4 },
    {TEXT("\\/"), TEXT("Forward"), 36, 12 },
    {TEXT("<->"), TEXT("Back"), 26, 0 },
    {TEXT("/\\"), TEXT("Back"), 24, 2 },
    {TEXT("|="), TEXT("Midfield"), 26, 3 },
    {TEXT("=>"), TEXT("Back"), 24, 3},
    {TEXT("<=>"), TEXT("Forward"), 13, 3 },
};
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MAT3DIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAT3DIS));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAT3DIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MAT3DIS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
void AddControls(HWND hWnd);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        AddControls(hWnd);
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {

            case BN_CLICKED:
               //MessageBox(NULL, L"Button pressed", L"Windows", MB_OK);
            break;
            case ADD_TEXT:
                wchar_t name[60];
                GetWindowTextW(hEdit, name, 30);
                wcscat_s(name, L"Hola");
                    SetWindowText(hOut, name);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDC_LISTBOX_EXAMPLE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ListBoxExampleProc);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
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

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message,
    WPARAM wParam, LPARAM lParam)
{
        TCHAR Planets[9][10] =
        {
            TEXT("=>"), TEXT("->"), TEXT("|="), TEXT("<->"),
            TEXT("\//"), TEXT("<=>"), TEXT("/\\"), TEXT("-.-"),
            TEXT("Pluto??")
        };
    switch (message)
    {
    case WM_INITDIALOG:
    {
        TCHAR A[16];
        int  k = 0;
        int xpos = 100;            // Horizontal position of the window.
        int ypos = 100;            // Vertical position of the window.
        int nwidth = 200;          // Width of the window
        int nheight = 200;         // Height of the window
        HWND hwndParent = hDlg; // Handle to the parent window
        HWND hWndComboBox = CreateWindowW(WC_COMBOBOX, TEXT(""),
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
            xpos, ypos, nwidth, nheight, hwndParent, NULL, HINST_THISCOMPONENT,
            NULL);
        memset(&A, 0, sizeof(A));
        for (k = 0; k <= 8; k += 1)
        {
            wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)Planets[k]);

            // Add string to combobox.
            SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);
        return TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;

        case IDC_COMBO1:
        {
            switch (HIWORD(wParam))
            {
            case CBN_SELCHANGE:
            {
                int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
                    (WPARAM)0, (LPARAM)0);
                TCHAR  ListItem[256];
                (TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT,
                    (WPARAM)ItemIndex, (LPARAM)ListItem);
                MessageBox(hDlg, (LPCWSTR)ListItem, Planets[ItemIndex], MB_OK);
                return TRUE;
            }
            }
        }
        return TRUE;
        }
    }
    return FALSE;
}
void AddControls(HWND hWnd) {
    CreateWindowW(L"static", L"This", WS_VISIBLE | WS_CHILD , 200, 30, 100, 50, hWnd, NULL, NULL, NULL);
    hEdit = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 70, 100, 50, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"This", WS_VISIBLE | WS_CHILD , 200, 150, 100, 50, hWnd, (HMENU)IDC_LISTBOX_EXAMPLE, NULL, NULL);
    hOut = CreateWindowW(L"STATIC", L"dd", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 200, 300, 200, hWnd, NULL, NULL, NULL);

}