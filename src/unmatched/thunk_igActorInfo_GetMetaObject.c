/* 0x001aa4a0 — thunk_igActorInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igActorInfo_GetMetaObject();

void thunk_igActorInfo_GetMetaObject(void) {
    igActorInfo_GetMetaObject();
}
