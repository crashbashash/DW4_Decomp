#include "dw4/lobbyui.h"
#include "dw4/igb.h"
#include "dw4/modelctrl.h"
#include "dw4/modelsubcom.h"
#include "dw4/hudmeter.h"
#include "dw4/hudnumber.h"
#include "eefloat.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The recovered script opens/closes each of five groups. Its terminal beep wait
 * starts AFTER the talk window closes. Model dispatcher overhead remains outside
 * this bounded UI controller; JOINTSET windows themselves come from the pack. */
enum { HIDDEN, OPENING, READING, CLOSING, BEEP, DONE };
struct window {
    uint32_t root;
    float open[2], loop[2], close[2];
};
struct item {
    uint32_t node, *tri, nt;
    unsigned model;
    dw4_tex *tex;
    float z;
};
struct number {uint32_t geometry,max,mode,count;float offset;struct {uint32_t vertex,place,kind;} map[48];};
struct layout {
    float x, y, width, height;
};
struct action_sink {dw4_lobbyui *ui;const char *name;};
struct dw4_lobbyui {
    dw4_scene *scene;
    dw4_dialogue *dialogue;
    dw4_scene common;
    dw4_modelctrl *controller[5];
    int frame_valid;int64_t frame_clock;
    struct action_sink sink[5];dw4_lobbyui_action action;void *action_user;
    unsigned scripted;
    unsigned hud_back;       /* ticks since the HUD came back after a message, saturating at 3: its fade-in */
    int64_t talk_close_t0;   /* the speaker window's time when its SQ_CLOSEL began, 0 while it is not closing */
    struct window model[10]; /* five greeting models, then stpnl00..04 */
    struct item item[128];
    unsigned nitem, ntex, phase_age, window_age;
    dw4_tex tex[16];
    uint32_t tex_id[16];
    dw4_fefont normal, minimum;
    dw4_tex atlas[2];
    struct layout layout[3];
    uint32_t text[15][512], speaker[64];
    unsigned len[15], nspeaker;
    int phase, page, hud, party;   /* party: a hub party's panels are drawn by the model view (fieldhud), not here */
    unsigned hud_age;
    int species;
    int status,health_set;int32_t health[5];
    float portrait[16][2];   /* the HUD portrait window's WAIT01..WAIT16 ranges, by shinka row */
    dw4_hudmeter meter[2];uint32_t meter_node[2];unsigned have_meter;
    struct number number[3];unsigned have_number;
    dw4_ui_draw *draw;
    unsigned ndraw, cap;
};
static void window_action(void *user,const char *sequence,const char *type,const char *action,int64_t time)
{
    struct action_sink *sink=user;(void)sequence;(void)time;
    if(sink->ui->action && !strcmp(type,"beModelCtrlACTION"))sink->ui->action(sink->ui->action_user,sink->name,action);
}
void dw4_lobbyui_actions(dw4_lobbyui *ui,dw4_lobbyui_action action,void *user)
{
    if(!ui)return;
    ui->action=action;ui->action_user=user;
    for(unsigned i=0;i<5;i++)dw4_modelctrl_observe(ui->controller[i],action?window_action:NULL,action?&ui->sink[i]:NULL);
}
static uint32_t slot(const dw4_igb_record *r, unsigned ord)
{
    for (unsigned i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == ord)
            return r->values[i].raw;
    return UINT32_MAX;
}
static int record(const dw4_igb *g, uint32_t id, dw4_igb_record *r)
{
    return id < g->table_n && g->id_kind[id] == 2 && dw4_igb_decode(g, g->id_off[id], r);
}
static const uint8_t *field(const dw4_igb *g, const dw4_igb_record *r, unsigned ord)
{
    for (unsigned i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == ord)
            return g->data + r->values[i].voff;
    return NULL;
}
static int window_range(const dw4_igb *g, const dw4_igb_record *info, const char *name,
                        float out[2])
{
    dw4_igb_record list = {0};
    uint32_t n;
    int found = 0;
    if (!record(g, slot(info, 9), &list))
        return 0;
    const uint8_t *data = dw4_igb_block(g, slot(&list, 4), &n);
    if (data && n % 4 == 0)
        for (unsigned i = 0; i < n / 4; i++) {
            dw4_igb_record action = {0}, commands = {0};
            uint32_t id;
            memcpy(&id, data + 4 * i, 4);
            if (!record(g, id, &action))
                continue;
            if (action.name && !strcmp(action.name, name) &&
                record(g, slot(&action, 3), &commands)) {
                uint32_t size;
                const uint8_t *ids = dw4_igb_block(g, slot(&commands, 4), &size);
                if (ids && size % 4 == 0)
                    for (unsigned j = 0; j < size / 4; j++) {
                        dw4_igb_record joint = {0};
                        memcpy(&id, ids + 4 * j, 4);
                        if (!record(g, id, &joint))
                            continue;
                        if (!strcmp(joint.class_name, "beAction2JOINTSET")) {
                            uint32_t a = slot(&joint, 3), b = slot(&joint, 4);
                            memcpy(out, &a, 4);
                            memcpy(out + 1, &b, 4);
                            found = isfinite(out[0]) && isfinite(out[1]) && out[1] >= out[0];
                        }
                        dw4_igb_record_free(&joint);
                    }
            }
            dw4_igb_record_free(&commands);
            dw4_igb_record_free(&action);
        }
    dw4_igb_record_free(&list);
    return found;
}
static int language(dw4_lobbyui *ui, const dw4_mount *mount)
{
    uint32_t size;
    dw4_igb g = {0};
    int have[3] = {0};
    const uint8_t *blob = dw4_mount_entry(mount, 1, 674, &size, NULL);
    if (!blob || dw4_igb_open(&g, blob, size, 0) || dw4_igb_refs_open(&g))
        goto fail;
    for (unsigned i = 0; i < g.table_n; i++) {
        dw4_igb_record r = {0};
        if (!record(&g, i, &r))
            continue;
        if (!strcmp(r.class_name, "beUnicodeObj") && r.name) {
            int page = -1;
            unsigned cap = 512;
            uint32_t *out = NULL;
            unsigned *len = NULL;
            if (!strcmp(r.name, "mswkNPC001")) {
                out = ui->speaker;
                len = &ui->nspeaker;
                cap = 64;
            } else if (sscanf(r.name, "mswk%d", &page) == 1 && page >= 67051 && page <= 67065) {
                page -= 67051;
                out = ui->text[page];
                len = &ui->len[page];
            }
            if (out) {
                uint32_t n;
                const uint8_t *s = dw4_igb_block(&g, slot(&r, 3), &n);
                if (!s || n % 2 || n / 2 > cap) {
                    dw4_igb_record_free(&r);
                    goto fail;
                }
                for (unsigned k = 0; k < n / 2; k++) {
                    unsigned c = s[2 * k] | ((unsigned)s[2 * k + 1] << 8);
                    if (!c)
                        break;
                    out[(*len)++] = c;
                }
            }
        } else if (!strcmp(r.class_name, "beFontInfoData") && r.name && slot(&r, 6) == 0) {
            int k = !strcmp(r.name, "TALKFONT01")   ? 0
                    : !strcmp(r.name, "TALKFONT02") ? 1
                    : !strcmp(r.name, "TALKFONT03") ? 2
                                                    : -1;
            if (k >= 0) {
                dw4_igb_record attr = {0}, children = {0}, transform = {0};
                uint32_t n;
                if (record(&g, slot(&r, 4), &attr) && record(&g, slot(&attr, 7), &children)) {
                    const uint8_t *ids = dw4_igb_block(&g, slot(&children, 4), &n);
                    uint32_t id = UINT32_MAX;
                    if (ids && n >= 4)
                        memcpy(&id, ids, 4);
                    if (record(&g, id, &transform) &&
                        !strcmp(transform.class_name, "igTransform")) {
                        const uint8_t *mat = field(&g, &transform, 8);
                        float m[16];
                        uint32_t a = slot(&r, 7), b = slot(&r, 8);
                        if (mat) {
                            memcpy(m, mat, sizeof m);
                            memcpy(&ui->layout[k].width, &a, 4);
                            memcpy(&ui->layout[k].height, &b, 4);
                            ui->layout[k].x = 320 + 100 * m[12];
                            ui->layout[k].y = 224 - 100 * m[13];
                            have[k] = 1;
                        }
                    }
                }
                dw4_igb_record_free(&transform);
                dw4_igb_record_free(&children);
                dw4_igb_record_free(&attr);
            }
        }
        dw4_igb_record_free(&r);
    }
    dw4_igb_close(&g);
    for (unsigned i = 0; i < 15; i++)
        if (!ui->len[i])
            return -1;
    return have[0] && have[1] && have[2] && ui->nspeaker ? 0 : -1;
fail:
    dw4_igb_close(&g);
    return -1;
}
static dw4_tex *texture(dw4_lobbyui *ui, const dw4_scene *source, uint32_t id)
{
    uint32_t key = id | (source == &ui->common ? 0x80000000u : 0);
    for (unsigned i = 0; i < ui->ntex; i++)
        if (ui->tex_id[i] == key)
            return ui->tex + i;
    const dw4_scene_image *im = dw4_scene_image_of(source, id);
    if (!im || ui->ntex == 16 || !im->w || !im->h || im->w > 8192 || im->h > 8192 || im->bpr < im->w)
        return NULL;
    const uint8_t *grid = dw4_scene_host(source, im->grid),
                  *pal = dw4_scene_host(source, im->pal);
    const dw4_scene_ent *ge = dw4_scene_lookup(source, dw4_scene_id_of(source, im->grid));
    const dw4_scene_ent *pe = dw4_scene_lookup(source, dw4_scene_id_of(source, im->pal));
    if (!grid || !pal || !ge || !pe || ge->size < (uint64_t)im->bpr * im->h || pe->size < 1024)
        return NULL;
    uint8_t *rgba = malloc((size_t)im->w * im->h * 4);
    if (!rgba)
        return NULL;
    for (unsigned y = 0; y < im->h; y++)
        for (unsigned x = 0; x < im->w; x++) {
            const uint8_t *p = pal + 4 * grid[y * im->bpr + x];
            uint8_t *o = rgba + 4 * (y * im->w + x);
            memcpy(o, p, 3);
            o[3] = (p[3] + 1u) / 2u;
        }
    unsigned k = ui->ntex++;
    ui->tex_id[k] = key;
    ui->tex[k] = (dw4_tex){.rgba = rgba, .w = im->w, .h = im->h};
    return ui->tex + k;
}
dw4_lobbyui *dw4_lobbyui_open(const dw4_mount *mount, dw4_scene *scene, const uint8_t *blob,
                              size_t size)
{
    static const char *names[] = {"i_messwn", "i_talkwn", "n_digilffic", "i_messky", "i_talkky",
        "i_stpnl00", "i_stpnl01", "i_stpnl02", "i_stpnl03", "i_stpnl04"};
    dw4_lobbyui *ui = calloc(1, sizeof *ui);
    dw4_igb g = {0};
    uint32_t common_size;
    const uint8_t *common = dw4_mount_entry(mount, 1, 674, &common_size, NULL);
    if (!ui)
        return NULL;
    ui->scene = scene;
    for(unsigned i=0;i<5;i++) {
        ui->sink[i]=(struct action_sink){ui,names[i]};
        ui->controller[i]=dw4_modelctrl_open(blob,size,names[i]);
        if(!ui->controller[i])goto fail;
    }
    ui->page = -1;
    for (unsigned i = 0; i < 10; i++)
        ui->model[i].root = UINT32_MAX;
    if (!common || dw4_scene_load(&ui->common, common, common_size) || language(ui, mount) || dw4_fefont_load_face(&ui->normal, mount, "NORMAL") ||
        dw4_fefont_load_face(&ui->minimum, mount, "MINIMUM") || dw4_igb_open(&g, blob, size, 0) ||
        dw4_igb_refs_open(&g))
        goto fail;
    for (unsigned i = 0; i < g.table_n; i++) {
        dw4_igb_record r = {0};
        if (!record(&g, i, &r))
            continue;
        if(!strcmp(r.class_name,"beNumberCtrlInfoRam")){
            dw4_igb_record geometry={0};
            if(record(&g,slot(&r,11),&geometry) && geometry.name){
                int k=!strcmp(geometry.name,"lvnm1")?0:!strcmp(geometry.name,"hpnm1")?1:!strcmp(geometry.name,"mpnm1")?2:-1;
                if(k>=0){
                    struct number *num=&ui->number[k];num->geometry=slot(&r,11);num->max=slot(&r,13);num->mode=slot(&r,14);
                    uint32_t raw=slot(&r,12);memcpy(&num->offset,&raw,4);
                    dw4_igb_record digits={0};uint32_t bytes;
                    const uint8_t *data=NULL;
                    if(record(&g,slot(&r,15),&digits))data=dw4_igb_block(&g,slot(&digits,4),&bytes);
                    if(!data || !bytes || bytes%4 || bytes/4>8){dw4_igb_record_free(&digits);dw4_igb_record_free(&geometry);dw4_igb_record_free(&r);goto fail;}
                    for(unsigned digit=0;digit<bytes/4;digit++){
                        uint32_t id;memcpy(&id,data+4*digit,4);dw4_igb_record dr={0},vertices={0};uint32_t vb;
                        const uint8_t *vd=NULL;
                        if(record(&g,id,&dr) && record(&g,slot(&dr,3),&vertices))vd=dw4_igb_block(&g,slot(&vertices,4),&vb);
                        if(!vd || vb!=24){dw4_igb_record_free(&vertices);dw4_igb_record_free(&dr);dw4_igb_record_free(&digits);dw4_igb_record_free(&geometry);dw4_igb_record_free(&r);goto fail;}
                        for(unsigned vertex=0;vertex<6;vertex++){
                            memcpy(&id,vd+4*vertex,4);dw4_igb_record vr={0};
                            if(!record(&g,id,&vr) || slot(&vr,3)>3){dw4_igb_record_free(&vr);dw4_igb_record_free(&vertices);dw4_igb_record_free(&dr);dw4_igb_record_free(&digits);dw4_igb_record_free(&geometry);dw4_igb_record_free(&r);goto fail;}
                            unsigned n=num->count++;num->map[n].vertex=slot(&vr,2);num->map[n].kind=slot(&vr,3);num->map[n].place=digit;
                            dw4_igb_record_free(&vr);
                        }
                        dw4_igb_record_free(&vertices);dw4_igb_record_free(&dr);
                    }
                    dw4_igb_record_free(&digits);ui->have_number|=1u<<k;
                }
            }
            dw4_igb_record_free(&geometry);
        }
        if(!strcmp(r.class_name,"beMeterCtrlOneData") && r.name){
            int k=!strcmp(r.name,"hpmt1")?0:!strcmp(r.name,"mpmt1")?1:-1;
            if(k>=0){
                uint32_t raw=slot(&r,4);float maximum;memcpy(&maximum,&raw,4);
                const uint8_t *nz=field(&g,&r,9),*nm=field(&g,&r,10);int64_t nonzero,nonmax;
                if(!nz || !nm){dw4_igb_record_free(&r);goto fail;}
                memcpy(&nonzero,nz,8);memcpy(&nonmax,nm,8);
                if(dw4_hudmeter_init(&ui->meter[k],maximum,slot(&r,14)!=0,nonzero,nonmax)){dw4_igb_record_free(&r);goto fail;}
                ui->meter_node[k]=slot(&r,3);ui->have_meter|=1u<<k;
                dw4_hudmeter_percent(&ui->meter[k],100);
            }
        }
        if (!strcmp(r.class_name, "beAction2Info") && r.name)
            for (unsigned k = 0; k < 10; k++)
                if (!strcmp(r.name, names[k])) {
                    uint32_t id = slot(&r, 7);
                    for (unsigned j = 0; j < scene->nnode; j++)
                        if (scene->node[j].id == id) {
                            ui->model[k].root = j;
                            break;
                        }
                    if (k < 3) {
                        if (!window_range(&g, &r, k ? "OPENL" : "OPEN01", ui->model[k].open) ||
                            !window_range(&g, &r, k ? "LOOPL" : "LOOP01", ui->model[k].loop) ||
                            !window_range(&g, &r, k ? "CLOSEL" : "CLOSE01", ui->model[k].close)) {
                            dw4_igb_record_free(&r);
                            goto fail;
                        }
                    } else if (k < 5 && !window_range(&g, &r, "LINESL00", ui->model[k].loop)) {
                        dw4_igb_record_free(&r);
                        goto fail;
                    }
                    if (k >= 5 && !window_range(&g, &r, "WAIT01", ui->model[k].loop)) {
                        dw4_igb_record_free(&r); goto fail;
                    }
                    if (k == 7) {
                        /* The atlas holds the four starters first (shinka rows 0..3) and then the evolved forms in an authored
                         * order that is not the shinka row order. Measured against retail HUD frames of every evolved form
                         * (each portrait matched to its atlas tile): row 4..15 -> tile 8,7,9,4,6,5,15,10,11,14,12,13. */
                        static const unsigned char tile[16] = {0, 1, 2, 3, 8, 7, 9, 4, 6, 5, 15, 10, 11, 14, 12, 13};
                        for (unsigned sp = 0; sp < 16; sp++) {
                            char wait[8];snprintf(wait, sizeof wait, "WAIT%02u", tile[sp] + 1u);
                            if (!window_range(&g, &r, wait, ui->portrait[sp])) {
                                dw4_igb_record_free(&r); goto fail;
                            }
                        }
                    }
                }
        dw4_igb_record_free(&r);
    }
    dw4_igb_close(&g);
    if(ui->have_meter!=3 || ui->have_number!=7)goto fail;
    /* Language texture library images are standalone resources; they need not
     * be referenced by an igTextureAttr inside that library's own graphs. */
    if (dw4_igb_open(&g, common, common_size, 0) || dw4_igb_refs_open(&g)) goto fail;
    for (unsigned id = 0; id < g.table_n; id++) {
        dw4_igb_record image = {0}, clut = {0};
        if (!record(&g,id,&image)) continue;
        if (!strcmp(image.class_name,"igImage") && !dw4_scene_image_of(&ui->common,id) &&
            record(&g,slot(&image,17),&clut)) {
            dw4_scene_image *images = realloc(ui->common.img,(ui->common.nimg+1)*sizeof *images);
            if (!images) { dw4_igb_record_free(&image); dw4_igb_record_free(&clut); goto fail; }
            ui->common.img = images;
            dw4_scene_image *im = &images[ui->common.nimg++];
            *im = (dw4_scene_image){.id=id,.name=image.name,.w=slot(&image,2),.h=slot(&image,3),
                .size=slot(&image,12),.bpr=slot(&image,19),
                .grid=dw4_scene_handle(&ui->common,slot(&image,13)),
                .pal=dw4_scene_handle(&ui->common,slot(&clut,5))};
            /* Decoded strings borrow the mount's mapped pack, not the record. */
        }
        dw4_igb_record_free(&image); dw4_igb_record_free(&clut);
    }
    dw4_igb_close(&g);
    for (unsigned k = 0; k < 10; k++) {
        uint32_t root = ui->model[k].root;
        if (root == UINT32_MAX)
            goto fail;
        unsigned end = root + 1;
        while (end < scene->nnode && scene->node[end].depth > scene->node[root].depth)
            end++;
        /* SELECTCTRL's single-message mode chooses ram/branch 0, not all four
         * choice rows sharing this switch. */
        if (k >= 3 && root + 1 < end) {
            end = root + 2;
            while (end < scene->nnode && scene->node[end].depth > scene->node[root + 1].depth)
                end++;
        }
        for (unsigned j = root + 1; j < end; j++) {
            uint32_t mesh = dw4_scene_node_mesh(scene, j);
            if (mesh == UINT32_MAX)
                continue;
            if (ui->nitem == 128)
                goto fail;
            struct item *it = &ui->item[ui->nitem++];
            const char *why = NULL;
            it->node = j;
            it->model = k;
            uint32_t image = dw4_scene_node_texture(scene, j);
            it->tex = image ? texture(ui, scene, image) : NULL;
            const char *texture_name = dw4_scene_node_texture_name(scene, j);
            if (!it->tex && texture_name) for (unsigned ti = 0; ti < ui->common.nimg; ti++)
                if (ui->common.img[ti].name && !strcmp(ui->common.img[ti].name, texture_name)) {
                    it->tex = texture(ui, &ui->common, ui->common.img[ti].id); break;
                }
            if (!it->tex || dw4_scene_tris(scene, &scene->mesh[mesh], &it->tri, &it->nt, &why))
                goto fail;
        }
    }
    unsigned number_bound=0;
    for(unsigned i=0;i<ui->nitem;i++)for(unsigned n=0;n<3;n++){
        uint32_t node=ui->item[i].node;
        if(scene->node[node].id!=ui->number[n].geometry && dw4_scene_id_of(scene,scene->node[node].geometry)!=ui->number[n].geometry)continue;
        uint32_t mesh=dw4_scene_node_mesh(scene,node);
        for(unsigned v=0;v<ui->number[n].count;v++)if(ui->number[n].map[v].vertex>=scene->mesh[mesh].num_verts)goto fail;
        number_bound|=1u<<n;
    }
    if(number_bound!=7)goto fail;
    ui->atlas[0] = (dw4_tex){.rgba = ui->normal.atlas, .w = ui->normal.aw, .h = ui->normal.ah};
    ui->atlas[1] = (dw4_tex){.rgba = ui->minimum.atlas, .w = ui->minimum.aw, .h = ui->minimum.ah};
    return ui;
fail:
    dw4_igb_close(&g);
    dw4_lobbyui_close(ui);
    return NULL;
}
void dw4_lobbyui_close(dw4_lobbyui *ui)
{
    if (!ui)
        return;
    for(unsigned i=0;i<5;i++)dw4_modelctrl_close(ui->controller[i]);
    for (unsigned i = 0; i < ui->nitem; i++)
        free(ui->item[i].tri);
    for (unsigned i = 0; i < ui->ntex; i++)
        free((void *)ui->tex[i].rgba);
    dw4_scene_close(&ui->common);
    dw4_fefont_free(&ui->normal);
    dw4_fefont_free(&ui->minimum);
    free(ui->draw);
    free(ui);
}
void dw4_lobbyui_start(dw4_lobbyui *ui)
{
    if (ui && ui->phase == HIDDEN) {
        ui->page = 0;
        ui->phase = OPENING;
        ui->phase_age = 0;
    }
}
static int talk(const dw4_lobbyui *ui)
{
    return ui->page < 10 || ui->page >= 12;
}
void dw4_lobbyui_tick(dw4_lobbyui *ui, int advance)
{
    if (ui && ui->hud) {ui->hud_age++;for(unsigned k=0;k<2;k++)dw4_hudmeter_tick(&ui->meter[k]);}
    if (!ui || ui->phase == HIDDEN || ui->phase == DONE)
        return;
    if (ui->phase == READING)
        ui->window_age++;
    ui->phase_age++;
    struct window *w = &ui->model[talk(ui) ? 1 : 0];
    if (ui->phase == OPENING && ui->phase_age >= w->open[1] - w->open[0]) {
        ui->phase = READING;
        ui->phase_age = 0;
        ui->window_age = 0;
    } else if (!dw4_dialogue_claimed(ui->dialogue) && ui->phase == READING && advance) {
        if (ui->page == 2 || ui->page == 7 || ui->page == 9 || ui->page == 11 || ui->page == 14)
            ui->phase = CLOSING;
        else
            ui->page++;
        ui->phase_age = 0;
    } else if (ui->phase == CLOSING && ui->phase_age >= w->close[1] - w->close[0]) {
        ui->page++;
        ui->phase_age = 0;
        ui->phase = ui->page == 15 ? DONE : ui->page == 10 ? BEEP : OPENING;
    } else if (ui->phase == BEEP && ui->phase_age >= 90) {
        ui->phase = OPENING;
        ui->phase_age = 0;
    }
}
int dw4_lobbyui_message(const dw4_lobbyui *ui)
{
    if(ui && dw4_dialogue_claimed(ui->dialogue))for(size_t i=0;i<dw4_dialogue_text_count(ui->dialogue);i++) {
        const dw4_dialogue_text *text=dw4_dialogue_text_at(ui->dialogue,i);
        if(!text || !text->visible || strcmp(text->name,"font00") ||
           (strcmp(text->group,"TALKFONT01") && strcmp(text->group,"TALKFONT02")))continue;
        for(unsigned page=0;page<15;page++) {
            if(text->count!=ui->len[page])continue;
            size_t k=0;while(k<text->count && text->codes[k]==ui->text[page][k])k++;
            if(k==text->count)return 39+(int)page;
        }
    }
    return ui && ui->phase == READING ? 39 + ui->page : -1;
}
int dw4_lobbyui_page(const dw4_lobbyui *ui)
{
    return ui ? ui->page : -1;
}
int dw4_lobbyui_delay(const dw4_lobbyui *ui)
{
    return ui && ui->phase == BEEP;
}
int dw4_lobbyui_script_service(void *user,const char *method,
    const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_lobbyui *ui=user;
    if(!ui || n<4 || n>5 ||
       a[1].type!=DW4_SCRIPT_STRING || a[3].type!=DW4_SCRIPT_STRING)goto unsupported;
    int model=-1;
    static const char *names[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky"};
    for(int i=0;i<5;i++)if(!strcmp(names[i],a[1].string))model=i;
    if(model<0)return 0;
    if(!strcmp(method,"sd") || (ui->scripted & (1u<<model))) {
        int rc=dw4_modelctrl_service(ui->controller[model],method,a,n,r,error,cap);
        if(!rc && !strcmp(method,"sd"))ui->scripted|=1u<<model;
        return rc;
    }
    int active=ui->phase==OPENING || ui->phase==READING || ui->phase==CLOSING;
    int selected=talk(ui)?1:0;
    active=active && (model==selected || (model==2 && selected==1) ||
                     (ui->phase==READING && model==selected+3));
    if(n==4 && !strcmp(a[3].string,"ISRUN")) {
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,active,NULL,0};return 0;
    }
    if(n==5 && !strcmp(a[3].string,"ISSEQNAME") && a[4].type==DW4_SCRIPT_STRING) {
        const char *seq=model>=3?"SQ_LINESL00":
            ui->phase==OPENING?(selected?"SQ_OPENL":"SQ_OPEN"):
            ui->phase==CLOSING?(selected?"SQ_CLOSEL":"SQ_CLOSE"):
                              (selected?"SQ_WAITL":"SQ_WAIT");
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,active && !strcmp(seq,a[4].string),NULL,0};return 0;
    }
unsupported:
    snprintf(error,cap,"unsupported lobby window %s",method);return -1;
}
void dw4_lobbyui_services_sample(dw4_lobbyui *ui,int64_t ns)
{
    if(ui && !ui->frame_valid){ui->frame_clock=ns;ui->frame_valid=1;}
    if(ui)for(unsigned i=0;i<5;i++)dw4_modelctrl_sample(ui->controller[i],ns);
}
int dw4_lobbyui_services_tick(dw4_lobbyui *ui,int64_t ns)
{
    if(!ui)return -1;
    uint32_t frame=ui->frame_valid?dw4_modelsubcom_frame(ui->frame_clock,ns):0;ui->frame_clock=ns;ui->frame_valid=1;
    for(unsigned i=0;i<5;i++)if(dw4_modelctrl_tick_frame(ui->controller[i],ns,frame))return -1;
    {const dw4_modelctrl *tw=ui->controller[1];const char *q=(ui->scripted&2u) && dw4_modelctrl_active(tw)?dw4_modelctrl_sequence(tw):NULL;
     if(!q || strcmp(q,"SQ_CLOSEL"))ui->talk_close_t0=0;else if(!ui->talk_close_t0)ui->talk_close_t0=dw4_modelctrl_time(tw)?:1;}
    if(ui->hud){if(dw4_lobbyui_talk_open(ui))ui->hud_back=0;else if(ui->hud_back<3)ui->hud_back++;}
    return 0;
}
const char *dw4_lobbyui_services_error(const dw4_lobbyui *ui)
{
    if(!ui)return "no lobby windows";
    for(unsigned i=0;i<5;i++)if(*dw4_modelctrl_error(ui->controller[i]))return dw4_modelctrl_error(ui->controller[i]);
    return "";
}
void dw4_lobbyui_services_random(dw4_lobbyui *ui,dw4_random *random,uint32_t *rhythm)
{
    if(ui)for(unsigned i=0;i<5;i++)dw4_modelctrl_random(ui->controller[i],random,rhythm);
}
static dw4_ui_draw *push(dw4_lobbyui *ui)
{
    if (ui->ndraw == ui->cap) {
        unsigned cap = ui->cap ? 2 * ui->cap : 512;
        dw4_ui_draw *d = realloc(ui->draw, cap * sizeof *d);
        if (!d)
            return NULL;
        ui->draw = d;
        ui->cap = cap;
    }
    dw4_ui_draw *d = ui->draw + ui->ndraw++;
    memset(d, 0, sizeof *d);
    d->stq = 1;
    d->blend = 1;
    for (unsigned e = 0; e < 3; e++)
        for (unsigned c = 0; c < 4; c++)
            d->rgba[e][c] = c == 3 ? 128 : 127;
    return d;
}
/* Font geometry uses 100 pixels per unit, ceil(advance*100), and its metric
 * width/height (not atlas texel dimensions). The text origin is the baseline;
 * NORMAL's 0.28 line height gives 28-pixel lines. */
static float text_align(const dw4_fefont *font,const uint32_t *codes,unsigned n,unsigned start,float width,int align)
{
    float length=0;
    for(unsigned i=start;i<n;i++) {
        if(codes[i]=='\n')break;
        const dw4_glyph *g=dw4_fefont_glyph(font,codes[i]);
        float advance=g?ceilf(g->advance*100):0;
        if(length+advance>width)break;
        length+=advance;
    }
    return align==1?width-length:align==2?(width-length)*.5f:0;
}
static void text_state(dw4_lobbyui *ui, dw4_fb *fb, const dw4_fefont *font, const dw4_tex *atlas,
                 const struct layout *layout, const uint32_t *codes, unsigned n,const float color[3],int align)
{
    float pen = 0, line = 0, unit = 100, sx = fb->w / 640.0f, sy = fb->h / 448.0f;
    float line_height = font->height * unit;
    float offset=text_align(font,codes,n,0,layout->width*unit,align);
    for (unsigned i = 0; i < n; i++) {
        uint32_t code = codes[i];
        const dw4_glyph *g = dw4_fefont_glyph(font, code);
        if (code == '\r')
            continue;
        float adv = g ? ceilf(g->advance * unit) : 0;
        if (code == '\n' || pen + adv > layout->width * unit) {
            pen = 0;
            line += line_height;
            offset=text_align(font,codes,n,i+(code=='\n'),layout->width*unit,align);
            if (code == '\n')
                continue;
        }
        if (!g || code < 32 || line + g->h * unit > layout->height * unit + 0.01f)
            continue;
        float x = layout->x + offset + pen + g->bx * unit,
              y = layout->y + line - g->h * unit - g->by * unit - font->baseline * unit;
        float v[4][5] = {{x * sx, y * sy, g->u0, g->v1, 1},
                         {(x + g->w * unit) * sx, y * sy, g->u1, g->v1, 1},
                         {(x + g->w * unit) * sx, (y + g->h * unit) * sy, g->u1, g->v0, 1},
                         {x * sx, (y + g->h * unit) * sy, g->u0, g->v0, 1}};
        for (unsigned k = 0; k < 2; k++) {
            dw4_ui_draw *d = push(ui);
            if (!d)
                return;
            d->tex = atlas;
            memcpy(d->v[0], v[0], sizeof v[0]);
            memcpy(d->v[1], v[k + 1], sizeof v[0]);
            memcpy(d->v[2], v[k + 2], sizeof v[0]);
            for (unsigned e = 0; e < 3; e++) {
                for(unsigned c=0;c<3;c++)d->rgba[e][c]=(uint8_t)fminf(128,fmaxf(0,color[c]*127));
                d->rgba[e][3] = 121;
            }
        }
        pen += adv;
    }
}
static void text(dw4_lobbyui *ui,dw4_fb *fb,const dw4_fefont *font,const dw4_tex *atlas,
    const struct layout *layout,const uint32_t *codes,unsigned n,int yellow)
{
    const float color[]={.9f,.9f,yellow?.475f:.9f};
    text_state(ui,fb,font,atlas,layout,codes,n,color,0);
}
void dw4_lobbyui_dialogue(dw4_lobbyui *ui,dw4_dialogue *d){if(ui)ui->dialogue=d;}
const dw4_ui_draw *dw4_lobbyui_draws(const dw4_lobbyui *ui, unsigned *n)
{
    if (n)
        *n = ui ? ui->ndraw : 0;
    return ui ? ui->draw : NULL;
}
int dw4_lobbyui_draw_backend(dw4_lobbyui *ui, dw4_fb *fb, dw4_gl_layer **gpu)
{return dw4_lobbyui_draw_parts(ui,fb,gpu,DW4_LOBBYUI_MODELS|DW4_LOBBYUI_TEXT);}
int dw4_lobbyui_draw_parts(dw4_lobbyui *ui, dw4_fb *fb, dw4_gl_layer **gpu, unsigned parts)
{
    if (!ui || !fb)
        return 0;
    ui->ndraw = 0;
    if(ui->status)return 0;
    const int hide_hud=ui->hud && dw4_lobbyui_talk_open(ui); /* retail closes the HUD while a message window is open */
    if (!dw4_dialogue_claimed(ui->dialogue) && !ui->scripted && !ui->hud && (ui->phase == HIDDEN || ui->phase == BEEP || ui->phase == DONE))
        return 0;
    unsigned model = talk(ui) ? 1 : 0;
    struct item *sorted[128];
    unsigned count = 0;
    for (unsigned k = 0; (parts & DW4_LOBBYUI_MODELS) && k < 10; k++) {
        int scripted=k<5 && (ui->scripted & (1u<<k));
        if(hide_hud && !scripted)continue;
        if(ui->party && k>=5)continue; /* the HUD pieces only: the message windows are scripted models */
        if(!scripted && !ui->hud && (ui->phase==HIDDEN || ui->phase==BEEP || ui->phase==DONE))continue;
        if (scripted ? !dw4_modelctrl_active(ui->controller[k]) : ui->hud ? (k < 5) :
            (k >= 5 || (k != model && !(model == 1 && k == 2) && !(ui->phase == READING && k == model + 3))))
            continue;
        struct window *w = ui->model + k;
        float frame=0;
        if (!scripted && (k >= 3 || ui->phase == READING)) {
            float duration = w->loop[1] - w->loop[0];
            frame = w->loop[0] +
                    (duration > 0 ? fmodf(ui->hud ? ui->hud_age : k >= 3 ? ui->phase_age : ui->window_age, duration) : 0);
        } else if(!scripted) {
            float *range = ui->phase == OPENING ? w->open : w->close;
            frame = fminf(range[1], range[0] + ui->phase_age);
        }
        for (unsigned j = w->root + 1;
             j < ui->scene->nnode && ui->scene->node[j].depth > ui->scene->node[w->root].depth; j++)
            if (ui->scene->node[j].has_seq) {
                int64_t time=scripted?dw4_modelctrl_time(ui->controller[k]):(long long)(frame*1000000000.0/60.0);
                if(ui->hud)for(unsigned m=0;m<2;m++){
                    uint32_t ancestor=j;
                    while(ancestor<ui->scene->nnode && ancestor!=w->root){
                        if(ui->scene->node[ancestor].id==ui->meter_node[m]){time=ui->meter[m].time;break;}
                        ancestor=ui->scene->node[ancestor].parent;
                    }
                }
                dw4_scene_node_drive(ui->scene,j,0,time);
            }
        dw4_scene_set_engine_time(ui->scene, 0);
        for (unsigned j = 0; j < ui->nitem; j++)
            if (ui->item[j].model == k) {
                struct item *it = ui->item + j;
                float world[16];
                dw4_scene_node_world(ui->scene, it->node, world);
                /* Compose the HUD face over the animated circular frame. The
                 * other HUD panels keep scene order: the MP dots' transforms
                 * carry the -135 depth (their vertices are at 0), unlike the
                 * HP ring (vertex -135, transform 0), so a transform-depth
                 * sort put the lit dots under the -127 dark socket ring. */
                it->z = ui->hud ? (it->model == 7 ? INFINITY : 0) : world[14];
                unsigned p = count;
                while (p && sorted[p - 1]->z > it->z) {
                    sorted[p] = sorted[p - 1];
                    p--;
                }
                sorted[p] = it;
                count++;
            }
    }
    const unsigned first_item_draw=ui->ndraw;
    for (unsigned i = 0; i < count; i++) {
        struct item *it = sorted[i];
        const dw4_scene_mesh *mesh = ui->scene->mesh + dw4_scene_node_mesh(ui->scene, it->node);
        const float *pos = dw4_scene_host(ui->scene, mesh->positions),
                    *uv = dw4_scene_host(ui->scene, mesh->uvs);
        float w[16], du = 0, dv = 0;
        dw4_scene_node_uv_offset(ui->scene, it->node, &du, &dv);
        if (!pos || !uv || dw4_scene_node_world(ui->scene, it->node, w))
            continue;
        if (ui->hud && it->model >= 6) { w[12] -= 260; w[13] -= 160; }
        for (unsigned t = 0; t < it->nt; t++) {
            dw4_ui_draw *d = push(ui);
            if (!d)
                return -1;
            d->tex = it->tex;
            for (unsigned e = 0; e < 3; e++) {
                unsigned v = it->tri[3 * t + e];
                float x = pos[3 * v], y = pos[3 * v + 1], z = pos[3 * v + 2];
                d->v[e][0] = (320 + x * w[0] + y * w[4] + z * w[8] + w[12]) * fb->w / 640.0f;
                d->v[e][1] = (224 - x * w[1] - y * w[5] - z * w[9] - w[13]) * fb->h / 448.0f;
                d->v[e][2] = uv[2 * v] + du;
                d->v[e][3] = uv[2 * v + 1] + dv;
                if(ui->hud)for(unsigned number=0;number<3;number++){
                    struct number *num=&ui->number[number];
                    if(ui->scene->node[it->node].id!=num->geometry && dw4_scene_id_of(ui->scene,ui->scene->node[it->node].geometry)!=num->geometry)continue;
                    static const int32_t hp[16]={180,160,150,170,170,170,170,170,170,170,170,170,170,170,170,170},mp[16]={50,70,80,60,60,60,60,60,60,60,60,60,60,60,60,60};   /* by shinka row; only the starters have a fixed first value */
                    int32_t value=ui->health_set?ui->health[number]:number==0?1:number==1?hp[ui->species]:mp[ui->species];
                    if((uint32_t)value>num->max)value=(int32_t)num->max;
                    for(unsigned nv=0;nv<num->count;nv++)if(num->map[nv].vertex==v){
                        dw4_hudnumber_uv(dw4_hudnumber_digit(value,num->mode,num->map[nv].place),num->map[nv].kind,num->offset,&d->v[e][2]);break;
                    }
                }
                d->v[e][4] = 1;
            }
        }
    }
    /* Retail frames after a message: the HUD (ring, digits, band, label) is not drawn while the window is up, and comes back with a fade over three
     * frames (about 40%, 80%, full at frames 34, 35, 36 after the closing press) instead of at full strength. */
    if(ui->hud && ui->hud_back<3){
        const float f=(float)ui->hud_back/3.f;
        for(unsigned i=first_item_draw;i<ui->ndraw;i++){dw4_ui_draw *d=ui->draw+i;
            for(unsigned e=0;e<3;e++){
                if(d->blend==2)for(unsigned c=0;c<3;c++)d->rgba[e][c]=(uint8_t)(d->rgba[e][c]*f);
                else d->rgba[e][3]=(uint8_t)(d->rgba[e][3]*f);}}
    }
    if ((parts & DW4_LOBBYUI_TEXT) && !ui->hud && !dw4_dialogue_claimed(ui->dialogue) && ui->phase == READING && (!(ui->scripted & (1u<<model)) ||
               (dw4_modelctrl_active(ui->controller[model]) &&
                (!strcmp(dw4_modelctrl_sequence(ui->controller[model]),"SQ_WAIT") ||
                 !strcmp(dw4_modelctrl_sequence(ui->controller[model]),"SQ_WAITL"))))) {
        text(ui, fb, &ui->normal, &ui->atlas[0], &ui->layout[model], ui->text[ui->page],
             ui->len[ui->page], 0);
        if (model == 1)
            text(ui, fb, &ui->minimum, &ui->atlas[1], &ui->layout[2], ui->speaker, ui->nspeaker, 1);
    }
    if((parts & DW4_LOBBYUI_TEXT) && dw4_dialogue_claimed(ui->dialogue)) {
        const dw4_ui_draw *draws;size_t n;
        if(dw4_dialogue_draw(ui->dialogue,fb->w,fb->h,&draws,&n))return -1;
        for(size_t i=0;i<n;i++){dw4_ui_draw *d=push(ui);if(!d)return -1;*d=draws[i];}
    }
    int wrap = dw4_render_tex_wrap, linear = dw4_render_tex_linear, aref = dw4_render_aref;
    dw4_render_tex_wrap = 1;
    dw4_render_tex_linear = 1;
    dw4_render_aref = 12;
    dw4_gl_layer_ui_or_cpu(gpu, fb, ui->draw, ui->ndraw, 8);
    dw4_render_tex_wrap = wrap;
    dw4_render_tex_linear = linear;
    dw4_render_aref = aref;
    return (int)ui->ndraw;
}

int dw4_lobbyui_draw(dw4_lobbyui *ui, dw4_fb *fb)
{
    dw4_gl_layer *gpu = NULL;
    return dw4_lobbyui_draw_backend(ui, fb, &gpu);
}

void dw4_lobbyui_restore_hud(dw4_lobbyui *ui, int species)
{
    if (!ui || ui->hud || species < 0 || species > 15) return;
    ui->hud = 1; ui->hud_age = 0; ui->hud_back = 3; ui->species = species;
    memcpy(ui->model[7].loop, ui->portrait[species], sizeof ui->model[7].loop);
}

void dw4_lobbyui_party(dw4_lobbyui *ui,int party){if(ui)ui->party=!!party;}
/* The speaker's window (i_talkwn) is generated when the message opens and removed when its closing range ends: retail frames
 * (Digi-Elf, one frame apart) show the HUD gone within a frame of the press, before the window has opened or any text shows, and
 * back after the window has closed, so the window's life brackets the hidden span, not the text. */
int dw4_lobbyui_talk_open(const dw4_lobbyui *ui)
{
    if(!ui)return 0;
    if(dw4_dialogue_talk_open(ui->dialogue))return 1;
    if(!(ui->scripted&2u) || !dw4_modelctrl_active(ui->controller[1]))return 0;
    /* The return is not at the window's removal: retail frames put the HUD back about 11 frames after the closing range starts (the authored range is 16),
     * so the window is still collapsing while the HUD slides in (a measured offset: the script or engine event that triggers it is not recovered). */
    return !(ui->talk_close_t0 && dw4_modelctrl_time(ui->controller[1])-ui->talk_close_t0>=11*16666667);
}
void dw4_lobbyui_status(dw4_lobbyui *ui,int active){if(ui)ui->status=!!active;}
int dw4_lobbyui_health(dw4_lobbyui *ui,int32_t level,int32_t hp,int32_t mp,int32_t max_hp,int32_t max_mp)
{
    if(!ui || level<0 || hp<0 || mp<0 || max_hp<=0 || max_mp<=0 || hp>max_hp || mp>max_mp)return -1;
    ee_f32 hp_percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(hp),0x42c80000),ee_f32_from_s32(max_hp));
    ee_f32 mp_percent=ee_f32_div(ee_f32_mul(ee_f32_from_s32(mp),0x42c80000),ee_f32_from_s32(max_mp));
    float percent;memcpy(&percent,&hp_percent,4);dw4_hudmeter_percent(&ui->meter[0],percent);
    memcpy(&percent,&mp_percent,4);dw4_hudmeter_percent(&ui->meter[1],percent);
    ui->health_set=1;ui->health[0]=level;ui->health[1]=hp;ui->health[2]=mp;ui->health[3]=max_hp;ui->health[4]=max_mp;return 0;
}
const dw4_modelctrl *dw4_lobbyui_model(const dw4_lobbyui *ui,unsigned i){return ui && i<5?ui->controller[i]:NULL;}

const dw4_hudmeter *dw4_lobbyui_meter(const dw4_lobbyui *ui,unsigned index,uint32_t *node)
{if(!ui || index>=2)return NULL;if(node)*node=ui->meter_node[index];return &ui->meter[index];}

int dw4_lobbyui_health_publish(dw4_lobbyui *ui,const dw4_playerhealth *h)
{
    if(!ui || !h)return -1;
    static const int32_t hp[16]={180,160,150,170,170,170,170,170,170,170,170,170,170,170,170,170};
    int32_t old_hp=ui->health_set?ui->health[1]:hp[ui->species];
    int32_t old_max=ui->health_set?ui->health[3]:hp[ui->species];
    dw4_hudmeter old_meter=ui->meter[0];
    int rc=dw4_lobbyui_health(ui,h->level,h->hp,h->mp,h->max_hp,h->max_mp);
    if(!rc && !h->hp_publish){ui->health[1]=old_hp;ui->health[3]=old_max;ui->meter[0]=old_meter;}
    return rc;
}
