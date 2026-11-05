/* 0x0014ce20 — thunk_igParticleArray_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igParticleArray_GetMetaObject();

void thunk_igParticleArray_GetMetaObject(void) {
    igParticleArray_GetMetaObject();
}
