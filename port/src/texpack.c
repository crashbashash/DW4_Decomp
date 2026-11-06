/* texpack.c — texture-pack reader.  See dw4/texpack.h for the layout. */
#include "dw4/texpack.h"

#include <stdlib.h>
#include <string.h>

#define MAXBLK  1024
#define MAXCAND 256

typedef struct {
    uint32_t id;
    uint32_t size;      /* the block's bytes in the pool */
    uint32_t off;       /* the record's offset in the pack */
    uint32_t w, h;      /* image only */
    int kind;           /* 0 = clut, 1 = image */
} blk_t;

static uint32_t rd32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

static uint16_t rd16(const uint8_t *p)
{
    return (uint16_t)((uint16_t)p[0] | ((uint16_t)p[1] << 8));
}

/* The record scan is the same pattern the Python decoder uses: a clut record opens with
 * `_fmt` 7, a 1..256 entry count, a 2 or 4 byte stride and `_clutSize == entries*stride`;
 * an image record opens with `_pfmt` 0x10000 and `_imageSize == W*H`.  Both carry the
 * class tag (11 / 10) below 64 as the first word, which is what keeps a stray match out. */
static int find_records(const uint8_t *b, size_t n, blk_t *out, uint32_t *nblk,
                        uint32_t *nclut, uint32_t *nimg)
{
    size_t p;
    uint32_t c = 0;

    for (p = 0; p + 64 <= n; p++) {
        const uint8_t *v = b + p;
        uint32_t tag = rd32(v);
        uint32_t sz = rd32(v + 4);

        if (tag >= 64)
            continue;
        if (sz == 28 && rd32(v + 8) == 7 && rd32(v + 12) >= 1 && rd32(v + 12) <= 256 &&
            (rd32(v + 16) == 2 || rd32(v + 16) == 4) &&
            rd32(v + 24) == rd32(v + 12) * rd32(v + 16)) {
            if (c >= MAXBLK)
                return -1;
            out[c].id = rd32(v + 20);
            out[c].size = rd32(v + 12) * rd32(v + 16);
            out[c].off = (uint32_t)p;
            out[c].w = out[c].h = 0;
            out[c].kind = 0;
            c++;
            (*nclut)++;
        } else if (sz >= 104 && sz <= 140 && (sz & 3) == 0 && rd32(v + 8) >= 4 && rd32(v + 8) <= 1024 &&
                   rd32(v + 12) >= 4 && rd32(v + 12) <= 1024 && rd32(v + 16) == 1 &&
                   rd32(v + 20) == 1 && rd32(v + 24) == 100 && rd32(v + 44) == 0x10000 &&
                   rd32(v + 48) == rd32(v + 8) * rd32(v + 12)) {
            if (c >= MAXBLK)
                return -1;
            out[c].id = rd32(v + 52);
            out[c].size = rd32(v + 48);
            out[c].off = (uint32_t)p;
            out[c].w = rd32(v + 8);
            out[c].h = rd32(v + 12);
            out[c].kind = 1;
            c++;
            (*nimg)++;
        }
    }
    *nblk = c;
    return c ? 0 : -1;
}

static int by_id(const void *a, const void *b)
{
    uint32_t x = ((const blk_t *)a)->id, y = ((const blk_t *)b)->id;
    return x < y ? -1 : (x > y ? 1 : 0);
}

static int by_off(const void *a, const void *b)
{
    uint32_t x = ((const blk_t *)a)->off, y = ((const blk_t *)b)->off;
    return x < y ? -1 : (x > y ? 1 : 0);
}

/* `id -> class`, the object packs' table shape with class entries.  It is
 * validated by requiring one class to be exactly the clut blocks and another exactly the
 * images' `_pClut` values; anything less means the pack is not one we understand, and the
 * caller must not get guessed offsets. */
static int find_class_table(const uint8_t *b, size_t n, const blk_t *blk, uint32_t nblk,
                            uint32_t nclut, uint32_t *tbl_off, uint32_t *tbl_count,
                            const uint8_t **tbl, uint32_t *block_class, uint32_t *obj_class)
{
    uint32_t clut_ids[MAXBLK], obj_ids[MAXBLK];
    uint32_t nc = 0, no = 0, i, k;
    size_t p;

    for (i = 0; i < nblk; i++)
        if (blk[i].kind == 0)
            clut_ids[nc++] = blk[i].id;
    for (i = 0; i < nblk; i++)
        if (blk[i].kind == 1)
            obj_ids[no++] = rd32(b + blk[i].off + 68);
    if (!nc || !no || nc != nclut)
        return -1;

    for (p = 0x30; p + 8 <= n; p++) {
        uint32_t tb = rd32(b + p), cnt = rd32(b + p + 4);
        uint32_t kb = 0xffffffffu, ko = 0xffffffffu;
        const uint8_t *t;

        if (tb != 8 + 2 * cnt || cnt < nc || (size_t)tb > n - p)
            continue;
        t = b + p + 8;
        for (k = 0; k < 64; k++) {
            uint32_t cn = 0, hitc = 0, ho = 0;
            for (i = 0; i < cnt; i++) {
                uint32_t j;
                if (rd16(t + 2 * i) != k)
                    continue;
                cn++;
                for (j = 0; j < nc; j++)
                    if (clut_ids[j] == i) {
                        hitc++;
                        break;
                    }
                for (j = 0; j < no; j++)
                    if (obj_ids[j] == i) {
                        ho++;
                        break;
                    }
            }
            if (cn && cn == nc && hitc == cn)
                kb = k;
            if (cn && cn == nc && ho == cn)
                ko = k;
        }
        if (kb == 0xffffffffu || ko == 0xffffffffu || kb == ko)
            continue;
        *tbl_off = (uint32_t)p;
        *tbl_count = cnt;
        *tbl = t;
        *block_class = kb;
        *obj_class = ko;
        return 0;
    }
    return -1;
}

/* A pad is a four-byte slot in a gap of the id sequence.  Which gap is not stored, so it
 * is chosen by the property the layout exposes: a palette block's entry 0 has black RGB.
 * Ties go to the lexicographically latest combination, matching the Python decoder. */
static void choose_pads(const uint8_t *b, const blk_t *blk, uint32_t nblk, uint32_t base,
                        uint32_t npads, uint32_t *pads)
{
    uint32_t cand[MAXCAND];
    uint32_t ncand = 0, best = 0, i;
    uint32_t combo[4];
    int have = 0;

    if (!npads)
        return;
    if (npads > 4) {
        pads[0] = 0xffffffffu;   /* signal "unknown": the caller refuses */
        return;
    }
    for (i = 0; i + 1 < nblk; i++)
        if (blk[i + 1].id - blk[i].id > 1 && ncand < MAXCAND)
            cand[ncand++] = blk[i].id;
    if (ncand < npads) {
        pads[0] = 0xffffffffu;
        return;
    }
    for (i = 0; i < npads; i++)
        combo[i] = i;
    for (;;) {
        uint32_t c = base, good = 0, j, k;
        for (j = 0; j < nblk; j++) {
            if (blk[j].kind == 0 && c + 4 <= (uint32_t)0xffffffffu &&
                b[c + 1] == 0 && b[c + 2] == 0 && b[c + 3] == 0)
                good++;
            c += blk[j].size;
            for (k = 0; k < npads; k++)
                if (blk[j].id == cand[combo[k]])
                    c += 4;
        }
        if (!have || good >= best) {
            best = good;
            for (k = 0; k < npads; k++)
                pads[k] = cand[combo[k]];
            have = 1;
        }
        /* next combination, lexicographic order */
        for (i = npads; i-- > 0;) {
            if (combo[i] < ncand - (npads - i))
                break;
        }
        if (i == (uint32_t)-1)
            break;
        combo[i]++;
        for (i = i + 1; i < npads; i++)
            combo[i] = combo[i - 1] + 1;
    }
}

static void place_blocks(const uint8_t *b, blk_t *blk, uint32_t nblk, uint32_t base,
                         const uint32_t *pads, uint32_t npads, uint32_t *offs)
{
    uint32_t c = base, j, k;
    for (j = 0; j < nblk; j++) {
        offs[j] = c;
        c += blk[j].size;
        for (k = 0; k < npads; k++)
            if (pads[k] != 0xffffffffu && blk[j].id == pads[k])
                c += 4;
    }
    (void)b;
}

int dw4_texpack_open(dw4_texpack *tp, const uint8_t *b, size_t len)
{
    static blk_t blk[MAXBLK];
    static uint32_t offs[MAXBLK];
    uint32_t nblk = 0, nclut = 0, nimg = 0, hdr6, hdr7, sum = 0, pads[4], npads, i, j;
    uint32_t base, table_start, cnt;
    const uint8_t *tbl = NULL;
    char name[64];

    memset(tp, 0, sizeof(*tp));
    if (len < 0x30)
        return -1;
    hdr6 = rd32(b + 0x18);
    hdr7 = rd32(b + 0x1c);
    if (find_records(b, len, blk, &nblk, &nclut, &nimg) != 0)
        return -1;
    if (hdr7 != nclut + nimg + 3)
        return -1;
    for (i = 0; i < nblk; i++)
        sum += blk[i].size;
    if (hdr6 != sum + 4 * (nclut + 2) || nclut >= nblk)
        return -1;
    if (find_class_table(b, len, blk, nblk, nclut, &tp->tbl_off, &cnt, &tbl,
                         &tp->block_class, &tp->obj_class) != 0)
        return -1;

    table_start = (uint32_t)len - 1 - hdr6;
    base = table_start + 4 * nclut;
    npads = (hdr6 - 4 * nclut - sum) / 4;
    if (base + sum + 4 * npads > len)
        return -1;
    memset(pads, 0, sizeof(pads));
    qsort(blk, nblk, sizeof(blk[0]), by_id);   /* the pad search and the layout walk id order */
    choose_pads(b, blk, nblk, base, npads, pads);
    if (npads && pads[0] == 0xffffffffu)
        return -1;

    place_blocks(b, blk, nblk, base, pads, npads, offs);

    tp->b = b;
    tp->len = len;
    tp->pool_base = base;
    tp->pool_end = base + sum + 4 * npads;
    tp->nclut = nclut;
    tp->nimg = nimg;
    tp->npad = npads;
    tp->tbl_count = cnt;

    /* The igClut records in file order: the ids of the object class are in creation
     * order, so an image's `_pClut` names one of these by rank. */
    {
        static blk_t clut_recs[MAXBLK];
        uint32_t nrec = 0, rank[MAXBLK], nrank = 0;
        for (i = 0; i < nblk; i++)
            if (blk[i].kind == 0)
                clut_recs[nrec++] = blk[i];
        qsort(clut_recs, nrec, sizeof(clut_recs[0]), by_off);
        for (i = 0; i < cnt && nrank < MAXBLK; i++)
            if (rd16(tbl + 2 * i) == tp->obj_class)
                rank[nrank++] = i;   /* ascending, so index == rank */
        if (nrank != nrec)
            return -1;

        for (i = 0; i < nblk && tp->ntex < DW4_TEXPACK_MAXTEX; i++) {
            const blk_t *img = &blk[i];
            const uint8_t *r;
            uint32_t pclut, k, nlen;
            if (img->kind != 1)
                continue;
            r = b + img->off;
            pclut = rd32(r + 68);
            for (k = 0; k < nrank; k++)
                if (rank[k] == pclut)
                    break;
            if (k == nrank)
                return -1;
            nlen = rd32(r + 88);
            if (nlen >= sizeof(name) || img->off + 92 + nlen > len)
                nlen = 0;
            if (nlen)
                memcpy(name, r + 92, nlen);
            name[nlen] = '\0';
            memcpy(tp->tex[tp->ntex].name, name, nlen + 1);
            tp->tex[tp->ntex].image_id = img->id;
            tp->tex[tp->ntex].clut_id = clut_recs[k].id;
            tp->tex[tp->ntex].rec_off = img->off;
            tp->tex[tp->ntex].w = img->w;
            tp->tex[tp->ntex].h = img->h;
            tp->ntex++;
        }
        /* fill the offsets, now that ids are complete */
        for (i = 0; i < tp->ntex; i++) {
            for (j = 0; j < nblk; j++) {
                if (blk[j].id == tp->tex[i].image_id)
                    tp->tex[i].grid_off = offs[j];
                if (blk[j].id == tp->tex[i].clut_id)
                    tp->tex[i].pal_off = offs[j];
            }
        }
    }
    return 0;
}

void dw4_texpack_close(dw4_texpack *tp)
{
    tp->b = NULL;
    tp->ntex = 0;
}

const dw4_texpack_tex *dw4_texpack_find(const dw4_texpack *tp, const char *name)
{
    uint32_t i;
    for (i = 0; i < tp->ntex; i++)
        if (strcmp(tp->tex[i].name, name) == 0)
            return &tp->tex[i];
    /* also accept the stem, so callers need not know about the ".png" suffix */
    for (i = 0; i < tp->ntex; i++) {
        const char *dot = strrchr(tp->tex[i].name, '.');
        if (dot && (size_t)(dot - tp->tex[i].name) == strlen(name) &&
            strncmp(tp->tex[i].name, name, (size_t)(dot - tp->tex[i].name)) == 0)
            return &tp->tex[i];
    }
    return NULL;
}

int dw4_texpack_rgba(const dw4_texpack *tp, uint32_t image_id, uint32_t clut_id,
                     uint8_t *rgba)
{
    const uint8_t *grid = NULL, *pal = NULL;
    uint32_t i, w = 0, h = 0, x, y;

    for (i = 0; i < tp->ntex; i++) {
        if (tp->tex[i].image_id == image_id) {
            grid = tp->b + tp->tex[i].grid_off + 1;
            w = tp->tex[i].w;
            h = tp->tex[i].h;
        }
        if (tp->tex[i].clut_id == clut_id)
            pal = tp->b + tp->tex[i].pal_off;
    }
    if (!grid || !pal || !w || !h)
        return -1;
    if ((size_t)(grid - tp->b) + (size_t)w * h > tp->len ||
        (size_t)(pal - tp->b) + 4 * 256 > tp->len)
        return -1;

    for (y = 0; y < h; y++) {
        const uint8_t *row = grid + (size_t)(h - 1 - y) * w;
        for (x = 0; x < w; x++) {
            const uint8_t *e = pal + 4u * row[x];
            uint8_t *o = rgba + ((size_t)y * w + x) * 4;
            o[0] = e[1];
            o[1] = e[2];
            o[2] = e[3];
            o[3] = e[0];
        }
    }
    return 0;
}
