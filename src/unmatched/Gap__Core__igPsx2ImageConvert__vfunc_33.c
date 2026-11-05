void Gap__Core__igPsx2ImageConvert__vfunc_33(void *arg0, unsigned char *arg1, int arg2) {
    int i;
    for (i = 0; i < arg2; i++) {
        unsigned char t = *arg1;
        *arg1 = ((int) (t & 0xF0) >> 4) | ((t & 0xF) * 0x10);
        arg1++;
    }
}
