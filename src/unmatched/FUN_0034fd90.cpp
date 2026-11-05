/* 0x0034fd90 - FUN_0034fd90, 76 bytes. Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f & 4)` tested
 * with `!= false`, the null case jumping straight to the call (verified byte-identical with tools/verify.py). */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0034fe80();
extern S *DAT_00588860[4];
void *FUN_0034fd90(void);
}
void *FUN_0034fd90(void) {
    bool ok;
    if (DAT_00588860[0] == 0) goto make;
    ok = !!(DAT_00588860[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_0034fe80();
done:;
    return DAT_00588860[0];
}
