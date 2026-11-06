/* The flag test is a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f &
 * 4)` tested with `!= false`, the null case jumping straight to the call. */
struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003bf700();
extern S *DAT_0058b378[4];
void *beNDMWMdlPlayer2InfoWork_ResolveMetaObject(void);
}
void *beNDMWMdlPlayer2InfoWork_ResolveMetaObject(void) {
    bool ok;
    if (DAT_0058b378[0] == 0) goto make;
    ok = !!(DAT_0058b378[0]->f & 4);
    if (ok != false) goto done;
    asm { nop }
make:
    FUN_003bf700();
done:;
    return DAT_0058b378[0];
}
