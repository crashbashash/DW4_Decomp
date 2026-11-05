/* 0x00458050 — FUN_00458050. hand-matched: m2c dropped the leading argument; verified by tools/verify.py. */
/* 0x00458050 — FUN_00458050, m2c draft (hybrid mode), does not match yet.
 * Iterate here; a match is copied to src/FUN_00458050.c only after verify.py agrees. */
int igObject_IsKindOf();
int igGuiSystemModel_GetMetaObject();

void FUN_00458050(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}
