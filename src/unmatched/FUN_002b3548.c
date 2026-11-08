void FUN_002b3548(unsigned char *t) {
    int i;
    for (i = 0; i < 16; i++) {
        t[i] = 0;
    }
    for (i = 16; i < 236; i++) {
        t[i] = (unsigned int)((float)(i - 16) * 0.582f);
    }
    for (i = 236; i < 256; i++) {
        t[i] = 0x80;
    }
}
