void Gap__Gfx__igPsx2ImageConvert__vfunc_28(void *self, unsigned char *p, int n, int *mode) {
    unsigned int v, lo; int i, j;
    if (*mode == 100) {
        for (j = 0; j < n; j++) {
            lo = p[0]; v = lo | (p[1] << 8);
            v = ((v & 0xf) << 12) | ((v & 0xf0) << 4) | ((v & 0xf00) >> 4) | ((v & 0xf000) >> 12);
            p[0] = v;
            p[1] = (v & 0xff00) >> 8;
            p += 2;
        }
    } else {
        for (i = 0; i < n; i++) {
            lo = p[0]; v = lo | (p[1] << 8);
            v = ((v & 0xf000) >> 12) | ((v & 0xf00) >> 4) | ((v & 0xf0) << 4) | ((v & 0xf) << 12);
            p[0] = v;
            p[1] = (v & 0xff00) >> 8;
            p += 2;
        }
    }
}
