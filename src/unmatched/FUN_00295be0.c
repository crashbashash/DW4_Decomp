/* 0x00295be0 — FUN_00295be0 (32 bytes). Calls FUN_00295c00(a, b, 0, 0xFFFFF). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00295c00(int a, int b, int c, int d);

void FUN_00295be0(int a, int b) {
    FUN_00295c00(a, b, 0, 0xFFFFF);
}
