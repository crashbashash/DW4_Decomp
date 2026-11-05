/* 0x0039c8c0 — FUN_0039c8c0. m2c draft (build/m2c/FUN_0039c8c0.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
int FUN_001e06c0(int, int, void (*)(void));
int FUN_0034b4a0();
void FUN_0039c430(void);  /* code at 0x39c430, passed by address (was DAT_39c430; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_0039c8c0(void);
}
void FUN_0039c8c0(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0034b4a0(), FUN_0039c430);
}
