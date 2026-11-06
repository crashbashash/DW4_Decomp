/* Single-byte character decoder: stores the byte at `s` into *out (or a local when out is 0) and
 * returns whether it was non-zero; 0 for a null string, -1 for a zero length. The shape of
 * newlib's _mbtowc_r without multibyte support (hypothesis). */
int FUN_00126ef0(void *state, int *out, const char *s, unsigned int n) {
    int dummy;
    const unsigned char *t = (const unsigned char *)s;

    if (out == 0) {
        out = &dummy;
    }
    if (s == 0) {
        return 0;
    }
    if (n == 0) {
        return -1;
    }
    *out = *t;
    return *t != '\0';
}
