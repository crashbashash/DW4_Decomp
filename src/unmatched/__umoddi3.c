/* libgcc2 __umoddi3 (64-bit unsigned remainder) as built into the EE GCC 2.96
 * runtime: __udivmoddi4 is inlined and only the remainder is kept.  The
 * 32-bit helper macros follow the generic longlong.h fallbacks (count leading
 * zeros through the __clz_tab byte table at 0x4e82a8, udiv_qrnnd by 16-bit
 * halves, umul_ppmm through multu). */
#include "dw4/libgcc_longlong.h"

UDWtype __umoddi3(UDWtype u, UDWtype v)
{
    UDWtype w;

    (void) __udivmoddi4(u, v, &w);
    return w;
}
