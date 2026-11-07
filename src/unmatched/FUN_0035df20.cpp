struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_0035e090();
extern S *DAT_00589390[4];
void *FUN_0035df20(void);
}
void *FUN_0035df20(void) {
    bool ok;
    if (DAT_00589390[0] == 0) goto make;
    ok = !!(DAT_00589390[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_0035e090();
done:;
    return DAT_00589390[0];
}
