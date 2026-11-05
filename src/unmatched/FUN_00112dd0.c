/* 0x00112dd0 — FUN_00112dd0 (28 bytes). Forwards its three arguments to FUN_00112800 together with a 16-byte
 * scratch block on the stack. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00112800(int a, int b, int c, void *scratch);

void FUN_00112dd0(int a, int b, int c) {
    char scratch[16];

    FUN_00112800(a, b, c, scratch);
}
