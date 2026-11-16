#define __clz_tab __clz_tab_udivdi3
#include "dw4/libgcc_longlong.h"
#include "dw4/softfloat.h"

UDWtype __udivdi3(UDWtype n, UDWtype d)
{
    return __udivmoddi4(n, d, (UDWtype *) 0);
}
