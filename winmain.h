#pragma once
#include"defines.h"

typedef unsigned short wchar_t;

typedef struct Window
{
    unsigned int width;
    unsigned int height;
    bool running;
    const wchar_t* title;

    void* _hinstance_addr;
    void* _hwnd_addr;
    void* _hdc_addr;
    void* _bitmapinfo_addr;

} Window;

void Initialize_Window(Window* window, unsigned int width, unsigned int height, const char* title);
void Create_Window(Window* window);
bool ProcessMessages();
void PresentBuffer(Window* window, void* buffer);
void Destroy_Window(Window* window);