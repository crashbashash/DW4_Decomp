/* Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call:
 * `ok = !!(f & 4)` tested with `!= false`, the null case jumping straight to the call. */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003601e0();
extern S *DAT_00589560[4];
void *FUN_003600b0(void);
}
void *FUN_003600b0(void) {
    bool ok;
    if (DAT_00589560[0] == 0) goto make;
    ok = !!(DAT_00589560[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_003601e0();
done:;
    return DAT_00589560[0];
}
