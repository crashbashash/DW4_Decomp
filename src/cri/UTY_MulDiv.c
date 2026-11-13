/* Returns a * b / c through a 64-bit product, saturating to INT_MIN/INT_MAX (by the sign of a * b)
 * when c is 0. */

int UTY_MulDiv(int a, int b, int c) {
    if (c == 0) {
        return ((a ^ b) < 0) ? (int)0x80000000 : 0x7FFFFFFF;
    }
    return (long)a * b / c;
}
