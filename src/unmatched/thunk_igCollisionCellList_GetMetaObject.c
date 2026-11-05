/* 0x0023a6d0 — thunk_igCollisionCellList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCollisionCellList_GetMetaObject();

void thunk_igCollisionCellList_GetMetaObject(void) {
    igCollisionCellList_GetMetaObject();
}
