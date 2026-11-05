/* 0x0039ad80 — FUN_0039ad80. m2c draft (build/m2c/FUN_0039ad80.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
int FUN_001e06c0(int, int, void (*)(void));
int FUN_0034e870();
void FUN_0039a930(void);  /* code at 0x39a930, passed by address (was DAT_39a930; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_0039ad80(void);
}
void FUN_0039ad80(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0034e870(), FUN_0039a930);
}
