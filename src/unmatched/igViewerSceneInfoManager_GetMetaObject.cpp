/* 0x004593d0 - igViewerSceneInfoManager_GetMetaObject, 76 bytes. Metaobject singleton accessor: create when the cached object is null or its flag 4 is clear.
 * Retail keeps the flag test as a materialised C++ bool (sltu) with a padding nop before the call: `ok = !!(f & 4)` tested
 * with `!= false`, the null case jumping straight to the call (verified byte-identical with tools/verify.py). */
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
    asm { nop }
make:
    FUN_00459e40();
done:;
    return DAT_0058c790[0];
}
