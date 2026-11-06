/* base.c — candidate for FUN_00334460 (0x334460), input to decomp-permuter.
 *
 * This is the 76-byte VARIANT of the guard family (507 functions):
 * same source idiom as FUN_00130060, but retail keeps an extra `nop` before the
 * merged call block (index 11) and the two branch displacements are one word
 * larger. Compiling this source at -O3 gives the 72-byte form; at -O1/-O2 MWCC
 * emits the pad but reorders the prologue (`sd ra` before `lui at`), so a plain
 * flag difference is NOT the explanation — the search is for a source form that
 * keeps the pad while leaving the prologue in -O3 order.
 *
 * The load-bearing details are the same as the FUN_00130060 harness:
 *  1. the global is a 16-byte ARRAY so MWCC uses absolute `lui`/`lw` (a plain
 *     pointer is small data and goes gp-relative);
 *  2. the flag test must be a MATERIALISED C++ bool, so compile.sh copies to .cpp;
 *  3. the permuter's own parser is C-only, so `extern "C"` is #ifdef-guarded and
 *     the C branch supplies `typedef _Bool bool;` to keep `bool t;` parseable.
 * Make that typedef visible to MWCC's C++ mode and it would be a redefinition.
 */
#ifdef __cplusplus
extern "C" {
#else
typedef _Bool bool;
#endif

struct G { char pad[36]; int f; };
extern struct G *DAT_00587628[4];
void FUN_003344f0(void);

struct G *FUN_00334460(void)
{
    struct G *g = DAT_00587628[0];
    bool t;
    if (!g || !(t = g->f & 4))
        FUN_003344f0();
    return DAT_00587628[0];
}

#ifdef __cplusplus
}
#endif
