/* 0x002d7b00 — FUN_002d7b00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igResource_GetMetaObject();
int igObjectDirEntry_GetMetaObject();
int igMemoryDirEntry_GetMetaObject();
int igInfo_GetMetaObject();
int igExternalInfoEntry_GetMetaObject();
int igExternalIndexedEntry_GetMetaObject();
int igExternalDirEntry_GetMetaObject();
int igDirEntry_GetMetaObject();

void FUN_002d7b00(void) {
    igDirEntry_GetMetaObject();
    igObjectDirEntry_GetMetaObject();
    igMemoryDirEntry_GetMetaObject();
    igExternalDirEntry_GetMetaObject();
    igExternalIndexedEntry_GetMetaObject();
    igExternalInfoEntry_GetMetaObject();
    igInfo_GetMetaObject();
    igResource_GetMetaObject();
}
