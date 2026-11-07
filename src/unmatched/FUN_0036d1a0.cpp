struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0036d280();
extern S *DAT_00589fb0[4];
void *FUN_0036d1a0(void);
}
void *FUN_0036d1a0(void) {
    bool ok;
    if (DAT_00589fb0[0] == 0) goto make;
    ok = !!(DAT_00589fb0[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0036d280();
done:;
    return DAT_00589fb0[0];
}
