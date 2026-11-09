void FUN_0016fc80(unsigned char *dst, unsigned short *src, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        *dst++ = (((unsigned int)src[0] >> 4) & 0xF) | (((unsigned int)src[0] >> 8) & 0xF0);
        src++;
    }
}
