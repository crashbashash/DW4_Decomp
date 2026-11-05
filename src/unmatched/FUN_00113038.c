/* 0x00113038 — FUN_00113038 (32 bytes). Forwards its three arguments to FUN_00112e10 together with a 16-byte
 * scratch block on the stack and a zero fifth argument. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00112e10(int a, int b, int c, void *scratch, int e);

void FUN_00113038(int a, int b, int c) {
    char scratch[16];

    FUN_00112e10(a, b, c, scratch, 0);
}
