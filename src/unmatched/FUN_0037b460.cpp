/* 0x0037b460 — FUN_0037b460. m2c draft (build/m2c/FUN_0037b460.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
extern "C" {
int FUN_001e06c0(int, int, void (*)());
int FUN_003680b0();
void FUN_0037b010(void);  /* code at 0x37b010, passed by address (was DAT_37b010; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_0037b460(void);
}

void FUN_0037b460(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_003680b0(), FUN_0037b010);
}
