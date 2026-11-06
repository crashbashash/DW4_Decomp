/* The flag test is a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f &
 * 4)` tested with `!= false`, the null case jumping straight to the call. */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003427f0();
extern S *DAT_00587cd0[4];
void *FUN_003426c0(void);
}
void *FUN_003426c0(void) {
    bool ok;
    if (DAT_00587cd0[0] == 0) goto make;
    ok = !!(DAT_00587cd0[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_003427f0();
done:;
    return DAT_00587cd0[0];
}
