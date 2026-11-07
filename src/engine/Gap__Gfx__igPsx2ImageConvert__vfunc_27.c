void Gap__Gfx__igPsx2ImageConvert__vfunc_27(void *arg0, unsigned char *arg1, int arg2, int *arg3) {
    unsigned int c1;
    int i;
    unsigned int r;
    unsigned int v;
    unsigned int v2;
    unsigned int r2;
    int j;
    unsigned int c0;
    if (*arg3 == 0x64) {
        for (i = 0; i < arg2; i++) {
            v = arg1[0]; v |= arg1[1] << 8;
            r = ((v & 0x3E) << 9) | (((v & 0xF800) >> 11) | ((v & 0x7C0) >> 1)) | ((v & 1) ? 0x8000 : 0);
            arg1[0] = r;
            arg1[1] = (r & 0xFF00) >> 8;
            arg1 += 2;
        }
        return;
    }
    for (j = 0; j < arg2; j++) {
        v2 = arg1[0]; v2 |= arg1[1] << 8;
        c0 = ((v2 & 0x1F) << 11) | (((v2 & 0x7C00) >> 9) | ((v2 & 0x3E0) << 1));
        c1 = (v2 & 0x8000) != 0;
        r2 = c0 | c1;
        arg1[0] = r2;
        arg1[1] = (r2 & 0xFF00) >> 8;
        arg1 += 2;
    }
}
