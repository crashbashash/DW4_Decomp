int FUN_00294060(int value);
int FUN_002940a0(int value);

void FUN_00293f98(int *src, void **dst) {
    int a, b, c, d, e, f, g;

    a = src[0];
    b = FUN_00294060(src[1]);
    c = src[2];
    d = src[3];
    e = src[4];
    f = src[5];
    g = FUN_002940a0(src[6]);
    dst[8] = (void *)a;
    dst[7] = (void *)b;
    dst[0] = (void *)c;
    dst[1] = (void *)d;
    dst[2] = (void *)e;
    dst[3] = (void *)f;
    dst[4] = (void *)g;
    dst[5] = (void *)src[9];
    dst[6] = (void *)src[10];
    dst[9] = (void *)src[14];
    dst[10] = (void *)src[15];
    dst[11] = (void *)src[11];
}
