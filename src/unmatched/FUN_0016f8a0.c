void FUN_0016f8a0(unsigned int *dst, unsigned char *src, int count, unsigned char *alphaSrc)
{
    unsigned int *d = dst + count - 1;
    unsigned char *s = src + count * 3 - 3;
    unsigned int alpha = 0x80000000;
    int i;

    if (alphaSrc) {
        alpha = ((unsigned int)*alphaSrc >> 1) + (*alphaSrc & 1);
        alpha <<= 24;
    }
    for (i = 0; i < count; i++) {
        *d-- = alpha | (s[2] << 16) | (s[1] << 8) | s[0];
        s -= 3;
    }
}
