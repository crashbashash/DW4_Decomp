/* 0x00463530 — FUN_00463530. hand-matched: m2c dropped the leading argument; verified by tools/verify.py. */
/* 0x00463530 — FUN_00463530, m2c draft (hybrid mode), does not match yet.
 * Iterate here; a match is copied to src/FUN_00463530.c only after verify.py agrees. */
int igObject_IsKindOf();
int igOnOffModel_GetMetaObject();

void FUN_00463530(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igOnOffModel_GetMetaObject());
}
