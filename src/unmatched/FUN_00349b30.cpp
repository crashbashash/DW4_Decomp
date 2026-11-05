/* 0x00349b30 - FUN_00349b30, 76 bytes. Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f & 4)` tested
 * with `!= false`, the null case jumping straight to the call (verified byte-identical with tools/verify.py). */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00349cc0();
extern S *DAT_00588278[4];
void *FUN_00349b30(void);
}
void *FUN_00349b30(void) {
    bool ok;
    if (DAT_00588278[0] == 0) goto make;
    ok = !!(DAT_00588278[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_00349cc0();
done:;
    return DAT_00588278[0];
}
