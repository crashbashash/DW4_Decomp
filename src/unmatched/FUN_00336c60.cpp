struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00336f10();
extern S *DAT_00587870[4];
void *FUN_00336c60(void);
}
void *FUN_00336c60(void) {
    bool ok;
    if (DAT_00587870[0] == 0) goto make;
    ok = !!(DAT_00587870[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00336f10();
done:;
    return DAT_00587870[0];
}
