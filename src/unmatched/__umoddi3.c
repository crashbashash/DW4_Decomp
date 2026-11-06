/* libgcc2 __umoddi3 (64-bit unsigned remainder) with __udivmoddi4 inlined and only the remainder
 * kept. The 32-bit helper macros follow the generic longlong.h fallbacks (count leading zeros
 * through the __clz_tab byte table, udiv_qrnnd by 16-bit halves, umul_ppmm through multu). */
#include "dw4/libgcc_longlong.h"

UDWtype __umoddi3(UDWtype u, UDWtype v)
{
    UDWtype w;

    (void) __udivmoddi4(u, v, &w);
    return w;
}
