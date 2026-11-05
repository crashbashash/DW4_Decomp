/* 0x00146460 — thunk_igControllerList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igControllerList_GetMetaObject();

void thunk_igControllerList_GetMetaObject(void) {
    igControllerList_GetMetaObject();
}
