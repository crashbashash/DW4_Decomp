struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003c44e0();
extern S *DAT_0058ba30[4];
void *beNDMWLoadIntf2CtrlData_ResolveMetaObject(void);
}
void *beNDMWLoadIntf2CtrlData_ResolveMetaObject(void) {
    bool ok;
    if (DAT_0058ba30[0] == 0) goto make;
    ok = !!(DAT_0058ba30[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003c44e0();
done:;
    return DAT_0058ba30[0];
}
