#include<stdint.h>
#include"app_name.h"
#include"app_name_platform.h"
#include<stdio.h>

#define internal static
#define local_persist static
#define global_variable static

#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}

typedef double f64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint64_t u64;
typedef uint32_t u32;

typedef uint32_t b32;
typedef uint8_t b8;

extern "C" APP_UPDATE_AND_RENDER(AppUpdateAndRender)
{

    printf("DEBUG");
    
}
