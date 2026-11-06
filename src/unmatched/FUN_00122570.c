/* Returns 1 when the (soft-float, 64-bit) double is finite: the high word's exponent field is
 * below 0x7ff. The shape of newlib's finite() (hypothesis; the block below is its GET_HIGH_WORD
 * macro written out). */
typedef union DoubleShape122570 {
    double value;
    struct { unsigned int lsw; unsigned int msw; } parts;
} DoubleShape122570;

int FUN_00122570(double x) {
    int hx;

    /* matching construct: newlib GET_HIGH_WORD — the do/while(0) block of the macro bounds the scheduling region */
    do { DoubleShape122570 gh_u; gh_u.value = x; hx = gh_u.parts.msw; } while (0);
    return (int)((unsigned int)((hx & 0x7fffffff) - 0x7ff00000) >> 31);
}
