/* 0x00239ba0 — thunk_igCollisionGroupList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCollisionGroupList_GetMetaObject();

void thunk_igCollisionGroupList_GetMetaObject(void) {
    igCollisionGroupList_GetMetaObject();
}
