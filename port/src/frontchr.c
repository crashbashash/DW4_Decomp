#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"
/* The Game Start slot screen: the pack's own graphs (see dw4/frontchr.h). */
#include "dw4/frontchr.h"
#include "dw4/scene.h"
#include "dw4/igb.h"
#include "dw4/actoranim.h"
#include "dw4/fontlayout.h"
#include "dw4/fronttext.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHR_PART   0              /* NDMW.IGB `_ptNumber` 0 = NDMW.AFS */
#define CHR_ENTRY  806
#define CHR_REF_H  448.0f

/* Approximate timings from the 30 fps PS2 reference: 5 frames out,
 * 8 frames clear, 5 frames in. Keep these separate from the idle clip clock. */
#define CHR_FADE_OUT (1.0f / 6.0f)
#define CHR_FADE_IN_START (13.0f / 30.0f)
#define CHR_FADE_END (18.0f / 30.0f)

enum { L_PANELS, L_MESSWIN, L_LINEWIN, L_FACE, L_LEFT, L_RIGHT, L_FRAME, L_KEYBOARD, L_NAMEWIN, L_STATUS, L_MODE_CURSOR, L_KEY_CURSOR, L_KEY_LEFT, L_KEY_RIGHT, L_KEY_UP, L_KEY_DOWN, L_COUNT };

static const char *const layer_name[L_COUNT] = { "M01", "j_chrselmesswin", "j_linewin02", "j_digifacewin", "N01", "j_digiselcursorright", "j_namewin02", "j_namecursorus", "j_namewin01", "j_mainstatuswin", "j_namecursor01", "j_namecursor02", "j_namecursorleft", "j_namecursorright", "j_namecursorup", "j_namecursordown" };

struct chr_item {
    uint32_t node, mesh, image;
    int layer;
    int slot;                     /* panels: which of the four (0 = panel 1) */
    int ping;                     /* the window pointer's selection ping (group5), drawn only just after a move */
};

struct chr_tex {
    uint32_t id;
    dw4_tex t;
    uint8_t *px;
};

/* Summary rows live in the title's localized FontTree, not the model pack.
 * Keep the immutable authored transforms after decoding; glyphs use MINIMUM. */
struct summary_font { float matrix[16], width; };

struct dw4_frontchr {
    dw4_gl_layer *gpu,*portrait_gpu;
    int portrait_w,portrait_h;
    void (*sound_action)(void *, const char *, const char *);
    void *sound_user;
    void (*observe)(void *, const dw4_ui_draw *, size_t);
    void *observe_user;
    dw4_fefont minimum;
    dw4_tex minimum_atlas;
    dw4_tex summary_labels;
    struct summary_font summary[7];
    dw4_fronttext *text;int text_call;
    dw4_scene sc;
    int species;                 /* -1: Create/Call menu; 0..3: species preview */
    int outgoing;
    unsigned long long outgoing_frame;
    float change_t, outgoing_alpha;
    float name_cursor_t;         /* one-shot nudge, only restarted by letter selection */
    int phase, key_mode, key, key_first, name_length, confirm_no;
    char name[DW4_CHR_NAME_MAX + 1];
    int name_mode[DW4_CHR_NAME_MAX],name_key[DW4_CHR_NAME_MAX],name_first[DW4_CHR_NAME_MAX];
    int logging_in, login_frame;
    float ambient[3], diffuse[3], light_dir[3];
    uint32_t actor[4];
    dw4_actoranim *animation[4];
    unsigned long long actor_frame;
    uint32_t bg_root;
    unsigned long long bg_frame;
    struct chr_item *item;
    int nitems, cap;
    struct chr_tex tex[32];
    int ntex;
    uint32_t root[L_COUNT];
    uint32_t *seqn;               /* every sequenced node under a root, and its layer */
    int *seqg;
    int nseq;
    float t[L_COUNT];             /* each layer's own clock, seconds */
    float spin;                   /* the panels' bolt loop clock, seconds */
    int sel_prev;                 /* the highlighted row last frame */
    float sel_t;                  /* seconds since the highlight arrived */
};

static int chr_summary_load(dw4_frontchr *o,const dw4_mount *mnt)
{
    static const char *const group[7]={"CHRSELFONT03","CHRSELFONT04","CHRSELFONT04",
        "CHRSELFONT05","CHRSELFONT05","CHRSELFONT05","CHRSELFONT05"};
    static const char *const name[7]={"font000","font000","font010","font000","font001","font010","font011"};
    dw4_scene scene={0};dw4_igb g={0};uint32_t size,found=0;
    const uint8_t *blob=dw4_mount_data(mnt,"stagIS10/separate/USA_pack.igb",&size);
    if(!blob || dw4_scene_load(&scene,blob,size) || dw4_igb_open(&g,blob,size,0) ||
       dw4_igb_refs_open(&g) || dw4_fefont_load_face(&o->minimum,mnt,"MINIMUM"))goto bad;
    for(uint32_t id=0;id<g.table_n;id++)if(g.id_kind[id]==2){
        dw4_igb_record r={0};if(!dw4_igb_decode(&g,g.id_off[id],&r))goto bad;
        if(!strcmp(r.class_name,"beFontInfoData") && r.name){
            uint32_t attr=UINT32_MAX,width=0;
            for(unsigned k=0;k<r.nvalues;k++){
                if(r.values[k].ordinal==4)attr=r.values[k].raw;
                if(r.values[k].ordinal==7)width=r.values[k].raw;
            }
            for(unsigned k=0;k<7;k++)if(!strcmp(r.name,group[k])){
                for(unsigned j=0;j<scene.nnode;j++)if(scene.node[j].id==attr &&
                    scene.node[j].name && !strcmp(scene.node[j].name,name[k])){
                    /* The attr's first child is the font geometry transform. */
                    if(j+1>=scene.nnode || scene.node[j+1].parent!=j ||
                       dw4_scene_node_world(&scene,j+1,o->summary[k].matrix)){
                        dw4_igb_record_free(&r);goto bad;
                    }
                    memcpy(&o->summary[k].width,&width,4);
                    if(!isfinite(o->summary[k].width) || o->summary[k].width<=0){
                        dw4_igb_record_free(&r);goto bad;
                    }
                    found|=1u<<k;break;
                }
            }
        }
        dw4_igb_record_free(&r);
    }
    if(found!=127)goto bad;
    /* beTextureCtrlAttr names the localized atlas in another pack. Its
     * model geometry already supplies the Lv/HP/MP quads and their UVs. */
    for(uint32_t id=0;id<g.table_n;id++)if(g.id_kind[id]==2){
        dw4_igb_record r={0};if(!dw4_igb_decode(&g,g.id_off[id],&r))goto bad;
        if(!strcmp(r.class_name,"igImage") && r.name && !strcmp(r.name,"moji.png")){
            uint32_t w=0,h=0,bpr=0,grid_id=UINT32_MAX,clut=UINT32_MAX,bits=0;
            for(unsigned k=0;k<r.nvalues;k++){
                const dw4_igb_value *v=r.values+k;
                if(v->ordinal==2)w=v->raw;
                if(v->ordinal==3)h=v->raw;
                if(v->ordinal==13)grid_id=v->raw;
                if(v->ordinal==17)clut=v->raw;
                if(v->ordinal==18)bits=v->raw;
                if(v->ordinal==19)bpr=v->raw;
            }
            dw4_igb_record_free(&r);
            if(clut>=g.table_n || g.id_kind[clut]!=2 ||
               !dw4_igb_decode(&g,g.id_off[clut],&r))goto bad;
            if(strcmp(r.class_name,"igClut")){dw4_igb_record_free(&r);goto bad;}
            uint32_t pal_id=UINT32_MAX;
            for(unsigned k=0;k<r.nvalues;k++)if(r.values[k].ordinal==5)pal_id=r.values[k].raw;
            dw4_igb_record_free(&r);
            uint32_t grid_size,pal_size;
            const uint8_t *grid=dw4_igb_block(&g,grid_id,&grid_size),*pal=dw4_igb_block(&g,pal_id,&pal_size);
            if(!grid || !pal || !w || !h || w>8192 || h>8192 || bpr<w || bits!=8 ||
               (uint64_t)bpr*h>grid_size || pal_size<1024)goto bad;
            uint8_t *rgba=malloc((size_t)w*h*4);if(!rgba)goto bad;
            for(uint32_t y=0;y<h;y++)for(uint32_t x=0;x<w;x++){
                const uint8_t *p=pal+4*grid[y*bpr+x];uint8_t *q=rgba+4*(y*w+x);
                memcpy(q,p,3);q[3]=(p[3]+1u)>>1;
            }
            o->summary_labels=(dw4_tex){.rgba=rgba,.w=w,.h=h};break;
        }
        dw4_igb_record_free(&r);
    }
    if(!o->summary_labels.rgba)goto bad;
    o->minimum_atlas=(dw4_tex){.rgba=o->minimum.atlas,.w=o->minimum.aw,.h=o->minimum.ah};
    dw4_igb_close(&g);dw4_scene_close(&scene);return 0;
bad:
    dw4_igb_close(&g);dw4_scene_close(&scene);return -1;
}

static int chr_summary_text(dw4_frontchr *o,dw4_ui_draw **draw,int *count,int *cap,
    unsigned row,const char *text,int align,unsigned width,unsigned height)
{
    uint32_t codes[64];size_t n=0,nv=0;dw4_font_vertex *v=NULL;
    while(*text && n<64)codes[n++]=(unsigned char)*text++;
    const struct summary_font *f=o->summary+row;const float *m=f->matrix;
    if(dw4_fontlayout_build(&o->minimum,codes,n,f->width,align,&v,&nv))return -1;
    if(*count+(int)(nv/3)>*cap){
        int capacity=*count+(int)(nv/3);dw4_ui_draw *p=realloc(*draw,(size_t)capacity*sizeof(*p));
        if(!p){free(v);return -1;}*draw=p;*cap=capacity;
    }
    for(size_t i=0;i<nv;i+=3){
        dw4_ui_draw *d=*draw+(*count)++;memset(d,0,sizeof(*d));
        d->tex=&o->minimum_atlas;d->blend=d->stq=d->gs_raster=1;d->filter=1;
        for(unsigned k=0;k<3;k++){
            const dw4_font_vertex *p=v+i+k;
            float x=p->x*m[0]+p->y*m[4]+m[12],y=p->x*m[1]+p->y*m[5]+m[13];
            d->v[k][0]=(320+100*x)*width/640.0f;d->v[k][1]=(224-100*y)*height/448.0f;
            d->v[k][2]=p->u;d->v[k][3]=p->v;d->v[k][4]=1;
            memset(d->rgba[k],114,3);d->rgba[k][3]=121;
        }
    }
    free(v);return 0;
}

static const dw4_tex *chr_texture(dw4_frontchr *o, uint32_t image_id)
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
    if (getenv("DW4_CHR_GRID") && image_id == 4142) {
        for (y = 0; y < im->h; y++) {
            for (x = 0; x < im->w; x++)
                printf("%3u ", grid[y * im->bpr + x]);
            printf("\n");
        }
    }
    if (getenv("DW4_CHR_SEQ")) {
        unsigned amax = 0, k2;

        for (k2 = 0; k2 < 256; k2++)
            if (pal[k2 * 4 + 3] > amax) amax = pal[k2 * 4 + 3];
        { unsigned rm = 0, gm = 0, bm = 0;
            for (k2 = 0; k2 < 256; k2++) { if (pal[k2*4] > rm) rm = pal[k2*4]; if (pal[k2*4+1] > gm) gm = pal[k2*4+1]; if (pal[k2*4+2] > bm) bm = pal[k2*4+2]; }
            if (getenv("DW4_CHR_PAL")) for (k2 = 0; k2 < 256; k2++) { if (pal[k2*4+3]) printf("   pal%u[%u]=%u,%u,%u,%u\n", image_id, k2, pal[k2*4], pal[k2*4+1], pal[k2*4+2], pal[k2*4+3]); }
            printf("  chrtex image %u %ux%u clut max rgba %u %u %u %u\n", image_id, im->w, im->h, rm, gm, bm, amax); }
    }
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

static void chr_add(dw4_frontchr *o, uint32_t node, uint32_t mesh, uint32_t image, int layer, int slot, int ping)
{
    if (o->nitems == o->cap) {
        int nc = o->cap ? o->cap * 2 : 64;
        struct chr_item *g = (struct chr_item *)realloc(o->item, (size_t)nc * sizeof *g);

        if (!g)
            return;
        o->item = g;
        o->cap = nc;
    }
    o->item[o->nitems].node = node;
    o->item[o->nitems].mesh = mesh;
    o->item[o->nitems].image = image;
    o->item[o->nitems].layer = layer;
    o->item[o->nitems].slot = slot;
    o->item[o->nitems].ping = ping;
    o->nitems++;
}

static void chr_probe(const dw4_frontchr *o)
{
    uint32_t j, k;

    for (j = 0; j < o->sc.nnode; j++) {
        const dw4_scene_node *n = &o->sc.node[j];
        int l, hit = -1;

        if (!n->has_seq)
            continue;
        for (l = 0; l < L_COUNT; l++)
            if (o->root[l] != 0xFFFFFFFFu && is_under(&o->sc, j, o->root[l]))
                hit = l;
        if (hit < 0)
            continue;
        {
            const long long *t = (const long long *)n->seq.times;
            const float *tr = (const float *)n->seq.trans, *sc = (const float *)n->seq.scale;

            printf("  chrseq L%d node %4u %-14s keys=%u:", hit, j, n->name ? n->name : "-", n->seq.ntimes);
            for (k = 0; k < n->seq.ntimes && k < 10; k++) {
                printf(" [%.3fs", (double)t[k] / 1e9);
                if (tr && k < n->seq.ntrans)
                    printf(" t(%.0f,%.0f)", (double)tr[3 * k], (double)tr[3 * k + 1]);
                if (sc && k < n->seq.nscale)
                    printf(" s(%.2f,%.2f)", (double)sc[3 * k], (double)sc[3 * k + 1]);
                printf("]");
            }
            if (n->seq.nrot) {
                const float *q = (const float *)n->seq.rot;

                printf(" ROT%u:", n->seq.nrot);
                for (k = 0; k < n->seq.nrot && k < 30; k++)
                    printf(" [%.2f %.2f %.2f %.2f]", (double)q[4*k], (double)q[4*k+1], (double)q[4*k+2], (double)q[4*k+3]);
            }
            printf("\n");
        }
    }
}

/* The panels are four `PromotedAttr` siblings under one switch, identical in every transform: the slot
 * is the sibling's order, and the engine places each in its own quadrant. */
static int panel_slot(const dw4_frontchr *o, uint32_t node, uint32_t root)
{
    uint32_t a = node, guard = 0, j;
    int k = 0;

    while (a < o->sc.nnode && a != root && guard++ < 64u) {
        const dw4_scene_node *n = &o->sc.node[a];

        if (n->name && strcmp(n->name, "PromotedAttr") == 0)
            break;
        a = n->parent;
    }
    for (j = root; j < a && j < o->sc.nnode; j++)
        if (o->sc.node[j].name && strcmp(o->sc.node[j].name, "PromotedAttr") == 0)
            k++;
    return k > 3 ? 3 : k;
}

static int under_named(const dw4_frontchr *o, uint32_t node, uint32_t root, const char *name)
{
    uint32_t a = node, guard = 0;

    while (a < o->sc.nnode && a != root && guard++ < 64u) {
        const dw4_scene_node *n = &o->sc.node[a];

        if (n->name && strcmp(n->name, name) == 0)
            return 1;
        a = n->parent;
    }
    return 0;
}

/* A window's igSwitch holds `beModelCtrlNode2` variants (frames 0, 15, 30, 45 ...); the screen shows the
 * first, so a node under any later variant is skipped. */
static int first_variant(const dw4_frontchr *o, uint32_t node, uint32_t root)
{
    uint32_t a = node, guard = 0;

    while (a < o->sc.nnode && a != root && guard++ < 64u) {
        const dw4_scene_node *n = &o->sc.node[a];

        if (n->parent < o->sc.nnode && o->sc.node[n->parent].class_name &&
            !strcmp(o->sc.node[n->parent].class_name, "igSwitch"))
            return a == n->parent + 1;
        a = n->parent;
    }
    return 1;
}

static const dw4_igb_value *chr_value(const dw4_igb_record *r, unsigned ordinal)
{
    uint32_t i;
    for (i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == ordinal) return &r->values[i];
    return NULL;
}

/* Entry 806's enabled igLightStateAttr references identify the directional and ambient
 * lights. The unreferenced spotlight is not part of this rig. Read values from the pack. */
static void chr_lights(dw4_frontchr *o, const uint8_t *blob, uint32_t size)
{
    dw4_igb g;
    uint32_t i;
    if (dw4_igb_open(&g, blob, size, 0)) return;
    if (dw4_igb_refs_open(&g)) { dw4_igb_close(&g); return; }
    for (i = 0; i < g.table_n; i++) {
        dw4_igb_record state, light;
        const dw4_igb_value *ref, *enabled, *type, *ambient, *diffuse, *direction;
        uint32_t off;
        int k;
        if (g.id_kind[i] != 2 || !dw4_igb_decode(&g, g.id_off[i], &state)) continue;
        if (strcmp(state.class_name, "igLightStateAttr")) { dw4_igb_record_free(&state); continue; }
        ref = chr_value(&state, 4); enabled = chr_value(&state, 5);
        if (ref && enabled && enabled->raw && dw4_igb_ref(&g, ref->raw, &off, NULL) == 2 &&
            dw4_igb_decode(&g, off, &light)) {
            type = chr_value(&light, 4); ambient = chr_value(&light, 7);
            diffuse = chr_value(&light, 8); direction = chr_value(&light, 10);
            if (!strcmp(light.class_name, "igLightAttr") && type && !type->raw &&
                ambient && ambient->vsize >= 12 && diffuse && diffuse->vsize >= 12 &&
                direction && direction->vsize >= 12) {
                float a[3], d[3], v[3];
                memcpy(a, blob+ambient->voff, 12); memcpy(d, blob+diffuse->voff, 12);
                memcpy(v, blob+direction->voff, 12);
                for (k = 0; k < 3; k++) o->ambient[k] += a[k];
                if (d[0] || d[1] || d[2]) {
                    memcpy(o->diffuse, d, 12); memcpy(o->light_dir, v, 12);
                }
            }
            dw4_igb_record_free(&light);
        }
        dw4_igb_record_free(&state);
    }
    dw4_igb_close(&g);
}

dw4_frontchr *dw4_frontchr_open(const dw4_mount *mnt)
{
    dw4_frontchr *o;
    const uint8_t *blob;
    uint32_t size = 0, j;
    int l;

    if (!mnt)
        return NULL;
    o = (dw4_frontchr *)calloc(1, sizeof *o);
    if (!o)
        return NULL;
    blob = dw4_mount_entry(mnt, CHR_PART, CHR_ENTRY, &size, NULL);
    if (!blob || dw4_scene_load_actor_preview(&o->sc, blob, size) != 0) {
        free(o);
        return NULL;
    }
    if(chr_summary_load(o,mnt)){dw4_frontchr_close(o);return NULL;}
    o->text=dw4_fronttext_open(mnt);
    if(!o->text){dw4_frontchr_close(o);return NULL;}
    chr_lights(o, blob, size);
    {
        static const char *const mesh_names[4] = {
            "H_dorumon_Skin0Shape1", "H_agumon_Skin0Shape1", "H_vmon_Skin0Shape1", "H_girumon_Skin0Shape1"
        };
        for (l = 0; l < 4; l++) {
            o->actor[l] = 0xFFFFFFFFu;
            for (j = 0; j < o->sc.nnode; j++)
                if (o->sc.node[j].name && !strcmp(o->sc.node[j].name, mesh_names[l]) &&
                    o->sc.node[j].mesh != 0xFFFFFFFFu) { o->actor[l] = j; break; }
        }
    }
    for (l = 0; l < 4; l++) {
        o->animation[l] = dw4_actoranim_open(blob, size, &o->sc, o->actor[l]);
        if (!o->animation[l]) fprintf(stderr, "  preview: cannot load %s waitC\n", dw4_frontchr_species_name(l));
    }
    o->bg_root = 0xFFFFFFFFu;
    for (j = 0; j < o->sc.nnode; j++)
        if (o->sc.node[j].parent == 0xFFFFFFFFu && o->sc.node[j].name &&
            strcmp(o->sc.node[j].name, "BG02") == 0) {
            o->bg_root = j;
            break;
        }
    for (l = 0; l < L_COUNT; l++) {
        uint32_t root = 0xFFFFFFFFu;

        for (j = 0; j < o->sc.nnode; j++)
            if (o->sc.node[j].name && strcmp(o->sc.node[j].name, layer_name[l]) == 0) {
                root = j;
                break;
            }
        o->root[l] = root;
        if (root == 0xFFFFFFFFu)
            continue;
        for (j = 0; j < o->sc.nnode; j++) {
            uint32_t mi = dw4_scene_node_mesh(&o->sc, j);

            if (mi == 0xFFFFFFFFu || !is_under(&o->sc, j, root))
                continue;
            if (l != L_PANELS && !first_variant(o, j, root))
                continue;

            chr_add(o, j, mi, dw4_scene_node_texture(&o->sc, j), l, l == L_PANELS ? panel_slot(o, j, root) : 0,
                    l != L_PANELS && under_named(o, j, root, "EFRoot") ? 2 :
                    (under_named(o, j, root, "group5") || under_named(o, j, root, "nextpage")) ? 1 : 0);
        }
    }
    if (!o->nitems) {
        dw4_frontchr_close(o);
        return NULL;
    }
    for (j = 0; j < o->sc.nnode; j++) {
        if (!o->sc.node[j].has_seq)
            continue;
        for (l = 0; l < L_COUNT; l++)
            if (o->root[l] != 0xFFFFFFFFu && is_under(&o->sc, j, o->root[l])) {
                uint32_t *ns = (uint32_t *)realloc(o->seqn, (size_t)(o->nseq + 1) * sizeof *ns);
                int *gs = (int *)realloc(o->seqg, (size_t)(o->nseq + 1) * sizeof *gs);

                if (!ns || !gs)
                    break;
                o->seqn = ns;
                o->seqg = gs;
                o->seqn[o->nseq] = j;
                o->seqg[o->nseq++] = l;
                break;
            }
    }
    if (getenv("DW4_CHR_SEQ"))
        chr_probe(o);
    dw4_frontchr_reset(o);
    return o;
}

const char *dw4_frontchr_enable_gpu(dw4_frontchr *o, int w, int h)
{
    if (!o) return NULL;
    dw4_gl_layer_close(o->gpu);
    dw4_gl_layer_close(o->portrait_gpu);o->portrait_gpu=NULL;o->portrait_w=o->portrait_h=0;
    o->gpu = dw4_gl_layer_open(w, h);
    return dw4_frontchr_gpu_info(o);
}
const char *dw4_frontchr_use_gpu(dw4_frontchr *o, dw4_gl_layer *layer)
{
    if (!o) return NULL;
    dw4_gl_layer_close(o->gpu);
    dw4_gl_layer_close(o->portrait_gpu);o->portrait_gpu=NULL;o->portrait_w=o->portrait_h=0;
    o->gpu = dw4_gl_layer_share(layer);
    return dw4_frontchr_gpu_info(o);
}
const char *dw4_frontchr_gpu_info(const dw4_frontchr *o)
{
    return o && o->gpu ? dw4_gl_layer_info(o->gpu) : NULL;
}

void dw4_frontchr_close(dw4_frontchr *o)
{
    int i;

    if (!o)
        return;
    dw4_gl_layer_close(o->gpu);
    dw4_gl_layer_close(o->portrait_gpu);
    for (i = 0; i < o->ntex; i++)
        free(o->tex[i].px);
    for (i = 0; i < 4; i++) dw4_actoranim_close(o->animation[i]);
    free(o->item);
    free(o->seqn);
    free(o->seqg);
    dw4_scene_close(&o->sc);
    dw4_fronttext_close(o->text);
    dw4_fefont_free(&o->minimum);
    free((void *)o->summary_labels.rgba);
    free(o);
}

void dw4_frontchr_reset(dw4_frontchr *o)
{
    int l;

    if (!o)
        return;
    for (l = 0; l < L_COUNT; l++)
        o->t[l] = 0.0f;
    o->species = -1;
    o->outgoing = -1;
    o->actor_frame = o->outgoing_frame = 0;
    o->change_t = CHR_FADE_END;
    o->outgoing_alpha = 0;
    o->phase = DW4_CHR_SELECT;
    o->logging_in = o->login_frame = 0;
    o->name[0] = 0;
    o->name_length = 0;
    o->bg_frame = 0;
    o->spin = 0.0f;
    o->sel_prev = 0;
    o->sel_t = 0.0f;
    o->text_call=-1;
}

/* j_linewin02 WAIT00/WAIT01 loop the authored 0..15/40..55 joint ranges.
 * LINEON's 20..25/60..65 poses are confirmation actions, not idle pulses. */
static void chr_set_clocks(dw4_frontchr *o, int sel)
{
    int i;
    float ph = (float)fmod((double)o->sel_t, 15.0 / 60.0);
    float lw = ((o->phase == DW4_CHR_CONFIRM ? o->confirm_no : sel) ? 40.0f / 60.0f : 0) + ph;

    for (i = 0; i < o->nseq; i++) {
        const dw4_scene_node *n = &o->sc.node[o->seqn[i]];
        float t;

        switch (o->seqg[i]) {
        case L_PANELS: t = (n->name && strcmp(n->name, "bits") == 0) ? o->spin : 1.0f; break;
        case L_MESSWIN: t = 1.6f; break;
        case L_FACE: t = o->phase == DW4_CHR_SELECT ?
            0.75f + fminf(o->change_t, 5.0f / 12.0f) : 7.0f / 6.0f; break;
        case L_LEFT: case L_RIGHT:
            /* The first quarter-second is the idle arrow pulse. The ring and
             * line tracks assemble once on entry; later keys are input actions. */
            t = n->name && !strcmp(n->name, "cursor") ?
                fmodf(o->t[L_LEFT], 0.25f) : fminf(o->t[L_LEFT], 0.5f);
            break;
        case L_FRAME:
            /* The paired nameplate brackets nudge inward and settle on a
             * selection change (keys 0.333..0.500), then stay visible. */
            t = 1.0f / 3.0f + fminf(o->change_t, 1.0f / 6.0f);
            break;
        case L_KEYBOARD:
            /* Eight name positions, each with a 50-frame bracket pulse. */
            t = o->phase == DW4_CHR_NAME && o->name_length < DW4_CHR_NAME_MAX ?
                o->name_length * (5.0f / 6.0f) + fminf(o->name_cursor_t, 1.0f / 3.0f) :
                20.0f / 3.0f; /* whole-name brackets during confirmation */
            break;
        case L_MODE_CURSOR:
            t = fmodf(o->sel_t, 0.25f);
            break;
        case L_KEY_CURSOR:
            /* Keep group5 at the first key; placement below supplies its column.
             * Only the outline's scale track loops, never the column-change track. */
            t = n->name && !strcmp(n->name, "acurosr") ? fmodf(o->sel_t, 0.25f) : 0;
            break;
        case L_KEY_LEFT:
        case L_KEY_RIGHT: case L_KEY_UP: case L_KEY_DOWN: t = 0.0f; break;
        case L_NAMEWIN: t = n->name && !strcmp(n->name, "bitsA") ? o->spin : 1.0f; break;
        case L_STATUS: t = 0.0f; break;
        default: t = lw; break;
        }
        if (o->logging_in && o->seqg[i] == L_PANELS)
            t = (o->login_frame < 30 ? 70 + o->login_frame :
                 101 + (o->login_frame - 30 < 29 ? o->login_frame - 30 : 29)) / 60.0f;
        dw4_scene_node_drive(&o->sc, o->seqn[i], 0.0f, (long long)((double)t * 1e9));
    }
    dw4_scene_set_engine_time(&o->sc, 0);
}

/* BG02 is a separate scene in the same pack: the grid, coloured shards and glow.
 * Its tracks span six seconds.  This model layer uses the front-end projection,
 * not the title tunnel's demo camera.  The settled PS2 GS capture maps its pack
 * vertices to depth = 300 - world Z, focal X = 628.03, focal Y = 659.43 at 640x448. */
static void chr_background(dw4_frontchr *o, dw4_fb *fb, double seconds)
{
    dw4_layer_draw *draws = NULL;
    int count = 0, capacity = 0;
    uint32_t j;
    float fx = 628.03f * fb->w / 640.0f, fy = 659.43f * fb->h / CHR_REF_H;
    int old_wrap = dw4_render_tex_wrap, old_linear = dw4_render_tex_linear;

    if (o->bg_root == 0xFFFFFFFFu)
        return;
    for (j = 0; j < o->sc.nnode; j++)
        if (o->sc.node[j].has_seq && is_under(&o->sc, j, o->bg_root))
            dw4_scene_node_drive(&o->sc, j, 0.0f, (long long)(fmod(seconds, 6.0) * 1e9));
    dw4_scene_set_engine_time(&o->sc, 0);
    dw4_render_tex_wrap = 1;
    dw4_render_tex_linear = 1;
    for (j = o->bg_root; j < o->sc.nnode; j++) {
        uint32_t mi = dw4_scene_node_mesh(&o->sc, j), *tris = NULL, nt = 0, q;
        const dw4_scene_mesh *m;
        const float *pos, *uv;
        const dw4_tex *tex;
        float world[16], du = 0, dv = 0;
        uint32_t src = 4, dst = 5;
        if (mi == 0xFFFFFFFFu || !is_under(&o->sc, j, o->bg_root))
            continue;
        m = &o->sc.mesh[mi];
        pos = dw4_scene_host(&o->sc, m->positions);
        uv = dw4_scene_host(&o->sc, m->uvs);
        tex = uv ? chr_texture(o, dw4_scene_node_texture(&o->sc, j)) : NULL;
        if (!pos || dw4_scene_node_world(&o->sc, j, world) != 0 ||
            dw4_scene_tris(&o->sc, m, &tris, &nt, NULL) != 0)
            continue;
        dw4_scene_node_uv_offset(&o->sc, j, &du, &dv);
        dw4_scene_node_blend(&o->sc, j, &src, &dst);
        for (q = 0; q < nt; q++) {
            dw4_layer_draw d = {0};
            int e;
            d.tex = tex;
            d.blend = dst == 1 ? 2 : 1;
            d.aref = 12;   /* captured TEST: GREATER, AREF 12, AFAIL KEEP */
            for (e = 0; e < 3; e++) {
                uint32_t vi = tris[3*q+e];
                float w[3], v[3];
                int k;
                if (vi >= m->num_verts) break;
                for (k = 0; k < 3; k++)
                    w[k] = pos[3*vi]*world[k] + pos[3*vi+1]*world[4+k] + pos[3*vi+2]*world[8+k] + world[12+k];
                v[0] = w[0]; v[1] = w[1]; v[2] = w[2] - 300.0f;
                if (-v[2] < 1.0f) break;
                d.v[e][0] = fb->w*0.5f + fx*v[0]/-v[2];
                d.v[e][1] = fb->h*0.5f - fy*v[1]/-v[2];
                d.v[e][2] = (uv ? uv[2*vi]+du : 0) / -v[2];
                d.v[e][3] = (uv ? uv[2*vi+1]+dv : 0) / -v[2];
                d.v[e][4] = 1.0f / -v[2];
                /* GS integer depth, fitted from the same captured grid vertices. */
                d.z[e] = 10493663.0f / -v[2] - 1049.73f;
                memset(d.rgba[e], 127, 3);
                d.rgba[e][3] = 128;
            }
            if (e != 3) continue;
            if (count == capacity) {
                int next = capacity ? capacity*2 : 1024;
                void *p = realloc(draws, (size_t)next * sizeof *draws);
                if (!p) { free(tris); goto done; }
                draws = p; capacity = next;
            }
            draws[count++] = d;
        }
        free(tris);
    }
done:
    if (o->gpu && dw4_gl_layer_draw(o->gpu, fb, draws, count, 1, 1, dw4_render_alpha_ref)) {
        if(dw4_gpu_policy_required())dw4_gpu_policy_fail("character background draw");
        else {
            fprintf(stderr, "  character background: GPU failed; reverting to CPU\n");
            dw4_gl_layer_close(o->gpu); o->gpu = NULL;
        }
    }
    if(!o->gpu && dw4_gpu_policy_required())dw4_gpu_policy_fail("character background GPU unavailable");
    else if (!o->gpu){dw4_render_zbuf_clear(fb);dw4_render_layer_draws(fb, draws, count, 8);}
    free(draws);
    dw4_render_tex_wrap = old_wrap;
    dw4_render_tex_linear = old_linear;
}

/* The portrait is a separate 150x105 viewport with the pack's view/projection.
 * Evaluate waitC before projection and keep its depth buffer separate from the dome/UI. */
static void chr_actor(dw4_frontchr *o, dw4_fb *fb, int species, double seconds, float opacity)
{
    if(dw4_gpu_policy_error()[0])return;
    uint32_t node = o->actor[species], a, *tris = NULL, nt = 0, q;
    const dw4_scene_node *camera = NULL, *viewport = NULL;
    const dw4_scene_mesh *m;
    const float *pos, *uv, *norm;
    const dw4_tex *tex;
    dw4_fb portrait;
    dw4_layer_draw *draws;
    int count = 0, x0, y0, w, h, x, y;
    const char *why = NULL;
    if (node >= o->sc.nnode) return;
    for (a = node; a < o->sc.nnode; a = o->sc.node[a].parent) {
        if (o->sc.node[a].has_view && o->sc.node[a].has_projection) camera = &o->sc.node[a];
        if (o->sc.node[a].has_viewport && !viewport) viewport = &o->sc.node[a];
    }
    if (!camera || !viewport) return;
    m = &o->sc.mesh[o->sc.node[node].mesh];
    pos = dw4_scene_host(&o->sc, m->positions);
    uv = dw4_scene_host(&o->sc, m->uvs);
    norm = dw4_scene_host(&o->sc, m->normals);
    dw4_actoranim_pose(o->animation[species], &o->sc, node, seconds, &pos, &norm);
    tex = chr_texture(o, dw4_scene_node_texture(&o->sc, node));
    if (!pos || !uv || !tex || dw4_scene_tris(&o->sc, m, &tris, &nt, &why)) return;
    x0 = (int)(viewport->viewport[0] * fb->w / 640u);
    y0 = (int)((448u - viewport->viewport[1] - viewport->viewport[3]) * fb->h / 448u);
    w = (int)(viewport->viewport[2] * fb->w / 640u);
    h = (int)(viewport->viewport[3] * fb->h / 448u);
    if (w <= 0 || h <= 0 || dw4_fb_init(&portrait, w, h)) { free(tris); return; }
    /* Rasterized fragments become opaque; untouched pixels stay uncovered.
     * Do not colour-key black: eyes and dark markings are real geometry. */
    draws = calloc(nt, sizeof *draws);
    if (!draws) { free(tris); dw4_fb_free(&portrait); return; }
    for (q = 0; q < nt; q++) {
        dw4_layer_draw *d = &draws[count];
        int e;
        d->tex = tex; d->blend = 0; d->aref = 0;
        for (e = 0; e < 3; e++) {
            uint32_t vi = tris[q*3+e];
            float v[4], clip[4], diffuse = 0.0f;
            int k;
            if (vi >= m->num_verts) break;
            for (k = 0; k < 4; k++)
                v[k] = pos[vi*3]*camera->view[k] + pos[vi*3+1]*camera->view[4+k] +
                       pos[vi*3+2]*camera->view[8+k] + camera->view[12+k];
            for (k = 0; k < 4; k++)
                clip[k] = v[0]*camera->projection[k] + v[1]*camera->projection[4+k] +
                          v[2]*camera->projection[8+k] + v[3]*camera->projection[12+k];
            if (clip[3] <= 0.01f) break;
            /* The posed skeleton supplies the close-up framing in the original camera. */
            d->v[e][0] = (clip[0]/clip[3]+1)*w*0.5f;
            d->v[e][1] = (1-clip[1]/clip[3])*h*0.5f;
            d->v[e][2] = uv[vi*2]/clip[3];
            d->v[e][3] = uv[vi*2+1]/clip[3];
            d->v[e][4] = 1.0f/clip[3];
            /* Layer depth is quantized to GS integer units; unscaled reciprocal
             * depth rounded every character vertex to zero (back faces overwrote eyes/jaws). */
            d->z[e] = 16777216.0f/clip[3];
            if (norm) {
                float nn = sqrtf(norm[vi*3]*norm[vi*3] + norm[vi*3+1]*norm[vi*3+1] + norm[vi*3+2]*norm[vi*3+2]);
                float ln = sqrtf(o->light_dir[0]*o->light_dir[0] + o->light_dir[1]*o->light_dir[1] + o->light_dir[2]*o->light_dir[2]);
                if (nn > 0 && ln > 0)
                    diffuse = fmaxf(0, -(norm[vi*3]*o->light_dir[0] + norm[vi*3+1]*o->light_dir[1] + norm[vi*3+2]*o->light_dir[2])/(nn*ln));
            }
            for (k = 0; k < 3; k++) d->rgba[e][k] = (uint8_t)fminf(255, fmaxf(0, (o->ambient[k] + diffuse*o->diffuse[k])*128));
            d->rgba[e][3] = 128;
        }
        if (e == 3) count++;
    }
    int use_gpu=o->gpu!=NULL;
    if(!use_gpu && dw4_gpu_policy_required()){
        dw4_gpu_policy_fail("character portrait GPU unavailable");goto done;
    }
    if(use_gpu){
        if(!o->portrait_gpu || o->portrait_w!=w || o->portrait_h!=h){
            dw4_gl_layer_close(o->portrait_gpu);o->portrait_gpu=dw4_gl_layer_open(w,h);
            o->portrait_w=w;o->portrait_h=h;
        }
        if(!o->portrait_gpu || dw4_gl_layer_clear(o->portrait_gpu,&portrait,0,0,0,0) ||
           dw4_gl_layer_draw(o->portrait_gpu,&portrait,draws,count,dw4_render_tex_wrap,dw4_render_tex_linear,dw4_render_alpha_ref) ||
           dw4_gl_layer_blit(o->gpu,fb,&portrait,x0,y0,opacity)){
            if(dw4_gpu_policy_required()){dw4_gpu_policy_fail("character portrait GPU pass");goto done;}
            dw4_gl_layer_close(o->gpu);o->gpu=NULL;
            dw4_gl_layer_close(o->portrait_gpu);o->portrait_gpu=NULL;use_gpu=0;
        }
    }
    if(!use_gpu){
        if(dw4_gpu_policy_cpu(DW4_CPU_FILL))goto done;
        memset(portrait.rgba,0,(size_t)w*h*4);
        dw4_render_zbuf_clear(&portrait);dw4_render_layer_draws(&portrait,draws,count,1);
        if(dw4_gpu_policy_cpu(DW4_CPU_COMPOSITE))goto done;
        for (y = 0; y < h; y++) for (x = 0; x < w; x++) {
            const uint8_t *src = portrait.rgba + (y*w+x)*4;
            if (src[3] && x0+x >= 0 && x0+x < fb->w && y0+y >= 0 && y0+y < fb->h) {
                uint8_t *dst = fb->rgba + ((y0+y)*fb->w+x0+x)*4;
                unsigned alpha = (unsigned)(opacity * src[3] + 0.5f);
                for (int k = 0; k < 3; k++)
                    dst[k] = (uint8_t)((src[k]*alpha + dst[k]*(255-alpha) + 127)/255);
                dst[3] = 255;
            }
        }
    }
done:
    free(draws); free(tris); dw4_fb_free(&portrait);
}

/* The captured keyboard cycles modes vertically and scrolls five visible keys. */
static const char *chr_keys(int mode)
{
    static const char *const keys[] = {
        "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "0123456789", "&!?+-*/=.,:;()[]_ "
    };
    return keys[mode & 3];
}
static int chr_key_column(const dw4_frontchr *o)
{int n=(int)strlen(chr_keys(o->key_mode));return (o->key-o->key_first+n)%n;}

/* Native text-order fields: NORMAL, centered in their authored cell widths. */
static int chr_upper_text(dw4_frontchr *o)
{
    int error=0;uint32_t codes[16];char name[16];
    if(o->species<0 || o->phase==DW4_CHR_CREATED)return 0;
    if(o->phase==DW4_CHR_SELECT){
        const char *species=dw4_frontchr_species_name(o->species);size_t n=0;
        while(*species && n<16)codes[n++]=(unsigned char)*species++;
        return dw4_fronttext_set(o->text,"CHRSELFONT14","font000",codes,n,2,114);
    }
    const char *keys=chr_keys(o->key_mode);
    for(unsigned i=0;i<DW4_CHR_NAME_MAX;i++){
        size_t count=0;uint8_t luminance=114;
        if(i<(unsigned)o->name_length){codes[0]=(unsigned char)o->name[i];count=1;}
        else if(i==(unsigned)o->name_length && o->phase==DW4_CHR_NAME){codes[0]=(unsigned char)keys[o->key];count=1;luminance=64;}
        snprintf(name,sizeof name,"font%03u",i);
        error|=dw4_fronttext_set(o->text,"CHRSELFONT13",name,codes,count,2,luminance);
    }
    for(unsigned i=0;i<5;i++){
        codes[0]=(unsigned char)keys[(o->key_first+i)%strlen(keys)];snprintf(name,sizeof name,"font%03u",i);
        error|=dw4_fronttext_set(o->text,"CHRSELFONT11",name,codes,1,2,114);
    }
    for(unsigned i=0;i<3;i++){
        codes[0]=(unsigned char)chr_keys((o->key_mode+(int)i+3)%4)[0];snprintf(name,sizeof name,"font%03u",i);
        error|=dw4_fronttext_set(o->text,"CHRSELFONT10",name,codes,1,2,114);
    }
    return error;
}

struct badge_triangle {
    dw4_ui_draw draw;
    float depth;
    int order;
};
static int badge_depth_compare(const void *va, const void *vb)
{
    const struct badge_triangle *a = va, *b = vb;
    if (a->depth != b->depth) return a->depth < b->depth ? -1 : 1;
    return a->order - b->order;
}

void dw4_frontchr_draw(dw4_frontchr *o, dw4_fb *fb, int sel, const dw4_fefont *font)
{
    struct badge_triangle *badge = NULL;
    int nbadge = 0, capbadge = 0;
    dw4_ui_draw *dl = NULL;
    int ndl = 0, capdl = 0, i, actor_at = -1;
    const float scale = (float)fb->h / CHR_REF_H, sxs = (float)fb->w / 640.0f, cx = fb->w * 0.5f, cy = fb->h * 0.5f;
    const dw4_tex *fallback = NULL;
    long nc;
    const char *over = getenv("DW4_CHR_T");
    int *zorder = NULL;

    if (!o || !fb)
        return;
    if (sel != o->sel_prev) {
        o->sel_prev = sel;
        o->sel_t = 0.0f;
    }
    o->sel_t += 1.0f / 60.0f;
    o->spin += 1.0f / 60.0f;
    if (o->spin >= 1.0f)         /* keys 0..6 turn the bolt 180 degrees in 1.0 s (30 degrees per key); the slash is
                                   * symmetric every 180, so a 1.0 s loop is seamless -- the later keys are other poses */
        o->spin -= 1.0f;
    if (over)
        o->spin = o->sel_t = (float)atof(over);
    if (over) {
        o->change_t = fmaxf(0, (float)atof(over));
        o->t[L_LEFT] = o->change_t;
    }
    chr_set_clocks(o, sel);
    chr_background(o, fb, over ? atof(over) : (double)o->bg_frame++ / 60.0);
    for (i = 0; i < o->nitems && !fallback; i++)
        fallback = chr_texture(o, o->item[i].image);
    /* painter order: the pack's own z, a larger z is nearer (the layers are screen-space and carry no depth buffer) */
    {
        float *zk = (float *)malloc((size_t)o->nitems * sizeof *zk);
        int *ord = (int *)malloc((size_t)o->nitems * sizeof *ord);
        int a, b;

        if (zk && ord) {
            for (a = 0; a < o->nitems; a++) {
                const struct chr_item *it = &o->item[a];
                const dw4_scene_mesh *m = &o->sc.mesh[it->mesh];
                const float *pos = (const float *)dw4_scene_host(&o->sc, m->positions);
                float wm[16];

                ord[a] = a;
                zk[a] = 0.0f;
                if (pos && m->num_verts && dw4_scene_node_world(&o->sc, it->node, wm) == 0) {
                    float zs = 0.0f;
                    uint32_t k;

                    for (k = 0; k < m->num_verts; k++)
                        zs += pos[3 * k] * wm[2] + pos[3 * k + 1] * wm[6] + pos[3 * k + 2] * wm[10] + wm[14];
                    zk[a] = zs / (float)m->num_verts + (it->layer == L_PANELS ? 0.0f : it->layer == L_FRAME ? 500.0f : 1000.0f);

                }
            }
            for (a = 1; a < o->nitems; a++) {           /* stable insertion sort */
                int cur = ord[a];

                for (b = a - 1; b >= 0 && zk[ord[b]] > zk[cur]; b--)
                    ord[b + 1] = ord[b];
                ord[b + 1] = cur;
            }
        }
        zorder = ord;
        free(zk);
    }
    for (i = 0; i < o->nitems; i++) {
        const struct chr_item *it = &o->item[zorder ? zorder[i] : i];
        const dw4_scene_mesh *m = &o->sc.mesh[it->mesh];
        const dw4_tex *tex = chr_texture(o, it->image);
        const char *tex_name=dw4_scene_node_texture_name(&o->sc,it->node);
        if(tex_name && !strcmp(tex_name,"moji.png"))tex=&o->summary_labels;
        const float *pos = (const float *)dw4_scene_host(&o->sc, m->positions);
        const float *uv = m->uvs.off ? (const float *)dw4_scene_host(&o->sc, m->uvs) : NULL;
        uint32_t *tris = NULL, nt = 0, q;
        const char *why = NULL;
        float wm[16], ox = 0.0f, oy = 0.0f, du = 0.0f, dv = 0.0f;

        if ((o->logging_in && it->layer != L_PANELS) ||
            (o->species < 0 && it->layer >= L_FACE) ||
            (o->species >= 0 && it->layer == L_LINEWIN &&
             (o->phase != DW4_CHR_CONFIRM || !it->ping)) ||
            (it->layer == L_KEYBOARD && (o->phase == DW4_CHR_SELECT || o->phase == DW4_CHR_CREATED)) ||
            (it->layer == L_NAMEWIN && (o->phase == DW4_CHR_SELECT || o->phase == DW4_CHR_CREATED)) ||
            (it->layer == L_STATUS && o->phase != DW4_CHR_CREATED) ||
            (it->layer >= L_MODE_CURSOR && (o->phase == DW4_CHR_SELECT || o->phase == DW4_CHR_CREATED)) ||
            (o->phase != DW4_CHR_SELECT && (it->layer == L_LEFT || it->layer == L_RIGHT || it->layer == L_FRAME)))
            continue;
        if (o->species >= 0 && o->phase == DW4_CHR_SELECT && actor_at < 0 && it->layer != L_PANELS && it->layer != L_FRAME)
            actor_at = ndl;
        if (it->layer == L_KEY_CURSOR)
            ox += chr_key_column(o) * 46.0f;
        if (it->layer == L_PANELS) {      /* measured: the four quadrants are 310 x 220 apart */
            static const float px[4] = { -315.0f, -5.0f, -315.0f, -5.0f };
            static const float py[4] = { 240.0f, 240.0f, 20.0f, 20.0f };

            ox = px[it->slot];
            oy = py[it->slot];
        } else {                          /* the menu window sits on panel 1 */
            ox += -315.0f;
            oy = 240.0f;
        }
        if (getenv("DW4_CHR_ANG") && it->slot == 3 && it->layer == L_PANELS && o->sc.node[it->node].name && !strcmp(o->sc.node[it->node].name, "bits")) {
            float w2[16];

            if (dw4_scene_node_world(&o->sc, it->node, w2) == 0)
                printf("ang spin=%.3f m0=%.3f m1=%.3f m4=%.3f m5=%.3f deg=%.1f\n", (double)o->spin, (double)w2[0], (double)w2[1], (double)w2[4], (double)w2[5], atan2((double)w2[1], (double)w2[0]) * 57.29578);
        }
        if (getenv("DW4_CHR_ITEMS") && it->layer == L_LINEWIN) {
            float w2[16];

            if (dw4_scene_node_world(&o->sc, it->node, w2) == 0)
                printf("lw item node %u %s ping=%d verts=%u at (%.1f,%.1f)\n", it->node, o->sc.node[it->node].name ? o->sc.node[it->node].name : "-", it->ping, o->sc.mesh[it->mesh].num_verts, (double)w2[12], (double)w2[13]);
        }
        if (it->ping && ((it->ping == 2 && it->layer != L_LINEWIN) || (it->layer == L_MESSWIN &&
            !(o->phase == DW4_CHR_QUESTION && under_named(o, it->node, o->root[L_MESSWIN], "nextpage")))))
            continue;
        dw4_scene_node_uv_offset(&o->sc, it->node, &du, &dv);
        if (o->species >= 0 && it->layer == L_FACE && o->sc.node[it->node].name &&
            !strcmp(o->sc.node[it->node].name, "kaoShape")) {
            /* charaicon: Agumon, Veemon, Guilmon, Dorumon in the bottom atlas row. */
            static const int column[4] = { 3, 0, 1, 2 };
            du += column[o->species] * 0.25f;
        }
        if (getenv("DW4_CHR_UV") && it->slot == 0 && uv) {
            float u0 = 9e9f, u1 = -9e9f, v0 = 9e9f, v1 = -9e9f;
            uint32_t k;

            for (k = 0; k < m->num_verts; k++) {
                if (uv[2*k] < u0) u0 = uv[2*k];
                if (uv[2*k] > u1) u1 = uv[2*k];
                if (uv[2*k+1] < v0) v0 = uv[2*k+1];
                if (uv[2*k+1] > v1) v1 = uv[2*k+1];
            }
            printf("  chruv node %u %s verts %u u[%.3f %.3f] v[%.3f %.3f] off %.3f %.3f img %u\n", it->node,
                   o->sc.node[it->node].name ? o->sc.node[it->node].name : "-", m->num_verts, u0, u1, v0, v1, du, dv, it->image);
        }
        if (!pos || dw4_scene_node_world(&o->sc, it->node, wm) != 0)
            continue;
        if (it->layer == L_LINEWIN && o->phase == DW4_CHR_CONFIRM) {
            /* The naming list repositions the same authored diamond/ring.
             * Retail GS captures 17/18 place their centres at (29,159)/(29,176).
             * Font size does not scale this model's geometry. */
            ox = 29.0f - 320.0f - wm[12];
            oy = 224.0f - (o->confirm_no ? 176.0f : 159.0f) - wm[13];
        }
        if (dw4_scene_tris(&o->sc, m, &tris, &nt, &why) != 0)
            continue;
        for (q = 0; q < nt; q++) {
            dw4_ui_draw *dd;
            int e, ok = 1;
            float v[3][5];

            for (e = 0; e < 3; e++) {
                uint32_t vi = tris[3 * q + e];
                float lx, ly, lz, X, Y;

                if (vi >= m->num_verts) { ok = 0; break; }
                lx = pos[3 * vi]; ly = pos[3 * vi + 1]; lz = pos[3 * vi + 2];
                X = lx * wm[0] + ly * wm[4] + lz * wm[8] + wm[12] + ox;
                Y = ly * wm[5] + lx * wm[1] + lz * wm[9] + wm[13] + oy;
                v[e][0] = cx + X * sxs;
                v[e][1] = cy - Y * scale;
                v[e][2] = uv ? uv[2 * vi] + du : 0.0f;
                v[e][3] = uv ? uv[2 * vi + 1] + dv : 0.0f;
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
            /* Retail foreground model draws use neutral RGB 127, alpha 128. */
            for(e=0;e<3;e++)memset(dd->rgba[e],127,3);
            if(tex==&o->summary_labels){
                dd->gs_raster=1;
            }
            if (it->layer == L_FACE) {
                /* The base mesh contains both z=20 backing and z=120 rim.
                 * The z=80 portrait belongs between them, not over the rim. */
                if (nbadge == capbadge) {
                    int count = capbadge ? capbadge * 2 : 64;
                    struct badge_triangle *grown = realloc(badge, count * sizeof *badge);
                    if (!grown) { ndl--; continue; }
                    badge = grown; capbadge = count;
                }
                badge[nbadge].draw = *dd;
                /* Retail UI vertices use neutral RGB 127 and alpha 128. */
                for (e = 0; e < 3; e++)
                    for (int channel = 0; channel < 3; channel++)
                        badge[nbadge].draw.rgba[e][channel] = 127;
                badge[nbadge].depth = 0;
                for (e = 0; e < 3; e++) {
                    const float *p = pos + 3 * tris[3*q+e];
                    badge[nbadge].depth += (p[0]*wm[2] + p[1]*wm[6] + p[2]*wm[10] + wm[14])/3;
                }
                badge[nbadge].order = nbadge;
                nbadge++;
                ndl--;
            }
        }
        free(tris);
    }
    free(zorder);
    if (nbadge) {
        qsort(badge, nbadge, sizeof *badge, badge_depth_compare);
        if (ndl + nbadge > capdl) {
            dw4_ui_draw *grown = realloc(dl, (ndl + nbadge) * sizeof *dl);
            if (grown) { dl = grown; capdl = ndl + nbadge; }
        }
        if (ndl + nbadge <= capdl)
            for (i = 0; i < nbadge; i++) dl[ndl++] = badge[i].draw;
    }
    free(badge);
    if (!o->logging_in && font && font->have && font->atlas) {
        int call=o->species<0?161:o->phase==DW4_CHR_SELECT?225:
            o->phase==DW4_CHR_NAME?232:o->phase==DW4_CHR_QUESTION?235:
            o->phase==DW4_CHR_CONFIRM?236:240;
        if(call!=o->text_call){
            dw4_fronttext_clear(o->text);
            if(dw4_fronttext_event(o->text,call) || (call==161 && dw4_fronttext_event(o->text,250))){
                fprintf(stderr,"character text: %s\n",dw4_fronttext_error(o->text));
                dw4_gpu_policy_fail("original character text callback");
            }else o->text_call=call;
        }
        if(chr_upper_text(o))dw4_gpu_policy_fail("authored character upper fields");
        const dw4_ui_draw *message;size_t nmessage;
        if(dw4_fronttext_draw(o->text,fb->w,fb->h,&message,&nmessage))
            dw4_gpu_policy_fail("authored character text geometry");
        else if(nmessage){
            if(ndl+(int)nmessage>capdl){
                int capacity=ndl+(int)nmessage;dw4_ui_draw *grown=realloc(dl,(size_t)capacity*sizeof(*dl));
                if(!grown){dw4_gpu_policy_fail("character text submission allocation");nmessage=0;}
                else {dl=grown;capdl=capacity;}
            }
            if(nmessage){memcpy(dl+ndl,message,nmessage*sizeof(*dl));ndl+=(int)nmessage;}
        }

        if (o->phase == DW4_CHR_CREATED) {
            static const int hp[4] = {170, 180, 160, 150};
            static const int mp[4] = {60, 50, 70, 80};
            char value[8];
            int error=chr_summary_text(o,&dl,&ndl,&capdl,0,o->name,0,fb->w,fb->h);
            error|=chr_summary_text(o,&dl,&ndl,&capdl,1,"1",2,fb->w,fb->h);
            error|=chr_summary_text(o,&dl,&ndl,&capdl,2,dw4_frontchr_species_name(o->species),0,fb->w,fb->h);
            snprintf(value, sizeof value, "%d", hp[o->species]);
            error|=chr_summary_text(o,&dl,&ndl,&capdl,3,value,1,fb->w,fb->h);
            error|=chr_summary_text(o,&dl,&ndl,&capdl,5,value,1,fb->w,fb->h);
            snprintf(value, sizeof value, "%d", mp[o->species]);
            error|=chr_summary_text(o,&dl,&ndl,&capdl,4,value,1,fb->w,fb->h);
            error|=chr_summary_text(o,&dl,&ndl,&capdl,6,value,1,fb->w,fb->h);
            if(error)dw4_gpu_policy_fail("character summary text preparation");
        }
    }
    nc = sysconf(_SC_NPROCESSORS_ONLN);
    if (nc > 8)
        nc = 8;
    dw4_render_tex_wrap = 1;
    dw4_render_tex_linear = 1;
    dw4_render_aref = 12;
    if(o->observe)o->observe(o->observe_user,dl,(size_t)ndl);
    if (o->species >= 0 && actor_at >= 0) {
        dw4_gl_layer_ui_or_cpu(&o->gpu, fb, dl, actor_at, (int)nc);
        if (o->outgoing >= 0 && o->change_t < CHR_FADE_OUT)
            chr_actor(o, fb, o->outgoing, (double)o->outgoing_frame / 60.0,
                      o->outgoing_alpha * (1 - o->change_t / CHR_FADE_OUT));
        else if (o->change_t > CHR_FADE_IN_START)
            chr_actor(o, fb, o->species, over ? atof(over) : (double)o->actor_frame / 60.0,
                      fminf(1, (o->change_t - CHR_FADE_IN_START) / (CHR_FADE_END - CHR_FADE_IN_START)));
        dw4_gl_layer_ui_or_cpu(&o->gpu, fb, dl + actor_at, ndl - actor_at, (int)nc);
    } else {
        dw4_gl_layer_ui_or_cpu(&o->gpu, fb, dl, ndl, (int)nc);
    }
    dw4_render_tex_wrap = 0;
    dw4_render_tex_linear = 0;
    dw4_render_aref = -1;
    free(dl);
    if (o->logging_in) {
        unsigned keep = o->login_frame < 30 ? 30 :
                        o->login_frame < 60 ? 60 - o->login_frame : 0;
        /* Global load fade also clears the animated BG02 field. */
        if(o->gpu){
            if(dw4_gl_layer_multiply(o->gpu,fb,keep,30))dw4_gpu_policy_fail("character closing fade");
        }else{
            if(dw4_gpu_policy_cpu(DW4_CPU_COMPOSITE))return;
            for(size_t p=0;p<(size_t)fb->w*fb->h;p++)for(unsigned k=0;k<3;k++)fb->rgba[4*p+k]=fb->rgba[4*p+k]*keep/30;
        }
        if (o->login_frame <= 60) o->login_frame++;
    }
    o->name_cursor_t = fminf(o->name_cursor_t + 1.0f / 60.0f, 1.0f / 3.0f);
    o->change_t += 1.0f / 60.0f;
    o->t[L_LEFT] += 1.0f / 60.0f;
    o->outgoing_frame++;
    if (o->change_t > CHR_FADE_IN_START) o->actor_frame++;
}

void dw4_frontchr_set_sound(dw4_frontchr *o,
                           void (*fn)(void *, const char *, const char *), void *user)
{
    if (o) { o->sound_action = fn; o->sound_user = user; }
}
void dw4_frontchr_observe_draws(dw4_frontchr *o,
    void (*fn)(void *,const dw4_ui_draw *,size_t),void *user)
{if(o){o->observe=fn;o->observe_user=user;}}
static void chr_sound(dw4_frontchr *o, const char *model, const char *action)
{
    if (o->sound_action) o->sound_action(o->sound_user, model, action);
}

const char *dw4_frontchr_species_name(int species)
{
    static const char *const names[4] = { "Dorumon", "Agumon", "Veemon", "Guilmon" };
    return species >= 0 && species < 4 ? names[species] : "";
}

static void species_set(dw4_frontchr *o, int species, int sound);
void dw4_frontchr_species(dw4_frontchr *o, int species) { species_set(o, species, 1); }
void dw4_frontchr_draw_preview(dw4_frontchr *o, dw4_fb *fb, int species)
{
    int old_wrap = dw4_render_tex_wrap, old_linear = dw4_render_tex_linear, old_aref = dw4_render_aref;
    if (!o || !fb || species < 0 || species > 3) return;
    species_set(o, species, 0);
    dw4_render_tex_wrap = 1; dw4_render_tex_linear = 1; dw4_render_aref = 12;
    if (o->outgoing >= 0 && o->change_t < CHR_FADE_OUT)
        chr_actor(o, fb, o->outgoing, (double)o->outgoing_frame / 60.0, o->outgoing_alpha * (1 - o->change_t / CHR_FADE_OUT));
    else if (o->change_t > CHR_FADE_IN_START)
        chr_actor(o, fb, o->species, (double)o->actor_frame / 60.0,
                  fminf(1, (o->change_t - CHR_FADE_IN_START) / (CHR_FADE_END - CHR_FADE_IN_START)));
    dw4_render_tex_wrap = old_wrap; dw4_render_tex_linear = old_linear; dw4_render_aref = old_aref;
    o->change_t += 1.0f / 60.0f;
    o->outgoing_frame++;
    if (o->change_t > CHR_FADE_IN_START) o->actor_frame++;
}
static void species_set(dw4_frontchr *o, int species, int sound)
{
    species = species >= 0 && species < 4 ? species : -1;
    if (!o || o->species == species) return;
    /* Retarget rapid input from the portrait actually on screen, including its
     * current opacity; never flash a fully opaque intermediate selection. */
    if (o->change_t < CHR_FADE_OUT) {
        o->outgoing_alpha *= 1 - o->change_t / CHR_FADE_OUT;
    } else {
        o->outgoing = o->species;
        o->outgoing_frame = o->actor_frame;
        o->outgoing_alpha = fminf(1, fmaxf(0,
            (o->change_t - CHR_FADE_IN_START) / (CHR_FADE_END - CHR_FADE_IN_START)));
    }
    if (o->species < 0 || species < 0) {
        o->outgoing = -1;
        o->outgoing_alpha = 0;
        o->t[L_LEFT] = 0;
    }
    if (sound && o->species >= 0 && species >= 0) chr_sound(o, "j_digifacewin", "CHANGE");
    o->actor_frame = 0;
    o->change_t = 0;
    o->species = species;
}

void dw4_frontchr_begin_name(dw4_frontchr *o)
{
    if (!o || o->species < 0) return;
    chr_sound(o, "j_linewin01", "LINEON00");
    o->phase = DW4_CHR_NAME;
    o->key_mode = o->key = o->key_first = o->name_length = o->confirm_no = 0;
    o->name[0] = 0;
    o->name_cursor_t = 1.0f / 3.0f;
}

int dw4_frontchr_phase(const dw4_frontchr *o) { return o ? o->phase : DW4_CHR_SELECT; }
const char *dw4_frontchr_name(const dw4_frontchr *o) { return o ? o->name : ""; }
void dw4_frontchr_name_selection(const dw4_frontchr *o,int *mode,int *first,int *column)
{if(mode)*mode=o?o->key_mode:0;if(first)*first=o?o->key_first:0;if(column)*column=o?chr_key_column(o):0;}

int dw4_frontchr_name_input(dw4_frontchr *o, int horizontal, int vertical,
                           int cross, int circle, int start)
{
    if (!o || o->logging_in) return 0;
    if (o->phase == DW4_CHR_NAME) {
        if (circle) {
            chr_sound(o, "j_namecursorus", "CANCEL");
            o->name_cursor_t = 1.0f / 3.0f;
            if (o->name_length) {
                /* 3e0040 clears the current preview, then 3e0114..3e014c
                 * restores the previous cell's saved mode/scroll/column. */
                int cell=--o->name_length;o->name[cell]=0;
                o->key_mode=o->name_mode[cell];o->key=o->name_key[cell];o->key_first=o->name_first[cell];
            }
            else { o->phase = DW4_CHR_SELECT; o->species = -1; }
        } else if (start && o->name_length) {
            chr_sound(o, "j_namewin02", "LINEON00");
            o->phase = DW4_CHR_QUESTION;
            printf("  title: name question: %s\n", o->name);
        } else if (vertical) {
            chr_sound(o, "j_namecursorus", "NAMECG00");
            o->name_cursor_t = 1.0f / 6.0f;
            int column=chr_key_column(o);
            /* 3df914/3dfa8c: Up decrements, Down increments the mode. */
            o->key_mode = (o->key_mode + (vertical > 0 ? 1 : 3)) % 4;
            /* The strip restarts, retaining the selected column. */
            o->key_first = 0; o->key = column;
        } else if (horizontal) {
            chr_sound(o, "j_namewin02", "LINECG00");
            int n = (int)strlen(chr_keys(o->key_mode));
            int column=chr_key_column(o);
            o->name_cursor_t = 1.0f / 6.0f;
            o->key = (o->key + (horizontal > 0 ? 1 : n-1)) % n;
            /* 3df550..3df838 retain the edge column and wrap the five-key
             * strip's start, rather than moving to the opposite edge. */
            if((horizontal>0 && column==4) || (horizontal<0 && column==0))
                o->key_first=(o->key_first+(horizontal>0?1:n-1))%n;
        } else if (cross && o->name_length < DW4_CHR_NAME_MAX) {
            chr_sound(o, "j_namecursorus", "NAMEON00");
            o->name_cursor_t = 1.0f / 3.0f;
            o->name_mode[o->name_length]=o->key_mode;o->name_key[o->name_length]=o->key;o->name_first[o->name_length]=o->key_first;
            o->name[o->name_length++] = chr_keys(o->key_mode)[o->key];
            o->name[o->name_length] = 0;
        }
    } else if (o->phase == DW4_CHR_QUESTION || o->phase == DW4_CHR_CONFIRM) {
        if (circle) { chr_sound(o, "j_linewin02", "CANCEL"); o->phase = DW4_CHR_NAME; }
        else if (o->phase == DW4_CHR_QUESTION && cross) {
            chr_sound(o, "j_linewin01", "LINEON00");
            o->phase = DW4_CHR_CONFIRM; o->confirm_no = 0; o->sel_t = 0;
        } else if (o->phase == DW4_CHR_CONFIRM) {
            if (vertical) {
                chr_sound(o, "j_linewin02", o->confirm_no ? "LINEUP00" : "LINEDW01");
                o->confirm_no = !o->confirm_no; o->sel_t = 0;
            }
            else if (cross) {
                chr_sound(o, "j_linewin02", o->confirm_no ? "LINEON01" : "LINEON00");
                o->phase = o->confirm_no ? DW4_CHR_NAME : DW4_CHR_CREATED;
                if (!o->confirm_no) printf("  title: created %s named %s\n",
                                           dw4_frontchr_species_name(o->species), o->name);
            }
        }
    } else if (o->phase == DW4_CHR_CREATED) {
        if (circle) { chr_sound(o, "j_mainstatuswin", "CANCEL"); o->phase = DW4_CHR_NAME; }
        else if (start) { chr_sound(o, "j_mainstatuswin", "LINEON00"); return 1; }
    }
    return 0;
}

void dw4_frontchr_set_called(dw4_frontchr *o, int species, const char *name)
{
    if (!o) return;
    if (species < 0 || species > 3) {
        dw4_frontchr_species(o, -1);
        o->phase = DW4_CHR_SELECT;
        return;
    }
    dw4_frontchr_species(o, species);
    o->phase = DW4_CHR_CREATED;
    o->name_length = 0;
    for (; name && *name && o->name_length < DW4_CHR_NAME_MAX; ++name) {
        o->name_mode[o->name_length] = o->name_key[o->name_length] = o->name_first[o->name_length] = 0;
        o->name[o->name_length++] = *name;
    }
    o->name[o->name_length] = 0;
    for (int l = 0; l < L_COUNT; ++l) o->t[l] = 2.0f;
}

void dw4_frontchr_begin_login(dw4_frontchr *o)
{
    if (!o || o->phase != DW4_CHR_CREATED || o->logging_in) return;
    o->logging_in = 1;
    o->login_frame = 0;
}

int dw4_frontchr_login_done(const dw4_frontchr *o)
{
    return o && o->logging_in && o->login_frame > 60;
}

void dw4_frontchr_cancel_login(dw4_frontchr *o)
{
    if (!o) return;
    o->logging_in = o->login_frame = 0;
    o->phase = DW4_CHR_CREATED;
    for (int l = 0; l < L_COUNT; ++l) o->t[l] = 2.0f;
}
