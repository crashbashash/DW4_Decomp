namespace Gap {
namespace Gfx {

void igPsx2ImageConvert::swapRGBA8888(unsigned char *pixels, int count, unsigned int *order)
{
}

void igPsx2ImageConvert::swapRGB888(unsigned char *pixels, int count, unsigned int *order)
{
}

void igPsx2ImageConvert::swapRGBA5551(unsigned char *pixels, int count, unsigned int *order)
{
    unsigned int c1;
    int i;
    unsigned int r;
    unsigned int v;
    unsigned int v2;
    unsigned int r2;
    int j;
    unsigned int c0;
    if (*order == IG_GFX_IMAGE_ORDER_DEFAULT) {
        for (i = 0; i < count; i++) {
            v = pixels[0]; v |= pixels[1] << 8;
            r = ((v & 0x3E) << 9) | (((v & 0xF800) >> 11) | ((v & 0x7C0) >> 1)) | ((v & 1) ? 0x8000 : 0);
            pixels[0] = r;
            pixels[1] = (r & 0xFF00) >> 8;
            pixels += 2;
        }
        return;
    }
    for (j = 0; j < count; j++) {
        v2 = pixels[0]; v2 |= pixels[1] << 8;
        c0 = ((v2 & 0x1F) << 11) | (((v2 & 0x7C00) >> 9) | ((v2 & 0x3E0) << 1));
        c1 = (v2 & 0x8000) != 0;
        r2 = c0 | c1;
        pixels[0] = r2;
        pixels[1] = (r2 & 0xFF00) >> 8;
        pixels += 2;
    }
}

void igPsx2ImageConvert::swapRGBA4444(unsigned char *pixels, int count, unsigned int *order)
{
    int j;
    unsigned int vb;
    int i;
    unsigned int va;
    if (*order == IG_GFX_IMAGE_ORDER_DEFAULT) {
        for (j = 0; j < count; j++) {
            va=pixels[0]; va|=pixels[1]<<8;
            va = ((va & 0xf) << 12) | ((va & 0xf0) << 4) | ((va & 0xf00) >> 4) | ((va & 0xf000) >> 12);
            pixels[0] = va;
            pixels[1] = (va & 0xff00) >> 8;
            pixels += 2;
        }
    } else {
        for (i = 0; i < count; i++) {
            vb=pixels[0]; vb|=pixels[1]<<8;
            vb = ((vb & 0xf000) >> 12) | ((vb & 0xf00) >> 4) | ((vb & 0xf0) << 4) | ((vb & 0xf) << 12);
            pixels[0] = vb;
            pixels[1] = (vb & 0xff00) >> 8;
            pixels += 2;
        }
    }
}

void igPsx2ImageConvert::swapRGB565(unsigned char *pixels, int count, unsigned int *order)
{
    int i;
    unsigned int v;
    unsigned int t;
    for (i = 0; i < count; i++) {
        t=pixels[0]; t|=pixels[1]<<8;
        v = ((t & 0x1F) << 11) | (((t & 0xF800) >> 11) | (t & 0x7E0));
        pixels[0] = v;
        pixels[1] = (v & 0xFF00) >> 8;
        pixels += 2;
    }
}

void igPsx2ImageConvert::swapRGB332(unsigned char *pixels, int count, unsigned int *order)
{
}

void igPsx2ImageConvert::swapLA88(unsigned char *pixels, int count, unsigned int *order)
{
}

void igPsx2ImageConvert::swapRGBA2222(unsigned char *pixels, int count, unsigned int *order)
{
}

void igPsx2ImageConvert::swapLA44(unsigned char *pixels, int count, unsigned int *order)
{
    int i;
    for (i = 0; i < count; i++) {
        unsigned char t = *pixels;
        *pixels = ((int) (t & 0xF0) >> 4) | ((t & 0xF) * 0x10);
        pixels++;
    }
}

void igPsx2ImageConvert::swapRGBA3328(unsigned char *pixels, int count, unsigned int *order)
{
}
}
}

