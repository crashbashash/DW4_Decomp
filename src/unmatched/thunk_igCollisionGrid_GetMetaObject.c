/* 0x0023a3d0 — thunk_igCollisionGrid_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCollisionGrid_GetMetaObject();

void thunk_igCollisionGrid_GetMetaObject(void) {
    igCollisionGrid_GetMetaObject();
}
