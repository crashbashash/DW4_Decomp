/* 0x0014f410 — thunk_igGenericCapabilityManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGenericCapabilityManager_GetMetaObject();

void thunk_igGenericCapabilityManager_GetMetaObject(void) {
    igGenericCapabilityManager_GetMetaObject();
}
