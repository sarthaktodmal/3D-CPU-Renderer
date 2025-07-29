#define UNICODE
#include<stdlib.h>
#include"winmain.h"
#include"windows.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool ProcessMessages()
{
    MSG msg = {};
    while(PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
        {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}
const wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c)+1;
    wchar_t* wc = malloc(cSize * sizeof(wchar_t));
    mbstowcs (wc, c, cSize);
    return wc;
}
void Initialize_Window(Window* window, unsigned int width, unsigned int height, const char* title)
{
    HINSTANCE* m_hinstance = malloc(sizeof(HINSTANCE));
    HWND* m_hwnd = malloc(sizeof(HWND));
    HDC* m_hdc = malloc(sizeof(HDC));

    BITMAPINFO *bitmap_info = malloc(sizeof(BITMAPINFO));
    bitmap_info->bmiHeader.biSize = sizeof(bitmap_info->bmiHeader);
    bitmap_info->bmiHeader.biWidth = width;
    bitmap_info->bmiHeader.biHeight = height;
    bitmap_info->bmiHeader.biPlanes = 1;
    bitmap_info->bmiHeader.biBitCount = 32;
    bitmap_info->bmiHeader.biCompression = BI_RGB;

    //Assign
    window->width = width;
    window->height = height;
    window->title = GetWC(title);
    window->running = 1;

    window->_hinstance_addr = (void*)m_hinstance;
    window->_hwnd_addr = (void*)m_hwnd;
    window->_hdc_addr = (void*)m_hdc;
    window->_bitmapinfo_addr = (void*)bitmap_info;

    *(HINSTANCE*)window->_hinstance_addr = GetModuleHandle(nullptr);
}

void Create_Window(Window* window)
{
    const wchar_t* CLASS_NAME = L"Windows Class";
    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = *(HINSTANCE*)window->_hinstance_addr;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);
    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + window->width;
    rect.bottom = rect.top + window->height;

    AdjustWindowRect(&rect, style, false);

    *(HWND*)window->_hwnd_addr = CreateWindowEx
    (
        0, CLASS_NAME, window->title,
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        *(HINSTANCE*)window->_hinstance_addr,
        NULL
    );
    *(HDC*)window->_hdc_addr = GetDC(*(HWND*)window->_hwnd_addr);
    ShowWindow(*(HWND*)window->_hwnd_addr, SW_SHOW);
}

void PresentBuffer(Window* window, void* buffer)
{
    int a = StretchDIBits(*(HDC*)window->_hdc_addr,0,0,window->width, window->height, 0,0, window->width, window->height, buffer, (BITMAPINFO*)window->_bitmapinfo_addr, DIB_RGB_COLORS, SRCCOPY);
}

void Destroy_Window(Window* window)
{
    const wchar_t* CLASS_NAME = L"Windows Class";
    UnregisterClass(CLASS_NAME, *(HINSTANCE*)window->_hinstance_addr);

    free((HINSTANCE*)window->_hinstance_addr);
    free((HWND*)window->_hwnd_addr);
    free((HDC*)window->_hdc_addr);
    free((BITMAPINFO*)window->_bitmapinfo_addr);
}