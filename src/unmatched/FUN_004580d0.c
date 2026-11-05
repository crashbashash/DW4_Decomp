/* 0x004580d0 — FUN_004580d0. hand-matched: m2c dropped the leading argument; verified by tools/verify.py. */
/* 0x004580d0 — FUN_004580d0, m2c draft (hybrid mode), does not match yet.
 * Iterate here; a match is copied to src/FUN_004580d0.c only after verify.py agrees. */
int igObject_IsKindOf();
int igGuiSystemModel_GetMetaObject();

void FUN_004580d0(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}
