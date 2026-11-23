namespace Gap {
namespace Gfx {

/* matching construct: the empty cases (a format converted to itself, a format with no conversion) keep retail's switch tables */
igImageConvert::conversionFn *igPsx2ImageConvert::getConversionFn(IG_GFX_IMAGE_ORDER order, IG_GFX_TEXTURE_FORMAT sFmt, IG_GFX_TEXTURE_FORMAT tFmt, int xSize, int ySize)
{
    switch (sFmt) {
    case IG_GFX_TEXTURE_FORMAT_X_4:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_X_8: return pal_4_To_pal_8;
        case IG_GFX_TEXTURE_FORMAT_X_4: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_X_8:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_X_4: return pal_8_To_pal_4;
        case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32: return pal_8_To_rgba_8888;
        case IG_GFX_TEXTURE_FORMAT_X_8: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_2222_8:
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_332_8:
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32: return rgba_5551_To_rgba_8888;
        case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_565_16:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_RGB_888_24: return rgb_565_To_rgb_888;
        case IG_GFX_TEXTURE_FORMAT_RGB_565_16: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32: return rgba_4444_To_rgba_8888;
        case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_3328_16:
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_888_24:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32: return rgb_888_To_rgba_8888;
        case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16: return rgb_888_To_rgba_5551;
        case IG_GFX_TEXTURE_FORMAT_RGB_565_16: return rgb_888_To_rgb_565;
        case IG_GFX_TEXTURE_FORMAT_RGB_888_24: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_RGB_888_24: return rgba_8888_To_rgb_888;
        case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16: return rgba_8888_To_rgba_5551;
        case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16: return rgba_8888_To_rgba_4444;
        case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_L_8:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_A_8: return luminance_8_To_alpha_8;
        case IG_GFX_TEXTURE_FORMAT_X_8: return (conversionFn *)FUN_0016fe00;
        case IG_GFX_TEXTURE_FORMAT_L_8: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_A_8:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_L_8: return alpha_8_To_luminance_8;
        case IG_GFX_TEXTURE_FORMAT_X_8: return (conversionFn *)FUN_0016fe20;
        case IG_GFX_TEXTURE_FORMAT_X_4: return alpha_8_To_pal_4;
        case IG_GFX_TEXTURE_FORMAT_A_8: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_88_16:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32: return la_88_To_rgba_8888;
        case IG_GFX_TEXTURE_FORMAT_LA_44_8: return la_88_To_la_44;
        case IG_GFX_TEXTURE_FORMAT_X_8: return la_88_To_pal_8;
        case IG_GFX_TEXTURE_FORMAT_X_4: return la_88_To_pal_4;
        case IG_GFX_TEXTURE_FORMAT_LA_88_16: break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_44_8:
        switch (tFmt) {
        case IG_GFX_TEXTURE_FORMAT_LA_88_16: return la_44_To_la_88;
        case IG_GFX_TEXTURE_FORMAT_X_8: return (conversionFn *)thunk_memcpy;
        case IG_GFX_TEXTURE_FORMAT_X_4: return la_44_To_pal_4;
        case IG_GFX_TEXTURE_FORMAT_LA_44_8: break;
        }
        break;
    }
    return 0;
}

igImageConvert::conversionFn *igPsx2ImageConvert::getPackConversionFn(IG_GFX_IMAGE_ORDER order, IG_GFX_TEXTURE_FORMAT packedFormat, bool isUnpack)
{
    switch (packedFormat) {
    case IG_GFX_TEXTURE_FORMAT_LA_44_8:
        return isUnpack ? la_44_To_la_88 : la_88_To_la_44;
    case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
        return isUnpack ? rgba_5551_To_rgba_8888 : rgba_8888_To_rgba_5551;
    case IG_GFX_TEXTURE_FORMAT_RGB_565_16:
        return isUnpack ? rgb_565_To_rgb_888 : rgb_888_To_rgb_565;
    case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16:
        return isUnpack ? rgba_4444_To_rgba_8888 : rgba_8888_To_rgba_4444;
    case IG_GFX_TEXTURE_FORMAT_X_4:
        return isUnpack ? pal_4_To_pal_8 : pal_8_To_pal_4;
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
void igPsx2ImageConvert::pal_8_To_rgba_8888(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    ImagePalette *palette = (ImagePalette *)misc;
    unsigned int *colors;
    int last;
    const unsigned char *s = source + nSample - 1;
    unsigned int *d;
    int i;
    palette->used = 1;
    colors = palette->colors;
    last = palette->lastIndex;
    d = (unsigned int *)dest + nSample - 1;
    for (i = 0; i < nSample; i++, s--) {
        *d-- = colors[ClampIndex(*s, last)];
    }
}

void igPsx2ImageConvert::rgba_5551_To_rgba_8888(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    unsigned int *d = (unsigned int *)dest + nSample - 1;
    const unsigned short *s = (const unsigned short *)source + nSample - 1;
    int i;

    for (i = 0; i < nSample; i++) {
        *d-- = ((((unsigned int)*s & 0x8000) >> 8) << 24) | ((*s & 0x7C00) << 9) | ((*s & 0x3E0) << 6)
             | ((*s & 0x1F) << 3);
        s--;
    }
}

/* matching construct: 48-variant sweep — declaration order */
void igPsx2ImageConvert::rgb_565_To_rgb_888(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    unsigned char *d = dest + nSample * 3 - 3;
    const unsigned short *s = (const unsigned short *)source + nSample - 1;
    int i;
    unsigned int px;

    for (i = 0; i < nSample; i++) {
        px = *s;
        d[0] = (px & 0x1F) << 3;
        d[1] = (px >> 3) & 0xFC;
        d[2] = (px >> 8) & 0xF8;
        s--;
        d -= 3;
    }
}

/* matching construct: variant sweep — declaration order */
void igPsx2ImageConvert::rgba_4444_To_rgba_8888(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    unsigned int *d = (unsigned int *)dest + nSample - 1;
    const unsigned short *s = (const unsigned short *)source + nSample - 1;
    int i;
    unsigned int px;
    unsigned int alpha, g, b, r;

    for (i = 0; i < nSample; i++) {
        px = *s;
        alpha = ((px >> 8) & 0xF0) + ((px >> 12) & 0xF);
        alpha = ((alpha >> 1) + (alpha & 1)) << 24;
        g = px & 0xF0;
        b = px & 0xF00;
        r = px & 0xF;
        *d-- = (r | (r << 4)) | (((g << 8) | (g << 4)) | (alpha | ((b << 12) | (b << 8))));
        s--;
    }
}

void igPsx2ImageConvert::rgb_888_To_rgba_8888(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    const unsigned char *alphaSrc = (const unsigned char *)misc;
    unsigned int *d = (unsigned int *)dest + nSample - 1;
    const unsigned char *s = source + nSample * 3 - 3;
    unsigned int alpha = 0x80000000;
    int i;

    if (alphaSrc) {
        alpha = ((unsigned int)*alphaSrc >> 1) + (*alphaSrc & 1);
        alpha <<= 24;
    }
    for (i = 0; i < nSample; i++) {
        *d-- = alpha | (s[2] << 16) | (s[1] << 8) | s[0];
        s -= 3;
    }
}

void igPsx2ImageConvert::rgb_888_To_rgba_5551(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    const unsigned char *alphaSrc = (const unsigned char *)misc;
    unsigned short *dst = (unsigned short *)dest;
    const unsigned char *src = source;
    unsigned int alpha = 0x8000;
    int i;

    if (alphaSrc) {
        alpha = (*alphaSrc & 0x80) << 8;
        alpha &= 0x8000;
    }
    for (i = 0; i < nSample; i++) {
        *dst++ = alpha | ((src[2] & 0xF8u) << 7) | ((src[1] & 0xF8u) << 2) | ((src[0] & 0xF8u) >> 3);
        src += 3;
    }
}

void igPsx2ImageConvert::rgb_888_To_rgb_565(unsigned char *dest, const unsigned char *source, int nSample, void *misc) {
    unsigned short *dst = (unsigned short *)dest;
    const unsigned char *src = source;
    int i;
    for (i = 0; i < nSample; i++) {
        *dst++ = ((src[2] & 0xF8u) << 8) | ((src[1] & 0xFCu) << 3) | ((src[0] & 0xF8u) >> 3);
        src += 3;
    }
}

void igPsx2ImageConvert::rgba_8888_To_rgb_888(unsigned char *dest, const unsigned char *source, int nSample, void *misc) {
    unsigned char *dst = dest;
    const unsigned int *src = (const unsigned int *)source;
    int i;
    for (i = 0; i < nSample; i++) {
        unsigned int pixel = *src;
        dst[0] = pixel;
        dst[1] = (pixel & 0xFF00) >> 8;
        dst[2] = (pixel & 0xFF0000) >> 16;
        dst += 3;
        src++;
    }
}

void igPsx2ImageConvert::rgba_8888_To_rgba_5551(unsigned char *dest, const unsigned char *source, int nSample, void *misc) {
    unsigned short *dst = (unsigned short *)dest;
    const unsigned int *src = (const unsigned int *)source;
    int i;
    for (i = 0; i < nSample; i++, src++) {
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

void igPsx2ImageConvert::rgba_8888_To_rgba_4444(unsigned char *dest, const unsigned char *source, int nSample, void *misc) {
    unsigned short *dst = (unsigned short *)dest;
    const unsigned int *src = (const unsigned int *)source;
    int i;
    for (i = 0; i < nSample; i++, src++) {
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

void igPsx2ImageConvert::la_44_To_la_88(unsigned char *dest, const unsigned char *source, int nSample, void *misc) {
    unsigned short *d = (unsigned short *)dest + nSample - 1;
    const unsigned char *s = source + nSample - 1;
    int i;
    for (i = 0; i < nSample; i++) {
        unsigned int lo = *s & 0x0F;
        unsigned int hi = *s & 0xF0;
        hi |= hi >> 4;
        lo |= lo << 4;
        *d-- = (hi << 8) | lo;
        s--;
    }
}

void igPsx2ImageConvert::la_88_To_la_44(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    unsigned char *dst = dest;
    const unsigned short *src = (const unsigned short *)source;
    int i;

    for (i = 0; i < nSample; i++) {
        *dst++ = (((unsigned int)src[0] >> 8) & 0xF0) | ((src[0] & 0xF0u) >> 4);
        src++;
    }
}

void igPsx2ImageConvert::la_88_To_rgba_8888(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    unsigned int *dst = (unsigned int *)dest;
    const unsigned short *src = (const unsigned short *)source;
    int i;

    for (i = 0; i < nSample; i++) {
        unsigned int lum = *src & 0xFF;
        unsigned int hi = *src & 0xFF00;
        unsigned int alpha = (hi >> 9) + ((hi >> 8) & 1);
        *dst++ = (alpha << 24) | (lum << 16) | (lum << 8) | lum;
        src++;
    }
}

void igPsx2ImageConvert::la_88_To_pal_8(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    unsigned char *dst = dest;
    const unsigned short *src = (const unsigned short *)source;
    int i;

    for (i = 0; i < nSample; i++) {
        *dst++ = (((unsigned int)src[0] >> 4) & 0xF) | (((unsigned int)src[0] >> 8) & 0xF0);
        src++;
    }
}

void igPsx2ImageConvert::la_88_To_pal_4(unsigned char *dest, const unsigned char *source, int nSample, void *misc)
{
    unsigned char *dst = dest;
    const unsigned short *src = (const unsigned short *)source;
    int i;

    for (i = 0; i < nSample; i += 2) {
        *dst++ = ((src[0] & 0xC0u) >> 2) | (((unsigned int)src[0] >> 8) & 0xC0u)
               | ((src[1] & 0xC0u) >> 6) | ((((unsigned int)src[1] >> 8) & 0xC0u) >> 4);
        src += 2;
    }
}
}
}

void *thunk_memcpy(void *d, const void *s, unsigned int n) {
    return (void *)memcpy(d, s, n);
}

namespace Gap {
namespace Gfx {

void igPsx2ImageConvert::la_44_To_pal_4(unsigned char *dest, const unsigned char *source, int nSample, void *misc) {
    unsigned char *dst = dest;
    const unsigned char *src = source;
    int i;
    for (i = 0; i < nSample; i += 2) {
        *dst++ = (src[0] & 0xC0u) | ((src[0] & 0x0Cu) << 2) | ((src[1] & 0xC0u) >> 4) | ((src[1] & 0x0Cu) >> 2);
        src += 2;
    }
}

void igPsx2ImageConvert::alpha_8_To_pal_4(unsigned char *dest, const unsigned char *source, int nSample, void *misc) {
    unsigned char *dst = dest;
    const unsigned char *src = source;
    int i; for (i = 0; i < nSample; i += 2) { *dst++ = (src[0] & 0xF0) | ((src[1] & 0xF0u) >> 4); src += 2; }
}
}
}

void FUN_0016fe00(void *dst, const void *src, unsigned int size) {
    if (dst != src) {
        memmove(dst, src, size);
    }
}

void FUN_0016fe20(void *dst, const void *src, unsigned int size) {
    if (dst != src) {
        memmove(dst, src, size);
    }
}

