unsigned char *__DecodeUnsignedNumber(unsigned char *p, unsigned int *out) {
    unsigned int b0 = p[0];
    unsigned int b1, b2;
    if (!(b0 & 1)) {
        *out = b0 >> 1;
        return p + 1;
    }
    b1 = p[1];
    if (!(b0 & 2)) {
        *out = ((b0 >> 2) << 8) | b1;
        return p + 2;
    }
    b2 = p[2];
    if (!(b0 & 4)) {
        *out = b2 | (((b0 >> 3) << 16) | (b1 << 8));
        return p + 3;
    }
    *out = p[3] | ((b2 << 8) | (((b0 >> 3) << 24) | (b1 << 16)));
    return p + 4;
}
