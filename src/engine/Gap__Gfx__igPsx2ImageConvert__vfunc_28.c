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
