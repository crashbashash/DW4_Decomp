/* 0x00189160 — FUN_00189160. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00189230();
int igMetaObject_CreateInstance(int, int);

void FUN_00189160(int arg0) {
    FUN_00189230();
    igMetaObject_CreateInstance(*(int *)0x561048, arg0);
}
