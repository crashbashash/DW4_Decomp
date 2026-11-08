#define __clz_tab D_004e7fa8
#include "dw4/libgcc_longlong.h"
typedef int word_type __attribute__ ((mode (SI)));
static inline long long __negdi2(long long u)
{
    DWunion w;
    DWunion uu;

    uu.ll = u;

    w.s.low = -uu.s.low;
    w.s.high = -uu.s.high - ((UWtype) w.s.low > 0);

    return w.ll;
}

long long __divdi3(long long u, long long v)
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
        c = ~c,
        vv.ll = __negdi2(vv.ll);

    w = __udivmoddi4(uu.ll, vv.ll, (UDWtype *) 0);
    if (c)
        w = __negdi2(w);

    return w;
}
