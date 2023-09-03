#include<windows.h>

#include"app_name.cpp"
#include"win32_app_name.h"

global_variable b32 GlobalRunning;
global_variable win32_offscreen_buffer GlobalBackbuffer;

internal  win32_app_code Win32LoadDLL(char *FileName)
{
    win32_app_code Result = {};
    Result.AppDLL = LoadLibraryA(FileName);

    if(Result.AppDLL)
    {
        Result.AppUpdateAndRender = (app_update_and_render*)GetProcAddress(Result.AppDLL, "AppUpdateAndRender");

        Result.IsValid = (Result.AppUpdateAndRender && 1);   
    }
    else
    {
        Result.IsValid = false;
        OutputDebugStringA("Couln't load the DLL\n");
    }
    return Result;
}

internal void
Win32DisplayBufferInWindow(win32_offscreen_buffer *Buffer,
                           HDC DeviceContext, int WindowWidth, int WindowHeight)
{

    if((WindowWidth >= 2*Buffer->Width) &&
       (WindowHeight >= 2*Buffer->Height))
    {
        StretchDIBits(DeviceContext,
                      0, 0, 2*Buffer->Width, 2*Buffer->Height,
                      0, 0, Buffer->Width, Buffer->Height,
                      Buffer->Memory,
                      &Buffer->Info,
                      DIB_RGB_COLORS, SRCCOPY);
    }
    else
    {
        int OffsetX = 10;
        int OffsetY = 10;

        PatBlt(DeviceContext, 0, 0, WindowWidth, OffsetY, BLACKNESS);
        PatBlt(DeviceContext, 0, OffsetY + Buffer->Height, WindowWidth, WindowHeight, BLACKNESS);
        PatBlt(DeviceContext, 0, 0, OffsetX, WindowHeight, BLACKNESS);
        PatBlt(DeviceContext, OffsetX + Buffer->Width, 0, WindowWidth, WindowHeight, BLACKNESS);

        StretchDIBits(DeviceContext,
                      OffsetX, OffsetY, Buffer->Width, Buffer->Height,
                      0, 0, Buffer->Width, Buffer->Height,
                      Buffer->Memory,
                      &Buffer->Info,
                      DIB_RGB_COLORS, SRCCOPY);
    }
}

internal win32_window_dimension
Win32GetWindowDimension(HWND Window)
{
    win32_window_dimension Result;
    
    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    Result.Width = ClientRect.right - ClientRect.left;
    Result.Height = ClientRect.bottom - ClientRect.top;

    return(Result);
}

internal LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
                        UINT Message,
                        WPARAM WParam,
                        LPARAM LParam)
{       
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_CLOSE:
        {
            GlobalRunning = false;
        } break;

        case WM_SETCURSOR:
        {

        } break;
        
        case WM_ACTIVATEAPP:
        {
#if 0
            if(WParam == TRUE)
            {
                SetLayeredWindowAttributes(Window, RGB(0, 0, 0), 255, LWA_ALPHA);
            }
            else
            {
                SetLayeredWindowAttributes(Window, RGB(0, 0, 0), 64, LWA_ALPHA);
            }
#endif
        } break;

        case WM_DESTROY:
        {
            GlobalRunning = false;
        } break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            win32_window_dimension Dimension = Win32GetWindowDimension(Window);
            Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext,
                                       Dimension.Width, Dimension.Height);
            EndPaint(Window, &Paint);
        } break;

        default:
        {
            Result = DefWindowProcA(Window, Message, WParam, LParam);
        } break;
    }
    
    return(Result);    
}

int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR CommandLine,
        int ShowCode)
{
    WNDCLASSA WindowClass = {};
    
    WindowClass.style = CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.hInstance = Instance;
    WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
    WindowClass.lpszClassName = "AppNameWindowClass";

    if(RegisterClassA(&WindowClass))
    {
        GlobalRunning = true;
        
        HWND Window =
            CreateWindowExA(
                0,
                WindowClass.lpszClassName,
                "app_name",
                WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                Instance,
                0);
        
        if(Window)
        {
            win32_state Win32State = {};
            // TODO() No hardcoded path
            Win32State.DLLPath = "C:\\Users\\axeld\\Documents\\Projects\\Projects_Programming\\app_template\\build\\app_name.dll";
            
            win32_app_code AppCode = Win32LoadDLL(Win32State.DLLPath);
            app_memory AppMemory = {};

            if(AppCode.IsValid)
            {
                while(GlobalRunning)
                {
                    app_offscreen_buffer Buffer = {};
                    
                    AppCode.AppUpdateAndRender(&AppMemory, &Buffer);

                }            
            }
            
        }
    }
               
    return(0);
}
