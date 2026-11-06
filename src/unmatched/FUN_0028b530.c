/* Fills count words at dst with value, unrolled by 16. */
void FUN_0028b530(int *dst, int value, unsigned int count) {
    int *p = dst + count;
    unsigned int n;

    /* filled backwards from the end: the remainder first, then blocks of 16 */
    for (n = count & 15; n != 0; n--) {
        *--p = value;
    }
    for (count >>= 4; count != 0; count--) {
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
        *--p = value; *--p = value; *--p = value; *--p = value;
    }
}
