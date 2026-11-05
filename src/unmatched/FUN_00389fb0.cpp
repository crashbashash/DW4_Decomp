/* 0x00389fb0 — FUN_00389fb0. m2c draft (build/m2c/FUN_00389fb0.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
int FUN_001e06c0(int, int, void (*)(void));
int FUN_0035cd40();
void FUN_00389b90(void);  /* code at 0x389b90, passed by address (was DAT_389b90; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_00389fb0(void);
}
void FUN_00389fb0(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0035cd40(), FUN_00389b90);
}
