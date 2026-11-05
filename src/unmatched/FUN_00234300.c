/* 0x00234300 — FUN_00234300. m2c draft (build/m2c/FUN_00234300.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int printf();
int FUN_00230298();
extern int DAT_004e9630[4];
void FUN_00234300(int arg0, int arg1) {
    printf(&DAT_004e9630[0], arg0, arg1, FUN_00230298());
}
