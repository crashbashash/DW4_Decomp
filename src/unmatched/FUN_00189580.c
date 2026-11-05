/* 0x00189580 — FUN_00189580. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00189650();
int igMetaObject_CreateInstance(int, int);

void FUN_00189580(int arg0) {
    FUN_00189650();
    igMetaObject_CreateInstance(*(int *)0x561060, arg0);
}
