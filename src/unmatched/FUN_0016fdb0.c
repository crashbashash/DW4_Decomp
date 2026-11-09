void FUN_0016fdb0(unsigned char *dst, unsigned char *src, int count) {
    int i; for (i = 0; i < count; i += 2) { *dst++ = (src[0] & 0xF0) | ((src[1] & 0xF0u) >> 4); src += 2; }
}
