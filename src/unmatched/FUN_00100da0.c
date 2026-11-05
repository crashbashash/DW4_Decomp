signed char *FUN_00100da0(signed char *p, int *out) {
    int b0 = p[0];
    unsigned int b1, b2;
    if (!(b0 & 1)) {
        *out = b0 >> 1;
        return p + 1;
    }
    b1 = ((unsigned char *)p)[1];
    if (!(b0 & 2)) {
        *out = ((b0 >> 2) << 8) | b1;
        return p + 2;
    }
    b2 = ((unsigned char *)p)[2];
    if (!(b0 & 4)) {
        *out = b2 | (((b0 >> 3) << 16) | (b1 << 8));
        return p + 3;
    }
    *out = ((unsigned char *)p)[3] | ((b2 << 8) | (((b0 >> 3) << 24) | (b1 << 16)));
    return p + 4;
}
