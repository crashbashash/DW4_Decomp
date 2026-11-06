/* The flag test is a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f &
 * 4)` tested with `!= false`, the null case jumping straight to the call. */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003b2370();
extern S *DAT_0058aa58[4];
void *FUN_003b2290(void);
}
void *FUN_003b2290(void) {
    bool ok;
    if (DAT_0058aa58[0] == 0) goto make;
    ok = !!(DAT_0058aa58[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_003b2370();
done:;
    return DAT_0058aa58[0];
}
