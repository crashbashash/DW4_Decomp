/* The flag test is a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f &
 * 4)` tested with `!= false`, the null case jumping straight to the call. */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0036b2b0();
extern S *DAT_00589e18[4];
void *FUN_0036b1c0(void);
}
void *FUN_0036b1c0(void) {
    bool ok;
    if (DAT_00589e18[0] == 0) goto make;
    ok = !!(DAT_00589e18[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_0036b2b0();
done:;
    return DAT_00589e18[0];
}
