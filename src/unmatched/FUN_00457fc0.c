/* 0x00457fc0 — FUN_00457fc0. hand-matched: m2c dropped the leading argument; verified by tools/verify.py. */
/* 0x00457fc0 — FUN_00457fc0, m2c draft (hybrid mode), does not match yet.
 * Iterate here; a match is copied to src/FUN_00457fc0.c only after verify.py agrees. */
int igObject_IsKindOf();
int igRadioGroupModel_GetMetaObject();

void FUN_00457fc0(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igRadioGroupModel_GetMetaObject());
}
