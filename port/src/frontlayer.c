/* src/frontlayer.c — the front-end title's generated light-trail layer.  See dw4/frontlayer.h.
 *
 * The whole subsystem is recovered knowledge, not a replay: the graph and the controller live in
 * AREA.AFS entry 620, and the layer has 16 meshes and 3184 triangles.  The pack's own `sback00.png` (an 8bpp `igImage`
 * plus its `igClut`) is the texture; nothing here touches a capture.
 */
#include "dw4/frontlayer.h"
#include "dw4/gpupolicy.h"

#include "dw4/igb.h"
#include "dw4/scene.h"
#include "dw4/gl_layer.h"
#include "dw4/cameratime.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/* The pack's scene entry (the front-end title pack) and the graph the controller drives. */
#define FL_AREA_PART   1          /* NDMW.IGB `_ptNumber` 1 = AREA.AFS (dw4/mount.h) */
#define FL_AREA_ENTRY  620
#define FL_SCENE       "j_startback"
#define FL_TEXTURE     "sback00.png"

/* igImage field ordinals (data/reflection.json): _pImage is the pixel-grid pool block, _pClut the
 * igClut object.  igClut._pData is its palette block.  The grid is 8bpp, `_px * _py` bytes. */
#define IMG_PIMAGE_ORD 13
#define IMG_PCLUT_ORD  17
#define CLUT_PDATA_ORD 5

/* The projection.  The layer is a 3D tunnel (`j_startback`) viewed down its axis, so a world point
 * is taken to view space by the recovered camera's view matrix and projected as
 * `centre + focal * (x, -y) / depth`, with the GS STQ per-pixel divide on the texture.
 *
 * The title's own camera is recovered, not calibrated.  `SETDEMOCAMERA "entry"` selects the
 * `beCameraCtrlInfo`/`igSceneInfo` named `entry` in the title-screen pack (`NDMW.AFS` entry 806),
 * whose `beCameraDemoData._cameraPath` is the `igGraphPath` 2997 over the chain
 * `animCamera01_60 -> cameraanim_GP1 (+600) -> cameraanim_group01 -> cameraanim01 (+130) ->
 * igCamera cameraanimShape01`.  The demo runs for `_totalSec` 1 s but the path is *static*: none of
 * its four `igTransform` nodes carries a `_transformInput` sequence, so `beCameraMode::vfunc_28`'s
 * per-frame `FUN_001c5b30(path, m, nowTimeL)` composes the same matrix at every `_nowTimeL`.  The
 * menu-state pose is therefore the chain's own world -- an ON-AXIS eye at world z = 730 with a
 * ~0.04-degree tilt -- confirmed live (the beCameraMode's view matrix translation is z = -730).  The
 * port composes that chain from the pack; nothing here is calibrated. */
#define FL_FOCAL  622.0f          /* 0.5*448/tan(0.6912/2): the engine's 39.60-deg projection */
#define FL_REF_H  448.0f

/* The recovered camera: the title pack and the named igCamera the demo path ends at. */
#define FL_CAM_PART   0           /* NDMW.IGB `_ptNumber` 0 = NDMW.AFS (dw4/mount.h) */
#define FL_CAM_ENTRY  806
#define FL_CAM_NAME   "cameraanimShape01"

/* The generation rate the controller converts against: JOINTSET start/end are 60 fps frame numbers
 * (`_startTime*1e9/60`). */
#define FL_FRAME_NS 16666666LL    /* floor(1e9/60) */

struct dw4_frontlayer {
    dw4_gl_layer *gpu;
    dw4_scene sc;
    dw4_tex tex;
    uint8_t *tex_px;
    int have_tex;
    /* The layer's own per-node textures.  The pack binds a *different* `igImage` to different
     * meshes (sback00 for the tunnel, logo for the mark, mojips for the panels, cursor for the
     * ticks), so drawing the whole layer with one texture is wrong -- that is what painted the white
     * mark over the centre.  The loader resolves each node's own binding, so they are read from the
     * scene here. */
#define FL_MAXTEX 8
    struct { uint32_t img; dw4_tex tex; uint8_t *px; } *tx;
    int ntx;
    uint32_t gi;                 /* the `j_startback` graph index */
    struct { uint32_t node, mesh; float col[4]; } *item;
    int ncolor;                  /* how many items carry a pack colour */
    int nitems;
    long long engine_ns;
    /* The recovered title camera: the `entry` pack, whether its named igCamera resolved, and the
     * camera's view matrix (world -> view) built from the demo path's own chain. */
    dw4_scene cam;
    int cam_loaded;
    int have_cam;
    float view[16];
    dw4_camera_time camera_time;
    int demo;
};

/* --- the controller schedule -------------------------------------------------------------------
 *
 * `SQ_OPEN` carries a `beAction2JOINTSET 0…209` mode `OS` (one-shot, hold at the end); on its
 * completion `SQ_WAIT`'s `WAIT01` runs `JOINTSET 240…360` mode `LP` (loop).  The ranges are frames,
 * so the node time is `frames * 1e9 / 60` ns.  A loop re-bases the bias by one duration each wrap
 *; here that is the modulo, which needs no per-frame cursor. */
static long long fl_phase(long long e)
{
    const long long open_end = 209LL * 1000000000LL / 60;
    const long long wait_s   = 240LL * 1000000000LL / 60;
    const long long wait_e   = 360LL * 1000000000LL / 60;
    if (e < 0)
        e = 0;
    if (e <= open_end)
        return e;                                   /* SQ_OPEN: one-shot, then hold */
    {
        long long dur = wait_e - wait_s;
        return wait_s + (e - open_end) % dur;        /* SQ_WAIT: loop */
    }
}

/* The `SQ_OPEN` one-shot's length, for the caller that has to wait it out. */
long long dw4_frontlayer_open_ns(void) { return 209LL * 1000000000LL / 60; }

/* --- the pack's own sback00 texture ------------------------------------------------------------ */

static int fl_value(const dw4_igb_record *r, uint32_t ord, uint32_t *out)
{
    uint32_t k;
    for (k = 0; k < r->nvalues; k++)
        if (r->values[k].ordinal == ord) {
            *out = r->values[k].raw;
            return 0;
        }
    return -1;
}

/* igImage palettes store alpha in the host-friendly 0..255 range.  The PS2 upload converts that
 * to the GS's 0..128 fixed-point range (0x80 == 1.0): the ring-f008 texture dump maps every pack
 * alpha exactly as (a + 1) >> 1 (255->128, 73->37, 219->110). */
static uint8_t fl_gs_alpha(uint8_t a)
{
    return (uint8_t)(((unsigned)a + 1u) >> 1);
}

/* Decode `sback00.png` from the pack: its 8bpp grid block through its igClut's palette block.  The
 * palette entry is RGBA in its four bytes (the pairing was verified pixel-for-pixel against the
 * game's own uploaded copy).  Returns 0 on success. */
static int fl_load_texture(dw4_frontlayer *fl, const uint8_t *blob, size_t len)
{
    dw4_igb g;
    uint32_t id, img = 0xFFFFFFFFu, pimage = 0, pclut = 0, pdata = 0;
    const uint8_t *grid = NULL, *pal = NULL;
    uint32_t glen = 0, plen = 0, w = 0, h = 0;
    uint8_t *rgba;

    if (dw4_igb_open(&g, blob, len, 0) != 0)
        return -1;
    if (dw4_igb_refs_open(&g) != 0) {
        dw4_igb_close(&g);
        return -1;
    }
    for (id = 0; id < g.table_n; id++) {
        dw4_igb_record rec;
        uint32_t off, rlen;
        if (dw4_igb_ref(&g, id, &off, &rlen) != 2)
            continue;                                /* an object record, not a block */
        if (dw4_igb_decode(&g, off, &rec) != 1)
            continue;
        if (getenv("DW4_FL_ALLTEX") && rec.class_name && strcmp(rec.class_name, "igImage") == 0 &&
            rec.name) {                              /* probe: dump every igImage in the pack */
            uint32_t pw = 0, ph = 0, ppi = 0, pcl = 0, pd = 0;
            fl_value(&rec, 2, &pw); fl_value(&rec, 3, &ph);
            fl_value(&rec, IMG_PIMAGE_ORD, &ppi); fl_value(&rec, IMG_PCLUT_ORD, &pcl);
            if (ppi && pcl && pw && ph) {
                uint32_t gl2 = 0, pl2 = 0;
                const uint8_t *gr = dw4_igb_block(&g, ppi, &gl2);
                uint32_t o2, r2; dw4_igb_record cr;
                if (dw4_igb_ref(&g, pcl, &o2, &r2) == 2 && dw4_igb_decode(&g, o2, &cr) == 1) {
                    if (cr.class_name && strcmp(cr.class_name, "igClut") == 0)
                        fl_value(&cr, CLUT_PDATA_ORD, &pd);
                    dw4_igb_record_free(&cr);
                }
                const uint8_t *pa = pd ? dw4_igb_block(&g, pd, &pl2) : NULL;
                if (gr && gl2 == (uint64_t)pw * ph && pa && pl2 >= 1024) {
                    char pth[256];
                    snprintf(pth, sizeof pth, "/tmp/tex_%s.ppm", rec.name);
                    FILE *fp = fopen(pth, "wb");
                    if (fp) {
                        uint32_t q2, n2 = pw * ph;
                        fprintf(fp, "P6\n%u %u\n255\n", pw, ph);
                        for (q2 = 0; q2 < n2; q2++) { const uint8_t *e = pa + 4u * gr[q2]; fwrite(e, 1, 3, fp); }
                        fclose(fp);
                        printf("  texdump: %s (%ux%u)\n", pth, pw, ph);
                    }
                }
            }
        }
        if (rec.class_name && strcmp(rec.class_name, "igImage") == 0 &&
            rec.name && strcmp(rec.name, FL_TEXTURE) == 0) {
            img = id;
            if (fl_value(&rec, IMG_PIMAGE_ORD, &pimage) != 0 ||
                fl_value(&rec, IMG_PCLUT_ORD, &pclut) != 0) {
                dw4_igb_record_free(&rec);
                break;
            }
            /* _px / _py are ordinals 2 / 3 */
            fl_value(&rec, 2, &w);
            fl_value(&rec, 3, &h);
            dw4_igb_record_free(&rec);
            break;
        }
        dw4_igb_record_free(&rec);
    }
    if (img == 0xFFFFFFFFu || !pclut) {
        dw4_igb_close(&g);
        return -1;
    }
    grid = dw4_igb_block(&g, pimage, &glen);
    if (!grid || !w || !h || glen != (uint64_t)w * h) {
        dw4_igb_close(&g);
        return -1;
    }
    {   /* the palette: resolve the igClut object's `_pData` block */
        uint32_t off, rlen;
        dw4_igb_record rec;
        if (dw4_igb_ref(&g, pclut, &off, &rlen) == 2 && dw4_igb_decode(&g, off, &rec) == 1) {
            if (rec.class_name && strcmp(rec.class_name, "igClut") == 0)
                fl_value(&rec, CLUT_PDATA_ORD, &pdata);
            dw4_igb_record_free(&rec);
        }
        if (pdata)
            pal = dw4_igb_block(&g, pdata, &plen);
        if (!pal || plen < 256u * 4u) {
            dw4_igb_close(&g);
            return -1;
        }
    }
    rgba = (uint8_t *)malloc((size_t)w * h * 4);
    if (!rgba) {
        dw4_igb_close(&g);
        return -1;
    }
    {   /* the grid is a byte per pixel (top-down), the palette entry is RGBA in its four bytes */
        uint32_t i, n = w * h;
        for (i = 0; i < n; i++) {
            const uint8_t *e = pal + 4u * grid[i];
            rgba[4 * i + 0] = e[0];
            rgba[4 * i + 1] = e[1];
            rgba[4 * i + 2] = e[2];
            rgba[4 * i + 3] = fl_gs_alpha(e[3]);
        }
    }
    dw4_igb_close(&g);
    if (getenv("DW4_FL_TEXDUMP")) {                  /* probe: dump the decoded sback00 texture */
        FILE *fp = fopen("/tmp/sback00.ppm", "wb");
        if (fp) {
            uint32_t i2, n2 = w * h;
            fprintf(fp, "P6\n%u %u\n255\n", w, h);
            for (i2 = 0; i2 < n2; i2++)
                fwrite(rgba + 4 * i2, 1, 3, fp);
            fclose(fp);
            printf("  front-end layer: dumped /tmp/sback00.ppm (%ux%u)\n", w, h);
        }
        /* probe: the alpha plane, so the GS alpha test's fragment alpha can be modelled */
        fp = fopen("/tmp/sback00_alpha.pgm", "wb");
        if (fp) {
            uint32_t i2, n2 = w * h;
            fprintf(fp, "P5\n%u %u\n255\n", w, h);
            for (i2 = 0; i2 < n2; i2++)
                fputc(rgba[4 * i2 + 3], fp);
            fclose(fp);
        }
    }
    fl->tex_px = rgba;
    fl->tex.rgba = rgba;
    fl->tex.w = (int)w;
    fl->tex.h = (int)h;
    fl->have_tex = 1;
    return 0;
}

/* --- the layer's own colour -----------------------------------------------------
 *
 * The pack's `igColorAttr` records (265 of them, all `_color` = 0.9, 0.9, 0.9, 0.95) belong to the
 * 265 *font* attribute sets: `dw4_scene_load` resolves one for `font00`, `font01`, ... and none for
 * the layer's 16 meshes, so this holds for the layer -- its shade is not pack data.  The
 * loader still resolves the colour wherever the pack names one (`dw4_scene_node`, alongside the
 * texture), and this uses it, with `DW4_FL_COLOR=r,g,b,a` (0..1 floats) as an override so the value
 * can be A/B'd against a capture and the earlier neutral shade as the fallback. */
static uint8_t fl_u8(float x)
{
    if (x <= 0.0f)
        return 0;
    if (x >= 1.0f)
        return 255;
    return (uint8_t)(x * 255.0f + 0.5f);
}

/* Fill `out` with the colour a drawn node is shaded with; 1 when it is the pack's own. */
static int fl_node_color(const dw4_frontlayer *fl, uint32_t node, float out[4])
{
    const char *e = getenv("DW4_FL_COLOR");
    float v[4];

    if (e && sscanf(e, "%f,%f,%f,%f", &v[0], &v[1], &v[2], &v[3]) == 4) {
        memcpy(out, v, sizeof v);                  /* an override is the caller's, not the pack's */
        return 0;
    }
    if (node < fl->sc.nnode && fl->sc.node[node].has_color) {
        memcpy(out, fl->sc.node[node].color, sizeof v);
        return 1;
    }
    out[0] = 72.0f / 255.0f; out[1] = 72.0f / 255.0f;
    out[2] = 77.0f / 255.0f; out[3] = 127.0f / 255.0f;
    return 0;
}

/* The layer's per-vertex shade.  The pack gives these meshes no colour (no colour stream, and the
 * only `igColorAttr`s are the fonts'), but the game's vertex colours in the GS stream are not flat: a
 * fit over 4,494 stream vertices matched to the pack's vertices (ring-f008) is
 * `min(1, ambient + diffuse * max(0, N.L))`, in the GS's 0x80 = 1.0 domain (x127.5): ambient
 * (0.5, 0.5, 0.55), directional L = (0.297, 0.414, 0.861) toward the light, diffuse 1.5 x (1, 1, 0.875).
 * RMS error 17 levels, 94 % of vertices within 8.  `DW4_FL_FLATCOLOR=1` restores the old flat grey. */
static void fl_lit_color(const float n[3], uint8_t out[4])
{
    static const float amb[3] = { 0.5f, 0.5f, 0.55f };
    static const float dif[3] = { 1.5f, 1.5f, 1.3125f };
    static const float L[3] = { 0.297f, 0.414f, 0.861f };
    float d = n[0] * L[0] + n[1] * L[1] + n[2] * L[2];
    int k;

    if (d < 0.0f)
        d = 0.0f;
    for (k = 0; k < 3; k++) {
        float c = (amb[k] + dif[k] * d) * 127.5f;
        out[k] = (uint8_t)(c > 127.0f ? 127.0f : c);
    }
    out[3] = 128;
}

/* The draw's blend mode, from the pack's own `igBlendFunctionAttr` (the node's, else its nearest
 * ancestor's).  `_src=4 _dst=1` is `Cs*As + Cd` (GS ALPHA 0x48, mode 2); `_src=4 _dst=5` is ordinary
 * alpha, `(Cs-Cd)*As + Cd` (ALPHA 0x44, mode 1).  A node with no blend attribute -- the tunnel
 * cylinder -- draws with the default ordinary alpha: ring-f008 runs 0-2 are `pCylinderShape3` under
 * ALPHA 0x44.  The pack makes 10 of the 16 layer meshes ordinary and the last 6
 * (`polySurfaceShape101`, `pCubeShape3`, `pCylinderShape6/7/8`, `polySurfaceShape104`) additive;
 * the original draws the layer in that order, so the ordinary meshes cover the tunnel.
 * `DW4_FL_ALLADD=1` restores the old blanket additive blend, to reproduce the before image. */
static uint8_t fl_node_blend(const dw4_frontlayer *fl, uint32_t node, int all_add)
{
    uint32_t src = 0, dst = 0;

    if (all_add)
        return 2;
    if (dw4_scene_node_blend(&fl->sc, node, &src, &dst) && src == 4 && dst == 1)
        return 2;
    return 1;
}

/* Resolve every drawn node's own colour: the pack's `igColorAttr`, resolved by the loader. */
static void fl_colors(dw4_frontlayer *fl)
{
    int i;

    fl->ncolor = 0;
    for (i = 0; i < fl->nitems; i++)
        fl->ncolor += fl_node_color(fl, fl->item[i].node, fl->item[i].col);
}

/* Resolve (and decode, once) every distinct texture the drawn nodes bind.  A node's own binding is
 * the pack's: `dw4_scene_node_texture` returns the `igImage` its nearest `igAttrSet` ancestor binds,
 * and the scene already carries that image's index grid and palette. */
static void fl_textures(dw4_frontlayer *fl)
{
    int i;

    fl->tx = (void *)calloc(FL_MAXTEX, sizeof *fl->tx);
    if (!fl->tx)
        return;
    for (i = 0; i < fl->nitems; i++) {
        uint32_t img = dw4_scene_node_texture(&fl->sc, fl->item[i].node);
        const dw4_scene_image *im;
        const uint8_t *grid, *pal;
        uint8_t *rgba;
        uint32_t n, q, bpr;
        int t;

        if (!img)
            continue;
        for (t = 0; t < fl->ntx; t++)
            if (fl->tx[t].img == img)
                break;
        if (t < fl->ntx || fl->ntx >= FL_MAXTEX)
            continue;
        im = dw4_scene_image_of(&fl->sc, img);
        if (!im || !im->w || !im->h)
            continue;
        grid = (const uint8_t *)dw4_scene_host(&fl->sc, im->grid);
        pal = (const uint8_t *)dw4_scene_host(&fl->sc, im->pal);
        if (!grid || !pal)
            continue;
        rgba = (uint8_t *)malloc((size_t)im->w * im->h * 4);
        if (!rgba)
            continue;
        bpr = im->bpr ? im->bpr : im->w;         /* the index grid may be padded per row */
        n = im->w * im->h;
        for (q = 0; q < n; q++) {
            const uint8_t *e = pal + 4u * grid[(q / im->w) * bpr + (q % im->w)];

            rgba[4 * q + 0] = e[0];
            rgba[4 * q + 1] = e[1];
            rgba[4 * q + 2] = e[2];
            rgba[4 * q + 3] = fl_gs_alpha(e[3]);
        }
        fl->tx[fl->ntx].img = img;
        fl->tx[fl->ntx].px = rgba;
        fl->tx[fl->ntx].tex.rgba = rgba;
        fl->tx[fl->ntx].tex.w = (int)im->w;
        fl->tx[fl->ntx].tex.h = (int)im->h;
        fl->ntx++;
    }
}

/* The texture a drawn node samples: the pack's own binding for it. */
static const dw4_tex *fl_tex_of(const dw4_frontlayer *fl, uint32_t node)
{
    uint32_t img = dw4_scene_node_texture(&fl->sc, node);
    int t;

    for (t = 0; t < fl->ntx; t++)
        if (fl->tx[t].img == img)
            return &fl->tx[t].tex;
    return fl->have_tex ? &fl->tex : NULL;       /* the pack named none: the recovered sback00 */
}

/* --- the layer --------------------------------------------------------------------------------- */

dw4_frontlayer *dw4_frontlayer_open(const dw4_mount *mnt)
{
    dw4_frontlayer *fl;
    const uint8_t *blob;
    uint32_t size = 0, j, k;
    int cap = 0;

    if (!mnt)
        return NULL;
    blob = dw4_mount_entry(mnt, FL_AREA_PART, FL_AREA_ENTRY, &size, NULL);
    if (!blob || !size)
        return NULL;
    fl = (dw4_frontlayer *)calloc(1, sizeof(*fl));
    if (!fl)
        return NULL;
    fl->gi = 0xFFFFFFFFu;
    fl_load_texture(fl, blob, size);                 /* optional: untextured when it fails */
    if (dw4_scene_load(&fl->sc, blob, size) != 0) {
        dw4_frontlayer_close(fl);
        return NULL;
    }
    for (j = 0; j < fl->sc.ngraph; j++)
        if (fl->sc.graph[j].name && strcmp(fl->sc.graph[j].name, FL_SCENE) == 0)
            fl->gi = j;
    if (fl->gi == 0xFFFFFFFFu) {
        dw4_frontlayer_close(fl);
        return NULL;
    }
    /* the drawn geometry: each `igGeometry` node of the graph, with the mesh of the same name */
    if (getenv("DW4_FL_SEQ")) {   /* probe: every sequenced node of the layer, key by key */
        uint32_t d;
        for (d = 0; d < fl->sc.nnode; d++) {
            const dw4_scene_node *q = &fl->sc.node[d];
            uint32_t t;
            if (!q->has_seq)
                continue;
            printf("  seq %-18s %-16s keys=%u", q->name ? q->name : "-",
                   q->class_name ? q->class_name : "-", q->seq.ntimes);
            for (t = 0; t < q->seq.ntimes && t < 8; t++)
                printf(" %.3fs", (double)((const long long *)q->seq.times)[t] / 1e9);
            printf(" | scale=%u", q->seq.nscale);
            for (t = 0; t < q->seq.nscale && t < 6; t++)
                printf(" (%.2f,%.2f,%.2f)", ((const float *)q->seq.scale)[3 * t],
                       ((const float *)q->seq.scale)[3 * t + 1], ((const float *)q->seq.scale)[3 * t + 2]);
            printf("\n");
        }
    }
    for (j = 0; j < fl->sc.nnode; j++) {
        const dw4_scene_node *n = &fl->sc.node[j];
        const dw4_scene_mesh *m = NULL;
        if (n->scene != fl->gi || !n->class_name || strcmp(n->class_name, "igGeometry") != 0)
            continue;
        if (!n->name)
            continue;
        for (k = 0; k < fl->sc.nmesh; k++)
            if (fl->sc.mesh[k].name && strcmp(fl->sc.mesh[k].name, n->name) == 0) {
                m = &fl->sc.mesh[k];
                break;
            }
        if (!m)
            continue;
        if (fl->nitems == cap) {
            void *g;
            cap = cap ? cap * 2 : 32;
            g = realloc(fl->item, (size_t)cap * sizeof(*fl->item));
            if (!g) {
                dw4_frontlayer_close(fl);
                return NULL;
            }
            fl->item = g;
        }
        fl->item[fl->nitems].node = j;
        fl->item[fl->nitems].mesh = (uint32_t)(m - fl->sc.mesh);
        fl->item[fl->nitems].col[0] = 72.0f / 255.0f;
        fl->item[fl->nitems].col[1] = 72.0f / 255.0f;
        fl->item[fl->nitems].col[2] = 77.0f / 255.0f;
        fl->item[fl->nitems].col[3] = 127.0f / 255.0f;
        fl->nitems++;
    }
    if (fl->nitems == 0) {
        dw4_frontlayer_close(fl);
        return NULL;
    }
    /* The layer's own shade: each node's `igColorAttr` in the pack, not a constant. */
    fl_colors(fl);
    printf("  front-end layer: %d mesh(es), %d with the pack's own colour\n", fl->nitems, fl->ncolor);
    /* The layer's own textures: one `igImage` per binding, not sback00 for everything. */
    fl_textures(fl);
    printf("  front-end layer: %d texture(s) bound by the pack\n", fl->ntx);
    /* The recovered camera: the title pack's `entry` camera chain, composed from the pack.  The demo
     * path is static (see the header), so its world is the chain's own -- the menu-state pose.  When
     * the pack or the camera is missing the layer stays un-drawn rather than falling back to a
     * calibrated distance. */
    {
        uint32_t csize = 0;
        const uint8_t *cblob = dw4_mount_entry(mnt, FL_CAM_PART, FL_CAM_ENTRY, &csize, NULL);
        if (cblob && csize && dw4_scene_load(&fl->cam, cblob, csize) == 0) {
            float world[16];
            fl->cam_loaded = 1;
            if (dw4_scene_camera(&fl->cam, FL_CAM_NAME, world, fl->view) >= 0) {
                fl->have_cam = 1;
                printf("  front-end layer camera: '%s' eye (%.2f %.2f %.2f)\n",
                       FL_CAM_NAME, (double)world[12], (double)world[13], (double)world[14]);
            }
            dw4_igb g={0};
            if(!dw4_igb_open(&g,cblob,csize,0) && !dw4_igb_refs_open(&g)) {
                uint32_t demo=UINT32_MAX;
                for(uint32_t i=0;i<g.table_n;i++)if(g.id_kind[i]==2) {
                    dw4_igb_record r={0};
                    if(!dw4_igb_decode(&g,g.id_off[i],&r))continue;
                    if(!strcmp(r.class_name,"beCameraCtrlInfo") && r.name && !strcmp(r.name,"entry"))
                        for(unsigned k=0;k<r.nvalues;k++)if(r.values[k].ordinal==7)demo=r.values[k].raw;
                    dw4_igb_record_free(&r);
                }
                dw4_igb_record r={0};
                if(demo<g.table_n && g.id_kind[demo]==2 &&
                   dw4_igb_decode(&g,g.id_off[demo],&r)) {
                    if(!strcmp(r.class_name,"beCameraDemoData"))
                        for(unsigned k=0;k<r.nvalues;k++)if(r.values[k].ordinal==3) {
                            fl->camera_time.end=r.values[k].raw64;
                            fl->camera_time.loaded=1;
                        }
                    dw4_igb_record_free(&r);
                }
            }
            dw4_igb_close(&g);
        }
        if (!fl->have_cam)
            fprintf(stderr, "  front-end layer camera: '%s' not recovered in NDMW.AFS %d\n",
                    FL_CAM_NAME, FL_CAM_ENTRY);
    }
    return fl;
}
void dw4_frontlayer_camera_tick(dw4_frontlayer *fl,uint64_t ns)
{ if(fl && fl->demo)dw4_camera_time_tick(&fl->camera_time,ns); }
int dw4_frontlayer_camera_service(void *user,const char *method,
    const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_frontlayer *fl=user;
    if(!fl || !fl->have_cam || !fl->camera_time.loaded || n<4 || n>5 ||
       a[3].type!=DW4_SCRIPT_STRING)goto unsupported;
    const char *key=a[3].string;
    if(!strcmp(method,"querySD") && n==4 && !strcmp(key,"ISDEMOCAMERA")) {
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,fl->demo && !fl->camera_time.finished,NULL,0};return 0;
    }
    if(!strcmp(method,"sd")) {
        if(n==5 && !strcmp(key,"SETDEMOCAMERA") && a[4].type==DW4_SCRIPT_STRING &&
           !strcmp(a[4].string,"entry")) {
            uint64_t end=fl->camera_time.end;
            fl->camera_time=(dw4_camera_time){.end=end,.loaded=1};fl->demo=1;return 0;
        }
        if(n==4 && !strcmp(key,"SETBOXCAMERA")){fl->demo=0;return 0;}
        if(n==4 && (!strcmp(key,"ONFREEZE") || !strcmp(key,"OFFREEZE"))) {
            fl->camera_time.frozen=!strcmp(key,"ONFREEZE");return 0;
        }
    }
unsupported:
    snprintf(error,cap,"unsupported title CAMERA %s (requires static entry path)",method);return -1;
}

void dw4_frontlayer_close(dw4_frontlayer *fl)
{
    int t;

    if (!fl)
        return;
    for (t = 0; t < fl->ntx; t++)
        free(fl->tx[t].px);
    dw4_gl_layer_close(fl->gpu);
    free(fl->tx);
    free(fl->item);
    free(fl->tex_px);
    if (fl->cam_loaded)
        dw4_scene_close(&fl->cam);
    dw4_scene_close(&fl->sc);
    free(fl);
}

const char *dw4_frontlayer_enable_gpu(dw4_frontlayer *fl, int w, int h)
{
    if (!fl) return NULL;
    dw4_gl_layer_close(fl->gpu);
    fl->gpu = dw4_gl_layer_open(w, h);
    return fl->gpu ? dw4_gl_layer_info(fl->gpu) : NULL;
}

const char *dw4_frontlayer_use_gpu(dw4_frontlayer *fl, dw4_gl_layer *layer)
{
    if (!fl) return NULL;
    dw4_gl_layer_close(fl->gpu);
    fl->gpu = dw4_gl_layer_share(layer);
    return fl->gpu ? dw4_gl_layer_info(fl->gpu) : NULL;
}

const char *dw4_frontlayer_gpu_info(const dw4_frontlayer *fl)
{
    return fl && fl->gpu ? dw4_gl_layer_info(fl->gpu) : NULL;
}

int dw4_frontlayer_view(const dw4_frontlayer *fl, float view[16], float *focal_per_ref)
{
    if (!fl || !fl->have_cam)
        return -1;
    if (view)
        memcpy(view, fl->view, sizeof(fl->view));
    if (focal_per_ref)
        *focal_per_ref = FL_FOCAL / FL_REF_H;
    return 0;
}

int dw4_frontlayer_meshes(const dw4_frontlayer *fl)
{
    return fl ? fl->nitems : 0;
}

void dw4_frontlayer_set_engine(dw4_frontlayer *fl, long long engine_ns)
{
    long long phase, k;
    uint32_t j;

    if (!fl)
        return;
    {   /* probe: DW4_FL_T=<frame> pins the layer clock (frames at 60 Hz), to compare a capture's time */
        const char *ft = getenv("DW4_FL_T");

        if (ft)
            engine_ns = (long long)atoi(ft) * 1000000000LL / 60;
    }
    fl->engine_ns = engine_ns;
    phase = fl_phase(engine_ns);
    k = (long long)(1.0 * (double)(engine_ns >> 18)) << 18;   /* _timeScale == 1 */
    /* every animated node takes the same JOINTSET window (the controller drives the action's time
     * node and the joints share the clock), so the bias rebases each node's `_time` onto `phase` */
    for (j = 0; j < fl->sc.nnode; j++)
        if (fl->sc.node[j].has_seq)
            dw4_scene_node_drive(&fl->sc, j, 1.0f, phase - k);
    dw4_scene_set_engine_time(&fl->sc, engine_ns);
    if (getenv("DW4_FL_DEBUG")) {                    /* probe: each drawn node's applied world scale
                                                      * and its own sequence keys (the layer's own
                                                      * animation lives on its PARENT groups, so a
                                                      * geometry node normally reports no sequence) */
        int d;
        const float focal0 = FL_FOCAL;   /* reference 640x448, same projection the draw uses */
        for (d = 0; d < fl->nitems; d++) {
            uint32_t nj = fl->item[d].node;
            const dw4_scene_node *n = &fl->sc.node[nj];
            const dw4_scene_mesh *m = &fl->sc.mesh[fl->item[d].mesh];
            float w[16], wx, wy, wz;
            dw4_scene_node_world(&fl->sc, nj, w);
            wx = sqrtf(w[0] * w[0] + w[1] * w[1] + w[2] * w[2]);
            wy = sqrtf(w[4] * w[4] + w[5] * w[5] + w[6] * w[6]);
            wz = sqrtf(w[8] * w[8] + w[9] * w[9] + w[10] * w[10]);
            printf("  fl item %2d node %4u %-20s mesh %-22s world=(%.3f %.3f %.3f) uvs=%d nv=%u ntris=%u\n",
                   d, nj, n->name ? n->name : "?", m->name ? m->name : "?",
                   (double)wx, (double)wy, (double)wz, (int)(m->uvs.off != 0),
                   m->num_verts, m->num_prims);
            {
                uint32_t bs = 0, bd = 0;
                int hb = dw4_scene_node_blend(&fl->sc, nj, &bs, &bd);
                printf("    blend %s src=%u dst=%u\n", hb ? "pack" : "none", bs, bd);
            }
            if (getenv("DW4_FL_STRIPS") && m->lengths.off) {   /* probe: the mesh's strip lengths */
                const uint32_t *ln = (const uint32_t *)dw4_scene_host(&fl->sc, m->lengths);
                uint32_t zi;

                printf("    prim_type=%u num_prims=%u strips(%u):", m->prim_type, m->num_prims, m->num_lengths);
                for (zi = 0; zi < m->num_lengths && zi < 40; zi++)
                    printf(" %u", ln[zi]);
                printf("\n");
            }
            if (getenv("DW4_FL_MAT")) {   /* probe: the full world matrix and the projected screen */
                const float *pos = (const float *)dw4_scene_host(&fl->sc, m->positions);
                const float *vwm = fl->view;
                uint32_t vi;
                float x0 = 1e9f, x1 = -1e9f, y0 = 1e9f, y1 = -1e9f, z0 = 1e9f, z1 = -1e9f;
                printf("      L=[%7.3f %7.3f %7.3f %7.3f | %7.3f %7.3f %7.3f %7.3f | %7.3f %7.3f %7.3f %7.3f | %7.3f %7.3f %7.3f %7.3f]\n",
                       (double)w[0], (double)w[1], (double)w[2], (double)w[3],
                       (double)w[4], (double)w[5], (double)w[6], (double)w[7],
                       (double)w[8], (double)w[9], (double)w[10], (double)w[11],
                       (double)w[12], (double)w[13], (double)w[14], (double)w[15]);
                for (vi = 0; pos && vi < m->num_verts; vi++) {
                    float lx = pos[3 * vi], ly = pos[3 * vi + 1], lz = pos[3 * vi + 2];
                    float X = lx * w[0] + ly * w[4] + lz * w[8] + w[12];
                    float Y = lx * w[1] + ly * w[5] + lz * w[9] + w[13];
                    float Z = lx * w[2] + ly * w[6] + lz * w[10] + w[14];
                    float Xv = X * vwm[0] + Y * vwm[4] + Z * vwm[8] + vwm[12];
                    float Yv = X * vwm[1] + Y * vwm[5] + Z * vwm[9] + vwm[13];
                    float Zv = X * vwm[2] + Y * vwm[6] + Z * vwm[10] + vwm[14];
                    float pz = -Zv < 1.0f ? 1.0f : -Zv;
                    float sx = 320.0f + focal0 * Xv / pz;
                    float sy = 224.0f - focal0 * Yv / pz;
                    if (sx < x0) x0 = sx; if (sx > x1) x1 = sx;
                    if (sy < y0) y0 = sy; if (sy > y1) y1 = sy;
                    if (Zv < z0) z0 = Zv; if (Zv > z1) z1 = Zv;
                }
                if (m->num_verts)
                    printf("      scr x[%.0f,%.0f] y[%.0f,%.0f] viewz[%.1f,%.1f]\n",
                           (double)x0, (double)x1, (double)y0, (double)y1, (double)z0, (double)z1);
            }
        }
        if (getenv("DW4_FL_NODES")) {                /* probe: every node of the layer graph with
                                                      * its own `_m` (placeholder) and parent */
            for (d = 0; d < (int)fl->sc.nnode; d++) {
                const dw4_scene_node *n = &fl->sc.node[d];
                if (n->scene != fl->gi)
                    continue;
                printf("  fl node %4u %-18s %-16s parent=%d depth=%u seq=%d nrot=%u mat=%d",
                       d, n->name ? n->name : "-", n->class_name ? n->class_name : "-",
                       (int)n->parent, n->depth, n->has_seq, n->seq.nrot, n->has_matrix);
                if (n->has_matrix)
                    printf(" _m=[%.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f]",
                           (double)n->m[0], (double)n->m[1], (double)n->m[2], (double)n->m[3],
                           (double)n->m[4], (double)n->m[5], (double)n->m[6], (double)n->m[7],
                           (double)n->m[8], (double)n->m[9], (double)n->m[10], (double)n->m[11],
                           (double)n->m[12], (double)n->m[13], (double)n->m[14], (double)n->m[15]);
                printf("\n");
            }
        }
        for (d = 0; d < (int)fl->sc.nnode; d++) {
            const dw4_scene_node *n = &fl->sc.node[d];
            const dw4_scene_seq *q = &n->seq;
            const int64_t *T = (const int64_t *)q->times;
            const float *S = (const float *)q->scale;
            uint32_t z;
            if (!n->has_seq)
                continue;
            printf("  fl seq node %4u %-20s ntimes=%u ntrans=%u nscale=%u times=", d,
                   n->name ? n->name : "?", q->ntimes, q->ntrans, q->nscale);
            for (z = 0; z < q->ntimes && z < 6; z++)
                printf("%.4f ", (double)T[z] / 1e9);
            printf(" trans=");
            {
                const float *X = (const float *)q->trans;
                for (z = 0; z < q->ntrans && z < 6; z++)
                    printf("(%.4f,%.4f,%.4f) ", (double)X[3 * z], (double)X[3 * z + 1],
                           (double)X[3 * z + 2]);
            }
            printf(" scale=");
            for (z = 0; z < q->nscale && z < 6; z++)
                printf("(%.2f,%.2f,%.2f) ", (double)S[3 * z], (double)S[3 * z + 1],
                       (double)S[3 * z + 2]);
            printf("\n");
        }
    }
}

void dw4_frontlayer_draw(dw4_frontlayer *fl, dw4_fb *fb)
{
    /* The recovered per-draw material state.  The layer's shade is the pack's own: each mesh's
     * `igGeometryAttr1_5` names an `igColorAttr` (`_color` = 0.9, 0.9, 0.9, 0.95 across this pack,
     * ), resolved in `fl_colors`.  The *texture state* is the pack's `sback00.png`,
     * whose alpha the rasteriser already applies.  The blend is per mesh and the pack's own
     * (`fl_node_blend`: additive `_dst=1` for 6 meshes, ordinary alpha otherwise; PRIM ABE=1 IIP=1).  Lighting is off in the pack (`igLightingStateAttr._enabled = 0`), so a per-vertex
     * colour would be flat anyway -- the single pack colour is the whole shade. */
    const int e_nearest = getenv("DW4_FL_NEAREST") != NULL, e_nodepth = getenv("DW4_FL_NODEPTH") != NULL,
              e_clamp = getenv("DW4_FL_CLAMP") != NULL, e_nocyoff = getenv("DW4_FL_NOCYOFF") != NULL,
              e_flatcolor = getenv("DW4_FL_FLATCOLOR") != NULL || getenv("DW4_FL_COLOR") != NULL,
              e_nouvoff = getenv("DW4_FL_NOUVOFF") != NULL, e_noatest = getenv("DW4_FL_NOATEST") != NULL,
              e_mirror = getenv("DW4_FL_MIRROR") != NULL, e_notex = getenv("DW4_FL_NOTEX") != NULL,
              e_noblend = getenv("DW4_FL_NOBLEND") != NULL, e_flat = getenv("DW4_FL_FLAT") != NULL,
              e_cull = getenv("DW4_FL_CULL") != NULL, e_dumpv = getenv("DW4_FL_DUMPV") != NULL,
              e_alladd = getenv("DW4_FL_ALLADD") != NULL, e_nofog = getenv("DW4_FL_NOFOG") != NULL;
    const char *e_far = getenv("DW4_FL_FAR"), *e_sk = getenv("DW4_FL_SKIP"), *e_upto = getenv("DW4_FL_UPTO"),
               *e_only = getenv("DW4_FL_ONLY");
    dw4_layer_draw *dl = NULL;          /* the frame's triangles, drawn once at the end across threads */
    int ndl = 0, capdl = 0;
    const float *vw = fl->view;
    float focal, cx, cy;
    int i;

    if (!fl || !fb || !fl->nitems || !fl->have_cam)
        return;
    {   /* probe: apply the pack's `igAlphaFunctionAttr _refValue` (the GS alpha test) */
        const char *at = getenv("DW4_FL_ALPHATEST");
        dw4_render_alpha_ref = at ? (float)atof(at) : -1.0f;
    }
    dw4_render_tex_linear = e_nearest ? 0 : 1;   /* the layer's TEX1 is linear */
    dw4_render_tex_wrap = e_clamp ? 0 : 1;   /* the layer's CLAMP is REPEAT (WMS = WMT = 0) */
    focal = FL_FOCAL * (float)fb->h / FL_REF_H;
    cx = fb->w * 0.5f;
    /* The GS's vertices sit 0.87 px below the pure projection's centre at 448 lines (measured over 4,494
     * matched ring-f008 vertices: median 0.873, 80 % within 0.81-0.96; dx -0.03). */
    cy = fb->h * 0.5f + (e_nocyoff ? 0.0f : 0.873f * (float)fb->h / 448.0f);
    for (i = 0; i < fl->nitems; i++) {
        uint32_t nj = fl->item[i].node;
        const dw4_scene_mesh *m = &fl->sc.mesh[fl->item[i].mesh];
        uint8_t rgba[3][4];
        {   /* probe: DW4_FL_SKIP=<n> leaves item n out */
            const char *sk = e_sk;

            if (sk && i == atoi(sk))
                continue;
        }
        {   /* probe: DW4_FL_UPTO=<n> draws only the first n items, in draw order */
            const char *upto = e_upto;

            if (upto && i >= atoi(upto))
                continue;
        }
        {   /* probe: DW4_FL_ONLY=<substring> draws one mesh, to attribute a defect to it */
            const char *only = e_only;
            const char *nm = m->name ? m->name : (fl->sc.node[nj].name ? fl->sc.node[nj].name : "");

            if (only && *only && !strstr(nm, only))
                continue;
        }
        const float *pos = (const float *)dw4_scene_host(&fl->sc, m->positions);
        const float *uv = m->uvs.off ? (const float *)dw4_scene_host(&fl->sc, m->uvs) : NULL;
        float uoff = 0.0f, voff = 0.0f;       /* the `_target=9` transform's UV offset */
        int fog_on = 0;
        const float *nrm = m->normals.off ? (const float *)dw4_scene_host(&fl->sc, m->normals) : NULL;
        int lit = nrm && !e_flatcolor &&
                  !(nj < fl->sc.nnode && fl->sc.node[nj].has_color);

        if (!e_nouvoff)
            dw4_scene_node_uv_offset(&fl->sc, nj, &uoff, &voff);
        {   /* the GS fog stage applies where the pack's `igFogStateAttr` is enabled (the cylinder's
             * 'New Object' set; every other layer set has it off) */
            uint32_t fen = 0;

            fog_on = !e_nofog && dw4_scene_node_fog(&fl->sc, nj, &fen) && fen;
        }
        {   /* the GS alpha test: GREATER, AREF = floor(_refValue * 128) from the pack's own
             * `igAlphaFunctionAttr` (0.6 on the tunnel cylinder's set); the engine default is 0.1
             * (the stream's other draws test AREF 12) */
            float ref = 0.1f;

            dw4_scene_node_alpha_ref(&fl->sc, nj, &ref);
            dw4_render_aref = e_noatest ? -1 : (int)floorf(ref * 128.0f);
        }
        /* A mesh with no `_uvs` cannot be sampled: drawing it at u = v = 0 paints the whole face with
         * the texture's texel (0,0) -- a flat block, which is what put the white square over the
         * centre.  Such a mesh is drawn with the vertex colour alone (`tex` NULL). */
        const dw4_tex *mtx = uv ? fl_tex_of(fl, nj) : NULL;
        uint32_t *tris = NULL, nt = 0;
        const char *why = NULL;
        float wm[16];
        uint32_t q;

        if (!pos || dw4_scene_node_world(&fl->sc, nj, wm) != 0)
            continue;
        if (dw4_scene_tris(&fl->sc, m, &tris, &nt, &why) != 0)
            continue;
        {   /* the pack's own colour for this mesh, byte-quantised for the rasteriser */
            int ch;
            for (ch = 0; ch < 3; ch++) {
                rgba[ch][0] = fl_u8(fl->item[i].col[0]);
                rgba[ch][1] = fl_u8(fl->item[i].col[1]);
                rgba[ch][2] = fl_u8(fl->item[i].col[2]);
                rgba[ch][3] = fl_u8(fl->item[i].col[3]);
            }
        }
        for (q = 0; q < nt; q++) {
            float v[3][8];
            uint8_t vc[3][4];
            float vz[3], vf[3];
            int e, ok = 1;
            for (e = 0; e < 3; e++) {
                uint32_t vi = tris[3 * q + e];
                float lx, ly, lz, X, Y, Z, Xv, Yv, Zv, pz, u, vv;
                if (vi >= m->num_verts) {
                    ok = 0;
                    break;
                }
                lx = pos[3 * vi]; ly = pos[3 * vi + 1]; lz = pos[3 * vi + 2];
                X = lx * wm[0] + ly * wm[4] + lz * wm[8] + wm[12];
                Y = lx * wm[1] + ly * wm[5] + lz * wm[9] + wm[13];
                Z = lx * wm[2] + ly * wm[6] + lz * wm[10] + wm[14];
                /* the recovered camera's view matrix (world -> view); the camera looks down -z, so
                 * the view-space depth is -Zv */
                Xv = X * vw[0] + Y * vw[4] + Z * vw[8] + vw[12];
                Yv = X * vw[1] + Y * vw[5] + Z * vw[9] + vw[13];
                Zv = X * vw[2] + Y * vw[6] + Z * vw[10] + vw[14];
                pz = -Zv;
                if (pz < 1.0f)
                    pz = 1.0f;
                {   /* the GS fog coefficient: linear in view depth, near 100 / far 2000, truncated
                     * (an exact fit over 160 distinct stream (depth, F) pairs) */
                    float ff = floorf(255.0f * (2000.0f - pz) / 1900.0f);

                    vf[e] = ff < 0.0f ? 0.0f : (ff > 255.0f ? 255.0f : ff);
                }
                {   /* the GS Z of this vertex: fitted to the stream, z = 6.57e5 / depth - 329.4, larger =
                     * nearer, 0 at the far end */
                    float zf = 657000.0f / pz - 329.4f;

                    vz[e] = zf < 0.0f ? 0.0f : floorf(zf + 0.5f);   /* the GS's Z is an integer */
                }
                if (lit) {                           /* world-space normal -> the layer's lit shade */
                    float nx = nrm[3 * vi], ny = nrm[3 * vi + 1], nz = nrm[3 * vi + 2], wn[3];

                    wn[0] = nx * wm[0] + ny * wm[4] + nz * wm[8];
                    wn[1] = nx * wm[1] + ny * wm[5] + nz * wm[9];
                    wn[2] = nx * wm[2] + ny * wm[6] + nz * wm[10];
                    fl_lit_color(wn, vc[e]);
                }
                /* The layer's texture is sampled u-mirrored.  Straight, the trace meshes
                 * (polySurfaceShape97/98, pCubeShape2) sample v=0.984 across u 0.07..0.49 -- the black
                 * left half of the texture's bottom row -- and paint black, though the game's traces are
                 * the vivid blue at x>=64; the panels land on the wrong art the same way.  Mirrored, the
                 * circuit traces and the panel art both sit on their real texels. */
                u = (uv ? uv[2 * vi] : 0.0f) + uoff;
                vv = (uv ? uv[2 * vi + 1] : 0.0f) + voff;
                if (e_mirror)
                    u = 1.0f - u;                    /* the old u-mirror, for A/B */
                v[e][0] = cx + focal * Xv / pz;
                v[e][1] = cy - focal * Yv / pz;
                v[e][2] = u * pz;                    /* GS STQ: q is the depth, divided per pixel */
                v[e][3] = vv * pz;
                v[e][4] = pz;
                {   /* probe: DW4_FL_DUMPV=<file> appends each projected vertex (mesh, index, screen,
                     * pack UV, model-space normal, view-space normal) for matching to a GS stream */
                    static FILE *dv;
                    const char *dp = e_dumpv ? getenv("DW4_FL_DUMPV") : NULL;

                    if (dp && !dv)
                        dv = fopen(dp, "w");
                    if (dv) {
                        const float *nrm = m->normals.off ? (const float *)dw4_scene_host(&fl->sc, m->normals) : NULL;
                        float nx = nrm ? nrm[3 * vi] : 0.0f, ny = nrm ? nrm[3 * vi + 1] : 0.0f,
                              nz = nrm ? nrm[3 * vi + 2] : 0.0f;
                        float wnx = nx * wm[0] + ny * wm[4] + nz * wm[8];
                        float wny = nx * wm[1] + ny * wm[5] + nz * wm[9];
                        float wnz = nx * wm[2] + ny * wm[6] + nz * wm[10];
                        fprintf(dv, "%s %u %.3f %.3f %.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f %.3f\n",
                                m->name ? m->name : "?", vi, (double)(cx + focal * Xv / pz),
                                (double)(cy - focal * Yv / pz), (double)(uv ? uv[2 * vi] : 0.0f),
                                (double)(uv ? uv[2 * vi + 1] : 0.0f), (double)nx, (double)ny, (double)nz,
                                (double)(wnx * vw[0] + wny * vw[4] + wnz * vw[8]),
                                (double)(wnx * vw[1] + wny * vw[5] + wnz * vw[9]),
                                (double)(wnx * vw[2] + wny * vw[6] + wnz * vw[10]), (double)(-Zv));
                        fflush(dv);
                    }
                }
                v[e][5] = Xv;                        /* probe: the view-space position (back-face cull) */
                v[e][6] = Yv;
                v[e][7] = Zv;
            }
            if (!ok)
                continue;
            {   /* the layer's far clip: the stream omits every primitive with a vertex beyond view depth
                 * 2048 (drawn geometry reaches 2040, omitted polySurfaceShape101 quads start at 2049;
                 * ).  DW4_FL_FAR=<depth> overrides, 0 disables. */
                const char *fe = e_far;
                float far_z = fe ? (float)atof(fe) : 2048.0f;

                if (far_z > 0.0f && (v[0][4] > far_z || v[1][4] > far_z || v[2][4] > far_z))
                    continue;
            }
            {   /* probe: back-face cull in view space (the eye is the view-space origin).
                 * From outside the tube (t<2.583 s) the tunnel's inward-facing wall is a back
                 * face; once group15's +800 z translation puts the eye inside it, it fronts. */
                const char *cf = e_cull ? getenv("DW4_FL_CULL") : NULL;
                if (cf && (*cf == '3' || *cf == '4')) {
                    float e1[3], e2[3], nv[3], cen[3], dot;
                    int ch2;
                    for (ch2 = 0; ch2 < 3; ch2++) {
                        cen[ch2] = (v[0][5 + ch2] + v[1][5 + ch2] + v[2][5 + ch2]) / 3.0f;
                        e1[ch2] = v[1][5 + ch2] - v[0][5 + ch2];
                        e2[ch2] = v[2][5 + ch2] - v[0][5 + ch2];
                    }
                    nv[0] = e1[1] * e2[2] - e1[2] * e2[1];
                    nv[1] = e1[2] * e2[0] - e1[0] * e2[2];
                    nv[2] = e1[0] * e2[1] - e1[1] * e2[0];
                    dot = nv[0] * cen[0] + nv[1] * cen[1] + nv[2] * cen[2];
                    if ((*cf == '3' && dot >= 0.0f) || (*cf == '4' && dot <= 0.0f))
                        continue;
                }
            }
            {   /* probes (task 4C): isolate each material term on the early trace frame.
                 * DW4_FL_NOTEX  -> TME=0 equivalent (no texture sample)
                 * DW4_FL_NOBLEND-> ABE=0 equivalent (opaque, no additive accumulation)
                 * DW4_FL_FLAT   -> IIP=0 equivalent (the first vertex's colour for the face) */
                const dw4_tex *use_tex = e_notex ? NULL : mtx;
                uint8_t use_blend = e_noblend ? 0 : fl_node_blend(fl, nj, e_alladd);
                uint8_t r3[3][4];
                int c2;
                for (c2 = 0; c2 < 3; c2++)
                    memcpy(r3[c2], lit ? vc[e_flat ? 0 : c2] : (e_flat ? rgba[0] : rgba[c2]), 4);
                if (ndl == capdl) {
                    dw4_layer_draw *g = (dw4_layer_draw *)realloc(dl, (size_t)(capdl ? 2 * capdl : 2048) * sizeof *dl);

                    if (!g)
                        continue;
                    dl = g;
                    capdl = capdl ? 2 * capdl : 2048;
                }
                {
                    dw4_layer_draw *dd = &dl[ndl++];

                    /* Reallocated slots contain arbitrary bytes. Keep optional renderer
                     * state at its frontend defaults before filling this triangle. */
                    memset(dd, 0, sizeof *dd);
                    dd->tex = use_tex;
                    dd->blend = use_blend;
                    dd->aref = dw4_render_aref;
                    dd->fog = fog_on;
                    for (c2 = 0; c2 < 3; c2++) {
                        memcpy(dd->v[c2], v[c2], 5 * sizeof(float));
                        memcpy(dd->rgba[c2], r3[c2], 4);
                        dd->f[c2] = vf[c2];
                        dd->z[c2] = e_nodepth ? 1e9f : vz[c2];   /* 1e9 passes GEQUAL against any buffer */
                    }
                }
            }
        }
        free(tris);
    }
    {
        const char *te = getenv("DW4_FL_THREADS");
        long nc = te ? atol(te) : sysconf(_SC_NPROCESSORS_ONLN);

        if (nc > 8)
            nc = 8;                         /* band work stops scaling well past this */
        if (fl->gpu && dw4_gl_layer_draw(fl->gpu, fb, dl, ndl,
                dw4_render_tex_wrap, dw4_render_tex_linear, dw4_render_alpha_ref) < 0) {
            if(dw4_gpu_policy_required())dw4_gpu_policy_fail("title trail draw");
            else {
                fprintf(stderr, "  title trails: GPU draw failed; reverting to CPU\n");
                dw4_gl_layer_close(fl->gpu);
                fl->gpu = NULL;
            }
        }
        if(!fl->gpu && dw4_gpu_policy_required())dw4_gpu_policy_fail("title trail GPU unavailable");
        else if (!fl->gpu){
            if(!e_nodepth)dw4_render_zbuf_clear(fb);
            dw4_render_layer_draws(fb, dl, ndl, (int)nc);
        }
    }
    free(dl);
    dw4_render_tex_wrap = 0;
    dw4_render_tex_linear = 0;
    dw4_render_aref = -1;
}
