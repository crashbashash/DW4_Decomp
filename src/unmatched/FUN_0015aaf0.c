void FUN_0015aaf0(unsigned char *dst, unsigned char *src, int count)
{
    int i;
    unsigned int packed;

    for (i = 0; i < count - 1; i += 2) {
        packed = src[0] & 0xF;
        packed |= src[1] << 4;
        *dst++ = packed;
        src += 2;
    }
    if (i < count)
        *dst = (*src & 0xF) << 4;
}
