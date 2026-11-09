void FUN_0016f9b0(unsigned short *dst, unsigned char *src, int count) {
    int i;
    for (i = 0; i < count; i++) {
        *dst++ = ((src[2] & 0xF8u) << 8) | ((src[1] & 0xFCu) << 3) | ((src[0] & 0xF8u) >> 3);
        src += 3;
    }
}
