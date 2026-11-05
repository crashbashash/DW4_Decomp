/* 0x0037b760 — FUN_0037b760. m2c draft (build/m2c/FUN_0037b760.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
int FUN_001e06c0(int, int, void (*)());
int FUN_00367e50();
void FUN_0037b4a0(void);  /* code at 0x37b4a0, passed by address (was DAT_37b4a0; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_0037b760(void);
}

void FUN_0037b760(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_00367e50(), FUN_0037b4a0);
}
