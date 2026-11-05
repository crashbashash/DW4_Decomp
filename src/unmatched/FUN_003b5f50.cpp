/* 0x003b5f50 - FUN_003b5f50, 76 bytes. Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f & 4)` tested
 * with `!= false`, the null case jumping straight to the call (verified byte-identical with tools/verify.py). */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003b6110();
extern S *DAT_0058ac48[4];
void *FUN_003b5f50(void);
}
void *FUN_003b5f50(void) {
    bool ok;
    if (DAT_0058ac48[0] == 0) goto make;
    ok = !!(DAT_0058ac48[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_003b6110();
done:;
    return DAT_0058ac48[0];
}
