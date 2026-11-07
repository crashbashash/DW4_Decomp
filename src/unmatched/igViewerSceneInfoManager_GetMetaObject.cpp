struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00459e40();
extern S *DAT_0058c790[4];
void *igViewerSceneInfoManager_GetMetaObject(void);
}
void *igViewerSceneInfoManager_GetMetaObject(void) {
    bool ok;
    if (DAT_0058c790[0] == 0) goto make;
    ok = !!(DAT_0058c790[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00459e40();
done:;
    return DAT_0058c790[0];
}
