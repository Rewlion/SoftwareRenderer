#pragma once

#include "InputUtillity.h"

#include <Windows.h>
#include <Gdiplus.h>
#include <gdiplusgraphics.h>
#include <gdiplusheaders.h>
#include <gdipluscolor.h>
#include <gdiplusinit.h>
#include <gdiplusimaging.h>
#include <Gdipluspixelformats.h>

struct WindowSize
{
    unsigned int m_Width;
    unsigned int m_Height;
};

class InputCallback
{
public:
    virtual void HandleKeyInput(Key key, KeyAction action) = 0;
};

struct SharedWindowProcData
{
    bool           m_ShouldWindowClose;
    InputCallback* m_InputCallback;
};

class WindowManager
{
public:
    WindowManager(HINSTANCE hInstance, PWSTR pCmdLine, const int nCmdShow, const char* title, const WindowSize& size);
    ~WindowManager();

    void PollEvents();
    
    inline void Blt() { m_Graphics->DrawImage(m_FrameBitmap, 0, 0); }

    inline void SetInputCallback(InputCallback* callback) { m_ProcData.m_ShouldWindowClose = callback; }

    inline bool ShouldWindowClose() const { return m_ProcData.m_ShouldWindowClose; }

    inline HWND GetWindowHandler() const { return m_WindowHandler; }

    inline Gdiplus::Bitmap* GetBitmap() { return m_FrameBitmap; }

    void DrawString(const WCHAR* str);
private:
    HINSTANCE            m_hInstance;
    PWSTR                m_pCmdLine;
    int                  m_nCmdShow;
    
    const char*          m_Title;
    WindowSize           m_WindowSize;
    
    ULONG_PTR            m_GdiplusToken;
    HWND                 m_WindowHandler;
    Gdiplus::Graphics*   m_Graphics;
    Gdiplus::Bitmap*     m_FrameBitmap;

    SharedWindowProcData m_ProcData;
};