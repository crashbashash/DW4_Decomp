/* Shifts the trailing zero bits out of *word and returns how many there were, 32 for zero (newlib
 * mprec lo0bits shape; name is a hypothesis). */
int FUN_00127770(unsigned int *word) {
    int count;
    unsigned int x = *word;

    if (x & 7) {
        if (x & 1) {
            return 0;
        }
        if (x & 2) {
            *word = x >> 1;
            return 1;
        }
        *word = x >> 2;
        return 2;
    }
    count = 0;
    if (!(x & 0xffff)) {
        count = 16;
        x >>= 16;
    }
    if (!(x & 0xff)) {
        count += 8;
        x >>= 8;
    }
    if (!(x & 0xf)) {
        count += 4;
        x >>= 4;
    }
    if (!(x & 0x3)) {
        count += 2;
        x >>= 2;
    }
    if (!(x & 1)) {
        count++;
        x >>= 1;
        if (!x) {
            return 32;
        }
    }
    *word = x;
    return count;
}
