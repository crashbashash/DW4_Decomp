
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
