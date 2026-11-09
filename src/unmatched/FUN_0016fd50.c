void FUN_0016fd50(unsigned char *dst, unsigned char *src, int count) {
    int i;
    for (i = 0; i < count; i += 2) {
        *dst++ = (src[0] & 0xC0u) | ((src[0] & 0x0Cu) << 2) | ((src[1] & 0xC0u) >> 4) | ((src[1] & 0x0Cu) >> 2);
        src += 2;
    }
}
