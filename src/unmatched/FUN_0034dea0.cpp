struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0034df30();
extern S *DAT_005886b0[4];
void *FUN_0034dea0(void);
}
void *FUN_0034dea0(void) {
    bool ok;
    if (DAT_005886b0[0] == 0) goto make;
    ok = !!(DAT_005886b0[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0034df30();
done:;
    return DAT_005886b0[0];
}
