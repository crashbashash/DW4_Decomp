void FUN_0016fa10(unsigned char *dst, unsigned int *src, int count) {
    int i;
    for (i = 0; i < count; i++) {
        unsigned int pixel = *src;
        dst[0] = pixel;
        dst[1] = (pixel & 0xFF00) >> 8;
        dst[2] = (pixel & 0xFF0000) >> 16;
        dst += 3;
        src++;
    }
}
