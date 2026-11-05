/* 0x001a80b0 — FUN_001a80b0. m2c draft, hybrid (gap-promoted function); verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_001a8220();
int igMetaObject_CreateInstance();
extern int DAT_00562268[4];
void FUN_001a80b0(int arg0) {
    FUN_001a8220();
    igMetaObject_CreateInstance(DAT_00562268[0], arg0);
}
