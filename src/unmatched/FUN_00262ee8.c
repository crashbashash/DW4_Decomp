typedef struct {
    unsigned char f0[4];
    int f4;
    int f8;
    short f12;
    char pad14[46];
    unsigned char f60;
    unsigned char f61;
} CriHeader;

extern unsigned char DAT_004edfc8[];
void FUN_00262a60(unsigned char *dst, int v);
void FUN_00262a30(unsigned char *dst, short v);

void FUN_00262ee8(unsigned char *dst, CriHeader *h)
{
    unsigned char *p;
    int i;

    p = DAT_004edfc8;
    *dst++ = h->f0[0];
    *dst++ = h->f0[1];
    *dst++ = h->f0[2];
    *dst++ = h->f0[3];
    FUN_00262a60(dst, h->f4);
    dst += 4;
    FUN_00262a60(dst, h->f8);
    dst += 4;
    FUN_00262a30(dst, h->f12);
    dst += 2;
    *dst++ = h->f60;
    *dst++ = h->f61;
    for (i = 9; i >= 0; i--) {
        *dst++ = 0;
    }
    for (i = 6; i >= 0; i--) {
        *dst++ = *p++;
    }
}
