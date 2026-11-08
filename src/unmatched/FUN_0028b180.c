void FUN_0028b180(char *d, char *s, unsigned int n) {
    int i;
    int a, b, c, e;
    for (i = n & 0x1F; i != 0; i--) {
        *d++ = *s++;
    }
    for (n >>= 5; n != 0; n--) {
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[0] = a; d[1] = b; d[2] = c; d[3] = e;
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[4] = a; d[5] = b; d[6] = c; d[7] = e;
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[8] = a; d[9] = b; d[10] = c; d[11] = e;
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[12] = a; d[13] = b; d[14] = c; d[15] = e;
        d += 16;
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[0] = a; d[1] = b; d[2] = c; d[3] = e;
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[4] = a; d[5] = b; d[6] = c; d[7] = e;
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[8] = a; d[9] = b; d[10] = c; d[11] = e;
        a = *s++; b = *s++; c = *s++; e = *s++;
        d[12] = a; d[13] = b; d[14] = c; d[15] = e;
        d += 16;
    }
}
