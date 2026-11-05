/* 0x00291818 — FUN_00291818 (168 bytes). 64-bit a * b / c rounded to nearest, computed on magnitudes with the sign restored; division by zero saturates to the signed 64-bit limit of the result's sign. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern long long FUN_0022e440(long long a, long long b); /* 64-bit multiply */

long long FUN_00291818(long long a, long long b, long long c) {
    int sign;

    if (c == 0) {
        return ((a ^ b) >= 0) ? 0x7FFFFFFFFFFFFFFFLL : (long long)0x8000000000000000ULL;
    }
    sign = 1;
    if (a < 0) {
        sign = -1;
        a = -a;
    }
    if (b < 0) {
        sign = -sign;
        b = -b;
    }
    if (c < 0) {
        c = -c;
        sign = -sign;
    }
    a = (FUN_0022e440(a, b) + c / 2) / c;
    return (sign < 0) ? -a : a;
}
