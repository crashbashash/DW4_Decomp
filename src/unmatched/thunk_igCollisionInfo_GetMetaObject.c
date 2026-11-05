/* 0x002399a0 — thunk_igCollisionInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCollisionInfo_GetMetaObject();

void thunk_igCollisionInfo_GetMetaObject(void) {
    igCollisionInfo_GetMetaObject();
}
