/* base.c — candidate for FUN_00130060 (0x130060), input to decomp-permuter.
 *
 * STATUS: instructions 0-7 match retail EXACTLY; the only difference is the
 * missing `sltu v0,zero,v0` at index 8, after which everything shifts one word
 * (68 bytes vs retail's 72). See docs/engine/guard-family.md.
 *
 * Three things about this file are load-bearing:
 *
 * 1. The global is a 16-byte ARRAY, not a pointer. As a plain pointer it is small
 *    data and MWCC emits gp-relative `lw v0,-5184(gp)`; retail uses absolute
 *    `lui at,0x56 ; lw v0,-5184(at)`, which the array form reproduces.
 * 2. MWCC needs C++ mode (only C++ has a bool type, and retail materialises the flag
 *    test as a boolean). compile.sh copies this file to a .cpp to force that.
 * 3. Therefore the extern "C" declarations, and therefore the #ifdef guard: C++
 *    mode mangles names otherwise, but the permuter's own parser is C-only and
 *    chokes on `extern "C"`. Guarded this way the permuter sees plain C while MWCC
 *    (via .cpp) sees the linkage specification. Both are required.
 */
#ifdef __cplusplus
extern "C" {
#endif

struct G { char pad[36]; int f; };
extern struct G *DAT_0055ebc0[4];
void FUN_001301c0(void);

struct G *FUN_00130060(void)
{
    struct G *g = DAT_0055ebc0[0];
    if (!g || !(g->f & 4))
        FUN_001301c0();
    return DAT_0055ebc0[0];
}

#ifdef __cplusplus
}
#endif
