/* 0x00458090 — FUN_00458090. hand-matched: m2c dropped the leading argument; verified by tools/verify.py. */
/* 0x00458090 — FUN_00458090, m2c draft (hybrid mode), does not match yet.
 * Iterate here; a match is copied to src/FUN_00458090.c only after verify.py agrees. */
int igObject_IsKindOf();
int igGuiSystemModel_GetMetaObject();

void FUN_00458090(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}
