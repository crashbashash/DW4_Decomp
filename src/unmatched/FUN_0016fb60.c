void FUN_0016fb60(unsigned short *dst, unsigned char *src, int count) {
    unsigned short *d = dst + count - 1;
    unsigned char *s = src + count - 1;
    int i;
    for (i = 0; i < count; i++) {
        unsigned int lo = *s & 0x0F;
        unsigned int hi = *s & 0xF0;
        hi |= hi >> 4;
        lo |= lo << 4;
        *d-- = (hi << 8) | lo;
        s--;
    }
}
