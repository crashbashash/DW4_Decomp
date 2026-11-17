#define __clz_tab __clz_tab_umoddi3
#include "dw4/support/libgcc_longlong.h"
#include "dw4/support/softfloat.h"

UDWtype __umoddi3(UDWtype u, UDWtype v)
{
    UDWtype w;

    (void) __udivmoddi4(u, v, &w);
    return w;
}
