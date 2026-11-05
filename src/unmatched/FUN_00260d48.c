/* 0x00260d48 — FUN_00260d48 (28 bytes). Calls FUN_00260d68 with its first two arguments, 0, and its third argument. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00260d68(int a0, int a1, int a2, int a3);

void FUN_00260d48(int a0, int a1, int a2) {
    FUN_00260d68(a0, a1, 0, a2);
}
