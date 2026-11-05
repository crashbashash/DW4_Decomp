/* 0x003bf890 — FUN_003bf890. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003bfae0();
void FUN_003bf890(int arg0);
}

void FUN_003bf890(int arg0) {
    FUN_003bfae0();
    igMetaObject_CreateInstance(*(int *)0x58B3A8, arg0);
}
