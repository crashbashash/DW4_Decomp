/* 0x002342e0 — FUN_002342e0. m2c draft (build/m2c/FUN_002342e0.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int printf();
extern int DAT_004e9610[4];
void FUN_002342e0(int arg0, int arg1, int arg2) {
    printf(&DAT_004e9610[0], arg0, arg1, arg2);
}
