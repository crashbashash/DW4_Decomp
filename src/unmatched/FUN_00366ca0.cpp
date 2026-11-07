struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00366e00();
extern S *DAT_005899f8[4];
void *FUN_00366ca0(void);
}
void *FUN_00366ca0(void) {
    bool ok;
    if (DAT_005899f8[0] == 0) goto make;
    ok = !!(DAT_005899f8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00366e00();
done:;
    return DAT_005899f8[0];
}
