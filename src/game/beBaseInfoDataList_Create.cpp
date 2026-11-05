/* 0x0036ae80 — beBaseInfoDataList_Create. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_0036afa0();
void beBaseInfoDataList_Create(int arg0);
}

void beBaseInfoDataList_Create(int arg0) {
    FUN_0036afa0();
    igMetaObject_CreateInstance(*(int *)0x589E00, arg0);
}
