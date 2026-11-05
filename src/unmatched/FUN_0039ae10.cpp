/* 0x0039ae10 — FUN_0039ae10. m2c draft (build/m2c/FUN_0039ae10.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
int FUN_001e06c0(int, int, void (*)(void));
int FUN_0034e5d0();
void FUN_0039adc0(void);  /* code at 0x39adc0, passed by address (was DAT_39adc0; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_0039ae10(void);
}
void FUN_0039ae10(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0034e5d0(), FUN_0039adc0);
}
