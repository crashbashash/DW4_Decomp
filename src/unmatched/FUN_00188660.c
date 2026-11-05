/* 0x00188660 — FUN_00188660. m2c draft, hybrid (gap-promoted function); verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_00188780();
int igMetaObject_CreateInstance();
extern int DAT_00561000[4];
void FUN_00188660(int arg0) {
    FUN_00188780();
    igMetaObject_CreateInstance(DAT_00561000[0], arg0);
}
