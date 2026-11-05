/* 0x00361e50 — FUN_00361e50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00362170();
void FUN_00361e50(int arg0);
}

void FUN_00361e50(int arg0) {
    FUN_00362170();
    igMetaObject_CreateInstance(*(int *)0x589678, arg0);
}
