/* livetex.c — textures read from a live EE RAM dump.  See dw4/livetex.h. */
#include "dw4/livetex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw4/texture.h"

/* The recovered vtable of the runtime image class (finding #529: the engine's `ig*` classes are
 * in `data/vtables-getvtable.json`; 0x525630 is `igPsx2Image`, the concrete `igImage`). */
#define VT_PSX2IMAGE 0x00525630u

/* Reflective field offsets (data/reflection.json). */
#define IMG_PX 0x08
#define IMG_PY 0x0c
#define IMG_SIZE 0x30
#define IMG_PIMAGE 0x34
#define IMG_PCLUT 0x44
#define IMG_BITSIDX 0x48
#define IMG_BPR 0x4c
#define IMG_PNAME 0x58

#define CLUT_NUMENTRIES 0x0c
#define CLUT_STRIDE 0x10
#define CLUT_PDATA 0x14

typedef struct {
    char name[64];
    uint32_t img;
} dw4_liveimg;

struct dw4_livetex {
    uint8_t *b;
    size_t len;
    uint32_t base;
    dw4_liveimg *img;
    int n, cap;
};

static uint32_t lt_u32(const dw4_livetex *lt, uint32_t a)
{
    uint32_t o = a - lt->base;
    if (a < lt->base || (size_t)o + 4 > lt->len)
        return 0;
    return (uint32_t)lt->b[o] | ((uint32_t)lt->b[o + 1] << 8) |
           ((uint32_t)lt->b[o + 2] << 16) | ((uint32_t)lt->b[o + 3] << 24);
}

static const uint8_t *lt_ptr(const dw4_livetex *lt, uint32_t a, size_t n)
{
    uint32_t o = a - lt->base;
    if (a < lt->base || (size_t)o + n > lt->len)
        return NULL;
    return lt->b + o;
}

/* An address a live pointer may take: inside the guest arena (finding #481: 32-bit handles). */
static int lt_addr_ok(const dw4_livetex *lt, uint32_t a)
{
    return a >= lt->base && (size_t)(a - lt->base) + 4 <= lt->len;
}

static void lt_cstr(const dw4_livetex *lt, uint32_t a, char *out, size_t n)
{
    size_t i = 0;
    const uint8_t *p;
    out[0] = 0;
    if (!a || !(p = lt_ptr(lt, a, 1)))
        return;
    while (i + 1 < n && (size_t)(a - lt->base) + i < lt->len && p[i]) {
        out[i] = (char)p[i];
        i++;
    }
    out[i] = 0;
}

static int lt_add(dw4_livetex *lt, const char *name, uint32_t img)
{
    int i;
    if (!name[0])
        return 0;
    for (i = 0; i < lt->n; i++)
        if (strcmp(lt->img[i].name, name) == 0)
            return 0;                        /* the first live instance wins */
    if (lt->n == lt->cap) {
        int cap = lt->cap ? lt->cap * 2 : 64;
        dw4_liveimg *v = (dw4_liveimg *)realloc(lt->img, (size_t)cap * sizeof(*v));
        if (!v)
            return -1;
        lt->img = v;
        lt->cap = cap;
    }
    snprintf(lt->img[lt->n].name, sizeof(lt->img[lt->n].name), "%s", name);
    lt->img[lt->n].img = img;
    lt->n++;
    return 0;
}

/* Validate an `igPsx2Image` and register it when it can decode. */
static void lt_probe(dw4_livetex *lt, uint32_t img)
{
    uint32_t px, py, bits, bpr, size, pimage, pclut;
    char name[64];

    px = lt_u32(lt, img + IMG_PX);
    py = lt_u32(lt, img + IMG_PY);
    bits = lt_u32(lt, img + IMG_BITSIDX);
    bpr = lt_u32(lt, img + IMG_BPR);
    size = lt_u32(lt, img + IMG_SIZE);
    pimage = lt_u32(lt, img + IMG_PIMAGE);
    pclut = lt_u32(lt, img + IMG_PCLUT);
    lt_cstr(lt, lt_u32(lt, img + IMG_PNAME), name, sizeof(name));
    if (!px || !py || px > 4096 || py > 4096 || (bits != 4 && bits != 8))
        return;
    if (!lt_addr_ok(lt, pimage) || !lt_addr_ok(lt, pclut))
        return;
    if (!size)
        size = (px * py * bits + 7) / 8;
    if (!lt_ptr(lt, pimage, size))
        return;
    if (!lt_ptr(lt, pclut + CLUT_PDATA, 4))
        return;
    lt_add(lt, name, img);
}

dw4_livetex *dw4_livetex_open(const char *path)
{
    FILE *fp = fopen(path, "rb");
    dw4_livetex *lt;
    long sz;
    size_t i;

    if (!fp)
        return NULL;
    if (fseek(fp, 0, SEEK_END) != 0 || (sz = ftell(fp)) <= 0 || fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        return NULL;
    }
    lt = (dw4_livetex *)calloc(1, sizeof(*lt));
    if (!lt) {
        fclose(fp);
        return NULL;
    }
    lt->len = (size_t)sz;
    lt->b = (uint8_t *)malloc(lt->len);
    if (!lt->b || fread(lt->b, 1, lt->len, fp) != lt->len) {
        fclose(fp);
        free(lt->b);
        free(lt);
        return NULL;
    }
    fclose(fp);
    /* 32 MB is the whole EE RAM from 0; 31 MB is RAM from 0x00100000 (the kernel owns the low
     * megabyte).  Anything else is not something this reader can address. */
    if (lt->len == 0x2000000u)
        lt->base = 0;
    else if (lt->len == 0x1f00000u)
        lt->base = 0x00100000u;
    else {
        free(lt->b);
        free(lt);
        return NULL;
    }
    /* One pass for the image vtable; objects are 4-byte aligned (finding #481). */
    for (i = 0; i + 4 <= lt->len; i += 4) {
        uint32_t a = lt->base + (uint32_t)i;
        if (lt_u32(lt, a) == VT_PSX2IMAGE)
            lt_probe(lt, a);
    }
    return lt;
}

void dw4_livetex_close(dw4_livetex *lt)
{
    if (!lt)
        return;
    free(lt->b);
    free(lt->img);
    free(lt);
}

int dw4_livetex_count(const dw4_livetex *lt)
{
    return lt ? lt->n : 0;
}

const char *dw4_livetex_name(const dw4_livetex *lt, int i)
{
    if (!lt || i < 0 || i >= lt->n)
        return NULL;
    return lt->img[i].name;
}

int dw4_livetex_get(dw4_livetex *lt, const char *name, uint8_t **rgba, int *w, int *h)
{
    int i;
    uint32_t img = 0, px, py, bits, bpr, size, pimage, pclut, num, stride, pdata;
    const uint8_t *grid, *pal;
    uint8_t *out;
    dw4_pal_mode mode;
    uint32_t y;

    if (rgba)
        *rgba = NULL;
    if (!lt || !name || !name[0])
        return -1;
    for (i = 0; i < lt->n; i++)
        if (strcmp(lt->img[i].name, name) == 0) {
            img = lt->img[i].img;
            break;
        }
    if (!img)
        return -1;

    px = lt_u32(lt, img + IMG_PX);
    py = lt_u32(lt, img + IMG_PY);
    bits = lt_u32(lt, img + IMG_BITSIDX);
    bpr = lt_u32(lt, img + IMG_BPR);
    size = lt_u32(lt, img + IMG_SIZE);
    pimage = lt_u32(lt, img + IMG_PIMAGE);
    pclut = lt_u32(lt, img + IMG_PCLUT);
    if (!size)
        size = (px * py * bits + 7) / 8;
    num = lt_u32(lt, pclut + CLUT_NUMENTRIES);
    stride = lt_u32(lt, pclut + CLUT_STRIDE);
    pdata = lt_u32(lt, pclut + CLUT_PDATA);
    mode = (stride == 4) ? DW4_PAL_RGBA8888 : DW4_PAL_PS2_CSM1;
    grid = lt_ptr(lt, pimage, size);
    pal = lt_ptr(lt, pdata, num * (mode == DW4_PAL_PS2_CSM1 ? 2u : 4u));
    if (!grid || !pal || !num || !px || !py)
        return -1;

    out = (uint8_t *)malloc((size_t)px * py * 4);
    if (!out)
        return -1;
    if (dw4_texture_rgba(grid, size, px, py, (int)bits, bpr, pal,
                         num * (mode == DW4_PAL_PS2_CSM1 ? 2u : 4u), num, mode, out) != 0) {
        free(out);
        return -1;
    }
    /* The engine's buffers are bottom-up; `dw4_texpack_rgba` flips for the same reason, so the
     * sampler's own `1 - v` lands the right texel. */
    for (y = 0; y < py / 2; y++) {
        uint8_t *a = out + (size_t)y * px * 4;
        uint8_t *b = out + (size_t)(py - 1 - y) * px * 4;
        uint32_t x;
        for (x = 0; x < px * 4; x++) {
            uint8_t t = a[x];
            a[x] = b[x];
            b[x] = t;
        }
    }
    if (rgba)
        *rgba = out;
    else
        free(out);
    if (w)
        *w = (int)px;
    if (h)
        *h = (int)py;
    return 0;
}
