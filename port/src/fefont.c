/* dw4/fefont.c -- decode `bectext.igb`'s bitmap font from the disc; see include/dw4/fefont.h. */
#include "dw4/fefont.h"
#include "dw4/gl_layer.h"

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw4/igb.h"
#include "dw4/igfile.h"

/* The font's own unit -> pixels.  The metrics are in arbitrary font units; the atlas is 512x512 and
 * a NORMAL uppercase glyph's texel box is ~14x26 px, which the metrics call 0.15x0.27 units -- so a
 * unit is ~96 px and 1.0 draws the text at the atlas' resolution (calibrated against the live menu
 * capture, boot-contract W1). */
#define DW4_FEFONT_K   96.0f
#define DW4_FEFONT_ENTRY 79u      /* NDMW.AFS entry 79 = bectext.igb (finding #608) */

static uint32_t rec_u32(const dw4_igb_record *r, uint32_t ord, uint32_t def)
{
    uint32_t k;
    for (k = 0; k < r->nvalues; k++)
        if (r->values[k].ordinal == ord)
            return r->values[k].raw;
    return def;
}

static int font_record(const dw4_igb *g, uint32_t id, dw4_igb_record *r)
{
    return id < g->table_n && g->id_kind[id] == 2 &&
        dw4_igb_decode(g, g->id_off[id], r);
}

int dw4_fefont_decode(dw4_fefont *f, const dw4_igb *g, uint32_t id)
{
    dw4_igb_record r = {0};
    uint32_t metrics, texture, image, clut, grid_id, met_id;
    uint32_t px, py, bpr, count, bytes, clut_bytes, metric_bytes;
    const uint8_t *grid, *palette, *met;
    if (!f || !g) return -1;
    memset(f, 0, sizeof(*f));
    if (!font_record(g, id, &r) || strcmp(r.class_name, "beFontImage")) goto bad;
    uint32_t height = rec_u32(&r, 3, 0), baseline = rec_u32(&r, 4, 0);
    memcpy(&f->height, &height, 4); memcpy(&f->baseline, &baseline, 4);
    metrics = rec_u32(&r, 7, UINT32_MAX);
    texture = rec_u32(&r, 8, UINT32_MAX);
    dw4_igb_record_free(&r);
    if (!isfinite(f->height) || f->height <= 0 || !isfinite(f->baseline) ||
        !font_record(g, metrics, &r) || strcmp(r.class_name, "igCharMetricsList")) goto bad;
    count = rec_u32(&r, 2, 0); met_id = rec_u32(&r, 4, UINT32_MAX);
    dw4_igb_record_free(&r);
    if (!font_record(g, texture, &r) || strcmp(r.class_name, "igTextureBindAttr")) goto bad;
    texture = rec_u32(&r, 4, UINT32_MAX); dw4_igb_record_free(&r);
    if (!font_record(g, texture, &r) || strcmp(r.class_name, "igTextureAttr")) goto bad;
    image = rec_u32(&r, 12, UINT32_MAX); dw4_igb_record_free(&r);
    if (!font_record(g, image, &r) || strcmp(r.class_name, "igImage")) goto bad;
    px = rec_u32(&r, 2, 0); py = rec_u32(&r, 3, 0);
    bpr = rec_u32(&r, 19, 0); grid_id = rec_u32(&r, 13, UINT32_MAX);
    clut = rec_u32(&r, 17, UINT32_MAX);
    if (rec_u32(&r, 18, 0) != 8 || rec_u32(&r, 20, 0)) goto bad;
    if (r.name) snprintf(f->name, sizeof(f->name), "%s", r.name);
    dw4_igb_record_free(&r);
    if (!font_record(g, clut, &r) || strcmp(r.class_name, "igClut")) goto bad;
    clut = rec_u32(&r, 5, UINT32_MAX); dw4_igb_record_free(&r);
    grid = dw4_igb_block(g, grid_id, &bytes);
    palette = dw4_igb_block(g, clut, &clut_bytes);
    met = dw4_igb_block(g, met_id, &metric_bytes);
    if (!grid || !palette || !met || !px || !py || px > 8192 || py > 8192 ||
        bpr < px || (uint64_t)bpr * py > bytes || clut_bytes < 1024 ||
        !count || count > metric_bytes / 40 || count > INT_MAX) goto bad;
    f->aw = (int)px; f->ah = (int)py;
    f->atlas = malloc((size_t)px * py * 4);
    f->all = calloc(count ? count : 1, sizeof(*f->all));
    f->allcode = calloc(count ? count : 1, sizeof(*f->allcode));
    if (!f->atlas || !f->all || !f->allcode) goto bad;
    for (uint32_t y = 0; y < py; y++) for (uint32_t x = 0; x < px; x++) {
        const uint8_t *p = palette + 4 * grid[(size_t)y * bpr + x];
        uint8_t *o = f->atlas + 4 * ((size_t)y * px + x);
        memcpy(o, p, 3); o[3] = (p[3] + 1u) >> 1;
    }
    for (uint32_t i = 0; i < count; i++) {
        const uint8_t *e = met + (size_t)i * 40;
        float v[9]; memcpy(v, e + 4, sizeof(v));
        for (unsigned j = 0; j < 9; j++) if (!isfinite(v[j])) goto bad;
        uint32_t code = e[0] | (uint32_t)e[1] << 8;
        dw4_glyph glyph = {v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8]};
        f->all[i] = glyph; f->allcode[i] = code; f->nall++;
        if (code < 256) { f->glyph[code] = glyph; f->nglyph++; }
    }
    f->have = 1;
    return 0;
bad:
    dw4_igb_record_free(&r); dw4_fefont_free(f); return -1;
}

static int load_face(dw4_fefont *f, const uint8_t *blob, size_t size, const char *face)
{
    dw4_igb g = {0}; int rc = -1;
    memset(f, 0, sizeof(*f));
    if (dw4_igb_open(&g, blob, size, 0) || dw4_igb_refs_open(&g)) goto out;
    for (uint32_t id = 0; id < g.table_n; id++) {
        dw4_igb_record r = {0};
        if (!font_record(&g, id, &r)) continue;
        int match = !strcmp(r.class_name, "beFontImage") && r.name && !strcmp(r.name, face);
        dw4_igb_record_free(&r);
        if (match) { rc = dw4_fefont_decode(f, &g, id); break; }
    }
out:
    dw4_igb_close(&g); return rc;
}

int dw4_fefont_load(dw4_fefont *f, const char *roms)
{
    dw4_igfile file = {0};
    char afs[4096];
    int rc;
    memset(f, 0, sizeof(*f));
    snprintf(afs, sizeof afs, "%s/NDMW.AFS", roms);
    if (dw4_igfile_open_afs(&file, afs, DW4_FEFONT_ENTRY)) return -1;
    rc = load_face(f, file.data, file.len, "NORMAL");
    dw4_igfile_close(&file);
    return rc;
}

int dw4_fefont_load_face(dw4_fefont *f, const dw4_mount *mount, const char *face)
{
    uint32_t size;
    const uint8_t *blob = dw4_mount_entry(mount, 0, DW4_FEFONT_ENTRY, &size, NULL);
    memset(f, 0, sizeof(*f));
    return blob && face ? load_face(f, blob, size, face) : -1;
}

void dw4_fefont_free(dw4_fefont *f)
{
    if (!f)
        return;
    free(f->atlas);
    free(f->all);
    free(f->allcode);
    memset(f, 0, sizeof(*f));
}

void dw4_fefont_size(const dw4_fefont *f, const char *text, float scale, float *w, float *h)
{
    float pen = 0.0f, hh = 0.0f;
    const char *s;

    if (w) *w = 0.0f;
    if (h) *h = 0.0f;
    if (!f || !f->have || !text)
        return;
    for (s = text; *s; s++) {
        const dw4_glyph *g = &f->glyph[(unsigned char)*s];
        pen += g->advance * DW4_FEFONT_K * scale;
        if (g->h * DW4_FEFONT_K * scale > hh)
            hh = g->h * DW4_FEFONT_K * scale;
    }
    if (w) *w = pen;
    if (h) *h = hh;
}

int dw4_fefont_draw(dw4_fb *fb, const dw4_fefont *f, float x, float y, float scale,
                    const char *text, const uint8_t rgba[3][4])
{
    dw4_tex tex;
    const char *s;
    float pen = x;
    int drawn = 0;

    if (!fb || !f || !f->have || !f->atlas || !text)
        return 0;
    memset(&tex, 0, sizeof(tex));
    tex.rgba = f->atlas;
    tex.w = f->aw;
    tex.h = f->ah;

    for (s = text; *s; s++) {
        const dw4_glyph *g = &f->glyph[(unsigned char)*s];
        float gw = (g->u1 - g->u0) * f->aw * scale;
        float gh = (g->v1 - g->v0) * f->ah * scale;
        float gx = pen + g->bx * DW4_FEFONT_K * scale;
        float gy = y + g->by * DW4_FEFONT_K * scale;
        float v0[4], v1[4], v2[4], v3[4];

        pen += g->advance * DW4_FEFONT_K * scale;
        if (gw <= 0.0f || gh <= 0.0f)
            continue;
        v0[0] = gx;        v0[1] = gy;        v0[2] = g->u0; v0[3] = g->v1;
        v1[0] = gx + gw;   v1[1] = gy;        v1[2] = g->u1; v1[3] = g->v1;
        v2[0] = gx + gw;   v2[1] = gy + gh;   v2[2] = g->u1; v2[3] = g->v0;
        v3[0] = gx;        v3[1] = gy + gh;   v3[2] = g->u0; v3[3] = g->v0;
        dw4_render_ui_tri(fb, v0, v1, v2, rgba, &tex, 1);
        dw4_render_ui_tri(fb, v0, v2, v3, rgba, &tex, 1);
        drawn++;
    }
    return drawn;
}

const dw4_glyph *dw4_fefont_glyph(const dw4_fefont *f, uint32_t code)
{
    int i;

    if (!f || !f->have)
        return NULL;
    for (i = 0; i < f->nall; i++)
        if (f->allcode[i] == code)
            return &f->all[i];
    return NULL;
}

int dw4_fefont_draw_gpu(dw4_gl_layer *gpu,dw4_fb *fb,const dw4_fefont *f,float x,float y,float scale,
    const char *text,const uint8_t rgba[3][4])
{
    if(!gpu || !fb || !f || !f->have || !f->atlas || !text || !rgba)return -1;
    size_t length=strlen(text);if(!length)return 0;
    if(length>SIZE_MAX/(2*sizeof(dw4_ui_draw)) || length>INT_MAX/2)return -1;
    dw4_ui_draw *draws=calloc(length*2,sizeof *draws);if(!draws)return -1;
    dw4_tex tex={f->atlas,f->aw,f->ah};unsigned count=0;float pen=x;
    for(const unsigned char *s=(const unsigned char *)text;*s;s++){
        const dw4_glyph *g=f->glyph+*s;
        float gw=(g->u1-g->u0)*f->aw*scale,gh=(g->v1-g->v0)*f->ah*scale;
        float gx=pen+g->bx*DW4_FEFONT_K*scale,gy=y+g->by*DW4_FEFONT_K*scale;
        pen+=g->advance*DW4_FEFONT_K*scale;if(gw<=0 || gh<=0)continue;
        float v[4][5]={{gx,gy,g->u0,g->v1,1},{gx+gw,gy,g->u1,g->v1,1},
            {gx+gw,gy+gh,g->u1,g->v0,1},{gx,gy+gh,g->u0,g->v0,1}};
        static const unsigned index[2][3]={{0,1,2},{0,2,3}};
        for(unsigned t=0;t<2;t++){
            dw4_ui_draw *d=draws+count++;d->tex=&tex;d->blend=d->stq=1;d->filter=1;
            for(unsigned i=0;i<3;i++){memcpy(d->v[i],v[index[t][i]],sizeof v[0]);memcpy(d->rgba[i],rgba[i],4);}
        }
    }
    int rc=dw4_gl_layer_ui(gpu,fb,draws,(int)count);free(draws);return rc?-1:(int)count/2;
}

int dw4_fefont_quad(const dw4_fefont *f, uint32_t code, float x, float y, float scale,
                    float box[4], float uv[4], float *advance)
{
    const dw4_glyph *g = dw4_fefont_glyph(f, code);

    if (!g)
        return -1;
    box[0] = x + g->bx * DW4_FEFONT_K * scale;
    box[1] = y + g->by * DW4_FEFONT_K * scale;
    box[2] = box[0] + (g->u1 - g->u0) * f->aw * scale;
    box[3] = box[1] + (g->v1 - g->v0) * f->ah * scale;
    uv[0] = g->u0; uv[1] = g->v0; uv[2] = g->u1; uv[3] = g->v1;
    if (advance)
        *advance = ceilf(g->advance * DW4_FEFONT_K) * scale;   /* the game rounds each advance up to a whole pixel */
    return 0;
}
