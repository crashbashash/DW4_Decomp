typedef struct {
    unsigned char f0[4];
    int f4;
    int f8;
    short f12;
    char pad14[46];
    unsigned char f60;
    unsigned char f61;
} CriHeader;

void FUN_00262aa0(unsigned char *src, CriHeader *h)
{
    h->f0[0] = *src++;
    h->f0[1] = *src++;
    h->f0[2] = *src++;
    h->f0[3] = *src++;
    h->f4 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    h->f8 = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    src += 4;
    h->f12 = (src[0] << 8) | src[1];
    src += 2;
    h->f60 = src[0];
    h->f61 = src[1];
}
