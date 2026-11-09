typedef struct ImageView {
    char pad0[28];
    int rBits;
    int gBits;
    int bBits;
    int aBits;
    char pad44[8];
    unsigned char *pixels;
    char pad56[8];
    int f64;
    char pad68[4];
    int f72;
    int stride;
    char pad80[4];
    int f84;
} ImageView;

void *memcpy(void *dst, const void *src, unsigned int n);

void FUN_00158670(ImageView *img, int x, int y, const void *src) {
    int bpp = (img->f84 + (img->f64 + (img->f72 + (img->aBits + (img->bBits + (img->rBits + img->gBits)))))) >> 3;
    memcpy(img->pixels + (y * img->stride + bpp * x), src, bpp);
}
