typedef struct {
    short f0;
    short f2;
    signed char f4;
    signed char f5;
    signed char f6;
    signed char f7;
    signed char f8;
    signed char f9;
    signed char f10;
    signed char f11;
} Loop;

void FUN_00262c70(unsigned char *src, Loop *dst)
{
    dst->f0 = (src[0] << 8) | src[1];
    src += 2;
    if (dst->f0 > 0) {
        dst->f2 = (src[0] << 8) | src[1];
    }
    src += 2;
    dst->f4 = *src++;
    if (dst->f4 > 0) {
        dst->f5 = *src;
    }
    src++;
    dst->f6 = *src++;
    if (dst->f6 > 0) {
        dst->f7 = *src;
    }
    src++;
    dst->f8 = *src++;
    if (dst->f8 > 0) {
        dst->f9 = *src;
    }
    src++;
    dst->f10 = *src++;
    if (dst->f10 > 0) {
        dst->f11 = *src;
    }
}
