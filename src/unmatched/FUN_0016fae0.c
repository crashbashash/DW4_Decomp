void FUN_0016fae0(unsigned short *dst, unsigned int *src, int count) {
    int i;
    for (i = 0; i < count; i++, src++) {
        unsigned int pixel = *src;
        unsigned int alpha = pixel >> 24;
        unsigned int alpha2;
        if (alpha & 0x80) {
            alpha2 = ~(alpha & 0xFF) << 1;
        } else {
            alpha2 = alpha << 1;
        }
        *dst++ = ((alpha2 & 0xF0) << 8) | ((pixel & 0xF00000) >> 12) | ((pixel & 0xF000) >> 8) | ((pixel & 0xF0) >> 4);
    }
}
