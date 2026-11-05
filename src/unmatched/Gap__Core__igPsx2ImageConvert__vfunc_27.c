void Gap__Core__igPsx2ImageConvert__vfunc_27(void *arg0, unsigned char *arg1, int arg2, int *arg3) {
    unsigned int v;
    int i;
    unsigned int r;
    unsigned int b0;
    unsigned int b1;
    if (*arg3 == 0x64) {
        for (i = 0; i < arg2; i++) {
            b1 = arg1[1];
            b0 = arg1[0];
            v = b0 | (b1 << 8);
            r = ((v & 0x3E) << 9) | (((v & 0xF800) >> 11) | ((v & 0x7C0) >> 1)) | ((v & 1) ? 0x8000 : 0);
            arg1[0] = r;
            arg1[1] = (r & 0xFF00) >> 8;
            arg1 += 2;
        }
        return;
    }
    for (i = 0; i < arg2; i++) {
        b1 = arg1[1];
        b0 = arg1[0];
        v = b0 | (b1 << 8);
        b0 = ((v & 0x1F) << 11) | (((v & 0x7C00) >> 9) | ((v & 0x3E0) << 1));
        b1 = (v & 0x8000) != 0;
        r = b0 | b1;
        arg1[0] = r;
        arg1[1] = (r & 0xFF00) >> 8;
        arg1 += 2;
    }
}
