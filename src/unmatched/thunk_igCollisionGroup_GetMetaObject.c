/* 0x00239d10 — thunk_igCollisionGroup_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCollisionGroup_GetMetaObject();

void thunk_igCollisionGroup_GetMetaObject(void) {
    igCollisionGroup_GetMetaObject();
}
