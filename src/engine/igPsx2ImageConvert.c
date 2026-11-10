typedef void (*ConvertFunc)(void);

typedef struct ImagePalette {
    char pad0[12];
    int lastIndex;
    char pad10[4];
    unsigned int *colors;
    char pad18[4];
    unsigned char used;
} ImagePalette;

void *memcpy(void *, const void *, unsigned int);
int memmove();

void FUN_0015aaf0(void);
void FUN_0015ab50(void);
void FUN_0015ab70(void);
void FUN_0015ab90(void);
void FUN_0016f690();
void FUN_0016f700();
void FUN_0016f780();
void FUN_0016f7f0();
void FUN_0016f8a0();
void FUN_0016f930();
void FUN_0016f9b0();
void FUN_0016fa10();
void FUN_0016fa60();
void FUN_0016fae0();
void FUN_0016fb60();
void FUN_0016fbd0();
void FUN_0016fc20();
void FUN_0016fc80();
void FUN_0016fcd0();
void *thunk_memcpy();
void FUN_0016fd50();
void FUN_0016fdb0();
void FUN_0016fe00();
void FUN_0016fe20();

/* matching construct: a small sweep of spellings */
ConvertFunc Gap__Gfx__igPsx2ImageConvert__vfunc_24(void *self, int srcFormat, int from, int to)
{
    switch (from) {
    case 0x10001:
        switch (to) {
        case 0x10000: return FUN_0015ab90;
        case 0x10001: break;
        }
        break;
    case 0x10000:
        switch (to) {
        case 0x10001: return FUN_0015aaf0;
        case 7: return FUN_0016f690;
        case 0x10000: break;
        }
        break;
    case 6:
        break;
    case 4:
        break;
    case 8:
        switch (to) {
        case 7: return FUN_0016f700;
        case 8: break;
        }
        break;
    case 10:
        switch (to) {
        case 5: return FUN_0016f780;
        case 10: break;
        }
        break;
    case 9:
        switch (to) {
        case 7: return FUN_0016f7f0;
        case 9: break;
        }
        break;
    case 11:
        break;
    case 5:
        switch (to) {
        case 7: return FUN_0016f8a0;
        case 8: return FUN_0016f930;
        case 10: return FUN_0016f9b0;
        case 5: break;
        }
        break;
    case 7:
        switch (to) {
        case 5: return FUN_0016fa10;
        case 8: return FUN_0016fa60;
        case 9: return FUN_0016fae0;
        case 7: break;
        }
        break;
    case 0:
        switch (to) {
        case 1: return FUN_0015ab70;
        case 0x10000: return FUN_0016fe00;
        case 0: break;
        }
        break;
    case 1:
        switch (to) {
        case 0: return FUN_0015ab50;
        case 0x10000: return FUN_0016fe20;
        case 0x10001: return FUN_0016fdb0;
        case 1: break;
        }
        break;
    case 3:
        switch (to) {
        case 7: return FUN_0016fc20;
        case 2: return FUN_0016fbd0;
        case 0x10000: return FUN_0016fc80;
        case 0x10001: return FUN_0016fcd0;
        case 3: break;
        }
        break;
    case 2:
        switch (to) {
        case 3: return FUN_0016fb60;
        case 0x10000: return (ConvertFunc)thunk_memcpy;
        case 0x10001: return FUN_0016fd50;
        case 2: break;
        }
        break;
    }
    return 0;
}

ConvertFunc Gap__Gfx__igPsx2ImageConvert__vfunc_23(void *self, int srcFormat, int dstFormat, int flag)
{
    switch (dstFormat) {
    case 0x2:
        return flag ? FUN_0016fb60 : FUN_0016fbd0;
    case 0x8:
        return flag ? FUN_0016f700 : FUN_0016fa60;
    case 0xA:
        return flag ? FUN_0016f780 : FUN_0016f9b0;
    case 0x9:
        return flag ? FUN_0016f7f0 : FUN_0016fae0;
    case 0x10001:
        return flag ? FUN_0015ab90 : FUN_0015aaf0;
    default:
        return 0;
    }
}

static inline int ClampIndex(int index, int last)
{
    if (index >= last) {
        return last;
    } else {
        return index;
    }
}

/* matching construct: small sweep of spellings — local declaration order, s-- in the loop increment */
void FUN_0016f690(unsigned int *dst, unsigned char *src, int count, ImagePalette *palette)
{
    unsigned int *colors;
    int last;
    unsigned char *s = src + count - 1;
    unsigned int *d;
    int i;
    palette->used = 1;
    colors = palette->colors;
    last = palette->lastIndex;
    d = dst + count - 1;
    for (i = 0; i < count; i++, s--) {
        *d-- = colors[ClampIndex(*s, last)];
    }
}

void FUN_0016f700(unsigned int *dst, unsigned short *src, int count)
{
    unsigned int *d = dst + count - 1;
    unsigned short *s = src + count - 1;
    int i;

    for (i = 0; i < count; i++) {
        *d-- = ((((unsigned int)*s & 0x8000) >> 8) << 24) | ((*s & 0x7C00) << 9) | ((*s & 0x3E0) << 6)
             | ((*s & 0x1F) << 3);
        s--;
    }
}

/* matching construct: 48-variant sweep — declaration order */
void FUN_0016f780(unsigned char *dst, unsigned short *src, int count)
{
    unsigned char *d = dst + count * 3 - 3;
    unsigned short *s = src + count - 1;
    int i;
    unsigned int px;

    for (i = 0; i < count; i++) {
        px = *s;
        d[0] = (px & 0x1F) << 3;
        d[1] = (px >> 3) & 0xFC;
        d[2] = (px >> 8) & 0xF8;
        s--;
        d -= 3;
    }
}

void FUN_0016f8a0(unsigned int *dst, unsigned char *src, int count, unsigned char *alphaSrc)
{
    unsigned int *d = dst + count - 1;
    unsigned char *s = src + count * 3 - 3;
    unsigned int alpha = 0x80000000;
    int i;

    if (alphaSrc) {
        alpha = ((unsigned int)*alphaSrc >> 1) + (*alphaSrc & 1);
        alpha <<= 24;
    }
    for (i = 0; i < count; i++) {
        *d-- = alpha | (s[2] << 16) | (s[1] << 8) | s[0];
        s -= 3;
    }
}

void FUN_0016f930(unsigned short *dst, unsigned char *src, int count, unsigned char *alphaSrc)
{
    unsigned int alpha = 0x8000;
    int i;

    if (alphaSrc) {
        alpha = (*alphaSrc & 0x80) << 8;
        alpha &= 0x8000;
    }
    for (i = 0; i < count; i++) {
        *dst++ = alpha | ((src[2] & 0xF8u) << 7) | ((src[1] & 0xF8u) << 2) | ((src[0] & 0xF8u) >> 3);
        src += 3;
    }
}

void FUN_0016f9b0(unsigned short *dst, unsigned char *src, int count) {
    int i;
    for (i = 0; i < count; i++) {
        *dst++ = ((src[2] & 0xF8u) << 8) | ((src[1] & 0xFCu) << 3) | ((src[0] & 0xF8u) >> 3);
        src += 3;
    }
}

void FUN_0016fa10(unsigned char *dst, unsigned int *src, int count) {
    int i;
    for (i = 0; i < count; i++) {
        unsigned int pixel = *src;
        dst[0] = pixel;
        dst[1] = (pixel & 0xFF00) >> 8;
        dst[2] = (pixel & 0xFF0000) >> 16;
        dst += 3;
        src++;
    }
}

void FUN_0016fa60(unsigned short *dst, unsigned int *src, int count) {
    int i;
    for (i = 0; i < count; i++, src++) {
        unsigned int pixel = *src;
        unsigned int alpha = pixel >> 24;
        unsigned int alpha2;
        if (alpha & 0x80) {
            alpha2 = ~(alpha & 0xFF) << 1;
        } else {
            alpha2 = alpha << 1;
        }
        *dst++ = ((alpha2 & 0x80) << 8) | ((pixel & 0xF80000) >> 9) | ((pixel & 0xF800) >> 6) | ((pixel & 0xF8) >> 3);
    }
}

void FUN_0016fae0(unsigned short *dst, unsigned int *src, int count) {
    int i;
    for (i = 0; i < count; i++, src++) {
        unsigned int pixel = *src;
        unsigned int alpha = pixel >> 24;
        unsigned int alpha2;
        if (alpha & 0x80) {
            alpha2 = ~(alpha & 0xFF) << 1;
        } else {
            alpha2 = alpha << 1;
        }
        *dst++ = ((alpha2 & 0xF0) << 8) | ((pixel & 0xF00000) >> 12) | ((pixel & 0xF000) >> 8) | ((pixel & 0xF0) >> 4);
    }
}

void FUN_0016fb60(unsigned short *dst, unsigned char *src, int count) {
    unsigned short *d = dst + count - 1;
    unsigned char *s = src + count - 1;
    int i;
    for (i = 0; i < count; i++) {
        unsigned int lo = *s & 0x0F;
        unsigned int hi = *s & 0xF0;
        hi |= hi >> 4;
        lo |= lo << 4;
        *d-- = (hi << 8) | lo;
        s--;
    }
}

void FUN_0016fbd0(unsigned char *dst, unsigned short *src, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        *dst++ = (((unsigned int)src[0] >> 8) & 0xF0) | ((src[0] & 0xF0u) >> 4);
        src++;
    }
}

void FUN_0016fc20(unsigned int *dst, unsigned short *src, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        unsigned int lum = *src & 0xFF;
        unsigned int hi = *src & 0xFF00;
        unsigned int alpha = (hi >> 9) + ((hi >> 8) & 1);
        *dst++ = (alpha << 24) | (lum << 16) | (lum << 8) | lum;
        src++;
    }
}

void FUN_0016fc80(unsigned char *dst, unsigned short *src, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        *dst++ = (((unsigned int)src[0] >> 4) & 0xF) | (((unsigned int)src[0] >> 8) & 0xF0);
        src++;
    }
}

void FUN_0016fcd0(unsigned char *dst, unsigned short *src, int count)
{
    int i;

    for (i = 0; i < count; i += 2) {
        *dst++ = ((src[0] & 0xC0u) >> 2) | (((unsigned int)src[0] >> 8) & 0xC0u)
               | ((src[1] & 0xC0u) >> 6) | ((((unsigned int)src[1] >> 8) & 0xC0u) >> 4);
        src += 2;
    }
}

void *thunk_memcpy(void *d, const void *s, unsigned int n) {
    return memcpy(d, s, n);
}

void FUN_0016fd50(unsigned char *dst, unsigned char *src, int count) {
    int i;
    for (i = 0; i < count; i += 2) {
        *dst++ = (src[0] & 0xC0u) | ((src[0] & 0x0Cu) << 2) | ((src[1] & 0xC0u) >> 4) | ((src[1] & 0x0Cu) >> 2);
        src += 2;
    }
}

void FUN_0016fdb0(unsigned char *dst, unsigned char *src, int count) {
    int i; for (i = 0; i < count; i += 2) { *dst++ = (src[0] & 0xF0) | ((src[1] & 0xF0u) >> 4); src += 2; }
}

void FUN_0016fe00(int arg0, int arg1) {
    if (arg0 != arg1) {
        memmove();
    }
}

void FUN_0016fe20(int arg0, int arg1) {
    if (arg0 != arg1) {
        memmove();
    }
}
