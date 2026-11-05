/* 0x003993a0 — FUN_003993a0. m2c draft (build/m2c/FUN_003993a0.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
int FUN_001e06c0(int, int, void (*)(void));
int FUN_0034fd90();
void FUN_00398e50(void);  /* code at 0x398e50, passed by address (was DAT_398e50; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_003993a0(void);
}
void FUN_003993a0(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0034fd90(), FUN_00398e50);
}
