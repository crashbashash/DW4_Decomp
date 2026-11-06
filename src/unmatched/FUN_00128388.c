/* Returns 10^digits, from the powers-of-ten table below 24 and by repeated multiplication above
 * (newlib _mprec_log10 shape; name is a hypothesis). */
extern double DAT_004d3f38[]; /* 1e0 .. 1e23 */

double FUN_00128388(int digits) {
    double value = 1.0;

    if (digits < 24) {
        return DAT_004d3f38[digits];
    }
    while (digits > 0) {
        value *= 10;
        digits--;
    }
    return value;
}
