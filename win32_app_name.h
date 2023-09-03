struct win32_state
{
    char *DLLPath;
};

struct win32_app_code
{
    b32 IsValid;
    HMODULE AppDLL;
    app_update_and_render *AppUpdateAndRender;
};

struct win32_offscreen_buffer
{
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
};

struct win32_window_dimension
{
    int Width;
    int Height;
};


