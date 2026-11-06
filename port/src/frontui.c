#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"
/* The front-end title's own UI tree (see dw4/frontui.h). */
#include "dw4/frontui.h"
#include "dw4/scene.h"
#include "loadingnode.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define UI_AREA_PART   1          /* NDMW.IGB `_ptNumber` 1 = AREA.AFS */
#define UI_AREA_ENTRY  620
#define UI_REF_H       448.0f     /* the front-end's reference height (one model unit = one pixel) */

/* --- the recovered controller schedule (the pack's own `beAction2` data, AREA.AFS 620) ----------
 *
 * `beNDMWTitle2` drives each UI graph with `MODELCTRL <graph> GENERATE <seq>`, the
 * same mechanism `j_startback` uses.  Each graph's action-2 `OPEN`/`CLOSE` step carries a
 * `beAction2JOINTSET` (a *time range* in 60 fps frames -> `frames*1e9/60` ns) and a
 * `beAction2FADESET` (its fade time, in frames).  Recovered per graph (scripts/modelctrl_dump.py):
 *
 *   j_startlogo    OPEN  JOINTSET  0..30 'OS'   FADESET IN 10 frames, CLOSE FADESET OUT 30 frames
 *   j_startmenu01  OPEN  JOINTSET  0..15 'OS'   FADESET IN  1 frame,  CLOSE FADESET OUT  1 frame
 *   j_startmenu02  OPEN  JOINTSET  0..15 'OS'   FADESET IN  1 frame,  CLOSE FADESET OUT  1 frame
 *                  row steps: LINEON00 110..125, LINEDW01 50..70, LINEUP00 80..100, LINEON01 170..185
 *
 * A node's `_time` advances with the engine clock and is rebased onto the window;
 * `OS` clamps at `_endTime`.  The `select` node of `j_startmenu02` is the moving row
 * indicator: its sequence keys map `y` -60 (LINEDW01 start) -> -84 -> -108 (down) and the reverse
 * (LINEUP00), so the two rest positions are samples of that one sequence.
 */
#define UI_FRAME_NS    16666666LL                 /* floor(1e9/60) */
#define UI_OPEN_LOGO   (30LL * 1000000000LL / 60) /* j_startlogo   OPEN JOINTSET 0..30 OS -> ns */
#define UI_OPEN_MENU   (15LL * 1000000000LL / 60) /* j_startmenu01/02 OPEN JOINTSET 0..15 OS -> ns */
#define UI_FADE_IN_LOGO  (10LL * 1000000000LL / 60)   /* beAction2FADESET IN fadeTime 10 frames */
#define UI_FADE_IN_MENU  ( 1LL * 1000000000LL / 60)
#define UI_FADE_OUT_LOGO (30LL * 1000000000LL / 60)   /* beAction2FADESET OUT fadeTime 30 frames */
#define UI_FADE_OUT_MENU ( 1LL * 1000000000LL / 60)
/* the recovered row-selection windows (j_startmenu02 `select`, sequence 747) */
#define UI_SEL_DOWN_S  ( 50LL * 1000000000LL / 60)    /* LINEDW01 JOINTSET  50..70 OS -> y -60..-108 */
#define UI_SEL_DOWN_E  ( 70LL * 1000000000LL / 60)
#define UI_SEL_UP_S    ( 80LL * 1000000000LL / 60)    /* LINEUP00 JOINTSET  80..100 OS -> y -108..-60 */
#define UI_SEL_UP_E    (100LL * 1000000000LL / 60)
#define UI_SEL_ROW0_T  (250000000LL)                  /* seq 747 at 0.250 s: y = -60, scale (1,1,1) */
#define UI_SEL_ROW1_T  (1166666666LL)                 /* seq 747 at 1.1667 s: y = -108 */

struct ui_item {
    uint32_t node;
    uint32_t mesh;
    uint32_t image;
    float z;
    int row;                      /* 0 = the `start` row, 1 = the `menu` row, -1 = decor/logo */
};

struct ui_tex {
    uint32_t id;
    dw4_tex t;
    uint8_t *px;
    const char *name;
};

struct dw4_frontui {
    void (*observe)(void *,const dw4_ui_draw *,size_t);
    void *observe_user;
    int card, card_alpha;
    int loading;
    uint8_t load_initial[128], load_state[128];
    Dw4SystemClockApi load_api;
    dw4_gl_layer *gpu;
    dw4_scene sc;
    const dw4_title_host *host;
    struct ui_item *item;
    int nitems, cap;
    struct ui_tex tex[8];
    int ntex;
    int logo_item;
    uint32_t g_logo, g_menu1, g_menu2;   /* the three UI graph indices (or 0xFFFFFFFF) */
    uint32_t sel_node;                   /* the j_startmenu02 `select` node, or 0xFFFFFFFF */
    long long open_ns;                   /* when OPEN began (0) */
    long long close_ns;                  /* when CLOSE began, or -1 */
    long long menu_ns;                   /* when START advanced to the menu, or -1 */
    int state;                           /* DW4_FRONTUI_PRESS_START / DW4_FRONTUI_MENU */
    long long engine_ns;
    long long sel_start;                 /* engine ns at which the current transition began */
    int sel_dir;                         /* +1 down, -1 up, 0 resting */
    int cur_sel, prev_sel;
};

static const char *UI_SCENES[] = { "j_startlogo", "j_startmenu01", "j_startmenu02" };
void dw4_frontui_observe_draws(dw4_frontui *ui,void (*observe)(void *,const dw4_ui_draw *,size_t),void *user)
{if(ui){ui->observe=observe;ui->observe_user=user;}}

static void ui_add_item(dw4_frontui *ui, uint32_t node, uint32_t mesh, uint32_t image, int row)
{
    struct ui_item *d;
    float wm[16];
    if (ui->nitems == ui->cap) {
        int nc = ui->cap ? ui->cap * 2 : 16;
        d = (struct ui_item *)realloc(ui->item, (size_t)nc * sizeof(*d));
        if (!d)
            return;
        ui->item = d;
        ui->cap = nc;
    }
    d = &ui->item[ui->nitems];
    d->node = node;
    d->mesh = mesh;
    d->image = image;
    d->row = row;
    d->z = 0.0f;
    if (dw4_scene_node_world(&ui->sc, node, wm) == 0) {
        /* Loading cards store depth in mesh positions, not node translation. */
        const dw4_scene_mesh *m = &ui->sc.mesh[mesh];
        const float *pos = dw4_scene_host(&ui->sc, m->positions);
        double sum = 0;
        if (pos && m->num_verts) {
            for (uint32_t i = 0; i < m->num_verts; ++i)
                sum += pos[i*3]*wm[2] + pos[i*3+1]*wm[6] + pos[i*3+2]*wm[10] + wm[14];
            d->z = (float)(sum / m->num_verts);
        } else d->z = wm[14];
    }
    ui->nitems++;
}

static const dw4_tex *ui_texture(dw4_frontui *ui, uint32_t image_id)
{
    const dw4_scene_image *im;
    const uint8_t *grid, *pal;
    uint8_t *rgba;
    uint32_t x, y;
    int i;

    if (!image_id)
        return NULL;
    im = dw4_scene_image_of(&ui->sc, image_id);
    /* Authored bindings identify images, not names. The two mojips.png records
     * differ: copyright and menu quads each need their own rasterized atlas. */
    for (i = 0; i < ui->ntex; i++) {
        if (ui->tex[i].id == image_id)
            return &ui->tex[i].t;
    }
    if (ui->ntex >= (int)(sizeof(ui->tex) / sizeof(ui->tex[0])))
        return NULL;
    if (!im || !im->w || !im->h)
        return NULL;
    grid = (const uint8_t *)dw4_scene_host(&ui->sc, im->grid);
    pal = (const uint8_t *)dw4_scene_host(&ui->sc, im->pal);
    if (!grid || !pal)
        return NULL;
    rgba = (uint8_t *)malloc((size_t)im->w * im->h * 4);
    if (!rgba)
        return NULL;
    /* the pack stores the index grid top-down, one byte per pixel, `_bytesPerRow` wide; the palette
     * entry is RGBA in its four bytes (the pairing the sback00 decode already verified). */
    for (y = 0; y < im->h; y++)
        for (x = 0; x < im->w; x++) {
            uint32_t k = y * im->bpr + x, pi;
            if (k >= im->size)
                continue;
            pi = (uint32_t)grid[k] * 4u;
            rgba[(y * im->w + x) * 4 + 0] = pal[pi + 0];
            rgba[(y * im->w + x) * 4 + 1] = pal[pi + 1];
            rgba[(y * im->w + x) * 4 + 2] = pal[pi + 2];
            /* the palette's alpha is 0..255; the GS holds it as 0..128 (0x80 == 1.0), which the PCSX2
             * texture dump shows is exactly (a + 1) >> 1.  Without it every
             * soft edge and the band's partial alpha clamped to opaque. */
            rgba[(y * im->w + x) * 4 + 3] = (uint8_t)(((unsigned)pal[pi + 3] + 1u) >> 1);
        }
    {
        struct ui_tex *s = &ui->tex[ui->ntex++];
        s->id = image_id;
        s->px = rgba;
        s->t.rgba = rgba;
        s->t.w = (int)im->w;
        s->t.h = (int)im->h;
        s->name = im->name;
    }
    return &ui->tex[ui->ntex - 1].t;
}

/* The `select` node of `j_startmenu02` — the moving row indicator, whose sequence carries the
 * y -60/-108 rest positions.  Identified by graph + name + a `_transformInput` sequence. */
static uint32_t ui_find_selector(dw4_frontui *ui, uint32_t gi)
{
    uint32_t j, end;
    if (gi == 0xFFFFFFFFu)
        return 0xFFFFFFFFu;
    end = ui->sc.graph[gi].node + ui->sc.graph[gi].nnodes;
    for (j = ui->sc.graph[gi].node; j < end && j < ui->sc.nnode; j++) {
        const dw4_scene_node *n = &ui->sc.node[j];
        if (n->scene == gi && n->has_seq && n->name && strcmp(n->name, "select") == 0)
            return j;
    }
    return 0xFFFFFFFFu;
}

dw4_frontui *dw4_frontui_open(const dw4_mount *mnt)
{
    dw4_frontui *ui;
    const uint8_t *blob;
    uint32_t size = 0;
    unsigned s;
    int i;

    if (!mnt)
        return NULL;
    ui = (dw4_frontui *)calloc(1, sizeof(*ui));
    if (!ui)
        return NULL;
    ui->logo_item = -1;
    ui->g_logo = ui->g_menu1 = ui->g_menu2 = 0xFFFFFFFFu;
    ui->sel_node = 0xFFFFFFFFu;
    ui->close_ns = -1;
    ui->menu_ns = -1;
    ui->state = DW4_FRONTUI_PRESS_START;
    ui->prev_sel = -1;
    blob = dw4_mount_entry(mnt, UI_AREA_PART, UI_AREA_ENTRY, &size, NULL);
    if (!blob || dw4_scene_load(&ui->sc, blob, size) != 0) {
        free(ui);
        return NULL;
    }
    for (s = 0; s < sizeof(UI_SCENES) / sizeof(UI_SCENES[0]); s++) {
        uint32_t gi = 0xFFFFFFFFu, j;
        for (j = 0; j < ui->sc.ngraph; j++)
            if (ui->sc.graph[j].name && strcmp(ui->sc.graph[j].name, UI_SCENES[s]) == 0)
                gi = j;
        if (s == 0) ui->g_logo = gi;
        else if (s == 1) ui->g_menu1 = gi;
        else ui->g_menu2 = gi;
        if (gi == 0xFFFFFFFFu)
            continue;
        {
            uint32_t end = ui->sc.graph[gi].node + ui->sc.graph[gi].nnodes;
            for (j = ui->sc.graph[gi].node; j < end && j < ui->sc.nnode; j++) {
                uint32_t mi = dw4_scene_node_mesh(&ui->sc, j);
                uint32_t ti = dw4_scene_node_texture(&ui->sc, j);
                const dw4_scene_node *n = &ui->sc.node[j];
                const char *pn = (n->parent < ui->sc.nnode && ui->sc.node[n->parent].name)
                                     ? ui->sc.node[n->parent].name : (n->name ? n->name : "");
                int row = -1;
                if (mi == 0xFFFFFFFFu || !ti)
                    continue;
                if (strcmp(pn, "start") == 0)
                    row = 0;
                else if (strcmp(pn, "menu") == 0)
                    row = 1;
                ui_add_item(ui, j, mi, ti, row);
                if (strcmp(pn, "rogo") == 0)
                    ui->logo_item = ui->nitems - 1;
            }
        }
    }
    if (!ui->nitems) {
        dw4_frontui_close(ui);
        return NULL;
    }
    ui->sel_node = ui_find_selector(ui, ui->g_menu2);
    /* Resolve every item's texture eagerly, so the diagnostic and the verifier report the real
     * resolved set (logo.png / mojips.png / cursor.png) rather than a lazy-load zero. */
    for (i = 0; i < ui->nitems; i++)
        ui_texture(ui, ui->item[i].image);
    return ui;
}

/* Boot cards reuse the same material/geometry path as the title UI. A model can
 * be a named graph or a named subtree inside the stage's window graph. */
dw4_frontui *dw4_frontui_open_card(const dw4_mount *mnt, int part, int entry,
                                  const char *model)
{
    uint32_t size = 0, first = UINT32_MAX, end = 0, j;
    const uint8_t *blob = dw4_mount_entry(mnt, part, entry, &size, NULL);
    dw4_frontui *ui = calloc(1, sizeof(*ui));
    if (!ui) return NULL;
    ui->card = 1; ui->card_alpha = 128; ui->logo_item = -1;
    ui->g_logo = ui->g_menu1 = ui->g_menu2 = ui->sel_node = UINT32_MAX;
    if (!blob || dw4_scene_load(&ui->sc, blob, size)) { free(ui); return NULL; }
    for (j = 0; j < ui->sc.ngraph; ++j)
        if (ui->sc.graph[j].name && !strcmp(ui->sc.graph[j].name, model)) {
            first = ui->sc.graph[j].node; end = first + ui->sc.graph[j].nnodes; break;
        }
    if (first == UINT32_MAX) {
        for (j = 0; j < ui->sc.nnode; ++j)
            if (ui->sc.node[j].name && !strcmp(ui->sc.node[j].name, model)) {
                first = j; end = j + 1;
                while (end < ui->sc.nnode) {
                    uint32_t parent = ui->sc.node[end].parent;
                    while (parent < ui->sc.nnode && parent != first)
                        parent = ui->sc.node[parent].parent;
                    if (parent != first) break;
                    ++end;
                }
                break;
            }
    }
    for (j = first; j < end && j < ui->sc.nnode; ++j) {
        uint32_t mesh = dw4_scene_node_mesh(&ui->sc, j);
        uint32_t image = dw4_scene_node_texture(&ui->sc, j);
        if (mesh != UINT32_MAX && image) {
            ui_add_item(ui, j, mesh, image, -1); ui_texture(ui, image);
        }
    }
    if (!ui->nitems) { dw4_frontui_close(ui); return NULL; }
    return ui;
}

void dw4_frontui_card_sample(dw4_frontui *ui, int joint_frame, int alpha)
{
    if (!ui || !ui->card) return;
    ui->card_alpha = alpha < 0 ? 0 : alpha > 128 ? 128 : alpha;
    dw4_scene_set_time(&ui->sc, joint_frame * (1000000000.0 / 60.0));
}

static uint64_t loading_read(void *user, uint32_t address, unsigned width)
{
    dw4_frontui *ui = user;
    uint64_t v = 0;
    if (address >= 0x1000 && address + width <= 0x1080)
        memcpy(&v, ui->load_state + address - 0x1000, width);
    return v;
}
static void loading_write(void *user, uint32_t address, unsigned width, uint64_t value)
{
    dw4_frontui *ui = user;
    if (address >= 0x1000 && address + width <= 0x1080)
        memcpy(ui->load_state + address - 0x1000, &value, width);
}

/* The retail FileListInfoManager removes "st", inserts "ld", appends ".igb"
 * and prefixes "loadingUSA/". The stage argument is the bare retail stage id. */
dw4_frontui *dw4_frontui_open_loading(const dw4_mount *mnt, const char *stage)
{
    char path[128];
    if (!stage || strlen(stage) < 2 || strlen(stage) > 100) return NULL;
    snprintf(path, sizeof path, "loadingUSA/ld%s.igb", stage+2);
    const dw4_manifest_file *asset = dw4_manifest_find(&mnt->man, path);
    if (!asset) return NULL;
    dw4_frontui *ui = dw4_frontui_open_card(mnt, asset->pt, asset->entry, "LOADING");
    if (!ui) return NULL;
    uint32_t size;
    const uint8_t *blob = dw4_mount_entry(mnt, asset->pt, asset->entry, &size, NULL);
    dw4_igb g;
    if (dw4_igb_open(&g, blob, size, 0)) { dw4_frontui_close(ui); return NULL; }
    /* Runtime offsets from beNodeAnim/beLoadingNode reflection. Serialized
     * ordinals include all inherited fields, unlike the reflection own-field view. */
    for (uint32_t p = dw4_igb_find_chain(&g, 0x800);;) {
        dw4_igb_record r;
        if (!dw4_igb_decode(&g, p, &r)) break;
        if (!strcmp(r.class_name, "beLoadingNode")) {
            static const unsigned offset[] = {0x20,0x28,0x30,0x38,0x40,0x48,0x50,0x58,0x60,0x68,0x70,0x78};
            for (uint32_t i = 0; i < r.nvalues; ++i) {
                const dw4_igb_value *v = &r.values[i];
                if (v->ordinal >= 8 && v->ordinal <= 19) {
                    unsigned width = v->ordinal == 12 ? 1 : v->ordinal == 14 ? 4 : 8;
                    uint64_t value = width == 8 ? v->raw64 : v->raw;
                    memcpy(ui->load_initial + offset[v->ordinal-8], &value, width);
                }
            }
            ui->loading = 1;
        }
        p = r.end; dw4_igb_record_free(&r);
    }
    dw4_igb_close(&g);
    uint64_t loop_end = 0; memcpy(&loop_end, ui->load_initial+0x30, 8);
    /* A destination whose card has no beLoadingNode (stagML14, stagIS07/09/10/20: the 9,639-byte plain cards) is a still image: keep it as a card with
     * no loading clock, ready at once, rather than falling back to the plain "Now Loading" text. */
    if (!ui->loading || (int64_t)loop_end <= 0) { ui->loading = 0; return ui; }
    memcpy(ui->load_state, ui->load_initial, sizeof ui->load_state);
    ui->load_api = (Dw4SystemClockApi){ui, loading_read, loading_write, NULL};
    return ui;
}
void dw4_frontui_loading_sample(dw4_frontui *ui, uint64_t now)
{
    if (!ui || !ui->loading) return;
    if (!now) memcpy(ui->load_state, ui->load_initial, sizeof ui->load_state);
    if (loading_read(ui, 0x1040, 1)) {
        dw4_loadingnode_call(&ui->load_api, 0x39a960, 0x1000, loading_read(ui,0x1020,8), now);
        loading_write(ui,0x1060,8,now); loading_write(ui,0x1040,1,0);
    }
    uint64_t t = dw4_loadingnode_call(&ui->load_api, 0x39a9e0, 0x1000, now, 0);
    dw4_scene_set_time(&ui->sc, (double)(int64_t)t);
}
void dw4_frontui_loading_lock(dw4_frontui *ui)
{
    if (ui && ui->loading) dw4_loadingnode_call(&ui->load_api,0x39adf0,0x1000,0,0);
}
int dw4_frontui_loading_ready(dw4_frontui *ui)
{
    return !ui || !ui->loading || dw4_loadingnode_call(&ui->load_api,0x39ae00,0x1000,0,0);
}

const char *dw4_frontui_enable_gpu(dw4_frontui *ui, int w, int h)
{
    if (!ui) return NULL;
    dw4_gl_layer_close(ui->gpu);
    ui->gpu = dw4_gl_layer_open(w, h);
    return dw4_frontui_gpu_info(ui);
}
const char *dw4_frontui_use_gpu(dw4_frontui *ui, dw4_gl_layer *layer)
{
    if (!ui) return NULL;
    dw4_gl_layer_close(ui->gpu);
    ui->gpu = dw4_gl_layer_share(layer);
    return dw4_frontui_gpu_info(ui);
}
const char *dw4_frontui_gpu_info(const dw4_frontui *ui)
{
    return ui && ui->gpu ? dw4_gl_layer_info(ui->gpu) : NULL;
}
int dw4_frontui_clear(dw4_frontui *ui,dw4_fb *fb,uint8_t r,uint8_t g,uint8_t b)
{
    if(!ui || !fb)return -1;
    if(ui->gpu){if(!dw4_gl_layer_clear(ui->gpu,fb,r,g,b,255))return 0;}
    else if(!dw4_gpu_policy_required()){dw4_fb_clear(fb,r,g,b);return 0;}
    dw4_gpu_policy_fail("front-end card clear");return -1;
}

void dw4_frontui_close(dw4_frontui *ui)
{
    int i;
    if (!ui)
        return;
    for (i = 0; i < ui->ntex; i++) {
        dw4_gl_layer_texture_forget(ui->gpu, &ui->tex[i].t);   /* a card allocated at this address next would draw this atlas */
        free(ui->tex[i].px);
    }
    dw4_gl_layer_close(ui->gpu);
    free(ui->item);
    dw4_scene_close(&ui->sc);
    free(ui);
}

int dw4_frontui_items(const dw4_frontui *ui) { return ui ? ui->nitems : 0; }
int dw4_frontui_textures(const dw4_frontui *ui) { return ui ? ui->ntex : 0; }

int dw4_frontui_state(const dw4_frontui *ui)
{
    return ui ? ui->state : DW4_FRONTUI_PRESS_START;
}

void dw4_frontui_start(dw4_frontui *ui, long long engine_ns)
{
    if (!ui || ui->state != DW4_FRONTUI_PRESS_START)
        return;
    ui->state = DW4_FRONTUI_MENU;
    ui->menu_ns = engine_ns < 0 ? 0 : engine_ns;
}

void dw4_frontui_bind_title(dw4_frontui *ui, const dw4_title_host *host)
{
    if (ui) ui->host = host;
}
static const dw4_title_model *host_graph(const dw4_frontui *ui, uint32_t gi)
{
    return ui->host ? dw4_title_host_model(ui->host,
        gi == ui->g_logo ? T_j_startlogo : gi == ui->g_menu1 ? T_j_startmenu01 : T_j_startmenu02) : NULL;
}

/* Whether an item of graph `gi` is drawn in the current state: the logo/copyright always, the
 * press-start line only before START, the Game Start/Option rows only after. */
static int ui_item_visible(const dw4_frontui *ui, uint32_t gi)
{
    if (ui->card) return 1;
    if (ui->host) return host_graph(ui, gi)->active;
    if (gi == ui->g_menu1)
        return ui->state == DW4_FRONTUI_PRESS_START;
    if (gi == ui->g_menu2)
        return ui->state == DW4_FRONTUI_MENU;
    return 1;
}

int dw4_frontui_visible(const dw4_frontui *ui)
{
    int i, n = 0;
    if (!ui)
        return 0;
    for (i = 0; i < ui->nitems; i++)
        if (ui_item_visible(ui, ui->sc.node[ui->item[i].node].scene))
            n++;
    return n;
}

const char *dw4_frontui_texture_at(const dw4_frontui *ui, int i)
{
    if (!ui || i < 0 || i >= ui->ntex)
        return NULL;
    return ui->tex[i].name;
}

const char *dw4_frontui_logo_texture(const dw4_frontui *ui)
{
    const dw4_scene_image *im;
    if (!ui || ui->logo_item < 0)
        return NULL;
    im = dw4_scene_image_of(&ui->sc, ui->item[ui->logo_item].image);
    return im ? im->name : NULL;
}

/* The rows' own timeline (j_startmenu02) begins when START advanced to the menu; before that the
 * absolute engine time (they are hidden in the press-start state anyway). */
static long long ui_menu_time(const dw4_frontui *ui, long long e)
{
    if (ui->menu_ns < 0)
        return e;
    return e > ui->menu_ns ? e - ui->menu_ns : 0;
}

/* The selector's local time: the recovered rest key for the current row, or the advancing window of
 * the recovered move while a transition is in flight (LINEDW01 down / LINEUP00 up). */
static long long ui_sel_time(const dw4_frontui *ui, long long e)
{
    if (ui->sel_dir > 0) {
        long long t = UI_SEL_DOWN_S + (e - ui->sel_start);
        return t > UI_SEL_DOWN_E ? UI_SEL_DOWN_E : (t < UI_SEL_DOWN_S ? UI_SEL_DOWN_S : t);
    }
    if (ui->sel_dir < 0) {
        long long t = UI_SEL_UP_S + (e - ui->sel_start);
        return t > UI_SEL_UP_E ? UI_SEL_UP_E : (t < UI_SEL_UP_S ? UI_SEL_UP_S : t);
    }
    return ui->cur_sel == 0 ? UI_SEL_ROW0_T : UI_SEL_ROW1_T;
}

void dw4_frontui_set_engine(dw4_frontui *ui, long long engine_ns)
{
    long long e, k;
    uint32_t j;

    if (!ui)
        return;
    e = engine_ns < 0 ? 0 : engine_ns;
    ui->engine_ns = e;
    if (ui->host) {
        ui->state = ui->host->ctrl._st0 <= 1 ? DW4_FRONTUI_PRESS_START : DW4_FRONTUI_MENU;
        k = (long long)(1.0 * (double)(e >> 18)) << 18;
        for (j = 0; j < ui->sc.nnode; ++j) {
            dw4_scene_node *n = &ui->sc.node[j];
            if (!n->has_seq || (n->scene != ui->g_logo && n->scene != ui->g_menu1 && n->scene != ui->g_menu2)) continue;
            dw4_scene_node_drive(&ui->sc, j, 1.0f, dw4_title_model_time(host_graph(ui, n->scene)) - k);
        }
        dw4_scene_set_engine_time(&ui->sc, e);
        return;
    }
    /* a transition that has reached its window's end becomes the new rest */
    if (ui->sel_dir > 0 && e - ui->sel_start >= UI_SEL_DOWN_E - UI_SEL_DOWN_S)
        ui->sel_dir = 0;
    if (ui->sel_dir < 0 && e - ui->sel_start >= UI_SEL_UP_E - UI_SEL_UP_S)
        ui->sel_dir = 0;
    k = (long long)(1.0 * (double)(e >> 18)) << 18;   /* _timeScale == 1 */
    for (j = 0; j < ui->sc.nnode; j++) {
        dw4_scene_node *n = &ui->sc.node[j];
        long long t, te;
        if (!n->has_seq)
            continue;
        if (n->scene != ui->g_logo && n->scene != ui->g_menu1 && n->scene != ui->g_menu2)
            continue;                       /* not a title-UI node */
        /* the Game Start/Option rows start their own OPEN when START was pressed */
        te = (n->scene == ui->g_menu2) ? ui_menu_time(ui, e) : e;
        if (j == ui->sel_node) {
            /* during OPEN the selector plays the graph's pop-in; afterwards it is the row indicator */
            if (te < UI_OPEN_MENU && ui->sel_dir == 0)
                t = te;
            else
                t = ui_sel_time(ui, te);
        } else if (n->scene == ui->g_logo) {
            t = te < UI_OPEN_LOGO ? te : UI_OPEN_LOGO;  /* OPEN JOINTSET 0..30 'OS' */
        } else {
            t = te < UI_OPEN_MENU ? te : UI_OPEN_MENU;  /* OPEN JOINTSET 0..15 'OS' */
        }
        dw4_scene_node_drive(&ui->sc, j, 1.0f, t - k);
    }
    dw4_scene_set_engine_time(&ui->sc, e);
}

void dw4_frontui_begin_close(dw4_frontui *ui, long long engine_ns)
{
    if (!ui || ui->close_ns >= 0)
        return;
    ui->close_ns = engine_ns < 0 ? 0 : engine_ns;
}

int dw4_frontui_closing(const dw4_frontui *ui)
{
    if (!ui || ui->close_ns < 0)
        return 0;
    return ui->engine_ns - ui->close_ns < UI_FADE_OUT_LOGO;
}

int dw4_frontui_alpha(const dw4_frontui *ui)
{
    long long t;
    if (!ui || ui->close_ns < 0)
        return 255;
    t = ui->engine_ns - ui->close_ns;
    if (t >= UI_FADE_OUT_LOGO)
        return 0;
    return (int)(255 - 255 * t / UI_FADE_OUT_LOGO);
}

/* The recovered FADESET alpha for a graph, in 0..128 (the renderer's per-vertex colour, where 128
 * is identity): the OPEN fade in, or the CLOSE fade out once `dw4_frontui_begin_close` was called. */
static int ui_graph_alpha(const dw4_frontui *ui, uint32_t gi)
{
    if (ui->card) return ui->card_alpha;
    long long fin = (gi == ui->g_logo) ? UI_FADE_IN_LOGO : UI_FADE_IN_MENU;
    long long fout = (gi == ui->g_logo) ? UI_FADE_OUT_LOGO : UI_FADE_OUT_MENU;
    long long t;
    if (ui->close_ns >= 0) {
        t = ui->engine_ns - ui->close_ns;
        if (t >= fout || fout <= 0)
            return 0;
        return (int)(128 - 128 * t / fout);
    }
    t = ui->engine_ns - ui->open_ns;
    if (fin <= 0 || t >= fin)
        return 128;
    if (t < 0)
        t = 0;
    return (int)(128 * t / fin);
}

/* the logo quad's projected rectangle at `fb`'s size */
int dw4_frontui_logo_rect(const dw4_frontui *ui, const dw4_fb *fb, float rect[4])
{
    const struct ui_item *it;
    const dw4_scene_mesh *m;
    const float *pos;
    float wm[16], scale, sx, cx, cy, x0 = 1e9f, y0 = 1e9f, x1 = -1e9f, y1 = -1e9f;
    uint32_t v;

    if (!ui || !fb || ui->logo_item < 0)
        return -1;
    it = &ui->item[ui->logo_item];
    m = &ui->sc.mesh[it->mesh];
    pos = (const float *)dw4_scene_host(&ui->sc, m->positions);
    if (!pos || dw4_scene_node_world(&ui->sc, it->node, wm) != 0)
        return -1;
    scale = (float)fb->h / UI_REF_H;
    sx = ui->card ? scale : (float)fb->w / 640.0f;
    cx = fb->w * 0.5f;
    cy = fb->h * 0.5f;
    for (v = 0; v < m->num_verts; v++) {
        float lx = pos[3 * v], ly = pos[3 * v + 1], lz = pos[3 * v + 2];
        float X = lx * wm[0] + ly * wm[4] + lz * wm[8] + wm[12];
        float Y = lx * wm[1] + ly * wm[5] + lz * wm[9] + wm[13];
        float px = cx + X * sx, sy = cy - Y * scale;
        if (px < x0) x0 = px;
        if (px > x1) x1 = px;
        if (sy < y0) y0 = sy;
        if (sy > y1) y1 = sy;
    }
    rect[0] = x0; rect[1] = y0; rect[2] = x1; rect[3] = y1;
    return 0;
}

static int item_cmp(const void *a, const void *b)
{
    const struct ui_item *x = (const struct ui_item *)a, *y = (const struct ui_item *)b;
    if (x->z < y->z) return -1;          /* smaller z = farther = drawn first */
    if (x->z > y->z) return 1;
    return 0;
}

int dw4_frontui_draw(dw4_frontui *ui, dw4_fb *fb, int selected)
{
    struct ui_item *sorted;
    dw4_ui_draw *dl = NULL;       /* the frame's triangles, drawn once at the end across threads */
    int ndl = 0, capdl = 0;
    int i, drawn = 0;
    float scale, cx, cy;

    if (!ui || !fb || !ui->nitems)
        return 0;
    /* a selection change plays the recovered transition (the pack's own `select` indicator); the
     * rows only exist in the menu state */
    if (!ui->host && ui->state == DW4_FRONTUI_MENU && selected >= 0 && selected != ui->prev_sel) {
        if (ui->prev_sel >= 0 && ui->sel_node != 0xFFFFFFFFu) {
            ui->sel_dir = (selected > ui->prev_sel) ? 1 : -1;
            ui->sel_start = ui_menu_time(ui, ui->engine_ns);
        }
        ui->prev_sel = selected;
    }
    ui->cur_sel = selected >= 0 ? selected : (ui->prev_sel >= 0 ? ui->prev_sel : 0);
    scale = (float)fb->h / UI_REF_H;
    cx = fb->w * 0.5f;
    cy = fb->h * 0.5f;
    sorted = (struct ui_item *)malloc((size_t)ui->nitems * sizeof(*sorted));
    if (!sorted)
        return 0;
    memcpy(sorted, ui->item, (size_t)ui->nitems * sizeof(*sorted));
    qsort(sorted, (size_t)ui->nitems, sizeof(*sorted), item_cmp);
    for (i = 0; i < ui->nitems; i++) {
        const struct ui_item *it = &sorted[i];
        const dw4_scene_mesh *m = &ui->sc.mesh[it->mesh];
        const dw4_tex *tex;
        const float *pos;
        const float *uv;
        uint32_t *tris = NULL, nt = 0, q;
        const char *why = NULL;
        float wm[16], du = 0, dv = 0;
        uint8_t col[3][4];
        int a8;
        uint8_t blend = 1;

        /* the press-start line and the Game Start/Option rows are mutually exclusive states */
        if (!ui_item_visible(ui, ui->sc.node[it->node].scene))
            continue;
        tex = ui_texture(ui, it->image);
        pos = (const float *)dw4_scene_host(&ui->sc, m->positions);
        uv = m->uvs.off ? (const float *)dw4_scene_host(&ui->sc, m->uvs) : NULL;
        a8 = ui->host ? dw4_title_model_alpha(host_graph(ui, ui->sc.node[it->node].scene)) :
             ui_graph_alpha(ui, ui->sc.node[it->node].scene);

        /* The UI's material set carries only a texture. Retail title draws
         * use a neutral 127 RGB multiplier; FADESET controls the alpha. */
        for (q = 0; q < 4; q++)
            col[0][q] = col[1][q] = col[2][q] = 128;
        /* Settled retail title UI uses neutral 127/127/127, alpha 128.
         * Boot/loading cards retain their independently validated material. */
        if(!ui->card)for(q=0;q<3;q++)col[0][q]=col[1][q]=col[2][q]=127;
        col[0][3] = col[1][3] = col[2][3] = (uint8_t)a8;
        if (!pos || dw4_scene_node_world(&ui->sc, it->node, wm) != 0)
            continue;
        if (ui->card) {
            uint32_t src = 0, dst = 0;
            dw4_scene_node_uv_offset(&ui->sc, it->node, &du, &dv);
            /* The loading atlas has additive hexagon traces and edge lights. */
            if (dw4_scene_node_blend(&ui->sc, it->node, &src, &dst) && src == 4 && dst == 1)
                blend = 2;
        }
        if (dw4_scene_tris(&ui->sc, m, &tris, &nt, &why) != 0)
            continue;
        for (q = 0; q < nt; q++) {
            float v[3][5];
            int e, ok = 1;
            for (e = 0; e < 3; e++) {
                uint32_t vi = tris[3 * q + e];
                float lx, ly, lz, X, Y;
                if (vi >= m->num_verts) { ok = 0; break; }
                lx = pos[3 * vi]; ly = pos[3 * vi + 1]; lz = pos[3 * vi + 2];
                X = lx * wm[0] + ly * wm[4] + lz * wm[8] + wm[12];
                Y = lx * wm[1] + ly * wm[5] + lz * wm[9] + wm[13];
                v[e][0] = cx + X * (ui->card ? scale : (float)fb->w / 640.0f);
                v[e][1] = cy - Y * scale;
                v[e][2] = uv ? uv[2 * vi] + du : 0.0f;
                v[e][3] = uv ? uv[2 * vi + 1] + dv : 0.0f;
                v[e][4] = 1.0f;
            }
            if (!ok)
                continue;
            if (ndl == capdl) {
                dw4_ui_draw *g = (dw4_ui_draw *)realloc(dl, (size_t)(capdl ? 2 * capdl : 256) * sizeof *dl);

                if (!g)
                    continue;
                dl = g;
                capdl = capdl ? 2 * capdl : 256;
            }
            {
                dw4_ui_draw *dd = &dl[ndl++];

                memset(dd,0,sizeof *dd);
                dd->tex = tex;
                dd->blend = blend;
                dd->stq = 1;
                memcpy(dd->v, v, sizeof dd->v);
                memcpy(dd->rgba, col, sizeof dd->rgba);
            }
            drawn++;
        }
        free(tris);
    }
    free(sorted);
    {
        const char *te = getenv("DW4_UI_THREADS");
        long nc = te ? atol(te) : sysconf(_SC_NPROCESSORS_ONLN);

        if (nc > 8)
            nc = 8;
        /* the title's UI draws run with the same GS state as the layer's: TEX1 linear, CLAMP REPEAT
         * (WMS = WMT = 0), AREF 12, ALPHA 0x44, vertex colour 1.0 (the post-flash title dump) */
        if (!getenv("DW4_UI_PLAIN")) {
            dw4_render_tex_wrap = 1;
            dw4_render_tex_linear = 1;
            dw4_render_aref = 12;
        }
        if(ui->observe)ui->observe(ui->observe_user,dl,(size_t)ndl);
        dw4_gl_layer_ui_or_cpu(&ui->gpu, fb, dl, ndl, (int)nc);   /* Preserve material and painter order. */
        dw4_render_tex_wrap = 0;
        dw4_render_tex_linear = 0;
        dw4_render_aref = -1;
    }
    free(dl);
    return drawn;
}
