void FUN_0016fcd0(unsigned char *dst, unsigned short *src, int count)
{
    int i;

    for (i = 0; i < count; i += 2) {
        *dst++ = ((src[0] & 0xC0u) >> 2) | (((unsigned int)src[0] >> 8) & 0xC0u)
               | ((src[1] & 0xC0u) >> 6) | ((((unsigned int)src[1] >> 8) & 0xC0u) >> 4);
        src += 2;
    }
}
