/* 0x00134ee0 — thunk_igParticleAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igParticleAttr_GetMetaObject();

void thunk_igParticleAttr_GetMetaObject(void) {
    igParticleAttr_GetMetaObject();
}
