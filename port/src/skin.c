/* skin.c — a skinned character mesh from a live EE RAM dump.  See dw4/skin.h. */
#include "dw4/skin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VT_VERTEXARRAY 0x00525190u
#define VT_GEOMATTR    0x005238C0u
#define VT_BLENDSELECT 0x0052A400u
#define VT_BLENDMATS   0x00524190u

struct dw4_skin {
    uint8_t *b;
    size_t len;
    uint32_t base;

    uint32_t va, geom, num_verts;
    float *verts;        /* 3 * num_verts */
    float *weights;      /* num_verts */
    uint8_t *indices;    /* num_verts */

    uint32_t *bonemap;
    int nbones;

    int prim_type, num_prims;
    uint32_t *lengths;
    int nlengths;

    uint32_t *pcache;
    uint32_t *pcount;
    int npal;
};

static uint32_t sk_u32(const dw4_skin *sk, uint32_t a)
{
    size_t o = a - sk->base;
    if (a < sk->base || o + 4 > sk->len)
        return 0;
    return (uint32_t)sk->b[o] | ((uint32_t)sk->b[o + 1] << 8) |
           ((uint32_t)sk->b[o + 2] << 16) | ((uint32_t)sk->b[o + 3] << 24);
}

static int valid(const dw4_skin *sk, uint32_t a, size_t n)
{
    return a >= sk->base && (size_t)(a - sk->base) + n <= sk->len;
}

/* Every 4-aligned occurrence of `vtable` as a word, i.e. an object pointer. */
static void each_object(const dw4_skin *sk, uint32_t vtable,
                        void (*fn)(dw4_skin *s, uint32_t addr, void *ctx), void *ctx)
{
    for (size_t i = 0; i + 4 <= sk->len; i += 4) {
        if (sk->b[i] == (vtable & 0xFF) && sk->b[i + 1] == ((vtable >> 8) & 0xFF) &&
            sk->b[i + 2] == ((vtable >> 16) & 0xFF) && sk->b[i + 3] == (vtable >> 24) &&
            ((sk->base + i) % 4) == 0)
            fn((dw4_skin *)sk, (uint32_t)(sk->base + i), ctx);
    }
}

/* --- discovery ------------------------------------------------------------------------- */

struct pick { uint32_t va; uint32_t nv; uint32_t best_nv; };

static void pick_va(dw4_skin *sk, uint32_t a, void *ctx)
{
    struct pick *p = ctx;
    uint32_t nv = sk_u32(sk, a + 0x0c), bw = sk_u32(sk, a + 0x20);
    uint32_t bi = sk_u32(sk, a + 0x24), vd = sk_u32(sk, a + 0x08);
    if (!nv || !valid(sk, bw, 4 * nv) || !valid(sk, bi, nv) || !valid(sk, vd, 8))
        return;
    if (nv > p->best_nv) {
        p->best_nv = nv;
        p->va = a;
        p->nv = nv;
    }
}

/* the geometry search needs the VA separately, so use a small explicit struct */
struct geomsearch { uint32_t va; uint32_t found; };
static void pick_geom2(dw4_skin *sk, uint32_t a, void *ctx)
{
    struct geomsearch *g = ctx;
    if (sk_u32(sk, a + 0x0c) == g->va)
        g->found = a;
}

struct mapsearch { uint32_t want; uint32_t best; uint32_t bestlen; uint32_t maxslot; };
static void pick_map(dw4_skin *sk, uint32_t a, void *ctx)
{
    struct mapsearch *m = ctx;
    uint32_t lst = sk_u32(sk, a + 0x28);
    if (!valid(sk, lst, 0x14))
        return;
    uint32_t cnt = sk_u32(sk, lst + 0x08), arr = sk_u32(sk, lst + 0x10);
    if (cnt == 0 || cnt > 256 || !valid(sk, arr, 4 * cnt))
        return;
    if (cnt == m->want) {
        m->best = a;
        m->bestlen = cnt;
        for (uint32_t i = 0; i < cnt; i++) {
            uint32_t v = sk_u32(sk, arr + 4 * i);
            if (v > m->maxslot)
                m->maxslot = v;
        }
    }
}

struct palscan { dw4_skin *sk; };
static void pick_pal(dw4_skin *sk, uint32_t a, void *ctx)
{
    (void)ctx;
    uint32_t cache = sk_u32(sk, a + 0x0c), cnt = sk_u32(sk, a + 0x10);
    if (cnt == 0 || cnt > 256 || !valid(sk, cache, 64 * cnt))
        return;
    uint32_t *nc = realloc(sk->pcache, (sk->npal + 1) * sizeof(*nc));
    if (!nc)
        return;
    sk->pcache = nc;
    uint32_t *cc = realloc(sk->pcount, (sk->npal + 1) * sizeof(*cc));
    if (!cc)
        return;
    sk->pcount = cc;
    /* keep the pool in *object* address order (the same order live_skin.py lists) */
    int i = sk->npal;
    while (i > 0 && sk->pcache[i - 1] > a) {
        sk->pcache[i] = sk->pcache[i - 1];
        sk->pcount[i] = sk->pcount[i - 1];
        i--;
    }
    sk->pcache[i] = a;
    sk->pcount[i] = cnt;
    sk->npal++;
}

dw4_skin *dw4_skin_open(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f)
        return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n <= 0) {
        fclose(f);
        return NULL;
    }
    dw4_skin *sk = calloc(1, sizeof(*sk));
    if (!sk) {
        fclose(f);
        return NULL;
    }
    sk->b = malloc((size_t)n);
    if (!sk->b || fread(sk->b, 1, (size_t)n, f) != (size_t)n) {
        fclose(f);
        free(sk->b);
        free(sk);
        return NULL;
    }
    fclose(f);
    sk->len = (size_t)n;
    /* a 32 MB image is all of EE RAM from 0; a 31 MB one is from the 1 MB kernel base */
    sk->base = (sk->len >= 0x02000000u) ? 0u : 0x00100000u;

    struct pick p = { 0, 0, 0 };
    each_object(sk, VT_VERTEXARRAY, pick_va, &p);
    if (!p.va) {
        dw4_skin_close(sk);
        return NULL;
    }
    sk->va = p.va;
    sk->num_verts = p.nv;

    uint32_t vd = sk_u32(sk, sk->va + 0x08);
    uint32_t pos = sk_u32(sk, vd);
    uint32_t bw = sk_u32(sk, sk->va + 0x20), bi = sk_u32(sk, sk->va + 0x24);
    sk->verts = malloc(3 * sk->num_verts * sizeof(float));
    sk->weights = malloc(sk->num_verts * sizeof(float));
    sk->indices = malloc(sk->num_verts);
    if (!sk->verts || !sk->weights || !sk->indices || !valid(sk, pos, 12 * sk->num_verts)) {
        dw4_skin_close(sk);
        return NULL;
    }
    memcpy(sk->verts, sk->b + (pos - sk->base), 12 * sk->num_verts);
    memcpy(sk->weights, sk->b + (bw - sk->base), 4 * sk->num_verts);
    memcpy(sk->indices, sk->b + (bi - sk->base), sk->num_verts);

    struct geomsearch g = { sk->va, 0 };
    each_object(sk, VT_GEOMATTR, pick_geom2, &g);
    if (g.found) {
        sk->geom = g.found;
        sk->prim_type = (int)sk_u32(sk, sk->geom + 0x14);
        sk->num_prims = (int)sk_u32(sk, sk->geom + 0x18);
        uint32_t pl = sk_u32(sk, sk->geom + 0x30);
        if (valid(sk, pl, 0x10)) {
            uint32_t data = sk_u32(sk, pl + 0x08), cnt = sk_u32(sk, pl + 0x0c);
            if (cnt && cnt < 100000 && valid(sk, data, 4 * cnt)) {
                sk->lengths = malloc(4 * cnt);
                if (sk->lengths) {
                    memcpy(sk->lengths, sk->b + (data - sk->base), 4 * cnt);
                    sk->nlengths = (int)cnt;
                }
            }
        }
    }

    uint32_t maxbone = 0;
    for (uint32_t i = 0; i < sk->num_verts; i++)
        if (sk->indices[i] > maxbone)
            maxbone = sk->indices[i];
    struct mapsearch m = { maxbone + 1, 0, 0, 0 };
    each_object(sk, VT_BLENDSELECT, pick_map, &m);
    if (m.best) {
        uint32_t lst = sk_u32(sk, m.best + 0x28);
        uint32_t cnt = sk_u32(sk, lst + 0x08), arr = sk_u32(sk, lst + 0x10);
        sk->bonemap = malloc(4 * cnt);
        if (sk->bonemap) {
            memcpy(sk->bonemap, sk->b + (arr - sk->base), 4 * cnt);
            sk->nbones = (int)cnt;
        }
    }
    if (!sk->bonemap || (sk->nbones <= (int)maxbone)) {
        dw4_skin_close(sk);
        return NULL;
    }

    each_object(sk, VT_BLENDMATS, pick_pal, NULL);
    if (!sk->npal) {
        dw4_skin_close(sk);
        return NULL;
    }
    return sk;
}

void dw4_skin_close(dw4_skin *sk)
{
    if (!sk)
        return;
    free(sk->b);
    free(sk->verts);
    free(sk->weights);
    free(sk->indices);
    free(sk->bonemap);
    free(sk->lengths);
    free(sk->pcache);
    free(sk->pcount);
    free(sk);
}

int dw4_skin_palette_count(const dw4_skin *sk) { return sk->npal; }
uint32_t dw4_skin_palette_addr(const dw4_skin *sk, int i)
{
    return (i >= 0 && i < sk->npal) ? sk->pcache[i] : 0;
}
int dw4_skin_palette_size(const dw4_skin *sk, int i)
{
    return (i >= 0 && i < sk->npal) ? (int)sk->pcount[i] : 0;
}

int dw4_skin_default_palette(const dw4_skin *sk)
{
    uint32_t maxslot = 0;
    for (int i = 0; i < sk->nbones; i++)
        if (sk->bonemap[i] > maxslot)
            maxslot = sk->bonemap[i];
    for (int i = 0; i < sk->npal; i++)
        if (sk->pcount[i] > maxslot)
            return i;
    return 0;
}

/* `obj` is the igBlendMatricesAttr object; its `_matrixCache` (+0xc) is the data.  The stored
 * matrix is float32; widening to double makes the arithmetic match live_skin.py exactly. */
static void mat4(const dw4_skin *sk, uint32_t obj, int idx, double m[16])
{
    uint32_t cache = sk_u32(sk, obj + 0x0c);
    const float *f = (const float *)(sk->b + (cache + 64 * (uint32_t)idx - sk->base));
    for (int i = 0; i < 16; i++)
        m[i] = f[i];
}

int dw4_skin_write_obj(dw4_skin *sk, int palette, const char *path, int posed)
{
    if (palette < 0 || palette >= sk->npal)
        return -1;
    FILE *f = fopen(path, "w");
    if (!f)
        return -1;
    if (posed)
        fprintf(f, "# posed: palette %08x via bone map; live_skin.py\n", sk->pcache[palette]);
    else
        fprintf(f, "# bind pose, igVertexArray1_1 %08x\n", sk->va);

    uint32_t nb = (uint32_t)sk->nbones;
    for (uint32_t i = 0; i < sk->num_verts; i++) {
        const float *v = &sk->verts[3 * i];
        if (posed) {
            uint32_t bone = sk->indices[i];
            uint32_t slot = bone < nb ? sk->bonemap[bone] : 0;
            double dm[16];
            mat4(sk, sk->pcache[palette], (int)(slot % sk->pcount[palette]), dm);
            double x = v[0], y = v[1], z = v[2];
            fprintf(f, "v %.6f %.6f %.6f\n",
                    x * dm[0] + y * dm[4] + z * dm[8] + dm[12],
                    x * dm[1] + y * dm[5] + z * dm[9] + dm[13],
                    x * dm[2] + y * dm[6] + z * dm[10] + dm[14]);
        } else {
            fprintf(f, "v %.6f %.6f %.6f\n", v[0], v[1], v[2]);
        }
    }
    if (sk->prim_type == 3) {
        for (int t = 0; t < sk->num_prims; t++)
            fprintf(f, "f %d %d %d\n", 3 * t + 1, 3 * t + 2, 3 * t + 3);
    } else {
        uint32_t off = 0;
        for (int s = 0; s < sk->nlengths; s++) {
            uint32_t L = sk->lengths[s];
            for (uint32_t k = 0; k + 2 < L; k++)
                fprintf(f, "f %u %u %u\n", off + k + 1, off + k + 2, off + k + 3);
            off += L;
        }
    }
    fclose(f);
    return 0;
}

void dw4_skin_print(const dw4_skin *sk)
{
    printf("skin: VA %08x geometry %08x  %u verts  %d prims  %d bones  %d palette(s)\n",
           sk->va, sk->geom, sk->num_verts, sk->num_prims, sk->nbones, sk->npal);
    for (int i = 0; i < sk->npal; i++)
        printf("  palette[%d] %08x  %d matrices\n", i, sk->pcache[i], sk->pcount[i]);
}
