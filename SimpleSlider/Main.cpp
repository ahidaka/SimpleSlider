#include <windows.h>
#include <winuser.h>
#include <commctrl.h>
#include <stdio.h>
#include <tchar.h>

#include "CommonMacros.h"
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

//Macro that calculates the X coordinate (LEFT) and Y coordinate (TOP) to center the window
#define ScreenCenterX(Width) ((0)<((int)((GetSystemMetrics(SM_CXSCREEN)- Width) / 2)) ? ((int)((GetSystemMetrics(SM_CXSCREEN) - Width) / 2)) :(0))
#define ScreenCenterY(Height) ((0)<((int)((GetSystemMetrics(SM_CYSCREEN)- Height) / 2)) ? ((int)((GetSystemMetrics(SM_CYSCREEN) - Height) / 2)) :(0))

// Function declarations
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
// WinMain
//
// Application entry point
//
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // Initialize common controls
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);

    // Create the dialog box
    HWND hDlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, WindowProc, 0);
    if (NULL == hDlg)
    {
        return 1;
    }

    ShowWindow(hDlg, nShowCmd);
    UpdateWindow(hDlg);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessage(hDlg, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hwndSlider = 0;
    LONG value = 0;
    HWND hSlider1 = GetDlgItem(hWnd, IDC_SLIDER1);

    switch (message)
    {
    case WM_CREATE:
        // Initialize dialog (if needed)
        (VOID)TrackBar_SetRange(hSlider1, 0, 100);
        (VOID)TrackBar_SetPos(hSlider1, 50);
        break;

    case WM_COMMAND:
        // Process command messages
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hWnd, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;

    case WM_HSCROLL:
        // Handle slider movement
        value = TrackBar_GetPos(hSlider1);
        break;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
