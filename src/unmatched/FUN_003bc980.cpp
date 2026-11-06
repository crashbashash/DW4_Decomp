/* Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call:
 * `ok = !!(f & 4)` tested with `!= false`, the null case jumping straight to the call. */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003bca60();
extern S *DAT_0058b0d0[4];
void *FUN_003bc980(void);
}
void *FUN_003bc980(void) {
    bool ok;
    if (DAT_0058b0d0[0] == 0) goto make;
    ok = !!(DAT_0058b0d0[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_003bca60();
done:;
    return DAT_0058b0d0[0];
}
