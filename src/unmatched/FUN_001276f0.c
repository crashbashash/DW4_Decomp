/* Counts the leading zero bits of a 32-bit word, 32 for zero (newlib mprec hi0bits shape; name is
 * a hypothesis). */
int FUN_001276f0(unsigned int x) {
    int count = 0;

    if (!(x & 0xffff0000)) {
        count = 16;
        x <<= 16;
    }
    if (!(x & 0xff000000)) {
        count += 8;
        x <<= 8;
    }
    if (!(x & 0xf0000000)) {
        count += 4;
        x <<= 4;
    }
    if (!(x & 0xc0000000)) {
        count += 2;
        x <<= 2;
    }
    if (!(x & 0x80000000)) {
        count++;
        if (!(x & 0x40000000)) {
            return 32;
        }
    }
    return count;
}
