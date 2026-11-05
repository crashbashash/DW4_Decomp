#include "dw4/ramp.h"

/* Copied from the retail executable (0x004c8fc0 and 0x004c90b0, 60 floats each) as bit patterns. */
/* The falling table follows the rising one directly in the executable, and a large step on a rising fade reads into it; both live in
 * one array so that indexing matches. */
static const ee_f32 tables[120] = {
    0x3d23d70a, 0x3d8f5c29, 0x3dcccccd, 0x3e051eb8, 0x3e2e147b, 0x3e428f5c,
    0x3e6147ae, 0x3e800000, 0x3e8f5c29, 0x3e9eb852, 0x3eae147b, 0x3eb851ec,
    0x3ec7ae14, 0x3ed70a3d, 0x3ee147ae, 0x3ef0a3d7, 0x3efae148, 0x3f028f5c,
    0x3f0a3d71, 0x3f0f5c29, 0x3f147ae1, 0x3f19999a, 0x3f1eb852, 0x3f23d70a,
    0x3f2b851f, 0x3f2e147b, 0x3f333333, 0x3f3851ec, 0x3f3d70a4, 0x3f400000,
    0x3f451eb8, 0x3f4a3d71, 0x3f4ccccd, 0x3f51eb85, 0x3f547ae1, 0x3f59999a,
    0x3f5c28f6, 0x3f5eb852, 0x3f6147ae, 0x3f63d70a, 0x3f666666, 0x3f6b851f,
    0x3f6b851f, 0x3f6e147b, 0x3f70a3d7, 0x3f733333, 0x3f75c28f, 0x3f7851ec,
    0x3f7851ec, 0x3f7ae148, 0x3f7ae148, 0x3f7d70a4, 0x3f7d70a4, 0x3f800000,
    0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
    0x3f75c28f, 0x3f6e147b, 0x3f666666, 0x3f5eb852, 0x3f547ae1, 0x3f4f5c29,
    0x3f47ae14, 0x3f400000, 0x3f3851ec, 0x3f30a3d7, 0x3f28f5c3, 0x3f23d70a,
    0x3f1c28f6, 0x3f147ae1, 0x3f0f5c29, 0x3f07ae14, 0x3f028f5c, 0x3efae148,
    0x3eeb851f, 0x3ee147ae, 0x3ed70a3d, 0x3ecccccd, 0x3ec28f5c, 0x3eb851ec,
    0x3ea8f5c3, 0x3ea3d70a, 0x3e99999a, 0x3e8f5c29, 0x3e851eb8, 0x3e800000,
    0x3e6b851f, 0x3e570a3d, 0x3e4ccccd, 0x3e3851ec, 0x3e2e147b, 0x3e19999a,
    0x3e0f5c29, 0x3e051eb8, 0x3df5c28f, 0x3de147ae, 0x3dcccccd, 0x3da3d70a,
    0x3da3d70a, 0x3d8f5c29, 0x3d75c28f, 0x3d4ccccd, 0x3d23d70a, 0x3cf5c28f,
    0x3cf5c28f, 0x3ca3d70a, 0x3ca3d70a, 0x3c23d70a, 0x3c23d70a, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
#define rise (tables)
#define fall (tables + 60)

const ee_f32 *dw4_ramp_table(int rising) { return rising ? rise : fall; }

/* Retail indexes unchecked. A rising fade may step into the falling table (index 60..119); anything past the table pair, or negative,
 * is undefined there and is clamped here. */
static int clamp_index(ee_f32 position, int rising)
{
    int i = ee_f32_trunc_s32(position), top = rising ? 119 : 59;
    return i < 0 ? 0 : i > top ? top : i;
}

/* u.f = -210.0f * factor with the sign bit cleared, then (int)u.f - 210 + base, plus `add` (FUN_003a7590 / FUN_003a7890). */
static int level_of(ee_f32 factor, int add, int base)
{
    ee_f32 v = ee_f32_mul(0xc3520000u, factor) & 0x7fffffffu;
    return add + (ee_f32_trunc_s32(v) - 210 + base);
}

int dw4_ramp_start(dw4_ramp *r, int add, ee_f32 from, ee_f32 to, ee_f32 div)
{
    const ee_f32 *t;
    int i, lo = -1, hi = -1;
    r->mode = 3;
    r->from = from;
    r->to = to;
    if (ee_f32_cmp(from, to) < 0) {
        t = rise;
        for (i = 0; i < 60; i++) if (ee_f32_cmp(from, t[i]) <= 0) { lo = i; break; }
        for (i = 59; i > -1; i--) if (ee_f32_cmp(to, t[i]) >= 0) { hi = i; break; }
    } else {
        t = fall;
        for (i = 0; i < 60; i++) if (ee_f32_cmp(from, t[i]) >= 0) { lo = i; break; }
        for (i = 59; i > -1; i--) if (ee_f32_cmp(to, t[i]) <= 0) { hi = i; break; }
    }
    r->cur = ee_f32_from_s32(lo);
    r->step = ee_f32_div(ee_f32_from_s32(hi - lo), div);
    return level_of(t[clamp_index(r->cur, t == rise)], add, r->base);
}

int dw4_ramp_step(dw4_ramp *r, int add)
{
    const ee_f32 *t = ee_f32_cmp(r->from, r->to) < 0 ? rise : fall;
    int v0, v1;
    r->cur = ee_f32_add(r->cur, r->step);   /* FUN_003a7810 */
    v0 = level_of(t[clamp_index(r->cur, t == rise)], add, r->base);
    v1 = level_of(r->to, add, r->base);
    if (!(ee_f32_cmp(r->from, r->to) <= 0)) {
        if (v0 <= v1) {
            r->mode = 0;
            if (ee_f32_cmp(r->to, 0) == 0) return -999;
        }
    } else if (v0 >= v1) {
        r->mode = 0;
    }
    return v0;
}
