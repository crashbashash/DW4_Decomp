#include "dw4/sequencefraction.h"
#include "eefloat.h"
int64_t dw4_sequence_loop_clock(int64_t now,int64_t first,int64_t duration)
{
    if(duration>0 && now>first+duration)return first+(now-first)%duration;
    return now;
}
uint32_t dw4_sequence_fraction(int64_t now,int64_t first,int64_t last)
{
    uint32_t elapsed=(uint32_t)(((uint64_t)now-(uint64_t)first)>>18);
    uint32_t duration=(uint32_t)(((uint64_t)last-(uint64_t)first)>>18);
    /* Integer tick conversion is either zero or at least one, so the original
     * denominator < 1e-6 branch is exactly this zero test. */
    return duration?ee_f32_div(ee_f32_from_u32(elapsed),ee_f32_from_u32(duration)):0;
}
