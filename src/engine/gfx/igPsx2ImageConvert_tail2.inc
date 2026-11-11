void Gap__Gfx__igPsx2ImageConvert__vfunc_25(void) {

}

void Gap__Gfx__igPsx2ImageConvert__vfunc_26(void) {
}

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

void Gap__Gfx__igPsx2ImageConvert__vfunc_28(void *self, unsigned char *p, int n, int *mode) {
    int j;
    unsigned int vb;
    int i;
    unsigned int va;
    if (*mode == 100) {
        for (j = 0; j < n; j++) {
            va=p[0]; va|=p[1]<<8;
            va = ((va & 0xf) << 12) | ((va & 0xf0) << 4) | ((va & 0xf00) >> 4) | ((va & 0xf000) >> 12);
            p[0] = va;
            p[1] = (va & 0xff00) >> 8;
            p += 2;
        }
    } else {
        for (i = 0; i < n; i++) {
            vb=p[0]; vb|=p[1]<<8;
            vb = ((vb & 0xf000) >> 12) | ((vb & 0xf00) >> 4) | ((vb & 0xf0) << 4) | ((vb & 0xf) << 12);
            p[0] = vb;
            p[1] = (vb & 0xff00) >> 8;
            p += 2;
        }
    }
}

void Gap__Gfx__igPsx2ImageConvert__vfunc_29(void *arg0, unsigned char *p, int n) {
    int i;
    unsigned int v;
    unsigned int t;
    for (i = 0; i < n; i++) {
        t=p[0]; t|=p[1]<<8;
        v = ((t & 0x1F) << 11) | (((t & 0xF800) >> 11) | (t & 0x7E0));
        p[0] = v;
        p[1] = (v & 0xFF00) >> 8;
        p += 2;
    }
}

void Gap__Gfx__igPsx2ImageConvert__vfunc_30(void) {
}

void Gap__Gfx__igPsx2ImageConvert__vfunc_31(void) {
}

void Gap__Gfx__igPsx2ImageConvert__vfunc_32(void) {
}

void Gap__Gfx__igPsx2ImageConvert__vfunc_33(void *arg0, unsigned char *arg1, int arg2) {
    int i;
    for (i = 0; i < arg2; i++) {
        unsigned char t = *arg1;
        *arg1 = ((int) (t & 0xF0) >> 4) | ((t & 0xF) * 0x10);
        arg1++;
    }
}

void Gap__Gfx__igPsx2ImageConvert__vfunc_34(void) {
}

