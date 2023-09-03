struct buffer
{
    void *Data;
    size_t Count;
};

struct app_state
{
    void *DisplayBuffer;
};

struct app_offscreen_buffer
{
    buffer Data;
};

