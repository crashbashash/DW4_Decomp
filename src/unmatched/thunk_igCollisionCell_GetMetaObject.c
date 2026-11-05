/* 0x0023a8e0 — thunk_igCollisionCell_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCollisionCell_GetMetaObject();

void thunk_igCollisionCell_GetMetaObject(void) {
    igCollisionCell_GetMetaObject();
}
