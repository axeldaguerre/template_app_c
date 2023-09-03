#if !defined(APP_NAME_PLATFORM_H)

struct app_memory
{
    
};

#define APP_UPDATE_AND_RENDER(name) void name(app_memory *Memory, app_offscreen_buffer *Buffer)
typedef APP_UPDATE_AND_RENDER(app_update_and_render);

#define APP_NAME_PLATFORM_H
#endif
