#include "dw4/gl_layer.h"
/* The title's Option screen: the pack's own window and cursor graphs (see dw4/frontopt.h). */
#include "dw4/frontopt.h"
#include "dw4/scene.h"
#include "dw4/fetext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPT_PART   0              /* NDMW.IGB `_ptNumber` 0 = NDMW.AFS */
#define OPT_ENTRY  806
#define OPT_REF_H  448.0f

struct opt_item {
    uint32_t node, mesh, image;
    int group;                    /* 0 = window, 1 = cursor */
};

struct opt_tex {
    uint32_t id;
    dw4_tex t;
    uint8_t *px;
};

struct dw4_frontopt {
    dw4_gl_layer *gpu;
    dw4_scene sc;
    const dw4_title_host *host;
    struct opt_item *item;
    int nitems, cap;
    struct opt_tex tex[8];
    int ntex;
    uint32_t root[3];             /* j_optionwin02, j_optioncursor11, j_optioncursor12 */
    uint32_t *seqn;               /* every sequenced node under a root, and its root index */
    int *seqg;
    int nseq;
    float t_open;                 /* seconds since the screen opened */
    float p_row;                  /* the cursor's row position, 0..2, easing toward the selection */
};

static const dw4_tex *opt_texture(dw4_frontopt *o, uint32_t image_id)
{
    const dw4_scene_image *im;
    const uint8_t *grid, *pal;
    uint8_t *rgba;
    uint32_t x, y;
    int i;

    if (!image_id)
        return NULL;
    for (i = 0; i < o->ntex; i++)
        if (o->tex[i].id == image_id)
            return &o->tex[i].t;
    if (o->ntex >= (int)(sizeof(o->tex) / sizeof(o->tex[0])))
        return NULL;
    im = dw4_scene_image_of(&o->sc, image_id);
    if (!im || !im->w || !im->h)
        return NULL;
    grid = (const uint8_t *)dw4_scene_host(&o->sc, im->grid);
    pal = (const uint8_t *)dw4_scene_host(&o->sc, im->pal);
    if (!grid || !pal)
        return NULL;
    rgba = (uint8_t *)malloc((size_t)im->w * im->h * 4);
    if (!rgba)
        return NULL;
    for (y = 0; y < im->h; y++)
        for (x = 0; x < im->w; x++) {
            uint32_t k = y * im->bpr + x, pi;

            if (k >= im->size)
                continue;
            pi = (uint32_t)grid[k] * 4u;
            rgba[(y * im->w + x) * 4 + 0] = pal[pi + 0];
            rgba[(y * im->w + x) * 4 + 1] = pal[pi + 1];
            rgba[(y * im->w + x) * 4 + 2] = pal[pi + 2];
            rgba[(y * im->w + x) * 4 + 3] = (uint8_t)(((unsigned)pal[pi + 3] + 1u) >> 1);   /* GS alpha */
        }
    o->tex[o->ntex].id = image_id;
    o->tex[o->ntex].px = rgba;
    o->tex[o->ntex].t.rgba = rgba;
    o->tex[o->ntex].t.w = (int)im->w;
    o->tex[o->ntex].t.h = (int)im->h;
    return &o->tex[o->ntex++].t;
}

static int is_under(const dw4_scene *s, uint32_t node, uint32_t root)
{
    uint32_t guard = 0;

    while (node < s->nnode && guard++ < 64u) {
        if (node == root)
            return 1;
        node = s->node[node].parent;
    }
    return 0;
}

static void opt_add(dw4_frontopt *o, uint32_t node, uint32_t mesh, uint32_t image, int group)
{
    if (o->nitems == o->cap) {
        int nc = o->cap ? o->cap * 2 : 32;
        struct opt_item *g = (struct opt_item *)realloc(o->item, (size_t)nc * sizeof *g);

        if (!g)
            return;
        o->item = g;
        o->cap = nc;
    }
    o->item[o->nitems].node = node;
    o->item[o->nitems].mesh = mesh;
    o->item[o->nitems].image = image;
    o->item[o->nitems].group = group;
    o->nitems++;
}

dw4_frontopt *dw4_frontopt_open(const dw4_mount *mnt)
{
    static const char *const roots[] = { "j_optionwin02", "j_optioncursor11", "j_optioncursor12" };
    dw4_frontopt *o;
    const uint8_t *blob;
    uint32_t size = 0, j;
    int r;

    if (!mnt)
        return NULL;
    o = (dw4_frontopt *)calloc(1, sizeof *o);
    if (!o)
        return NULL;
    o->root[0] = o->root[1] = o->root[2] = 0xFFFFFFFFu;
    blob = dw4_mount_entry(mnt, OPT_PART, OPT_ENTRY, &size, NULL);
    if (!blob || dw4_scene_load(&o->sc, blob, size) != 0) {
        free(o);
        return NULL;
    }
    for (r = 0; r < 3; r++) {
        uint32_t root = 0xFFFFFFFFu;

        for (j = 0; j < o->sc.nnode; j++)
            if (o->sc.node[j].name && strcmp(o->sc.node[j].name, roots[r]) == 0) {
                root = j;
                break;
            }
        o->root[r] = root;
        if (root == 0xFFFFFFFFu)
            continue;
        for (j = 0; j < o->sc.nnode; j++) {
            uint32_t mi = dw4_scene_node_mesh(&o->sc, j);

            if (mi == 0xFFFFFFFFu || !is_under(&o->sc, j, root))
                continue;
            opt_add(o, j, mi, dw4_scene_node_texture(&o->sc, j), r);
        }
    }
    if (!o->nitems) {
        dw4_frontopt_close(o);
        return NULL;
    }
    if (getenv("DW4_OPT_SEQ")) {                  /* probe: every sequenced node of the three roots */
        for (j = 0; j < o->sc.nnode; j++) {
            const dw4_scene_node *n = &o->sc.node[j];
            const long long *t;
            const float *tr, *sc;
            uint32_t k;

            if (!n->has_seq)
                continue;
            {
                int hit = 0;

                for (r = 0; r < o->nitems && !hit; r++)
                    hit = is_under(&o->sc, o->item[r].node, j);
                if (!hit)
                    continue;
            }
            t = (const long long *)n->seq.times;
            tr = (const float *)n->seq.trans;
            sc = (const float *)n->seq.scale;
            printf("  optseq node %4u %-14s keys=%u:", j, n->name ? n->name : "-", n->seq.ntimes);
            for (k = 0; k < n->seq.ntimes && k < 12; k++) {
                printf(" [%.3fs", (double)t[k] / 1e9);
                if (tr && k < n->seq.ntrans)
                    printf(" t(%.0f,%.0f)", (double)tr[3 * k], (double)tr[3 * k + 1]);
                if (sc && k < n->seq.nscale)
                    printf(" s(%.2f,%.2f)", (double)sc[3 * k], (double)sc[3 * k + 1]);
                printf("]");
            }
            printf("\n");
        }
    }
    for (j = 0; j < o->sc.nnode; j++) {
        int g;

        if (!o->sc.node[j].has_seq)
            continue;
        for (g = 0; g < 3; g++)
            if (o->root[g] != 0xFFFFFFFFu && is_under(&o->sc, j, o->root[g])) {
                uint32_t *ns = (uint32_t *)realloc(o->seqn, (size_t)(o->nseq + 1) * sizeof *ns);
                int *gs = (int *)realloc(o->seqg, (size_t)(o->nseq + 1) * sizeof *gs);

                if (!ns || !gs)
                    break;
                o->seqn = ns;
                o->seqg = gs;
                o->seqn[o->nseq] = j;
                o->seqg[o->nseq++] = g;
                break;
            }
    }
    dw4_frontopt_reset(o, 0);
    return o;
}

const char *dw4_frontopt_enable_gpu(dw4_frontopt *o, int w, int h)
{
    if (!o) return NULL;
    dw4_gl_layer_close(o->gpu);
    o->gpu = dw4_gl_layer_open(w, h);
    return dw4_frontopt_gpu_info(o);
}
const char *dw4_frontopt_use_gpu(dw4_frontopt *o, dw4_gl_layer *layer)
{
    if (!o) return NULL;
    dw4_gl_layer_close(o->gpu);
    o->gpu = dw4_gl_layer_share(layer);
    return dw4_frontopt_gpu_info(o);
}
const char *dw4_frontopt_gpu_info(const dw4_frontopt *o)
{
    return o && o->gpu ? dw4_gl_layer_info(o->gpu) : NULL;
}

void dw4_frontopt_close(dw4_frontopt *o)
{
    int i;

    if (!o)
        return;
    dw4_gl_layer_close(o->gpu);
    for (i = 0; i < o->ntex; i++)
        free(o->tex[i].px);
    free(o->item);
    free(o->seqn);
    free(o->seqg);
    dw4_scene_close(&o->sc);
    free(o);
}

void dw4_frontopt_reset(dw4_frontopt *o, int sel)
{
    if (!o)
        return;
    o->t_open = 0.0f;
    o->p_row = (float)sel;
}

/* Put each node group on its own clock.  The three groups run separate windows of the one controller:
 *   window  (j_optionwin02)   the sequence has two passes: 0..1.9 s is a four-slot layout, 1.917..3.833 s a
 *                              three-slot one (bar C parked off-screen, the band without its socket).  The US
 *                              screen shows the second: the bars slide in over 0.75 s and hold;
 *   outline (j_optioncursor11) y = 60 / -10 / -80 for rows 0 / 1 / 2, the slides at 1.167-1.333 s and
 *                              2.667-2.833 s (so row position p maps onto those two windows);
 *   arrows  (j_optioncursor12) y = 60 / -10 on rows 0 / 1 (slides 0.5-0.833 s), parked off-screen for
 *                              the Return row, as in the real screen. */
static void opt_set_clocks(dw4_frontopt *o)
{
    if (o->host) {
        static const int targets[] = {T_j_optionwin02, T_j_optioncursor11, T_j_optioncursor12};
        for (int i = 0; i < o->nseq; ++i) {
            const dw4_title_model *m = dw4_title_host_model(o->host, targets[o->seqg[i]]);
            dw4_scene_node_drive(&o->sc, o->seqn[i], 0.0f, dw4_title_model_time(m));
        }
        dw4_scene_set_engine_time(&o->sc, 0);
        return;
    }
    const float p = o->p_row;
    float t_win = 1.917f + (o->t_open < 1.916f ? o->t_open : 1.916f);   /* the pack's second pass: three slots */
    float t_out, t_arr;
    int i;

    if (p <= 1.0f) {
        t_out = 1.1667f + p * (1.3333f - 1.1667f);          /* row 0 -> 1 */
        t_arr = 0.5f + p * (0.8333f - 0.5f);
    } else if (p < 1.5f) {
        t_out = 2.0f;                                        /* row 1 rest; the caller slides it down */
        t_arr = 1.0f;
    } else {
        t_out = 5.0f;                                        /* the short outline (group32) on the Return pill */
        t_arr = 2.5f;                                        /* arrows parked off to the right */
    }
    for (i = 0; i < o->nseq; i++) {
        float t = o->seqg[i] == 0 ? t_win : (o->seqg[i] == 1 ? t_out : t_arr);

        dw4_scene_node_drive(&o->sc, o->seqn[i], 0.0f, (long long)((double)t * 1e9));
    }
    dw4_scene_set_engine_time(&o->sc, 0);
}

void dw4_frontopt_bind_title(dw4_frontopt *o, const dw4_title_host *h)
{ if (o) o->host = h; }

void dw4_frontopt_draw(dw4_frontopt *o, dw4_fb *fb, int sel, const dw4_fefont *font, int camera_far,
                        int light_hard)
{
    dw4_ui_draw *dl = NULL;
    int ndl = 0, capdl = 0, i;
    const float scale = (float)fb->h / OPT_REF_H, cx = fb->w * 0.5f, cy = fb->h * 0.5f;
    const dw4_tex *fallback = NULL;
    long nc;

    if (!o || !fb)
        return;
    if (!o->host) o->t_open += 1.0f / 60.0f;
    if (!o->host) {   /* legacy standalone preview: ease the row position toward the selection: one row per 10 frames */
        const float step = 1.0f / 10.0f, target = (float)sel;

        if (o->p_row < target - step) o->p_row += step;
        else if (o->p_row > target + step) o->p_row -= step;
        else o->p_row = target;
    }
    opt_set_clocks(o);
    for (i = 0; i < o->nitems && !fallback; i++)
        fallback = opt_texture(o, o->item[i].image);
    for (i = 0; i < o->nitems; i++) {
        const struct opt_item *it = &o->item[i];
        const dw4_scene_mesh *m = &o->sc.mesh[it->mesh];
        const dw4_tex *tex = opt_texture(o, it->image);
        const float *pos = (const float *)dw4_scene_host(&o->sc, m->positions);
        const float *uv = m->uvs.off ? (const float *)dw4_scene_host(&o->sc, m->uvs) : NULL;
        uint32_t *tris = NULL, nt = 0, q;
        const char *why = NULL;
        float wm[16], dy = 0.0f, du = 0.0f, dv = 0.0f;

        if (o->host) {
            static const int targets[] = {T_j_optionwin02, T_j_optioncursor11, T_j_optioncursor12};
            if (!dw4_title_host_model(o->host, targets[it->group])->active) continue;
        }
        if (!pos || dw4_scene_node_world(&o->sc, it->node, wm) != 0)
            continue;
        if (dw4_scene_tris(&o->sc, m, &tris, &nt, &why) != 0)
            continue;
        if (!o->host && it->group != 0 && o->t_open < 0.55f)
            { free(tris); continue; }          /* the cursor appears once the bars are in */
        if (!o->host && it->group != 0 && o->p_row > 1.0f && o->p_row < 1.5f)
            dy = (o->p_row - 1.0f) * -160.0f;   /* row 1 -> the Return row (barD is 160 below barB) */
        if (!o->host && it->group == 2 && o->p_row >= 1.5f)
            { free(tris); continue; }          /* no arrows on the Return row */
        /* The highlight's target-9 transforms scroll the white strip around
         * its outline (NDMW 806 sequence 2701), independently of mesh position. */
        dw4_scene_node_uv_offset(&o->sc, it->node, &du, &dv);
        (void)sel;
        for (q = 0; q < nt; q++) {
            dw4_ui_draw *dd;
            int e, ok = 1;
            float v[3][5];

            for (e = 0; e < 3; e++) {
                uint32_t vi = tris[3 * q + e];
                float lx, ly, lz, X, Y;

                if (vi >= m->num_verts) { ok = 0; break; }
                lx = pos[3 * vi]; ly = pos[3 * vi + 1]; lz = pos[3 * vi + 2];
                X = lx * wm[0] + ly * wm[4] + lz * wm[8] + wm[12];
                Y = ly * wm[5] + lx * wm[1] + lz * wm[9] + wm[13] + dy;
                v[e][0] = cx + X * scale;
                v[e][1] = cy - Y * scale;
                v[e][2] = (uv ? uv[2 * vi] : 0.0f) + du;
                v[e][3] = (uv ? uv[2 * vi + 1] : 0.0f) + dv;
                v[e][4] = 1.0f;
            }
            if (!ok)
                continue;
            if (ndl == capdl) {
                dw4_ui_draw *g = (dw4_ui_draw *)realloc(dl, (size_t)(capdl ? 2 * capdl : 512) * sizeof *dl);

                if (!g)
                    break;
                dl = g;
                capdl = capdl ? 2 * capdl : 512;
            }
            dd = &dl[ndl++];
            memset(dd,0,sizeof *dd);
            dd->tex = tex ? tex : fallback;
            dd->blend = 1;
            dd->stq = 1;
            memcpy(dd->v, v, sizeof dd->v);
            memset(dd->rgba, 128, sizeof dd->rgba);
            if (o->host) {
                int target = it->group == 0 ? T_j_optionwin02 : it->group == 1 ? T_j_optioncursor11 : T_j_optioncursor12;
                int alpha = dw4_title_model_alpha(dw4_title_host_model(o->host, target));
                for (e = 0; e < 3; ++e) dd->rgba[e][3] = (uint8_t)alpha;
            }
        }
        free(tris);
    }
    if (font && font->have && font->atlas && (o->host ? (o->host->text & (1u << 1)) != 0 : o->t_open > 0.5f)) {
        dw4_fetext t;
        static const uint32_t ic_move[2] = { 8801, 8711 }, ic_back[1] = { 8811 }, ic_ok[1] = { 8810 };
        const char *camera = camera_far ? "Far" : "Near", *light = light_hard ? "Hard" : "Soft";
        float box[4], uv[4], adv, wn = 0.0f, cx_val;
        const char *near_s = "Near";
        const char *pc;

        t.dl = &dl; t.n = &ndl; t.cap = &capdl; t.font = font;
        t.atlas.rgba = font->atlas; t.atlas.w = font->aw; t.atlas.h = font->ah;
        t.s = scale; t.cx = cx; t.w640 = 640.0f; t.gs = 0.0f; t.sx = 0.0f;
        /* the legend, top right */
        dw4_fetext_codes(&t, &ic_move[0], 1, 379.9f, 24.0f);
        dw4_fetext_codes(&t, &ic_move[1], 1, 402.9f, 24.0f);
        dw4_fetext_str(&t, "Move Cursor", 431.9f, 24.0f);
        dw4_fetext_codes(&t, ic_back, 1, 379.9f, 53.0f);
        dw4_fetext_str(&t, "Return to Menu", 408.9f, 54.0f);
        dw4_fetext_codes(&t, ic_ok, 1, 379.9f, 83.0f);
        dw4_fetext_str(&t, "Confirm", 408.9f, 84.0f);
        /* the rows: labels and values are centred in their cells */
        dw4_fetext_str(&t, "Dungeon camera", 126.5f, 149.0f);
        dw4_fetext_str(&t, "Light", 192.5f, 219.0f);
        dw4_fetext_str(&t, "Return to Menu", 155.5f, 378.9f);
        /* the value cell's centre: "Near" starts at x = 412.9 on the real screen */
        for (pc = near_s; *pc; pc++)
            if (dw4_fefont_quad(font, (unsigned char)*pc, 0.0f, 0.0f, 1.0f, box, uv, &adv) == 0)
                wn += adv;
        dw4_fefont_quad(font, 'N', 0.0f, 0.0f, 1.0f, box, uv, &adv);
        cx_val = 412.9f - box[0] + wn * 0.5f;
        if (!o->host || (o->host->text & ((1u << 2) | (1u << 3))))
            dw4_fetext_centred(&t, camera, cx_val, 149.0f);
        if (!o->host || (o->host->text & ((1u << 4) | (1u << 5))))
            dw4_fetext_centred(&t, light, cx_val, 219.0f);
    }
    nc = sysconf(_SC_NPROCESSORS_ONLN);
    if (nc > 8)
        nc = 8;
    dw4_render_tex_wrap = 1;
    dw4_render_tex_linear = 1;
    dw4_render_aref = 12;
    dw4_gl_layer_ui_or_cpu(&o->gpu, fb, dl, ndl, (int)nc);
    dw4_render_tex_wrap = 0;
    dw4_render_tex_linear = 0;
    dw4_render_aref = -1;
    free(dl);
}
