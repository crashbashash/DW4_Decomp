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
make:
    FUN_003427f0();
done:;
    return DAT_00587cd0[0];
}
