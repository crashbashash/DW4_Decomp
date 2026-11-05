/* 0x002c19f0 — FUN_002c19f0. m2c draft, hybrid (gap-promoted function); verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_002c1b10();
int igMetaObject_CreateInstance();
extern int DAT_00586050[4];
void FUN_002c19f0(int arg0) {
    FUN_002c1b10();
    igMetaObject_CreateInstance(DAT_00586050[0], arg0);
}
