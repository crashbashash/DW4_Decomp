typedef struct {
    short f0;
    short f2;
    int f4;
    int f8;
    int f12;
    int f16;
} CriInfo;

void FUN_00262b80(unsigned char *src, CriInfo *dst)
{
    dst->f0 = (src[0] << 8) | src[1];
    src += 2;
    dst->f2 = (src[0] << 8) | src[1];
    src += 2;
    dst->f4 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->f8 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->f12 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    dst->f16 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
}
