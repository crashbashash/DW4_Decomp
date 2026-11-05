/* 0x0026d7c0 — FUN_0026d7c0 (24 bytes). Calls FUN_0026d7d8 with its two arguments and 0x40000000. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0026d7d8(void *a0, void *a1, int a2);

void FUN_0026d7c0(void *a0, void *a1) {
    FUN_0026d7d8(a0, a1, 0x40000000);
}
