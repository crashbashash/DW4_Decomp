struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_003ca8e0();
extern S *DAT_0058c128[4];
void *beNDMWAfsSetupDataList_ResolveMetaObject(void);
}
void *beNDMWAfsSetupDataList_ResolveMetaObject(void) {
    bool ok;
    if (DAT_0058c128[0] == 0) goto make;
    ok = !!(DAT_0058c128[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003ca8e0();
done:;
    return DAT_0058c128[0];
}
