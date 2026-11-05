/* 0x001e4c50 — FUN_001e4c50. m2c draft, hybrid (gap-promoted function); verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_001e4d30();
int igMetaObject_CreateInstance();
extern int DAT_00562bc0[4];
void FUN_001e4c50(int arg0) {
    FUN_001e4d30();
    igMetaObject_CreateInstance(DAT_00562bc0[0], arg0);
}
