void FUN_0016f700(unsigned int *dst, unsigned short *src, int count)
{
    unsigned int *d = dst + count - 1;
    unsigned short *s = src + count - 1;
    int i;

    for (i = 0; i < count; i++) {
        *d-- = ((((unsigned int)*s & 0x8000) >> 8) << 24) | ((*s & 0x7C00) << 9) | ((*s & 0x3E0) << 6)
             | ((*s & 0x1F) << 3);
        s--;
    }
}
