/* 0x0014fe50 — thunk_igCapabilityManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCapabilityManager_GetMetaObject();

void thunk_igCapabilityManager_GetMetaObject(void) {
    igCapabilityManager_GetMetaObject();
}
