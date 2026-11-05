/* 0x00263748 — FUN_00263748 (32 bytes). Calls FUN_00263768 with its two arguments, 0 and the limit 0xFFFFF. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00263768(int a0, int a1, int a2, int limit);

void FUN_00263748(int a0, int a1) {
    FUN_00263768(a0, a1, 0, 0xFFFFF);
}
