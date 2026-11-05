/* 0x002916f8 — FUN_002916f8 (108 bytes). Returns a * b / c through a 64-bit product, saturating to INT_MIN/INT_MAX (by the sign of a * b) when c is 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

int FUN_002916f8(int a, int b, int c) {
    if (c == 0) {
        return ((a ^ b) < 0) ? (int)0x80000000 : 0x7FFFFFFF;
    }
    return (long)a * b / c;
}
