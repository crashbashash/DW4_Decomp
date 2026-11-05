/* 0x0019ec50 — thunk_igInterpretedShaderData_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInterpretedShaderData_GetMetaObject();

void thunk_igInterpretedShaderData_GetMetaObject(void) {
    igInterpretedShaderData_GetMetaObject();
}
