/* Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call:
 * `ok = !!(f & 4)` tested with `!= false`, the null case jumping straight to the call. */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00336f10();
extern S *DAT_00587870[4];
void *FUN_00336c60(void);
}
void *FUN_00336c60(void) {
    bool ok;
    if (DAT_00587870[0] == 0) goto make;
    ok = !!(DAT_00587870[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_00336f10();
done:;
    return DAT_00587870[0];
}
