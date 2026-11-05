/* 0x0034dea0 - FUN_0034dea0, 76 bytes. Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f & 4)` tested
 * with `!= false`, the null case jumping straight to the call (verified byte-identical with tools/verify.py). */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0034df30();
extern S *DAT_005886b0[4];
void *FUN_0034dea0(void);
}
void *FUN_0034dea0(void) {
    bool ok;
    if (DAT_005886b0[0] == 0) goto make;
    ok = !!(DAT_005886b0[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_0034df30();
done:;
    return DAT_005886b0[0];
}
