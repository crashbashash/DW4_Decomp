#define __clz_tab __clz_tab_umoddi3
#include "dw4/libgcc_longlong.h"

UDWtype __umoddi3(UDWtype u, UDWtype v)
{
    UDWtype w;

    (void) __udivmoddi4(u, v, &w);
    return w;
}
