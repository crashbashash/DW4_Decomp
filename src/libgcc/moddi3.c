#define __clz_tab __clz_tab_moddi3
#include "dw4/libgcc_longlong.h"

long long __moddi3(long long u, long long v)
{
    word_type c = 0;
    DWunion uu, vv;
    long long w;

    uu.ll = u;
    vv.ll = v;

    if (uu.s.high < 0)
        c = ~c,
        uu.ll = __negdi2(uu.ll);
    if (vv.s.high < 0)
        vv.ll = __negdi2(vv.ll);

    (void) __udivmoddi4(uu.ll, vv.ll, (UDWtype *) &w);
    if (c)
        w = __negdi2(w);

    return w;
}
