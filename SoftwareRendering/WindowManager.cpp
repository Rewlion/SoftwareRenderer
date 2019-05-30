#include "WindowManager.h"
#include "InputUtillity.h"

#include <assert.h>

namespace
{
    inline Key ConvertWinApiKeyToManagerKey(const UINT scanCode, const bool isExtended)
    {
        switch (scanCode)
        {
        case VK_LBUTTON: //Left mouse button
            return Key::KEY_LMB;

        case VK_RBUTTON: //Right mouse button
            return Key::KEY_RMB;

        case VK_MBUTTON: //Middle mouse button(three - button mouse)
            return Key::KEY_MMB;

        case VK_XBUTTON1: //X1 mouse button
            return Key::KEY_X1MB;

        case VK_XBUTTON2: //X2 mouse button
            return Key::KEY_X2MB;

        case VK_BACK: //BACKSPACE key
            return Key::KEY_BACKSPACE;

        case VK_TAB: //TAB key
            return Key::KEY_TAB;

        case VK_RETURN: //ENTER key
            return Key::KEY_ENTER;

        case VK_SHIFT: //SHIFT key
            return isExtended ? Key::KEY_LEFT_SHIFT : Key::KEY_RIGHT_SHIFT;

        case VK_CONTROL: //CTRL key
            return isExtended ? Key::KEY_LEFT_CONTROL : Key::KEY_RIGHT_CONTROL;

        case VK_MENU: //ALT key
            return isExtended ? Key::KEY_LEFT_ALT : Key::KEY_RIGHT_ALT;

        case VK_CAPITAL: //CAPS LOCK key
            return Key::KEY_CAPS_LOCK;

        case VK_ESCAPE: //ESC key
            return Key::KEY_ESCAPE;

        case VK_SPACE: //SPACEBAR
            return Key::KEY_SPACE;

        case VK_PRIOR: //PAGE UP key
            return Key::KEY_PAGE_UP;

        case VK_NEXT: //PAGE DOWN key
            return Key::KEY_PAGE_DOWN;

        case VK_END: //END key
            return Key::KEY_END;

        case VK_HOME: //HOME key
            return Key::KEY_HOME;

        case VK_LEFT: //LEFT ARROW key
            return Key::KEY_LEFT;

        case VK_UP: //UP ARROW key
            return Key::KEY_UP;

        case VK_RIGHT: //RIGHT ARROW key
            return Key::KEY_RIGHT;

        case VK_DOWN: //DOWN ARROW key
            return Key::KEY_DOWN;

        case VK_INSERT: //INS key
            return Key::KEY_INSERT;

        case VK_DELETE: //DEL key
            return Key::KEY_DELETE;

        case 0x30: //0
            return Key::KEY_0;

        case 0x31: //1
            return Key::KEY_1;

        case 0x32: //2
            return Key::KEY_2;

        case 0x33: //3
            return Key::KEY_3;

        case 0x34: //4
            return Key::KEY_4;

        case 0x35: //5
            return Key::KEY_5;

        case 0x36: //6
            return Key::KEY_6;

        case 0x37: //7
            return Key::KEY_7;

        case 0x38: //8
            return Key::KEY_8;

        case 0x39: //9
            return Key::KEY_9;

        case 0x41: //A
            return Key::KEY_A;

        case 0x42: //B
            return Key::KEY_B;

        case 0x43: //C
            return Key::KEY_C;

        case 0x44: //D
            return Key::KEY_D;

        case 0x45: //E
            return Key::KEY_E;

        case 0x46: //F
            return Key::KEY_F;

        case 0x47: //G
            return Key::KEY_G;

        case 0x48: //H
            return Key::KEY_H;

        case 0x49: //I
            return Key::KEY_I;

        case 0x4A: //J
            return Key::KEY_J;

        case 0x4B: //K
            return Key::KEY_K;

        case 0x4C: //L
            return Key::KEY_L;

        case 0x4D: //M
            return Key::KEY_M;

        case 0x4E: //N
            return Key::KEY_N;

        case 0x4F: //O
            return Key::KEY_O;

        case 0x50: //P
            return Key::KEY_P;

        case 0x51: //Q
            return Key::KEY_Q;

        case 0x52: //R
            return Key::KEY_R;

        case 0x53: //S
            return Key::KEY_S;

        case 0x54: //T
            return Key::KEY_T;

        case 0x55: //U
            return Key::KEY_U;

        case 0x56: //V
            return Key::KEY_V;

        case 0x57: //W
            return Key::KEY_W;

        case 0x58: //X
            return Key::KEY_X;

        case 0x59: //Y
            return Key::KEY_Y;

        case 0x5A: //Z
            return Key::KEY_Z;

        case VK_NUMPAD0: //Numeric keypad 0 key
            return Key::KEY_KP_0;

        case VK_NUMPAD1: //Numeric keypad 1 key
            return Key::KEY_KP_1;

        case VK_NUMPAD2: //Numeric keypad 2 key
            return Key::KEY_KP_2;

        case VK_NUMPAD3: //Numeric keypad 3 key
            return Key::KEY_KP_3;

        case VK_NUMPAD4: //Numeric keypad 4 key
            return Key::KEY_KP_4;

        case VK_NUMPAD5: //Numeric keypad 5 key
            return Key::KEY_KP_5;

        case VK_NUMPAD6: //Numeric keypad 6 key
            return Key::KEY_KP_6;

        case VK_NUMPAD7: //Numeric keypad 7 key
            return Key::KEY_KP_7;

        case VK_NUMPAD8: //Numeric keypad 8 key
            return Key::KEY_KP_8;

        case VK_NUMPAD9: //Numeric keypad 9 key
            return Key::KEY_KP_9;

        case VK_F1: //F1 key
            return Key::KEY_F1;

        case VK_F2: //F2 key
            return Key::KEY_F2;

        case VK_F3: //F3 key
            return Key::KEY_F3;

        case VK_F4: //F4 key
            return Key::KEY_F4;

        case VK_F5: //F5 key
            return Key::KEY_F5;

        case VK_F6: //F6 key
            return Key::KEY_F6;

        case VK_F7: //F7 key
            return Key::KEY_F7;

        case VK_F8: //F8 key
            return Key::KEY_F8;

        case VK_F9: //F9 key
            return Key::KEY_F9;

        case VK_F10: //F10 key
            return Key::KEY_F10;

        case VK_F11: //F11 key
            return Key::KEY_F11;

        case VK_F12: //F12 key
            return Key::KEY_F12;

        default:
            return Key::KEY_UNKNOWN;
        }
    }
    
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        auto* procData = reinterpret_cast<SharedWindowProcData*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
        const int scanCode = (lParam >> 16) & 0xff;
        const bool isExtended = (lParam & 0x01000000) != 0;

        switch (uMsg)
        {
        case WM_DESTROY:
        {
            procData->m_ShouldWindowClose = true;
            return 0;
        }

        case WM_KEYUP:
        {
            if (procData && procData->m_InputCallback)
            {
                const Key key = ConvertWinApiKeyToManagerKey(scanCode, isExtended);
                procData->m_InputCallback->HandleKeyInput(key, KeyAction::Release);
            }
            
            return 0;
        }
        case WM_KEYDOWN:
        {
            if (procData && procData->m_InputCallback)
            {
                const Key key = ConvertWinApiKeyToManagerKey(scanCode, isExtended);
                procData->m_InputCallback->HandleKeyInput(key, KeyAction::Press);
            }
            return 0;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
}

WindowManager::WindowManager(HINSTANCE hInstance, PWSTR pCmdLine, const int nCmdShow, const char* title, const WindowSize& size)
    : m_hInstance(hInstance)
    , m_pCmdLine(pCmdLine)
    , m_nCmdShow(nCmdShow)
    , m_Title(title)
    , m_WindowSize(size)
    , m_ProcData{ false, nullptr }
{
    const LPCSTR CLASS_NAME = "Sample Window Class";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    RECT rect;
    rect.left = 0;
    rect.right = size.m_Width;
    rect.top = 0;
    rect.bottom = size.m_Height;

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m_WindowHandler = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "SoftwareRendering",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,

        NULL,       // Parent window
        NULL,       // Menu
        m_hInstance,
        NULL        // Additional application data
    );

    assert(m_WindowHandler != 0);
    ShowWindow(m_WindowHandler, m_nCmdShow);

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&m_GdiplusToken, &gdiplusStartupInput, NULL);

    const HDC deviceDC = GetDC(m_WindowHandler);
    m_Graphics = Gdiplus::Graphics::FromHDC(deviceDC);
    m_FrameBitmap = new Gdiplus::Bitmap(size.m_Width, size.m_Height, PixelFormat32bppRGB);

    SetWindowLongPtrA(m_WindowHandler, GWLP_USERDATA, reinterpret_cast<LONG>(&m_ProcData));
}

WindowManager::~WindowManager()
{
    Gdiplus::GdiplusShutdown(m_GdiplusToken);
}

void WindowManager::PollEvents()
{
    MSG msg = { };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void WindowManager::DrawString(const WCHAR* str)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(m_WindowHandler, &ps);

    // Initialize arguments.
    Gdiplus::Font myFont(L"Arial", 16);
    Gdiplus::RectF layoutRect(0.0f, 0.0f, 200.0f, 50.0f);
    Gdiplus::StringFormat format;
    format.SetAlignment(Gdiplus::StringAlignmentCenter);
    Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 255, 255, 255));

    // Draw string.
    m_Graphics->DrawString(
        str,
        11,
        &myFont,
        layoutRect,
        &format,
        &blackBrush);

    EndPaint(m_WindowHandler, &ps);
}