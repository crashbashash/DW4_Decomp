#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include <limits.h>
#include "dw4/lobby.h"
#include "dw4/playerpoint.h"
#include "dw4/materialcontact.h"
#include "dw4/modelview.h"
#include "dw4/gpupolicy.h"
#include "dw4/igfile.h"
#include "dw4/scene.h"
#include "dw4/texpack.h"
#include "dw4/igb.h"
#include "dw4/actoranim.h"
#include "dw4/lobbyui.h"
#include "dw4/frontaudio.h"
#include "dw4/options.h"
#include "dw4/npcmotion.h"
#include "dw4/modelai.h"
#include "dw4/modelsubcom.h"
#include "dw4/hitbox.h"
#include "dw4/controllers.h"
#include "dw4/padrepeat.h"
#include "dw4/lobbycollision.h"
#include "lobby_arrival.h"
#include "dw4/gl_layer.h"
#include "dw4/action2host.h"
#include "dw4/cameratime.h"
#include "dw4/boxcamera.h"
#include "lobbyclip.h"
#include "lobbyfade.h"
#include "lobbyparticle.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
/* beHitLandDelivInfoRam _checkFlag of the players (7: read from retail savestates, all 16 species' packs) and the default of a model without a record (3, the
 * InitFields value at 0x35e860): which wall infos the model collides with (dw4_hitland_info_applies). */
#define DW4_PLAYER_CHECK_FLAG 7u
#define DW4_ACTOR_CHECK_FLAG 3u

struct lobby_texture { uint32_t id; const dw4_scene *source; const char *name; uint8_t *mode_rgba[2]; dw4_tex tex; };
struct instance_motion {char *name;dw4_actoranim *animation;struct instance_motion *next;};
struct lobby_mesh { unsigned slot;uint32_t node, *tri, nt; const dw4_tex *tex; const dw4_scene *source; int actor, effect, shadow, caster_only, arrival, attachment; unsigned instance;int skinned,casts_shadow;struct instance_motion *motions;float bmin[3],bmax[3];int bounds; };
struct world_instance {const dw4_modelctrl *model;uint32_t root,end,database;char layer[16],name[48];};
struct actor_collision_owner {dw4_lobby *lobby;unsigned actor;};
enum { PORTAL_WAIT, PORTAL_OFF, PORTAL_ON, PORTAL_RISE, PORTAL_FALL };
struct portal_program {
    dw4_action2_component component[8];
    char name[8][16], loop[8][4];
    unsigned count;
    float fade_frames;
    int fade_in;
};
struct lobby_portal {
    uint32_t root;
    float pos[3];
    struct portal_program program[5];
    dw4_action2_host clock;
    unsigned started;
    int action, powered, active, visible;
    lobby_fade fade;
};
/* One joined player's presentation and walk state: its character pack and weapon, the idle/run/jump motions, the model controller, the pad
 * input and the world matrix. The lobby acts on the slot `l->p` points at (slot 0 unless a per-slot call selected another). */
struct lobby_player {
    dw4_lobby *lobby;unsigned slot;int joined;   /* the owning lobby, the player slot 0..3, and whether the slot has a player */
    dw4_scene player, weapon;
    char weapon_asset[32], weapon_bone[64], player_motion[32], weapon_label[16];
    uint32_t weapon_root,weapon_roots[16];unsigned weapon_count;char weapon_bones[16][64];
    unsigned weapon_submitted_triangles,weapon_submitted[16];
    dw4_actoranim *player_idle, *player_shadow;
    dw4_actoranim *player_run,*player_run_shadow;
    dw4_actoranim *player_jump[12][2];
    dw4_modelctrl *player_controller;
    float input_x,input_y;unsigned player_contacts;int jump_pressed,talk_pressed,talk_hits;
    char player_run_motion[32];
    uint64_t player_token,player_model_token;
    uint32_t player_node, player_shadow_node;
    float player_world[16];
    unsigned player_start;
    float player_fade;
    lobby_fade player_alpha;
    int64_t player_idle_start,player_previous_start;
    int player_loop;
    char player_name[9];
    int species;   /* the shinka row of the player's model */
};
struct dw4_lobby {
    struct lobby_player pl[4];   /* slot 0 is the created card's player; slots 1-3 are the other joined players (local co-op) */
    struct lobby_player *p;      /* the slot the code below acts on: pl+0 unless a per-slot call has selected another */
    int terminal,dynamic_world;
    struct world_instance *instances;unsigned ninstance;
    dw4_scene_node *instance_nodes;size_t mesh_capacity;
    int32_t arrival_point;
    char stage[16];int field;
    dw4_igfile stage_file;
    dw4_scene scene;
    uint32_t background_scene;
    dw4_actoranim *npc_motion[3], *female_motion[3];
    dw4_controllers *native_models;
    const dw4_modelctrl *native_actor[3];
    const dw4_modelctrl *native_fade,*native_portal[4];
    struct actor_collision_owner collision_owner[3];
    int64_t native_motion_ns[3];
    uint64_t native_origin,native_now,native_frame_clock;uint32_t native_frame;
    dw4_scriptservices *native_sd;
    struct world_cache {uint32_t node;const float *pos;unsigned n;float world[16];unsigned stable;float *w;} *wcache;size_t nwcache;
    int badge_live;
    uint64_t badge_active_ns;  /* game clock of the last stick/jump/talk input or lost control */
    uint32_t npc_node, female_node;
    float npc_pos[3], npc_yaw, female_pos[2][3], female_yaw[2];
    float point_matrix[8][4][16];unsigned char point_ok[8][4];   /* authored arrival points by group and player (PLAYERgetDataStr) */
    int female_index, second_index;
    unsigned second_start;
    dw4_npc_motion walk[3], turn[3]; /* male, guide, second female */
    dw4_lobby_collision collision;
    dw4_controllers *dyn_owner;size_t dyn_count;const dw4_modelctrl **dyn_model;   /* the model instance of each dynamic prop wall node (collision.dynamic[i]), resolved against dyn_owner */
    ee_f32 move_value, move_frame, stop_value, stop_frame;
    ee_f32 turn_value, turn_frame, turn_time, turn_stop, turn_stop_frame;
    int64_t guide_turn_wait, guide_walk_wait, male_turn_wait, action_start[3];
    unsigned phase[3], contacts[3], relocation;
    float guide_arrival_square, guide_rot_limit;
    dw4_scriptengine *scripts;
    dw4_be_state *script_state;
    uint64_t script_scope;
    dw4_script_model guide_model;
    dw4_model_ai_choice guide_ai[4][16];
    char guide_sequence[4][16][32];
    unsigned guide_count[4],guide_events,guide_choices;
    ee_f32 guide_bounds[3];
    int64_t guide_ai_deadline;
    int guide_ai_started,guide_choice;
    char script_error[512];
    unsigned female_start;
    unsigned age, restore, motion_start;
    dw4_lobbyui *ui;
    dw4_frontaudio *audio;
    dw4_gl_layer *gpu,*shadow_gpu;
    int npc_motion_index;
    int message, finished, species;
    int status_hold;
    dw4_lobby_control_state control;
    struct { float min[3], max[3], eye[16], interest[16]; } *box;
    unsigned nbox, nmaterial;
    struct { char name[32]; float min[3], max[3]; int inside; uint8_t run; } material[32];
    dw4_material_contact material_context;
    int exit_events;
    dw4_dialogue *native_dialogue;
    dw4_modelview *native_ui; /* borrowed; detached before controller teardown */
    struct lobby_texture *texture;
    unsigned ntexture;
    struct lobby_mesh *mesh;
    unsigned nmesh;
    uint32_t camera;
    dw4_camera_time camera_time;
    dw4_boxcamera box_camera;
    struct {int active;char code[24];float value,one_time,end;uint32_t start;} shake;   /* CAMERA SHAKE "<digits>/F<value>/F<oneTime>/F<endTime>" */
    int camera_scripted, camera_demo;
    /* A dungeon floor keeps its cameras outside the world pack: the box rig in <stage>/separate/aaacamera.igb (aaacameral.igb is the Far
     * Dungeon camera option) and the named demo cameras ("entry") in acmr_pack.igb. Their igCamera nodes live in this scene. */
    dw4_scene camera_pack;int ext_camera;
    /* Named demo cameras of a non-Terminal hub (beCameraCtrlInfo -> beCameraDemoData), e.g. the Commander Room's camsp0201,
     * ofani1, seratalk, seratalk2 and alarmoff: each drives the igCamera of the scene graph with its name. */
    struct { char name[32]; uint32_t node; uint64_t end; } demo[8];
    unsigned ndemo;
    uint8_t collision_off[64]; /* HITLANDMODEL OFFHIT: info-owned collision graphs removed from walking (scene->collision index) */
    uint64_t collision_part_off[64]; /* the same per door: bit i = the graph's i-th mesh (a name's place in its info's list) switched off */
    struct { char name[32]; uint32_t info; uint32_t index,count; } hit_name[64]; /* beHitLandModelInfo slot 9 igNamedObjectList names -> info id */
    unsigned nhit_name;
    float near_plane,far_plane;
    float fog_start, fog_end;
    uint8_t fog_color[3];
    struct lobby_portal effect[4];
    struct {
        struct portal_program program;
        uint32_t root,node[3];
        dw4_action2_host clock[3];
        lobby_fade fade[3];
        unsigned serial[3];
        int active[3];
        ee_f32 delay[3],run_frame;
        float offset[3][3],rotation[3][3];
    } rings;
    struct {
        float curve[8][45], lifetime, offset[3];
        ee_f32 delay, run[3];
        int64_t start[3];
        uint32_t node;
        const dw4_tex *tex;
        int blend,aref;
        unsigned count, started;
    } stars;
    unsigned hidden_actors;
    int light_hard;
    float soft_ambient[4], soft_diffuse[4], light_direction[3];
    float hard_ambient[3],hard_diffuse[3];
    struct portal_program arrival_fade;
    lobby_fade screen_alpha;
    /* The tick on which PLAYER SQ_ENTR starts the player's TRNSS1 entry (x_100trnsin01 rings, y_100trnsin01 stars):
     * the bounded adapter's generated greeting delay, or UINT_MAX until original first.lua dispatches SQ_ENTR. */
    unsigned entry_tick;
    dw4_fb shadow_fb;
    dw4_tex shadow_tex;
    dw4_layer_draw *casters;
    float shadow_bounds[4], shadow_factor;
    uint32_t shadow_receiver[2];
    dw4_layer_draw *draw;
    unsigned capacity, ndraw;
    dw4_texpack pack[2];
    dw4_igb texture_ids[2];
};

static const dw4_tex *named_texture(dw4_lobby *l, const char *name)
{
    unsigned i, p;
    if (!name) return NULL;
    for (i = 0; i < l->ntexture; i++)
        if (l->texture[i].name && !strcmp(l->texture[i].name, name))
            return &l->texture[i].tex;
    uint8_t *variant[2] = {0};
    int w = 0, h = 0;
    /* The scoped pair is Hard 821 / Soft 822; both carry the same logical
     * texture names with mode-specific palettes and index grids. */
    for (p = 0; p < 2; p++) {
        const dw4_texpack_tex *t = dw4_texpack_find(&l->pack[p], name);
        uint32_t ng, np;
        if (!t || (p && (w != (int)t->w || h != (int)t->h))) goto missing;
        w = t->w; h = t->h;
        const uint8_t *grid = dw4_igb_block(&l->texture_ids[p], t->image_id, &ng);
        const uint8_t *pal = dw4_igb_block(&l->texture_ids[p], t->clut_id, &np);
        if (!grid || !pal || ng < t->w*t->h || np < 1024) goto missing;
        variant[p] = malloc((size_t)w*h*4);
        if (!variant[p]) goto missing;
        /* Stored row order, exact remap/pool addressing, GS alpha range. */
        for (uint32_t pixel = 0; pixel < t->w*t->h; pixel++) {
            const uint8_t *c = pal + 4*grid[pixel];
            memcpy(variant[p] + 4*pixel, c, 3);
            variant[p][4*pixel+3] = (c[3]+1u)/2u;
        }
    }
    i = l->ntexture++;
    l->texture[i].name = name;
    l->texture[i].mode_rgba[1] = variant[0];
    l->texture[i].mode_rgba[0] = variant[1];
    l->texture[i].tex = (dw4_tex){.rgba=l->texture[i].mode_rgba[l->light_hard], .w=w, .h=h};
    return &l->texture[i].tex;
missing:
    free(variant[0]); free(variant[1]);
    fprintf(stderr, "  lobby: missing texture %s\n", name);
    return NULL;
}

int dw4_lobby_player(const dw4_lobby *l, dw4_lobby_player_state *out)
{
    if (!l || !out) return -1;
    *out = (dw4_lobby_player_state){l->p->weapon_asset, l->p->weapon_label,
                                  l->p->player_motion, l->p->weapon_bone, 0,l->p->weapon_submitted_triangles};
    for (unsigned i = 0; i < l->nmesh; i++)
        if (l->mesh[i].source == &l->p->weapon) out->weapon_triangles += l->mesh[i].nt;
    return 0;
}

unsigned dw4_lobby_weapon_parts(const dw4_lobby *l){return l?l->p->weapon_count:0;}
int dw4_lobby_weapon_part(const dw4_lobby *l,unsigned index,dw4_lobby_weapon_part_state *out)
{
    if(!l || !out || index>=l->p->weapon_count)return -1;
    *out=(dw4_lobby_weapon_part_state){l->p->weapon_bones[index],0,l->p->weapon_submitted[index]};
    for(unsigned i=0;i<l->nmesh;i++)if(l->mesh[i].source==&l->p->weapon && l->mesh[i].attachment==(int)index)
        out->triangles+=l->mesh[i].nt;
    return 0;
}
static const dw4_tex *texture(dw4_lobby *l, const dw4_scene *source, uint32_t id)
{
    const dw4_scene_image *im;
    const dw4_scene_ent *grid_ent, *pal_ent;
    const uint8_t *grid, *pal;
    uint8_t *rgba;
    unsigned i, x, y;
    if (!id) return NULL;
    for (i = 0; i < l->ntexture; i++)
        if (l->texture[i].source == source && l->texture[i].id == id) return &l->texture[i].tex;
    im = dw4_scene_image_of(source, id);
    if (!im || !im->w || !im->h || im->bpr < im->w ||
        im->w > 8192 || im->h > 8192) return NULL;
    grid = dw4_scene_host(source, im->grid);
    pal = dw4_scene_host(source, im->pal);
    grid_ent = dw4_scene_lookup(source, dw4_scene_id_of(source, im->grid));
    pal_ent = dw4_scene_lookup(source, dw4_scene_id_of(source, im->pal));
    if (!grid || !pal || !grid_ent || !pal_ent || pal_ent->size < 1024 ||
        (uint64_t)im->bpr * im->h > grid_ent->size) return NULL;
    rgba = malloc((size_t)im->w * im->h * 4);
    if (!rgba) return NULL;
    for (y = 0; y < im->h; y++) for (x = 0; x < im->w; x++) {
        unsigned index = grid[y*im->bpr+x]*4, out = (y*im->w+x)*4;
        memcpy(rgba+out, pal+index, 3);
        rgba[out+3] = (pal[index+3]+1u)/2u;
    }
    i = l->ntexture++;
    l->texture[i].id = id;
    l->texture[i].source = source;
    l->texture[i].tex = (dw4_tex){.rgba=rgba, .w=(int)im->w, .h=(int)im->h};
    return &l->texture[i].tex;
}

static uint32_t record_slot(const dw4_igb_record *r, unsigned slot)
{
    for (unsigned i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == slot) return r->values[i].raw;
    return UINT32_MAX;
}

static int object_record(const dw4_igb *g, uint32_t id, dw4_igb_record *r)
{
    return id < g->table_n && g->id_kind[id] == 2 && dw4_igb_decode(g, g->id_off[id], r);
}

static int named_record(const dw4_igb *g, const char *cls, const char *name,
                        dw4_igb_record *out)
{
    for (uint32_t i = 0; i < g->table_n; i++) {
        dw4_igb_record r = {0};
        if (!object_record(g, i, &r)) continue;
        if (!strcmp(r.class_name, cls) && (!name || (r.name && !strcmp(r.name, name)))) {
            *out = r; return 0;
        }
        dw4_igb_record_free(&r);
    }
    return -1;
}
static const uint8_t *record_list(const dw4_igb *g, uint32_t id, uint32_t *count)
{
    dw4_igb_record r = {0};
    uint32_t size;
    const uint8_t *data;
    *count = 0;
    if (!object_record(g, id, &r)) return NULL;
    data = dw4_igb_block(g, record_slot(&r, 4), &size);
    uint32_t n = record_slot(&r, 2);
    dw4_igb_record_free(&r);
    if (!data || n > size/4) return NULL;
    *count = n;
    return data;
}
static uint32_t list_id(const uint8_t *data, unsigned i)
{
    uint32_t id; memcpy(&id, data+4*i, 4); return id;
}
static int player_sequence_motion(const dw4_igb *g,const char *sequence,const char *label,char motion[32])
{
    dw4_igb_record r = {0};
    uint32_t count;
    const uint8_t *data;
    char action[32] = {0};
    int active = 0;
    if (named_record(g, "beModelCtrlData", sequence, &r)) return -1;
    data = record_list(g, record_slot(&r, 3), &count);
    dw4_igb_record_free(&r);
    if (!data) return -1;
    for (unsigned i = 0; i < count; i++) {
        if (!object_record(g, list_id(data, i), &r)) return -1;
        if (!strcmp(r.class_name, "beModelCtrlLABEL")) active = r.name && !strcmp(r.name, label);
        if (active && !strcmp(r.class_name, "beModelCtrlACTION") && r.name)
            snprintf(action, sizeof action, "%s", r.name);
        dw4_igb_record_free(&r);
        if (*action) break;
    }
    if (!*action || named_record(g, "beAction2Data", action, &r)) return -1;
    data = record_list(g, record_slot(&r, 3), &count);
    dw4_igb_record_free(&r);
    if (!data) return -1;
    for (unsigned i = 0; i < count; i++) {
        if (!object_record(g, list_id(data, i), &r)) return -1;
        int found = !strcmp(r.class_name, "beAction2MOTIONSET") && r.name;
        if (found) snprintf(motion, 32, "%s", r.name);
        dw4_igb_record_free(&r);
        /* RUNN starts a wait pose then replaces it with the run component. */
    }
    return *motion?0:-1;
}
static int list_column(const dw4_igb *g, uint32_t list, const char *name, uint32_t *columns)
{
    const uint8_t *data = record_list(g, list, columns);
    if (!data) return -1;
    for (unsigned i = 0; i < *columns; i++) {
        dw4_igb_record r = {0};
        if (!object_record(g, list_id(data, i), &r)) return -1;
        int match = r.name && !strcmp(r.name, name);
        dw4_igb_record_free(&r);
        if (match) return (int)i;
    }
    return -1;
}
/* Player models by shinka row (the order of GAMERAM's DIGIMONNO: the four starters, then the twelve evolved forms); each has an
 * `m_<name>.igb` actor pack. The lobby API's legacy `species` argument is 0..3 in the order dorumon, agumon, vmon, girumon. */
static const char *const lobby_models[16]={"p_agumon","p_vmon","p_girumon","p_dorumon","p_weregaru","p_hekabut","p_wargrey","p_angelr",
    "p_beelzeb","p_alpha","p_bwargrey","p_impdrafm","p_impdrapm","p_metalgaru","p_dukecrim","p_susanoo"};
static const int lobby_starter_row[4]={3,0,1,2};
static int lobby_asset_name(int row,char out[32]){return row<0||row>15||snprintf(out,32,"m_%s.igb",lobby_models[row]+2)>=32?-1:0;}
const char *dw4_lobby_model_name(int row){return row>=0&&row<16?lobby_models[row]:NULL;}
/* Read the created-card starter from species INI_WEAPON1 and weapon MODEL. */
static int starter_asset(dw4_mount *mnt, const char *model, char asset[32])
{
    dw4_igb g = {0};
    uint32_t size, initial = UINT32_MAX;
    const uint8_t *blob = dw4_mount_data(mnt, "usa_pack.igb", &size);
    int result = -1;
    if (!blob || dw4_igb_open(&g, blob, size, 0) || dw4_igb_refs_open(&g)) goto done;
    for (unsigned i = 0; i < g.table_n; i++) {
        dw4_igb_record db = {0}, value = {0};
        uint32_t shorts, strings, count;
        if (!object_record(&g, i, &db)) continue;
        if (strcmp(db.class_name, "beDataBase")) { dw4_igb_record_free(&db); continue; }
        int wc = list_column(&g, record_slot(&db, 4), "INI_WEAPON1", &shorts);
        int mc = list_column(&g, record_slot(&db, 12), "MODEL_NAME", &strings);
        if (wc >= 0 && mc >= 0) {
            const uint8_t *names = record_list(&g, record_slot(&db, 13), &count);
            uint32_t nshort = 0, shortsize = 0;
            const uint8_t *data = NULL;
            if (object_record(&g, record_slot(&db, 5), &value)) {
                nshort = record_slot(&value, 2);
                data = dw4_igb_block(&g, record_slot(&value, 4), &shortsize);
                dw4_igb_record_free(&value);
            }
            if (names && data && nshort <= shortsize/2 && strings && shorts)
                for (unsigned row = 0; row < count/strings && row < nshort/shorts; row++) {
                    if (!object_record(&g, list_id(names, row*strings+mc), &value)) break;
                    int match = value.name && !strcmp(value.name, model);
                    dw4_igb_record_free(&value);
                    if (match) {
                        uint16_t code; memcpy(&code, data+2*(row*shorts+wc), 2);
                        initial = code; break;
                    }
                }
        }
        dw4_igb_record_free(&db);
    }
    /* Retail item-weapon codes: 0x00xx graded, 0x01xx styled. The weapon DB
     * places 256 graded rows before the styled rows. Created starters use 01. */
    if ((initial >> 8) != 1) goto done;
    for (unsigned i = 0; i < g.table_n; i++) {
        dw4_igb_record db = {0}, value = {0};
        uint32_t cols, count;
        if (!object_record(&g, i, &db)) continue;
        if (strcmp(db.class_name, "beDataBase")) { dw4_igb_record_free(&db); continue; }
        int mc = list_column(&g, record_slot(&db, 12), "MODEL", &cols);
        uint32_t unused;
        int equip = list_column(&g, record_slot(&db, 6), "SOUBI", &unused);
        if (mc >= 0 && equip >= 0 && cols) {
            const uint8_t *data = record_list(&g, record_slot(&db, 13), &count);
            unsigned index = (256+(initial&255))*cols+mc;
            if (data && index < count && object_record(&g, list_id(data, index), &value)) {
                if (value.name && strlen(value.name)+4 < 32) {
                    snprintf(asset, 32, "%s.igb", value.name); result = 0;
                }
                dw4_igb_record_free(&value);
            }
        }
        dw4_igb_record_free(&db);
        if (!result) break;
    }
 done:
    dw4_igb_close(&g);
    return result;
}
static int open_player_weapon(dw4_lobby *l, dw4_mount *mnt, int species,
                              const uint8_t *player_blob, uint32_t player_size,const char *asset)
{
    const char *const *models = lobby_models;   /* species is a shinka row */
    dw4_igb g = {0}, player = {0};
    dw4_igb_record r = {0};
    uint32_t size, count, nodes, bones, root = UINT32_MAX;
    const uint8_t *blob, *data;
    int result = -1;
    if(asset && !*asset) {
        /* Unarmed (empty POWERSOCKETNAME): retail's player setup (3d3d88..3d3d98) skips PLAYERARMS GENERATE, so no
         * weapon graph and no weapon label; the player's sequences then enter at their first authored section, which
         * is the first SQ_WAIT label ("dual" in all sixteen packs). */
        dw4_igb_record lr={0};uint32_t n;const uint8_t *cmds;
        l->p->weapon_asset[0]=l->p->weapon_label[0]=l->p->weapon_bone[0]=0;l->p->weapon_count=0;
        if(dw4_igb_open(&player,player_blob,player_size,0) || dw4_igb_refs_open(&player) ||
           named_record(&player,"beModelCtrlData","SQ_WAIT",&lr))goto done;
        cmds=record_list(&player,record_slot(&lr,3),&n);dw4_igb_record_free(&lr);
        for(unsigned i=0;cmds && i<n && !*l->p->weapon_label;i++){
            if(!object_record(&player,list_id(cmds,i),&lr))goto done;
            if(!strcmp(lr.class_name,"beModelCtrlLABEL") && lr.name)snprintf(l->p->weapon_label,sizeof l->p->weapon_label,"%s",lr.name);
            dw4_igb_record_free(&lr);
        }
        if(*l->p->weapon_label && !player_sequence_motion(&player,"SQ_WAIT",l->p->weapon_label,l->p->player_motion) &&
           !player_sequence_motion(&player,"SQ_WALK",l->p->weapon_label,l->p->player_run_motion))result=0;
        goto done;
    }
    if(asset){if(strlen(asset)>=sizeof l->p->weapon_asset)return -1;snprintf(l->p->weapon_asset,sizeof l->p->weapon_asset,"%s",asset);}
    else if(starter_asset(mnt,models[species],l->p->weapon_asset))return -1;
    blob = dw4_mount_data(mnt, l->p->weapon_asset, &size);
    if (!blob || dw4_scene_load(&l->p->weapon, blob, size) ||
        dw4_igb_open(&g, blob, size, 0) || dw4_igb_refs_open(&g) ||
        dw4_igb_open(&player, player_blob, player_size, 0) || dw4_igb_refs_open(&player)) goto done;
    if (named_record(&g, "beWeaponSeqData", "SQ_WAIT", &r)) goto done;
    const char *label = NULL;
    for (unsigned i = 0; i < r.nvalues; i++)
        if (r.values[i].ordinal == 3) label = r.values[i].str;
    if (label) snprintf(l->p->weapon_label, sizeof l->p->weapon_label, "%s", label);
    dw4_igb_record_free(&r);
    if (!*l->p->weapon_label || player_sequence_motion(&player,"SQ_WAIT",l->p->weapon_label,l->p->player_motion) ||
        player_sequence_motion(&player,"SQ_WALK",l->p->weapon_label,l->p->player_run_motion) ||
        named_record(&g, "beWeaponInfo", NULL, &r)) goto done;
    nodes = record_slot(&r, 7); bones = record_slot(&r, 8);
    dw4_igb_record_free(&r);
    data=record_list(&g,nodes,&count);
    if(!data || !count || count>16)goto done;
    unsigned nn=count;uint32_t ids[16];for(unsigned k=0;k<nn;k++)ids[k]=list_id(data,k);
    data=record_list(&g,bones,&count);if(!data || count!=nn)goto done;
    for(unsigned k=0;k<nn;k++){
        if(!object_record(&g,list_id(data,k),&r) || !r.name || strlen(r.name)>=64)goto done;
        snprintf(l->p->weapon_bones[k],64,"%s",r.name);dw4_igb_record_free(&r);
        root=0;while(root<l->p->weapon.nnode && l->p->weapon.node[root].id!=ids[k])root++;
        if(root==l->p->weapon.nnode)goto done;
        l->p->weapon_roots[k]=root;
    }
    /* PC01's children are authored weapon parts (right/left), not player
     * slots. Publish every beWeaponInfo node's branch; choosing child zero
     * alone hides the left-hand pistol/dual blade/arm weapon. */
    for(uint32_t node=0;node<l->p->weapon.nnode;node++)if(l->p->weapon.node[node].name &&
        !strcmp(l->p->weapon.node[node].name,"PC01") && l->p->weapon.node[node].switch_mask.off){
        if(!l->p->weapon.node[node].switch_bits || dw4_scene_switch_set(&l->p->weapon,node,-1,0))goto done;
        for(unsigned k=0;k<nn;k++) {
            uint32_t child=l->p->weapon_roots[k];
            while(child<l->p->weapon.nnode && l->p->weapon.node[child].parent<l->p->weapon.nnode &&
                  l->p->weapon.node[child].parent!=node)child=l->p->weapon.node[child].parent;
            if(child>=l->p->weapon.nnode || l->p->weapon.node[child].parent!=node)continue;
            unsigned branch=0;
            for(uint32_t n=node+1;n<child;n++)if(l->p->weapon.node[n].parent==node)branch++;
            if(branch>=l->p->weapon.node[node].switch_bits || dw4_scene_switch_set(&l->p->weapon,node,branch,1))goto done;
        }
    }
    l->p->weapon_count=nn;l->p->weapon_root=l->p->weapon_roots[0];snprintf(l->p->weapon_bone,sizeof l->p->weapon_bone,"%s",l->p->weapon_bones[0]);result=0;
 done:
    dw4_igb_record_free(&r);
    dw4_igb_close(&g); dw4_igb_close(&player);
    return result;
}

/* Decode the complete bounded portal Action2 bank. Unknown components fail the
 * load instead of silently replacing authored behavior with a guessed loop. */
static int portal_program(const dw4_igb *g, const dw4_igb_record *info,
                           const char *name, struct portal_program *out)
{
    uint32_t count;
    const uint8_t *data = record_list(g, record_slot(info,9), &count);
    if (!data) return -1;
    for (unsigned i=0;i<count;i++) {
        dw4_igb_record action={0};
        if (!object_record(g,list_id(data,i),&action)) return -1;
        int match=action.name && !strcmp(action.name,name);
        uint32_t commands=record_slot(&action,3);
        dw4_igb_record_free(&action);
        if (!match) continue;
        const uint8_t *items=record_list(g,commands,&out->count);
        if (!items || !out->count || out->count>8) return -1;
        for(unsigned j=0;j<out->count;j++) {
            dw4_igb_record r={0};
            if(!object_record(g,list_id(items,j),&r)) return -1;
            dw4_action2_component *c=&out->component[j];
            if(!strcmp(r.class_name,"beAction2JOINTSET")) c->kind=DW4_A2_JOINTSET;
            else if(!strcmp(r.class_name,"beAction2WAITCHECK")) c->kind=DW4_A2_WAITCHECK;
            else if(!strcmp(r.class_name,"beAction2FADESET")) c->kind=DW4_A2_FADESET;
            else {dw4_igb_record_free(&r);return -1;}
            snprintf(out->name[j],sizeof out->name[j],"%s",r.name?r.name:"");
            c->name=out->name[j];c->loop=out->loop[j];
            c->first=record_slot(&r,3);c->last=record_slot(&r,4);
            if(c->kind==DW4_A2_JOINTSET) {
                for(unsigned k=0;k<r.nvalues;k++) if(r.values[k].ordinal==5 && r.values[k].str)
                    snprintf(out->loop[j],sizeof out->loop[j],"%s",r.values[k].str);
                if(strcmp(c->loop,"LP") && strcmp(c->loop,"OS")) {dw4_igb_record_free(&r);return -1;}
                float first,last;memcpy(&first,&c->first,4);memcpy(&last,&c->last,4);
                if(!isfinite(first) || !isfinite(last) || first<0 || last<first ||
                   last>10000 || (!strcmp(c->loop,"LP") && last==first)) {
                    dw4_igb_record_free(&r);return -1;
                }
            }
            if(c->kind==DW4_A2_WAITCHECK && strcmp(c->name,"Frame") && strcmp(c->name,"Joint")) {
                dw4_igb_record_free(&r);return -1;
            }
            if(c->kind==DW4_A2_FADESET) {
                memcpy(&out->fade_frames,&c->first,4);
                out->fade_in=c->name[0]=='I';
                if(!isfinite(out->fade_frames) || out->fade_frames<=0) {dw4_igb_record_free(&r);return -1;}
            }
            dw4_igb_record_free(&r);
        }
        return 0;
    }
    return -1;
}
static void portal_start(struct lobby_portal *p,int action,unsigned tick)
{
    p->action=action;p->started=tick;
    dw4_action2_host_start_program(&p->clock,p->program[action].component,
                                   p->program[action].count,(int64_t)tick*1000000000LL/60);
    if(p->program[action].fade_frames) {
        uint32_t frames;memcpy(&frames,&p->program[action].fade_frames,4);
        lobby_fade_start(&p->fade,p->program[action].fade_in,frames,(int64_t)tick*1000000000LL/60);
    } else p->fade=(lobby_fade){.value=0x3f800000};
}
static float portal_alpha(const struct lobby_portal *p,unsigned tick)
{
    const struct portal_program *program=&p->program[p->action];
    if(!program->fade_frames) return 1;
    (void)tick;
    return lobby_fade_alpha(&p->fade);
}

static int record_floats(const dw4_igb *g, const dw4_igb_record *r,
                         unsigned ordinal, float *out, unsigned count)
{
    for (unsigned i = 0; i < r->nvalues; i++) if (r->values[i].ordinal == ordinal) {
        if (r->values[i].voff + count*4 > g->size) return -1;
        memcpy(out, g->data+r->values[i].voff, count*4);
        for (unsigned k = 0; k < count; k++) if (!isfinite(out[k])) return -1;
        return 0;
    }
    return -1;
}

static int player_entry_fade(const uint8_t *blob,uint32_t size,float *frames)
{
    dw4_igb g={0};dw4_igb_record r={0};
    int result=-1;uint32_t count;
    if(dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g) ||
       named_record(&g,"beAction2Data","TRNSS1",&r)) goto done;
    const uint8_t *items=record_list(&g,record_slot(&r,3),&count);
    dw4_igb_record_free(&r);
    if(!items) goto done;
    for(unsigned i=0;i<count;i++) {
        if(!object_record(&g,list_id(items,i),&r)) goto done;
        if(!strcmp(r.class_name,"beAction2FADESET") && r.name && !strcmp(r.name,"IN")) {
            uint32_t value=record_slot(&r,3);memcpy(frames,&value,4);
            if(isfinite(*frames) && *frames>0 && *frames<=200) result=0;
        }
        dw4_igb_record_free(&r);
    }
 done:
    dw4_igb_record_free(&r);dw4_igb_close(&g);return result;
}

/* Box-camera lists share one authored region order. The region geometry is a
 * query volume, not visible world geometry. This bounded adapter selects by its
 * world bounds; the single-player transition runs beCameraCtrl's retained rig. */
/* The scene that owns the camera nodes: the world, or a dungeon floor's separate camera pack. */
static const dw4_scene *camera_scene_of(const dw4_lobby *l){return l->ext_camera?&l->camera_pack:&l->scene;}
/* A world pack carries the box rig and the material regions; a dungeon floor's world has only the regions (need_box 0), and its rig comes from the separate camera pack (need_material 0). */
static int load_control(dw4_lobby *l, const uint8_t *blob, size_t size, int need_box, int need_material)
{
    dw4_igb g = {0};
    int result = -1;
    if (dw4_igb_open(&g, blob, size, 0) || dw4_igb_refs_open(&g)) goto done;
    for (unsigned id = 0; id < g.table_n; id++) {
        dw4_igb_record r = {0};
        if (!object_record(&g, id, &r)) continue;
        if (!strcmp(r.class_name, "beCameraBoxData")) {
            uint32_t ng, ne, ni;
            const uint8_t *geometry = record_list(&g, record_slot(&r, 3), &ng);
            const uint8_t *eye = record_list(&g, record_slot(&r, 5), &ne);
            const uint8_t *interest = record_list(&g, record_slot(&r, 6), &ni);
            if (!geometry || !eye || !interest || !ng || ng != ne || ng != ni) {
                dw4_igb_record_free(&r); goto done;
            }
            if(l->box){dw4_igb_record_free(&r);goto done;}
            l->box=calloc(ng,sizeof *l->box);
            if(!l->box){dw4_igb_record_free(&r);goto done;}
            for (unsigned k = 0; k < ng; k++) {
                dw4_igb_record e = {0}, in = {0};
                dw4_igb_record geometry_record = {0}, bounds = {0};
                int bad_bounds = !object_record(&g,list_id(geometry,k),&geometry_record) ||
                    !object_record(&g,record_slot(&geometry_record,3),&bounds) ||
                    record_floats(&g,&bounds,2,l->box[k].min,3) ||
                    record_floats(&g,&bounds,3,l->box[k].max,3);
                dw4_igb_record_free(&geometry_record); dw4_igb_record_free(&bounds);
                if (bad_bounds) { dw4_igb_record_free(&r); goto done; }
                int bad = !object_record(&g, list_id(eye,k), &e) ||
                    !object_record(&g, list_id(interest,k), &in) ||
                    record_floats(&g,&e,8,l->box[k].eye,16) ||
                    record_floats(&g,&in,8,l->box[k].interest,16);
                dw4_igb_record_free(&e); dw4_igb_record_free(&in);
                if (bad) { dw4_igb_record_free(&r); goto done; }
            }
            l->nbox = ng;
        }
        if (!strcmp(r.class_name, "beMatCtrlData")) {
            dw4_igb_record bounds = {0};
            unsigned k = l->nmaterial;
            int bad = k >= 32 || !r.name || !object_record(&g,record_slot(&r,3),&bounds);
            if (!bad) bad = record_floats(&g,&bounds,2,l->material[k].min,3) ||
                            record_floats(&g,&bounds,3,l->material[k].max,3);
            if (!bad) { snprintf(l->material[k].name,sizeof l->material[k].name,"%s",r.name); l->material[k].run=1; l->nmaterial++; }
            dw4_igb_record_free(&bounds);
            if (bad) { dw4_igb_record_free(&r); goto done; }
        }
        dw4_igb_record_free(&r);
    }
    result = (!need_box || l->nbox) && (!need_material || l->nmaterial) ? 0 : -1;
done:
    dw4_igb_close(&g); return result;
}

/* Hit-land model names: each beHitLandModelInfo lists the names it answers to (slot 9, an igNamedObjectList), e.g. the
 * Commander Room's wall hitmovepass01z05 that start.lua turns off once its moving pass is on, or a dungeon floor's doorwall01..06.
 * Read from the world pack (a dungeon's camera data lives in separate packs, so this is not part of the camera scan). */
static void load_hit_names(dw4_lobby *l,const uint8_t *blob,size_t size)
{
    dw4_igb g={0};
    if(dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g))goto done;
    for(unsigned i=0;i<g.table_n;i++) {
        dw4_igb_record r={0};
        if(!object_record(&g,i,&r))continue;
        if(!strcmp(r.class_name,"beHitLandModelInfo")) {
            uint32_t count;const uint8_t *ids=record_list(&g,record_slot(&r,9),&count);
            for(uint32_t k=0;ids && k<count && l->nhit_name<sizeof l->hit_name/sizeof *l->hit_name;k++) {
                dw4_igb_record name={0};
                if(object_record(&g,list_id(ids,k),&name) && name.name && strlen(name.name)<sizeof l->hit_name[0].name) {
                    snprintf(l->hit_name[l->nhit_name].name,sizeof l->hit_name[0].name,"%s",name.name);
                    l->hit_name[l->nhit_name].index=k;l->hit_name[l->nhit_name].count=count;
                    l->hit_name[l->nhit_name++].info=i;
                }
                dw4_igb_record_free(&name);
            }
        }
        dw4_igb_record_free(&r);
    }
done:
    dw4_igb_close(&g);
}
/* The named demo cameras of a non-Terminal hub: every beCameraCtrlInfo whose slot 7 is a beCameraDemoData (end time, ordinal 3)
 * and whose scene graph of the same name holds an igCamera. Their transform sequences use the camera graphs' Euler rotation, as
 * camsp0101 does in the Terminal. A camera with another interpolation is not published, so SETDEMOCAMERA on it fails loudly. */
static int load_demo_cameras(dw4_lobby *l,dw4_scene *cs,const uint8_t *blob,size_t size)
{
    dw4_igb g={0};int rc=-1;
    if(dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g))goto done;
    for(unsigned i=0;i<g.table_n && l->ndemo<8;i++) {
        dw4_igb_record r={0},demo={0};
        if(!object_record(&g,i,&r))continue;
        if(strcmp(r.class_name,"beCameraCtrlInfo") || !r.name || strlen(r.name)>=sizeof l->demo[0].name ||
           !object_record(&g,record_slot(&r,7),&demo) || strcmp(demo.class_name,"beCameraDemoData")) {
            dw4_igb_record_free(&demo);dw4_igb_record_free(&r);continue;
        }
        uint64_t end=0;for(unsigned k=0;k<demo.nvalues;k++)if(demo.values[k].ordinal==3)end=demo.values[k].raw64;
        uint32_t graph=UINT32_MAX,node=UINT32_MAX;
        for(uint32_t j=0;j<cs->ngraph;j++)if(cs->graph[j].name && !strcmp(cs->graph[j].name,r.name)){graph=j;break;}
        for(uint32_t j=0;graph!=UINT32_MAX && j<cs->nnode;j++)
            if(cs->node[j].scene==graph && cs->node[j].class_name && !strcmp(cs->node[j].class_name,"igCamera")){node=j;break;}
        int euler=node!=UINT32_MAX && end;
        for(uint32_t j=0;euler && j<cs->nnode;j++)
            if(cs->node[j].scene==graph && cs->node[j].has_seq && ((cs->node[j].seq.interpolation_method>>8)&255u)!=1)euler=0;
        /* A field world publishes every demo camera with a camera node and an end time: its logic (SETDEMOCAMERA/ISDEMOCAMERA timing) is what the
         * scripts wait on. A camera whose interpolation is not the Euler one keeps its authored pose path unrendered (presentation not claimed). */
        int publish=euler || (l->field && node!=UINT32_MAX && end);
        if(publish) {
            for(uint32_t j=0;euler && j<cs->nnode;j++)if(cs->node[j].scene==graph && cs->node[j].has_seq)cs->node[j].seq.rotation_euler=1;
            snprintf(l->demo[l->ndemo].name,sizeof l->demo[0].name,"%s",r.name);l->demo[l->ndemo].node=node;l->demo[l->ndemo].end=end;l->ndemo++;
        }else fprintf(stderr,"  hub %s: demo camera %s not published (graph %u camera %u end %llu)\n",l->stage,r.name,graph,node,(unsigned long long)end);
        dw4_igb_record_free(&demo);dw4_igb_record_free(&r);
    }
    rc=0;
done:
    dw4_igb_close(&g);return rc;
}
static int contains(const float min[3], const float max[3], const float *p)
{
    return p[0]>=min[0] && p[0]<=max[0] && p[1]>=min[1] && p[1]<=max[1] && p[2]>=min[2] && p[2]<=max[2];
}
/* The camera's subject: the average position of the joined players (retail averages them before the box query); one player is its own centre. */
static void party_center(const dw4_lobby *l,float out[3])
{
    float sum[3]={0,0,0};unsigned n=0;
    for(unsigned q=0;q<4;q++)if(l->pl[q].joined){for(unsigned a=0;a<3;a++)sum[a]+=l->pl[q].player_world[12+a];n++;}
    if(n==1){memcpy(out,l->pl[0].player_world+12,3*sizeof *out);return;}
    for(unsigned a=0;a<3;a++)out[a]=n?sum[a]/(float)n:0;
}
static void box_camera_tick(dw4_lobby *l,float delta)
{
    float centre[3];party_center(l,centre);const float *p = centre;
    unsigned region = l->control.camera_region;
    /* List zero is the mutable rig, not a selectable region. No hit retains
     * the current region, and overlapping regions use authored order. */
    for (unsigned k = 1; k < l->nbox; k++)
        if (contains(l->box[k].min,l->box[k].max,p)) { region = k; break; }
    l->control.camera_region = region;
    dw4_boxcamera_tick(&l->box_camera,region,l->box[region].eye,l->box[region].interest,p,delta);
    dw4_boxcamera_world(&l->box_camera,l->control.camera_world);
    if(l->shake.active) {
        /* FUN_00378ed0 (the box camera controller): every frame the eye and interest x/y translations get dir * value, where dir is the
         * digit of the move code selected by the step timer (oneTime frames per step, cyclic), until endTime frames pass. */
        static const float dx[10]={0,0,1,1,1,0,-1,-1,-1,0},dy[10]={0,1,1,0,-1,-1,-1,0,1,0};
        float elapsed=(float)(l->age-l->shake.start);
        if(elapsed>=l->shake.end)l->shake.active=0;
        else {
            unsigned len=(unsigned)strlen(l->shake.code),step=l->shake.one_time>0?(unsigned)(elapsed/l->shake.one_time)%len:0;
            unsigned d=(unsigned)(l->shake.code[step]-'0');
            dw4_boxcamera shaken=l->box_camera;
            shaken.eye[12]+=dx[d]*l->shake.value;shaken.eye[13]+=dy[d]*l->shake.value;
            shaken.interest[12]+=dx[d]*l->shake.value;shaken.interest[13]+=dy[d]*l->shake.value;
            dw4_boxcamera_world(&shaken,l->control.camera_world);
        }
    }
}
/* Stage-specific material scripts outside the shared dispatch rule below (kept separate so that rule's owner can change it freely):
 * - Commander Room (stagML02): matg00 is its only point label ("Gate to Main Lobby", PintmessOpen) and mate00 its exit to the
 *   Terminal (funcStageChange stagML11 point 0). Its matf00/matf02 are the Ophanimon/Seraphimon event triggers and matf01 is an
 *   empty script; the shared matf* rule runs them.
 * - Terminal: mate01 is the Commander Room gate (funcStageChange stagML02 point 0 while flag 424 is clear). Redundant once the
 *   shared rule dispatches the Terminal gate pads. Both travel regions need the runtime's travel owner (exit events). */
static int stage_material_runs(const dw4_lobby *l,const char *name)
{
    if(!strcasecmp(l->stage,"stagML02"))return !strcmp(name,"matg00") || (l->exit_events && !strcmp(name,"mate00"));
    if(l->terminal)return l->exit_events && !strcmp(name,"mate01");
    return 0;
}
static void control_tick(dw4_lobby *l)
{
    l->control.material_mask = 0;
    uint8_t exists[4];for(unsigned q=0;q<4;q++)exists[q]=l->pl[q].joined;
    for (unsigned k = 0; k < l->nmaterial; k++) {
        int previous=l->material[k].inside;
        /* `inside` is the mask of joined players standing in the region (bit = slot), the cell the original callback publishes as `current`. */
        int mask=0;
        for(unsigned q=0;q<4;q++)if(l->pl[q].joined && contains(l->material[k].min,l->material[k].max,l->pl[q].player_world+12))mask|=1<<q;
        l->material[k].inside = mask;
        if (l->material[k].inside) l->control.material_mask |= 1u << k;
        /* Retail 38b1f0 dispatches changed membership, with current/previous
         * masks exposed through 38aea0. Enabled hub events execute original Lua:
         * - the Terminal heal pad mate03 (funcHealGate) always;
         * - the matf and matg regions, which in the hubs run the point-message labels (PintmessOpen: "Gate to Outside World",
         *   "Heal Circle", ...; the Commander Room's only label is matg00), always;
         * - the travel regions only with a travel owner (exit_events): the bridges matz00/matz01 and the gate pads mate*
         *   (Terminal mate00 field gate, mate01 Commander Room, mate02 Emergency Gate; the second exits Central/Shop mate00).
         *   The pad scripts apply their own story-flag and MATisAllPlayer guards and clear the label before their prompt. */
        const char *name=l->material[k].name;
        int label=!strncmp(name,"matf",4) || !strncmp(name,"matg",4),heal=!strcmp(name,"mate03"),
            travel=!heal && (!strncmp(name,"matz",4) || !strncmp(name,"mate",4));
        if(l->native_models && l->scripts && previous!=l->material[k].inside && l->material[k].run && (l->field || heal || label || (l->exit_events && travel) || stage_material_runs(l,l->material[k].name))) {   /* a field world runs every authored region */
            dw4_material_contact_begin(&l->material_context,k,(uint32_t)l->material[k].inside,(uint32_t)previous,exists);
            char event[40];snprintf(event,sizeof event,"%s.lua",l->material[k].name);
            int rc=dw4_scriptengine_run(l->scripts,event);
            l->material_context.active=0;
            if(l->material_context.request_index<l->nmaterial)
                l->material[l->material_context.request_index].run=l->material_context.request_value;
            if(rc){snprintf(l->script_error,sizeof l->script_error,"material %.32s: %.400s",l->material[k].name,dw4_scriptengine_error(l->scripts));return;}
        }
    }
    l->control.material_ticks++;
    dw4_lobbyui_tick(l->ui, 0);
}
/* Development and test aid: stand the player at a world position through the original MOVETRANS command (no progression change). */
int dw4_lobby_place_player(dw4_lobby *l,float x,float y,float z,float yaw)
{
    if(!l || !l->p->player_controller)return -1;
    char transform[160],error[256];snprintf(transform,sizeof transform,"V<%.9g,%.9g,%.9g>/V<0,%.9g,0>",x,y,z,yaw);
    dw4_script_value a[]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,transform,strlen(transform)}},r;
    return dw4_modelctrl_service(l->p->player_controller,"sd",a,5,&r,error,sizeof error);
}
int dw4_lobby_material_region(const dw4_lobby *l,const char *name,float min[3],float max[3])
{
    if(!l || !name)return -1;
    for(unsigned k=0;k<l->nmaterial;k++)if(!strcmp(l->material[k].name,name)) {
        if(min)memcpy(min,l->material[k].min,sizeof l->material[k].min);
        if(max)memcpy(max,l->material[k].max,sizeof l->material[k].max);
        return (int)k;
    }
    return -1;
}
void dw4_lobby_exit_events(dw4_lobby *l,int enabled){if(l)l->exit_events=!!enabled;}
const char *dw4_lobby_material_name(const dw4_lobby *l,unsigned index){return l && index<l->nmaterial?l->material[index].name:NULL;}
/* A beHitLandModelInfo that lists several names over a graph with as many meshes (the Humid Cave's doorwall01..06: one wall graph, one mesh per
 * door at the door's authored position, listed in the script's numbering) switches the name's own mesh; an info with one name switches its graph.
 * Hypothesis (#2857, unconfirmed): the names answer to the meshes in list order. */
static int hit_part(const dw4_lobby *l,unsigned h,unsigned k)
{return l->hit_name[h].count>1 && l->hit_name[h].count==dw4_lobby_collision_parts(&l->scene,k) && l->hit_name[h].index<64;}
int dw4_lobby_collision_hit(dw4_lobby *l,const char *name,int on)
{
    if(!l || !name)return -1;
    unsigned h=0;while(h<l->nhit_name && strcmp(l->hit_name[h].name,name))h++;
    if(h==l->nhit_name){snprintf(l->script_error,sizeof l->script_error,"HITLANDMODEL %s: no such hit-land model in %s",name,l->stage);return -1;}
    unsigned k=0;while(k<l->scene.ncollision && l->scene.collision[k].info_id!=l->hit_name[h].info)k++;
    if(k==l->scene.ncollision || k>=sizeof l->collision_off){snprintf(l->script_error,sizeof l->script_error,"HITLANDMODEL %s: info %u is not a static collision graph of %s",name,l->hit_name[h].info,l->stage);return -1;}
    int part=hit_part(l,h,k);uint64_t bit=part?1ull<<l->hit_name[h].index:0;
    if(part?(!(l->collision_part_off[k]&bit))==!!on:l->collision_off[k]==!on)return 0;
    if(part)l->collision_part_off[k]^=bit;else l->collision_off[k]=!on;
    dw4_lobby_collision next;
    if(dw4_lobby_collision_open_parts(&next,&l->scene,l->collision_off,l->collision_part_off)){
        if(part)l->collision_part_off[k]^=bit;else l->collision_off[k]=!!on;
        snprintf(l->script_error,sizeof l->script_error,"HITLANDMODEL: collision rebuild failed");return -1;
    }
    dw4_lobby_collision_dynamic_pose(&next,l->collision.pose,l->collision.pose_user);
    dw4_lobby_collision_close(&l->collision);l->collision=next;
    return 0;
}
/* Pose of a dynamic prop wall node: the live matrix of the model instance (the info's model name, ram slot i) while it is generated and drawable;
 * a slot that was never generated, was erased or broke, or is hidden is no wall (its authored preview matrix, (15*i,0,0), must never block). */
static int lobby_dynamic_pose(void *user,unsigned index,float world[16])
{
    dw4_lobby *l=user;
    if(!l->native_models){l->dyn_owner=NULL;return 0;}
    if(l->dyn_owner!=l->native_models || !l->dyn_model || l->dyn_count!=dw4_controllers_count(l->native_models)) {   /* a receiver attached later changes the count */
        free(l->dyn_model);l->dyn_model=calloc(l->collision.ndynamic?l->collision.ndynamic:1,sizeof *l->dyn_model);l->dyn_owner=NULL;
        if(!l->dyn_model)return 0;
        for(size_t i=0;i<dw4_controllers_count(l->native_models);i++) {
            const dw4_stageobject *info;int32_t slot;
            const dw4_modelctrl *m=dw4_controllers_model(l->native_models,i,&info,&slot);
            for(unsigned k=0;m && slot>=0 && k<l->collision.ndynamic;k++)
                if(!l->dyn_model[k] && l->collision.dynamic[k].slot==(unsigned)slot && !strcmp(l->collision.dynamic[k].name,dw4_stageobject_name(info)))l->dyn_model[k]=m;
        }
        l->dyn_owner=l->native_models;l->dyn_count=dw4_controllers_count(l->native_models);
    }
    const dw4_modelctrl *m=index<l->collision.ndynamic?l->dyn_model[index]:NULL;
    if(!m || !dw4_modelctrl_active(m) || !dw4_modelctrl_drawable(m))return 0;
    dw4_modelctrl_matrix(m,world);return 1;
}
int dw4_lobby_collision_counts(const dw4_lobby *l,unsigned *wall,unsigned *floor)
{
    if(!l)return -1;
    if(wall)*wall=l->collision.wall.count;
    if(floor)*floor=l->collision.floor.count;
    return 0;
}
int dw4_lobby_hit_state(const dw4_lobby *l,const char *name)
{
    if(!l || !name)return -1;
    for(unsigned h=0;h<l->nhit_name;h++)if(!strcmp(l->hit_name[h].name,name)) {
        for(unsigned k=0;k<l->scene.ncollision && k<sizeof l->collision_off;k++)if(l->scene.collision[k].info_id==l->hit_name[h].info)
            return hit_part(l,h,k)?!(l->collision_part_off[k]>>l->hit_name[h].index&1):!l->collision_off[k];
        return -1;
    }
    return -1;
}
void dw4_lobby_walk_clear_contacts(dw4_lobby *l){if(l)l->p->player_contacts=0;}
unsigned dw4_lobby_walk_probe(const dw4_lobby *l,const float old[3],float pos[3])
{return l?dw4_lobby_collision_walk_for(&l->collision,DW4_PLAYER_CHECK_FLAG,old,pos,3,4,4,1,1):0;}
void dw4_lobby_native_ui(dw4_lobby *l,dw4_modelview *ui){if(l)l->native_ui=ui;}
int dw4_lobby_material_call(dw4_lobby *l,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    return dw4_material_contact_call(l?&l->material_context:NULL,method,a,n,r,error,cap);
}

int dw4_lobby_control(const dw4_lobby *l, dw4_lobby_control_state *out)
{
    if (!l || !out) return -1;
    *out = l->control; return 0;
}

/* The camera node's near/far planes (igCamera "cameraShape00"); a dungeon floor's lives in its separate camera pack. */
static void camera_planes(dw4_lobby *l,const uint8_t *blob,size_t size)
{
    dw4_igb g={0};
    if(dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g))goto done;
    for(unsigned i=0;i<g.table_n;i++) {
        dw4_igb_record r={0};if(!object_record(&g,i,&r))continue;
        if(!strcmp(r.class_name,"igCamera") && r.name && !strcmp(r.name,"cameraShape00")) {
            uint32_t near=record_slot(&r,9),far=record_slot(&r,10);
            memcpy(&l->near_plane,&near,4);memcpy(&l->far_plane,&far,4);
        }
        dw4_igb_record_free(&r);
    }
done:dw4_igb_close(&g);
}
static int load_environment(dw4_lobby *l,const uint8_t *blob,size_t size)
{
    dw4_igb g={0};int rc=-1;
    if(dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g))goto done;
    for(unsigned i=0;i<g.table_n;i++) {
        dw4_igb_record r={0};if(!object_record(&g,i,&r))continue;
        if (!strcmp(r.class_name,"igLightAttr") && record_slot(&r,4) == 0) {
            float ambient[4], diffuse[4];
            if(record_floats(&g,&r,7,ambient,4) || record_floats(&g,&r,8,diffuse,4)) {
                dw4_igb_record_free(&r);goto done;
            }
            if (diffuse[0] > 0 || diffuse[1] > 0 || diffuse[2] > 0) {
                memcpy(l->soft_diffuse,diffuse,sizeof diffuse);
                if (record_floats(&g,&r,10,l->light_direction,3)) {
                    dw4_igb_record_free(&r);goto done;
                }
            } else memcpy(l->soft_ambient,ambient,sizeof ambient);
        }
        if(!strcmp(r.class_name,"igCamera") && r.name && !strcmp(r.name,"cameraShape00")) {
            uint32_t near=record_slot(&r,9),far=record_slot(&r,10);
            memcpy(&l->near_plane,&near,4);memcpy(&l->far_plane,&far,4);
        }
        if(!strcmp(r.class_name,"igProjectiveShadowShader")) {
            uint32_t width=record_slot(&r,14),height=record_slot(&r,15);
            if(width!=256 || height!=256 || dw4_fb_init(&l->shadow_fb,width,height)) {
                dw4_igb_record_free(&r);goto done;
            }
            l->shadow_tex=(dw4_tex){l->shadow_fb.rgba,(int)width,(int)height};
            uint32_t factor=record_slot(&r,13);memcpy(&l->shadow_factor,&factor,4);
            for(unsigned k=0;k<4;k++) {
                uint32_t value=record_slot(&r,48+k);memcpy(&l->shadow_bounds[k],&value,4);
            }
        }
        if(!strcmp(r.class_name,"beShadow01Info") && record_slot(&r,7)!=UINT32_MAX) {
            unsigned k=l->shadow_receiver[0]?1:0;
            l->shadow_receiver[k]=record_slot(&r,7);
        }
        if (!strcmp(r.class_name, "igFogAttr")) {
            uint32_t a = record_slot(&r, 5), b = record_slot(&r, 6);
            memcpy(&l->fog_start, &a, 4); memcpy(&l->fog_end, &b, 4);
            for (unsigned k = 0; k < r.nvalues; k++) if (r.values[k].ordinal == 8) {
                float color[4]; memcpy(color, g.data+r.values[k].voff, sizeof color);
                for (unsigned c = 0; c < 3; c++) l->fog_color[c] = (uint8_t)(255*fminf(1,fmaxf(0,color[c])));
            }
        }
        dw4_igb_record_free(&r);
    }
    if(getenv("DW4_ENV_DEBUG"))fprintf(stderr,"environment %s: shadow_factor %g bounds %g %g %g %g near %g far %g soft_a %g soft_d %g fb %p recv %u %u fog %g %g\n",l->stage,l->shadow_factor,l->shadow_bounds[0],l->shadow_bounds[1],l->shadow_bounds[2],l->shadow_bounds[3],l->near_plane,l->far_plane,l->soft_ambient[3],l->soft_diffuse[3],(void*)l->shadow_fb.rgba,l->shadow_receiver[0],l->shadow_receiver[1],l->fog_start,l->fog_end);
    rc=isfinite(l->shadow_factor) && l->shadow_factor>=0 && l->shadow_factor<=1 &&
        isfinite(l->shadow_bounds[0]) && isfinite(l->shadow_bounds[1]) &&
        isfinite(l->shadow_bounds[2]) && isfinite(l->shadow_bounds[3]) &&
        l->shadow_bounds[0]>l->shadow_bounds[1] && l->shadow_bounds[2]>l->shadow_bounds[3] &&
        isfinite(l->near_plane) && isfinite(l->far_plane) && l->near_plane>0 && l->far_plane>l->near_plane &&
        l->soft_ambient[3]==1 && l->soft_diffuse[3]==1 && l->shadow_fb.rgba &&
        l->shadow_receiver[0] && (l->shadow_receiver[1] || l->field) && isfinite(l->fog_start) &&
        isfinite(l->fog_end) && l->fog_end>l->fog_start?0:-1;
done:dw4_igb_close(&g);return rc;
}

static int load_effects(dw4_lobby *l, const uint8_t *blob, size_t size)
{
    static const char *names[] = {"g_cyexit", "g_cyheal", "g_cytelep1", "g_cytrerp2"};
    /* 009-layer-setup.lua's GENERATE transforms. */
    static const float placement[4][3] = {{155,57,55},{115,10,-95},{5,27,-95},{5,27,15}};
    dw4_igb g = {0};
    unsigned found = 0;
    if (dw4_igb_open(&g, blob, size, 0) || dw4_igb_refs_open(&g)) goto done;
    for (unsigned i = 0; i < g.table_n; i++) {
        dw4_igb_record r = {0};
        if (!object_record(&g, i, &r)) continue;


        if(!strcmp(r.class_name,"beCameraCtrlInfo") && r.name && !strcmp(r.name,"camsp0101")) {
            dw4_igb_record demo={0};
            if(!object_record(&g,record_slot(&r,7),&demo) || strcmp(demo.class_name,"beCameraDemoData")) {
                dw4_igb_record_free(&demo);dw4_igb_record_free(&r);goto done;
            }
            for(unsigned k=0;k<demo.nvalues;k++)if(demo.values[k].ordinal==3) {
                l->camera_time.end=demo.values[k].raw64;l->camera_time.loaded=1;
            }
            dw4_igb_record_free(&demo);
        }
        if(!strcmp(r.class_name,"beAction2Info") && r.name && !strcmp(r.name,"i_fadewn01")) {
            if(portal_program(&g,&r,"BLIN60",&l->arrival_fade)) {dw4_igb_record_free(&r);goto done;}
        }
        if(!strcmp(r.class_name,"beAction2Info") && r.name && !strcmp(r.name,"x_100trnsin01")) {
            if(portal_program(&g,&r,"ATCK01",&l->rings.program)) {dw4_igb_record_free(&r);goto done;}
            for(l->rings.root=0;l->rings.root<l->scene.nnode;l->rings.root++)
                if(l->scene.node[l->rings.root].id==record_slot(&r,7)) break;
            unsigned child=0;
            for(uint32_t j=l->rings.root+1;j<l->scene.nnode && child<3;j++)
                if(l->scene.node[j].parent==l->rings.root) l->rings.node[child++]=j;
            if(child!=3) {dw4_igb_record_free(&r);goto done;}
            for(unsigned k=0;k<3;k++) dw4_action2_host_init(&l->rings.clock[k]);
        }
        if(!strcmp(r.class_name,"beParticleCtrl2Info") && r.name && !strcmp(r.name,"y_100trnsin01")) {
            uint32_t root=UINT32_MAX;
            for(unsigned j=0;j<l->scene.nnode;j++) if(l->scene.node[j].id==record_slot(&r,8)) {root=j;break;}
            uint32_t bits=record_slot(&r,9);memcpy(&l->stars.lifetime,&bits,4);
            for(unsigned j=root+1;root<l->scene.nnode && j<l->scene.nnode && l->scene.node[j].depth>l->scene.node[root].depth;j++) {
                if(strcmp(l->scene.node[j].class_name,"ParticleTimer")) continue;
                dw4_igb_record timer={0};unsigned n;
                if(!object_record(&g,l->scene.node[j].id,&timer)) break;
                const uint8_t *attrs=record_list(&g,record_slot(&timer,8),&n);
                dw4_igb_record_free(&timer);
                for(unsigned a=0;attrs && a<n;a++) {
                    dw4_igb_record attr={0},array={0};
                    if(!object_record(&g,list_id(attrs,a),&attr)) break;
                    if(!strcmp(attr.class_name,"igParticleAttr") && object_record(&g,record_slot(&attr,5),&array)) {
                        unsigned size;const uint8_t *data=dw4_igb_block(&g,record_slot(&array,9),&size);
                        unsigned count=record_slot(&attr,6);
                        if(count==8 && record_slot(&array,8)==180 && data && size>=count*180) {
                            memcpy(l->stars.curve,data,count*180);l->stars.count=count;l->stars.node=j;
                        }
                    }
                    dw4_igb_record_free(&array);dw4_igb_record_free(&attr);
                }
                break;
            }
        }
        if(!strcmp(r.class_name,"beActionStarterInfo") && r.name && !strcmp(r.name,"y_100trnsin01")) {
            unsigned n;const uint8_t *targets=record_list(&g,record_slot(&r,7),&n);
            for(unsigned j=0;targets && j<n;j++) {
                dw4_igb_record target={0};if(!object_record(&g,list_id(targets,j),&target)) break;
                unsigned count;const uint8_t *items=record_list(&g,record_slot(&target,3),&count);
                if(target.name && !strcmp(target.name,"x_100trnsin01") && items && count) {
                    dw4_igb_record item={0};
                    if(object_record(&g,list_id(items,0),&item)) {
                        l->stars.delay=ee_f32_from_s32(record_slot(&item,4));
                        if(record_floats(&g,&item,5,l->stars.offset,3)) {dw4_igb_record_free(&item);dw4_igb_record_free(&target);dw4_igb_record_free(&r);goto done;}
                        dw4_igb_record_free(&item);
                    }
                }
                dw4_igb_record_free(&target);
            }
        }
        if(!strcmp(r.class_name,"beActionStarterInfo") && r.name && !strcmp(r.name,"x_100trnsin01")) {
            const char *const *players=lobby_models;
            uint32_t count;const uint8_t *targets=record_list(&g,record_slot(&r,7),&count);
            unsigned matches=0;
            for(unsigned j=0;targets && j<count;j++) {
                dw4_igb_record target={0};if(!object_record(&g,list_id(targets,j),&target)) break;
                int match=target.name && !strcmp(target.name,players[l->species]);
                uint32_t list=record_slot(&target,3);dw4_igb_record_free(&target);
                if(!match) continue;
                uint32_t n;const uint8_t *items=record_list(&g,list,&n);
                for(unsigned k=0;items && k<n;k++) {
                    dw4_igb_record item={0};if(!object_record(&g,list_id(items,k),&item)) break;
                    if(item.name && !strcmp(item.name,"TRNSS1") && matches<3) {
                        l->rings.delay[matches]=ee_f32_from_s32(record_slot(&item,4));
                        if(record_floats(&g,&item,5,l->rings.offset[matches],3) ||
                           (!strcmp(item.class_name,"beActionStarterData2") &&
                            record_floats(&g,&item,8,l->rings.rotation[matches],3))) {
                            dw4_igb_record_free(&item);dw4_igb_record_free(&r);goto done;
                        }
                        matches++;
                    }
                    dw4_igb_record_free(&item);
                }
            }
            if(matches!=3) {dw4_igb_record_free(&r);goto done;}
        }



        if (!strcmp(r.class_name, "beAction2Info") && r.name) for (unsigned k = 0; k < 4; k++) {
            uint32_t root;
            if (strcmp(r.name, names[k])) continue;
            static const char *actions[]={"WAIT01","OFSW01","ONSW01","OFF2ON","ON2OFF"};
            int valid=1;
            for(unsigned a=0;a<5;a++) if(portal_program(&g,&r,actions[a],&l->effect[k].program[a])) valid=0;
            if(!valid) continue;
            for (root = 0; root < l->scene.nnode; root++)
                if (l->scene.node[root].id == record_slot(&r, 7)) break;
            if (root == l->scene.nnode) continue;
            l->effect[k].root = root;
            l->effect[k].visible = 1;
            dw4_action2_host_init(&l->effect[k].clock);
            /* Created-card stage setup: flag 424 is clear, so the quest gate
             * is POWERON/ready (OFF pose), while exit/teleport stay POWEROF.
             * No active SWON transition is started during the greeting. */
            l->effect[k].powered=k==3;
            portal_start(&l->effect[k],k==3?PORTAL_OFF:PORTAL_WAIT,0);
            memcpy(l->effect[k].pos, placement[k], sizeof placement[k]);
            found |= 1u << k;
        }
        dw4_igb_record_free(&r);
    }
done:
    dw4_igb_close(&g);
    return isfinite(l->shadow_factor) && l->shadow_factor>=0 && l->shadow_factor<=1 &&
           isfinite(l->shadow_bounds[0]) && isfinite(l->shadow_bounds[1]) &&
           isfinite(l->shadow_bounds[2]) && isfinite(l->shadow_bounds[3]) &&
           l->shadow_bounds[0]>l->shadow_bounds[1] && l->shadow_bounds[2]>l->shadow_bounds[3] &&
           l->arrival_fade.fade_frames>0 && l->rings.program.count==5 && l->rings.root<l->scene.nnode &&
           l->stars.count==8 && l->stars.lifetime==1 && l->stars.delay &&
           isfinite(l->near_plane) && isfinite(l->far_plane) && l->near_plane>0 && l->far_plane>l->near_plane &&
           l->soft_ambient[3]==1 && l->soft_diffuse[3]==1 &&
           l->shadow_fb.rgba && l->shadow_receiver[0] && l->shadow_receiver[1] && found == 15 && isfinite(l->fog_start) && isfinite(l->fog_end) && l->fog_end > l->fog_start ? 0 : -1;
}

/* Action banks are actor-specific: male DELAY02 is 18, female DELAY02 is 90. */
static int64_t action_wait(const dw4_igb *g, const dw4_igb_record *bank, const char *name)
{
    dw4_igb_record list={0}; int64_t result=-1; uint32_t n;
    if (!object_record(g,record_slot(bank,9),&list)) return -1;
    const uint8_t *ids=dw4_igb_block(g,record_slot(&list,4),&n);
    if(ids && n%4==0) for(unsigned i=0;i<n;i+=4) {
        uint32_t id; dw4_igb_record a={0}, commands={0}; memcpy(&id,ids+i,4);
        if(!object_record(g,id,&a)) continue;
        if(a.name && !strcmp(a.name,name) && object_record(g,record_slot(&a,3),&commands)) {
            uint32_t size; const uint8_t *items=dw4_igb_block(g,record_slot(&commands,4),&size);
            if(items && size%4==0) for(unsigned j=0;j<size;j+=4) {
                dw4_igb_record w={0};memcpy(&id,items+j,4);
                if(object_record(g,id,&w) && !strcmp(w.class_name,"beAction2WAITCHECK"))
                    result=ee_f32_to_s64(ee_f32_div(ee_f32_mul(record_slot(&w,3),0x4e6e6b28),0x42700000));
                dw4_igb_record_free(&w);
            }
        }
        dw4_igb_record_free(&commands); dw4_igb_record_free(&a);
    }
    dw4_igb_record_free(&list);return result;
}
static int load_choreography(dw4_lobby *l,const uint8_t *blob,size_t size)
{
    dw4_igb g={0};unsigned found=0;
    if(dw4_igb_open(&g,blob,size,0)||dw4_igb_refs_open(&g)) goto done;
    for(unsigned i=0;i<g.table_n;i++) {
        dw4_igb_record r={0};if(!object_record(&g,i,&r)) continue;
        if(!strcmp(r.class_name,"beModelCtrlMOVE") && r.name) {
            if(!strcmp(r.name,"Move")) {l->move_value=record_slot(&r,3);l->move_frame=record_slot(&r,4);found|=1;}
            if(!strcmp(r.name,"Stop")) {l->stop_value=record_slot(&r,3);l->stop_frame=record_slot(&r,4);found|=2;}
        }
        if(!strcmp(r.class_name,"beModelCtrlMOVEEX") && r.name && !strcmp(r.name,"RYPACC") &&
           record_slot(&r,5)==0x41900000) {
            l->turn_value=record_slot(&r,3);l->turn_frame=record_slot(&r,4);l->turn_time=record_slot(&r,5);
            l->turn_stop=record_slot(&r,7);l->turn_stop_frame=record_slot(&r,8);found|=4;
        }
        if(!strcmp(r.class_name,"beAction2Info") && r.name) {
            if(!strcmp(r.name,"n_digilff")) {
                l->guide_turn_wait=action_wait(&g,&r,"DELAY03");
                l->guide_walk_wait=action_wait(&g,&r,"DELAY01");found|=8;
            }
            if(!strcmp(r.name,"n_digilfm")) {l->male_turn_wait=action_wait(&g,&r,"DELAY02");found|=16;}
        }
        if(!strcmp(r.class_name,"beModelCtrlInfo") && r.name && !strcmp(r.name,"n_digilff")) {
            /* Resolve this actor's AIM list, rather than another NPC's MAP01. */
            dw4_igb_record list={0};uint32_t n;
            if(object_record(&g,record_slot(&r,5),&list)) {
                const uint8_t *ids=dw4_igb_block(&g,record_slot(&list,4),&n);
                if(ids && n%4==0) for(unsigned j=0;j<n;j+=4) {
                    uint32_t id;dw4_igb_record aim={0},maps={0};memcpy(&id,ids+j,4);
                    if(object_record(&g,id,&aim) && !strcmp(aim.class_name,"beModelCtrlInfoDataAIM") &&
                       object_record(&g,record_slot(&aim,4),&maps)) {
                        uint32_t bytes;const uint8_t *mapids=dw4_igb_block(&g,record_slot(&maps,4),&bytes);
                        if(mapids && bytes%4==0) for(unsigned k=0;k<bytes;k+=4) {
                            dw4_igb_record map={0};memcpy(&id,mapids+k,4);
                            if(object_record(&g,id,&map) && !strcmp(map.class_name,"beModelCtrlAIMap") &&
                               map.name && !strcmp(map.name,"MAP01")) {
                                for(unsigned v=0;v<map.nvalues;v++) if(map.values[v].ordinal==11 &&
                                    map.values[v].str && !strcmp(map.values[v].str,"WPOS")) {
                                    uint32_t bits=record_slot(&map,3);memcpy(&l->guide_arrival_square,&bits,4);
                                    bits=record_slot(&map,6);memcpy(&l->guide_rot_limit,&bits,4);found|=32;
                                    for(unsigned z=0;z<4;z++) {
                                        if(z<3)l->guide_bounds[z]=record_slot(&map,z+3);
                                        uint32_t count;
                                        const uint8_t *choices=record_list(&g,record_slot(&map,z+7),&count);
                                        if(!choices || !count || count>16) {found=0;memset(l->guide_count,0,sizeof l->guide_count);goto bad_map;}
                                        l->guide_count[z]=count;
                                        for(unsigned c=0;c<count;c++) {
                                            dw4_igb_record choice={0};
                                            if(!object_record(&g,list_id(choices,c),&choice) ||
                                               strcmp(choice.class_name,"beModelCtrlAIData") || !choice.name ||
                                               strlen(choice.name)>=32) {dw4_igb_record_free(&choice);found=0;memset(l->guide_count,0,sizeof l->guide_count);goto bad_map;}
                                            strcpy(l->guide_sequence[z][c],choice.name);
                                            l->guide_ai[z][c]=(dw4_model_ai_choice){l->guide_sequence[z][c],
                                                record_slot(&choice,3),record_slot(&choice,4),(int32_t)record_slot(&choice,5)};
                                            dw4_igb_record_free(&choice);
                                        }
                                        if(l->guide_ai[z][count-1].limit<16){found=0;memset(l->guide_count,0,sizeof l->guide_count);goto bad_map;}
                                    }
                                }
                            }
bad_map:                    dw4_igb_record_free(&map);
                        }
                    }
                    dw4_igb_record_free(&maps);dw4_igb_record_free(&aim);
                }
            }
            dw4_igb_record_free(&list);
        }
        dw4_igb_record_free(&r);
    }
done:dw4_igb_close(&g);
    return found==63 && l->guide_count[0] && l->guide_count[1] &&
           l->guide_count[2] && l->guide_count[3] && isfinite(l->guide_arrival_square) && l->guide_arrival_square>0 &&
           isfinite(l->guide_rot_limit) && l->guide_rot_limit>0 &&
           l->guide_turn_wait>0 && l->guide_walk_wait>0 && l->male_turn_wait>0 ? 0:-1;
}
static ee_f32 npc_bits(float v) {ee_f32 b;memcpy(&b,&v,4);return b;}
static float npc_float(ee_f32 b) {float v;memcpy(&v,&b,4);return v;}
static void walk_start(dw4_lobby *l,unsigned actor,int stop)
{
    dw4_npc_motion_start(&l->walk[actor],stop?l->stop_value:l->move_value,
                        stop?l->stop_frame:l->move_frame,0,stop?2:0);
}
static void turn_start(dw4_lobby *l,unsigned actor)
{
    l->turn[actor].stop_value=l->turn_stop;l->turn[actor].stop_frame=l->turn_stop_frame;
    dw4_npc_motion_start(&l->turn[actor],l->turn_value,l->turn_frame,l->turn_time,0);
}

/* Original WPos bytecode supplies targets. Movement/sequence scheduling below
 * remains the bounded lobby adapter, rather than a general model controller. */
static int guide_wpos(dw4_lobby *l)
{
    dw4_script_model snapshot=l->guide_model;
    snapshot.call_name="WPos";snapshot.target_enabled=1;
    memset(snapshot.target,0,sizeof snapshot.target);
    int32_t before=l->guide_model.hp;
    if(dw4_scriptengine_model_event(l->scripts,l->script_scope,"aim_n_digilff.lua",&snapshot)) {
        snprintf(l->script_error,sizeof(l->script_error),"guide WPos: %s",dw4_scriptengine_error(l->scripts));
        return -1;
    }
    /* Retail commits cached HP only when the persistent value is unchanged. */
    if(l->guide_model.hp==before)l->guide_model.hp=snapshot.hp;
    memcpy(l->guide_model.target,snapshot.target,sizeof(snapshot.target));
    l->guide_events++;return 0;
}
static void guide_departure_tick(dw4_lobby *l,float delta,int64_t now)
{
    if(l->script_error[0])return;
    if(l->scripts && l->guide_ai_started && now>l->guide_ai_deadline) {
        ee_f32 distance=0;
        for(unsigned i=0;i<3;i++) {
            ee_f32 d=ee_f32_sub(npc_bits(l->guide_model.target[i]),npc_bits(l->female_pos[0][i]));
            distance=ee_f32_add(distance,ee_f32_mul(d,d));
        }
        unsigned zone=dw4_model_ai_zone(distance,l->guide_bounds);
        int c=dw4_model_ai_choose(&l->script_state->random,l->guide_ai[zone],l->guide_count[zone]);
        if(c<0){snprintf(l->script_error,sizeof(l->script_error),"guide MAP01 has no valid AI choice");return;}
        dw4_model_ai_choice *choice=l->guide_ai[zone]+c;
        l->guide_choice=c;l->guide_choices++;
        l->guide_ai_deadline=(int64_t)((uint64_t)now+(uint64_t)dw4_model_ai_duration(choice->frames));
        if(!strcmp(choice->sequence,"SQ_NEXT")) {
            if(guide_wpos(l))return;
            walk_start(l,1,0);l->phase[1]=5;
        } else if(!strcmp(choice->sequence,"SQ_WALK")) {walk_start(l,1,0);l->phase[1]=5;}
        else if(!strcmp(choice->sequence,"SQ_WAIT")) {walk_start(l,1,1);l->phase[1]=6;}
        else {snprintf(l->script_error,sizeof(l->script_error),"unsupported guide AI sequence: %s",choice->sequence);return;}
    }
    if(l->phase[1]!=5) return;
    const float *target=l->scripts?l->guide_model.target:lobby_guide_departure_target;
    float x=target[0]-l->female_pos[0][0];
    float z=target[2]-l->female_pos[0][2];
    if(!l->scripts && x*x+z*z<l->guide_arrival_square) {
        walk_start(l,1,1);l->phase[1]=6;
        return;
    }
    float desired=atan2f(x,z)*57.29577951308232f;
    float turn=remainderf(desired-l->female_yaw[0],360);
    float limit=l->guide_rot_limit*delta*57.29577951308232f;
    l->female_yaw[0]+=fmaxf(-limit,fminf(limit,turn));
}

static int add_actor(dw4_lobby *l, const dw4_scene *scene, uint32_t node, int actor)
{
    struct lobby_mesh *m = &l->mesh[l->nmesh];
    uint32_t mi = dw4_scene_node_mesh(scene, node);
    if (mi == UINT32_MAX) return -1;
    m->node = node; m->source = scene; m->actor = actor; m->slot = l->p->slot;
    if (dw4_scene_tris(scene, &scene->mesh[mi], &m->tri, &m->nt, NULL)) return -1;
    l->nmesh++;
    m->tex = texture(l, scene, dw4_scene_node_texture(scene, node));
    if (!m->tex && !(scene==&l->p->player && node==l->p->player_shadow_node)) {
        fprintf(stderr, "  lobby: actor %s has unresolved image %u\n", scene->node[node].name,
                dw4_scene_node_texture(scene, node));
        return -1;
    }
    l->capacity += 15*m->nt;
    return 0;
}

static unsigned player_collision(void *user,const float old[3],float position[3],int wall,int floor,const float land[4])
{
    struct lobby_player *P=user;dw4_lobby *l=P->lobby;struct lobby_player *saved=l->p;l->p=P;   /* the callback runs under whichever slot is current */
    const char *sequence=dw4_modelctrl_sequence(l->p->player_controller);
    unsigned contacts;
    /* The jump-slash finisher (SQ_ATCKTM) leaves the ground and waits for Landing like a jump. */
    int airborne=sequence && (!strcmp(sequence,"SQ_JUMP") || !strcmp(sequence,"SQ_FALL") || !strcmp(sequence,"SQ_ATCKTM"));
    if(airborne)contacts=dw4_lobby_collision_air_for(&l->collision,DW4_PLAYER_CHECK_FLAG,old,position,3,wall,floor);
    else contacts=dw4_lobby_collision_walk_for(&l->collision,DW4_PLAYER_CHECK_FLAG,old,position,3,4,4,wall,floor);
    l->p->player_contacts|=contacts;
    if(floor)dw4_modelctrl_player_floor(l->p->player_controller,airborne?!!(contacts&4):!(contacts&2),!!(contacts&4));
    l->p=saved;
    return contacts;
}
static void player_attack_labels(dw4_lobby *l);
static int player_labels(dw4_lobby *l)
{
    player_attack_labels(l);
    return dw4_modelctrl_label(l->p->player_controller,"SQ_WAIT",l->p->weapon_label) ||
        dw4_modelctrl_label(l->p->player_controller,"SQ_WALK",l->p->weapon_label) ||
        dw4_modelctrl_label(l->p->player_controller,"SQ_ENTR",l->p->weapon_label) ||
        dw4_modelctrl_label(l->p->player_controller,"SQ_JUMP",l->p->weapon_label) ||
        dw4_modelctrl_label(l->p->player_controller,"SQ_FALL",l->p->weapon_label);
}
/* The attack chain's weapon sections; a weapon family without a section keeps the sequence's unlabelled head. */
static void player_attack_labels(dw4_lobby *l)
{
    static const char *const names[]={"SQ_ATCK1","SQ_ATCK2","SQ_ATCK3","SQ_ATCKTM"};
    for(unsigned i=0;i<4;i++)dw4_modelctrl_label(l->p->player_controller,names[i],l->p->weapon_label);
}
static dw4_actoranim *player_animation(const dw4_lobby *l,const char *name,int shadow)
{
    if(name && !strcmp(name,l->p->player_run_motion))return shadow?l->p->player_run_shadow:l->p->player_run;
    if(name)for(unsigned i=0;i<12;i++) {
        char motion[16];snprintf(motion,sizeof motion,"jump%c%02u","DSAG"[i/3],i%3+1);
        if(!strcmp(name,motion))return l->p->player_jump[i][!!shadow];
    }
    return shadow?l->p->player_shadow:l->p->player_idle;
}
void dw4_lobby_jump(dw4_lobby *l,int pressed){if(l)l->p->jump_pressed=!!pressed;}
void dw4_lobby_talk(dw4_lobby *l,int pressed){if(l)l->p->talk_pressed=!!pressed;}
int dw4_lobby_talk_result(const dw4_lobby *l){return l?l->p->talk_hits:-1;}
static int player_run_open(dw4_lobby *l,const uint8_t *blob,uint32_t size)
{
    l->p->player_run=dw4_actoranim_open_motion(blob,size,&l->p->player,l->p->player_node,l->p->player_run_motion);
    l->p->player_run_shadow=dw4_actoranim_open_motion(blob,size,&l->p->player,l->p->player_shadow_node,l->p->player_run_motion);
    return !l->p->player_run || !l->p->player_run_shadow;
}
void dw4_lobby_input(dw4_lobby *l,float x,float y)
{
    if(l){l->p->input_x=isfinite(x)?fmaxf(-1,fminf(1,x)):0;l->p->input_y=isfinite(y)?fmaxf(-1,fminf(1,y)):0;}
}
int dw4_lobby_walk(const dw4_lobby *l,dw4_lobby_walk_state *out)
{
    if(!l || !out || !l->p->player_controller)return -1;
    dw4_modelctrl_actor a={0};dw4_modelctrl_actor_state(l->p->player_controller,&a);
    *out=(dw4_lobby_walk_state){.yaw=a.rotation[1],.motion=a.motion,.motion_ns=a.motion_ns,.contacts=l->p->player_contacts};
    memcpy(out->position,dw4_modelctrl_active(l->p->player_controller)?a.position:l->p->player_world+12,sizeof out->position);
    memcpy(&out->speed,&a.channel[2].speed,4);return 0;
}
static int player_walk_tick(dw4_lobby *l,int64_t now)
{
    dw4_modelctrl *m=l->p->player_controller;
    if(!dw4_modelctrl_active(m) && !l->native_models) {
        dw4_modelctrl_sample(m,now);
        if(player_labels(l) || dw4_modelctrl_start(m,"SQ_WAIT"))return -1;
        char transform[160],error[256];
        float yaw=atan2f(l->p->player_world[8],l->p->player_world[0])*57.295779513f;
        snprintf(transform,sizeof transform,"V<%.9g,%.9g,%.9g>/V<0,%.9g,0>",
            l->p->player_world[12],l->p->player_world[13],l->p->player_world[14],yaw);
        dw4_script_value a[]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
            {DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,transform,strlen(transform)}},r;
        if(dw4_modelctrl_service(m,"sd",a,5,&r,error,sizeof error))return -1;
        a[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"ONCTRL",6};
        if(dw4_modelctrl_service(m,"sd",a,4,&r,error,sizeof error))return -1;
    }
    float x=l->p->input_x,y=l->p->input_y;
    int walking=l->control.player_control && dw4_pad_directions(x,y)!=0;
    if(walking || l->p->jump_pressed || l->p->talk_pressed)l->badge_active_ns=l->native_now;
    /* 3d22f0 adds camera +Z yaw to atan(stickX,-stickY). Host +Y is
     * up; reversing the camera axis instead would reverse horizontal input. */
    uint32_t xb,yb;memcpy(&xb,&x,4);memcpy(&yb,&y,4);
    float cx=l->control.camera_world[8],cz=l->control.camera_world[10];uint32_t cxb,czb;
    memcpy(&cxb,&cx,4);memcpy(&czb,&cz,4);
    uint32_t direction=dw4_model_player_direction(xb,yb,cxb,czb);
    float yaw;memcpy(&yaw,&direction,4);
    const char *sequence=dw4_modelctrl_sequence(m);
    if(l->p->jump_pressed && l->finished && l->control.player_control && sequence &&
       (!strcmp(sequence,"SQ_WAIT") || !strcmp(sequence,"SQ_WALK"))) {
        dw4_modelctrl_sample(m,now);
        if(dw4_modelctrl_start(m,"SQ_JUMP"))return -1;
    }
    /* 3d22f0 refuses the probe in SQ_JUMP/SQ_FALL; one button is handled per update. */
    int talk=l->p->talk_pressed && !l->p->jump_pressed && l->finished && l->control.player_control && l->native_models &&
        sequence && strcmp(sequence,"SQ_JUMP") && strcmp(sequence,"SQ_FALL");
    l->p->talk_pressed=0;
    l->p->jump_pressed=0;
    if(dw4_modelctrl_player_input(m,walking,yaw) || (l->native_models?dw4_modelctrl_tick_frame(m,now,l->native_frame):dw4_modelctrl_tick(m,now)))return -1;
    dw4_modelctrl_actor actor={0};dw4_modelctrl_actor_state(m,&actor);
    float angle=actor.rotation[1]*.017453292519943295f;
    memset(l->p->player_world,0,sizeof l->p->player_world);
    l->p->player_world[0]=l->p->player_world[10]=cosf(angle);l->p->player_world[2]=-sinf(angle);l->p->player_world[8]=sinf(angle);
    l->p->player_world[5]=l->p->player_world[15]=1;memcpy(l->p->player_world+12,actor.position,sizeof actor.position);
    if(talk) {
        /* kind60000 start1/length1 executes once at the sub-command update after movement.
         * The probe's shooter is the pressing player's slot: BLTgetShootRamNo is the talk script's g_messPlayerNo (the hub NPC scripts store it, and
         * every selector and SUBWND of that talk names it). The single hub player is slot 0; a co-op player in a field world is its own slot. */
        dw4_model_talk_probe probe={.shoot_ram_no=(int32_t)l->p->slot,.world_ns=l->native_now};
        memcpy(probe.source_world,l->p->player_world,sizeof probe.source_world);
        dw4_hitbox_talk_probe(l->p->player_world,probe.box);
        l->p->talk_hits=dw4_controllers_talk(l->native_models,&probe);
        if(l->p->talk_hits<0){snprintf(l->script_error,sizeof l->script_error,"talk: %s",dw4_controllers_error(l->native_models));return -1;}
    }
    return 0;
}
int dw4_lobby_weapon(dw4_lobby *l,dw4_mount *mount,const char *asset,char *error,size_t cap)
{
    char player_asset_name[32];
    if(!l || !mount || !asset || !l->finished || lobby_asset_name(l->species,player_asset_name)){snprintf(error,cap,"weapon publication requires a live joined player");return -1;}
    char path[32];int len=snprintf(path,sizeof path,"%s%s",asset,!*asset || strstr(asset,".igb")?"":".igb");   /* "" unarmed */
    if(len<0 || (size_t)len>=sizeof path){snprintf(error,cap,"weapon asset name too long");return -1;}
    if(!strcmp(path,l->p->weapon_asset))return 0;
    uint32_t size;const uint8_t *player=dw4_mount_data(mount,player_asset_name,&size);if(!player)return -1;
    dw4_lobby *c=calloc(1,sizeof *c);if(!c)return -1;*c=*l;c->p=c->pl+(l->p-l->pl);
    c->p->weapon=(dw4_scene){0};c->p->weapon_count=0;c->p->weapon_label[0]=c->p->player_motion[0]=c->p->weapon_bone[0]=0;
    c->texture=NULL;c->mesh=NULL;c->p->player_idle=c->p->player_shadow=c->p->player_run=c->p->player_run_shadow=NULL;unsigned retained=0,newtextures=0;
    unsigned *texture_map=calloc(l->ntexture,sizeof *texture_map);if(!texture_map){free(c);return -1;}
    c->ntexture=0;c->nmesh=0;
    dw4_layer_draw *draw=NULL,*casters=NULL;
    if(open_player_weapon(c,mount,l->species,player,size,path))goto bad;
    c->p->player_idle=dw4_actoranim_open_motion(player,size,&l->p->player,l->p->player_node,c->p->player_motion);
    c->p->player_shadow=dw4_actoranim_open_motion(player,size,&l->p->player,l->p->player_shadow_node,c->p->player_motion);
    if(!c->p->player_idle || !c->p->player_shadow || player_run_open(c,player,size))goto bad;
    dw4_actoranim_loop(c->p->player_idle,1);dw4_actoranim_loop(c->p->player_shadow,1);
    for(unsigned k=0;k<c->p->weapon_count;k++){float bone[16];if(dw4_actoranim_bone(c->p->player_idle,c->p->weapon_bones[k],0,bone))goto bad;}
    c->texture=calloc(l->ntexture+c->p->weapon.nimg+l->pack[0].ntex+l->pack[1].ntex+1,sizeof *c->texture);
    c->mesh_capacity=l->nmesh+c->p->weapon.nnode+1;
    c->mesh=calloc(c->mesh_capacity,sizeof *c->mesh);if(!c->texture || !c->mesh)goto bad;
    for(unsigned i=0;i<l->ntexture;i++){
        texture_map[i]=UINT32_MAX;
        int used=l->stars.tex==&l->texture[i].tex;
        for(unsigned j=0;j<l->nmesh && !used;j++)
            used=l->mesh[j].source!=&l->p->weapon && l->mesh[j].tex==&l->texture[i].tex;
        if(used){texture_map[i]=c->ntexture;c->texture[c->ntexture++]=l->texture[i];}
    }
    newtextures=c->ntexture;
    for(unsigned i=0;i<l->nmesh;i++)if(l->mesh[i].source==&l->p->weapon)c->capacity-=15*l->mesh[i].nt;
    c->nmesh=0;
    for(unsigned i=0;i<l->nmesh;i++)if(l->mesh[i].source!=&l->p->weapon){
        struct lobby_mesh m=l->mesh[i];
        for(unsigned k=0;k<l->ntexture;k++)if(m.tex==&l->texture[k].tex){m.tex=&c->texture[texture_map[k]].tex;break;}
        c->mesh[c->nmesh++]=m;
    }retained=c->nmesh;
    for(unsigned k=0;k<c->p->weapon_count;k++)for(unsigned n=0;n<c->p->weapon.nnode;n++){
        uint32_t ancestor=n;while(ancestor<c->p->weapon.nnode && ancestor!=c->p->weapon_roots[k])ancestor=c->p->weapon.node[ancestor].parent;
        if(ancestor==c->p->weapon_roots[k] && dw4_scene_node_mesh(&c->p->weapon,n)!=UINT32_MAX){
            if(add_actor(c,&c->p->weapon,n,2))goto bad;
            c->mesh[c->nmesh-1].attachment=(int)k;
        }
    }
    draw=calloc((size_t)c->capacity*2,sizeof *draw);unsigned caster_count=0;
    for(unsigned i=0;i<c->nmesh;i++)if(c->mesh[i].actor || c->mesh[i].casts_shadow)caster_count+=c->mesh[i].nt;
    casters=calloc(caster_count,sizeof *casters);if(!draw || !casters)goto bad;
    const dw4_tex *star=NULL;for(unsigned k=0;k<l->ntexture;k++)if(l->stars.tex==&l->texture[k].tex)star=&c->texture[texture_map[k]].tex;
    if(dw4_gl_layer_textures_reset(l->gpu)){
        if(dw4_gpu_policy_required()){dw4_gpu_policy_fail("lobby texture cache reset");goto bad;}
        dw4_gl_layer_close(l->gpu);l->gpu=NULL;
    }
    for(unsigned i=0;i<l->nmesh;i++)if(l->mesh[i].source==&l->p->weapon)free(l->mesh[i].tri);
    dw4_scene_close(&l->p->weapon);dw4_actoranim_close(l->p->player_idle);dw4_actoranim_close(l->p->player_shadow);
    for(unsigned i=0;i<l->ntexture;i++)if(texture_map[i]==UINT32_MAX){
        if(l->texture[i].name){free(l->texture[i].mode_rgba[0]);free(l->texture[i].mode_rgba[1]);}
        else free((void *)l->texture[i].tex.rgba);
    }
    free(l->mesh);free(l->texture);free(l->draw);free(l->casters);
    l->p->weapon=c->p->weapon;l->p->weapon_count=c->p->weapon_count;l->p->weapon_root=c->p->weapon_root;
    memcpy(l->p->weapon_roots,c->p->weapon_roots,sizeof l->p->weapon_roots);memcpy(l->p->weapon_bones,c->p->weapon_bones,sizeof l->p->weapon_bones);
    memcpy(l->p->weapon_asset,c->p->weapon_asset,sizeof l->p->weapon_asset);memcpy(l->p->weapon_label,c->p->weapon_label,sizeof l->p->weapon_label);
    l->p->weapon_submitted_triangles=0;memset(l->p->weapon_submitted,0,sizeof l->p->weapon_submitted);
    memcpy(l->p->weapon_bone,c->p->weapon_bone,sizeof l->p->weapon_bone);memcpy(l->p->player_motion,c->p->player_motion,sizeof l->p->player_motion);
    l->mesh=c->mesh;l->mesh_capacity=c->mesh_capacity;l->nmesh=c->nmesh;l->texture=c->texture;l->ntexture=c->ntexture;l->capacity=c->capacity;l->draw=draw;l->casters=casters;l->stars.tex=star;
    for(unsigned i=retained;i<l->nmesh;i++)l->mesh[i].source=&l->p->weapon;
    for(unsigned i=newtextures;i<l->ntexture;i++)if(l->texture[i].source==&c->p->weapon)l->texture[i].source=&l->p->weapon;
    dw4_actoranim_close(l->p->player_run);dw4_actoranim_close(l->p->player_run_shadow);
    l->p->player_run=c->p->player_run;l->p->player_run_shadow=c->p->player_run_shadow;
    memcpy(l->p->player_run_motion,c->p->player_run_motion,sizeof l->p->player_run_motion);
    l->p->player_idle=c->p->player_idle;l->p->player_shadow=c->p->player_shadow;l->p->player_loop=1;
    if(player_labels(l) || (dw4_modelctrl_active(l->p->player_controller) && dw4_modelctrl_start(l->p->player_controller,"SQ_WAIT"))) {
        snprintf(l->script_error,sizeof l->script_error,"player weapon sequence publication failed");
    }
    l->p->player_idle_start=(((int64_t)(l->age?l->age-1:0)*1000000000LL/60)>>18)<<18;
    free(texture_map);free(c);return 0;
 bad:
    if(c->mesh)for(unsigned i=retained;i<c->nmesh;i++)free(c->mesh[i].tri);
    if(c->texture)for(unsigned i=newtextures;i<c->ntexture;i++){if(c->texture[i].name){free(c->texture[i].mode_rgba[0]);free(c->texture[i].mode_rgba[1]);}else free((void *)c->texture[i].tex.rgba);}
    free(c->mesh);free(c->texture);free(draw);free(casters);dw4_scene_close(&c->p->weapon);dw4_actoranim_close(c->p->player_idle);dw4_actoranim_close(c->p->player_shadow);dw4_actoranim_close(c->p->player_run);dw4_actoranim_close(c->p->player_run_shadow);free(texture_map);free(c);
    snprintf(error,cap,"weapon %s graph/motion/attachment preparation failed",path);return -1;
}
/* Field worlds: the overworld and fortress stages (stag0xxx, stagGFxx) and the dungeon floors (dngXXXxx), opened as ordinary worlds without the hub windows. */
int dw4_lobby_field_world(const char *stage)
{return stage && (!strncasecmp(stage,"stag0",5) || !strncasecmp(stage,"stagGF",6) || !strncasecmp(stage,"dng",3));}
/* Open the player the lobby currently acts on (l->p): its character pack and weapon, the idle/shadow/run/jump motions, the model controller and its
 * collision. Returns 0, or -1 with the slot partly built (dw4_lobby_close releases it). */
static int open_player(dw4_lobby *l,dw4_mount *mnt,int species,const char *player_asset,const char *selected_weapon)
{
    uint32_t player_size,j;
    const uint8_t *player_blob = dw4_mount_data(mnt, player_asset, &player_size);
    if (!player_blob || dw4_scene_load_actor_preview(&l->p->player, player_blob, player_size) ||
        open_player_weapon(l, mnt, species, player_blob, player_size,selected_weapon) ||
        player_entry_fade(player_blob,player_size,&l->p->player_fade)) return -1;
    /* PLAYER join enables P1 and its Shadow instance. Respect igLod's authored
     * ranges instead of selecting a mesh by its artist-assigned shape name. */
    for(j=0;j<l->p->player.nnode;j++) if(l->p->player.node[j].switch_mask.off) {
        if(dw4_scene_switch_set(&l->p->player,j,-1,0) || dw4_scene_switch_set(&l->p->player,j,0,1)) return -1;
        if(l->p->player.node[j].name && !strcmp(l->p->player.node[j].name,"PC01") &&
           dw4_scene_switch_set(&l->p->player,j,4,1)) return -1;
    }
    for (j = 0; j < l->p->player.nnode; j++) {
        uint32_t ancestor;
        if (dw4_scene_node_mesh(&l->p->player, j) == UINT32_MAX) continue;
        if (!dw4_scene_node_visible(&l->p->player,j,0) ||
            !dw4_scene_node_texture(&l->p->player, j)) continue;
        for (ancestor = j; ancestor < l->p->player.nnode; ancestor = l->p->player.node[ancestor].parent)
            if (!strcmp(l->p->player.node[ancestor].class_name, "igBlendMatrixSelect")) break;
        if (ancestor >= l->p->player.nnode) continue;
        l->p->player_idle = dw4_actoranim_open_motion(player_blob, player_size, &l->p->player, j, l->p->player_motion);
        if (l->p->player_idle) { l->p->player_node = j; break; }
    }
    if (l->p->player_node == UINT32_MAX) return -1;
    /* The registered Shadow switch references low-detail igActors directly,
     * bypassing the visible player's igLod. Its first child belongs to P1. */
    l->p->player_shadow_node=UINT32_MAX;
    for(j=0;j<l->p->player.nnode;j++) if(l->p->player.node[j].name &&
        !strcmp(l->p->player.node[j].name,"Shadow")) {
        for(uint32_t k=j+1;k<l->p->player.nnode && l->p->player.node[k].depth>l->p->player.node[j].depth;k++)
            if(dw4_scene_node_mesh(&l->p->player,k)!=UINT32_MAX) {
                l->p->player_shadow_node=k;
                l->p->player_shadow=dw4_actoranim_open_motion(player_blob,player_size,&l->p->player,k,l->p->player_motion);
                break;
            }
        break;
    }
    if(!l->p->player_shadow || player_run_open(l,player_blob,player_size)) return -1;
    for(unsigned i=0;i<12;i++) {
        char motion[16];snprintf(motion,sizeof motion,"jump%c%02u","DSAG"[i/3],i%3+1);
        l->p->player_jump[i][0]=dw4_actoranim_open_motion(player_blob,player_size,&l->p->player,l->p->player_node,motion);
        l->p->player_jump[i][1]=dw4_actoranim_open_motion(player_blob,player_size,&l->p->player,l->p->player_shadow_node,motion);
        if(!l->p->player_jump[i][0] || !l->p->player_jump[i][1])return -1;
    }
    l->p->player_controller=dw4_modelctrl_open(player_blob,player_size,lobby_models[species]);
    if(!l->p->player_controller || player_labels(l))return -1;
    dw4_modelctrl_collide(l->p->player_controller,player_collision,l->p);
    dw4_actoranim_loop(l->p->player_idle,0);dw4_actoranim_loop(l->p->player_shadow,0);
    return 0;
}
static dw4_lobby *open_stage(dw4_mount *mnt, int species, const char *name,const char *stage,int32_t point,const char *weapon,const dw4_lobby_member *others,unsigned nothers)
{
    dw4_lobby *l = calloc(1, sizeof *l);
    dw4_igfile f = {0};
    if (l) for (unsigned i = 0; i < 4; i++) {l->pl[i].lobby = l; l->pl[i].slot = i;}
    if (l) {l->p = l->pl; l->pl[0].joined = 1;}
    uint32_t j, world_scene = UINT32_MAX, camera_scene = UINT32_MAX;
    int dungeon=0;
    const char *step="stage selection";
    char player_asset[32];
    if (!l) return NULL;
    if (lobby_asset_name(species,player_asset) || !name || !*name || !stage || point<0) goto fail;
    /* Field worlds play the full "p_" character pack (attack sequences); the hubs use the talk-only "m_" pack. */
    if(dw4_lobby_field_world(stage) && snprintf(player_asset,sizeof player_asset,"%s.igb",lobby_models[species])>=(int)sizeof player_asset)goto fail;
    /* stagML02 is the Commander Room (NDMW 815/816), entered from the Terminal's mate01 gate. */
    static const char *stages[]={"stagML11","stagML12","stagML13","stagML14","stagML02"};
    unsigned si=0;while(si<5 && strcasecmp(stage,stages[si]))si++;
    /* Field stages (stag0xxx) run as an ordinary world without the hub's window models (si==5). */
    if(si==5 && (!dw4_lobby_field_world(stage) || strlen(stage)>=sizeof l->stage))goto fail;
    snprintf(l->stage,sizeof l->stage,"%s",si==5?stage:stages[si]);l->terminal=si==0;l->field=si==5;l->arrival_point=point;
    l->message = -1; l->species = species; l->pl[0].species = species; l->light_hard = 1;
    l->hard_ambient[0]=l->hard_ambient[1]=.2f;l->hard_ambient[2]=.35f;
    for(unsigned i=0;i<3;i++)l->hard_diffuse[i]=1.1f;
    snprintf(l->p->player_name, sizeof l->p->player_name, "%s", name);
    l->npc_node = l->female_node = l->p->player_node = UINT32_MAX;
    if (dw4_igfile_open_stage_pack(&f,mnt,l->stage,0,0) ||
        dw4_scene_load_world(&l->scene, f.data, f.len)) goto fail;
    if(l->terminal) {
        for (j = 0; j < l->scene.nnode; j++)
            if (l->scene.node[j].name && !strcmp(l->scene.node[j].name, "N_dijilfmShape")) {
                static const char *motions[] = {"walk01", "wait01", "talk01"};
                unsigned k;
                l->npc_node = j;
                for (k = 0; k < 3; k++) {
                    l->npc_motion[k] = dw4_actoranim_open_motion(f.data, f.len, &l->scene, j, motions[k]);
                    if (!l->npc_motion[k]) goto fail;
                }
                break;
            }
        for (j = 0; j < l->scene.nnode; j++)
            if (l->scene.node[j].name && !strcmp(l->scene.node[j].name, "N_dijilffShape1")) {
                static const char *motions[] = {"walk01", "wait01", "talk01"};
                l->female_node = j;
                for (unsigned k = 0; k < 3; k++) {
                    l->female_motion[k] = dw4_actoranim_open_motion(f.data, f.len, &l->scene, j, motions[k]);
                    if (!l->female_motion[k]) goto fail;
                }
                break;
            }
    }
    step="arrival point";if(dw4_playerpoint_matrix(f.data,f.len,point,0,l->p->player_world))goto fail;
    for(int g=0;g<8;g++)for(unsigned pl=0;pl<4;pl++)l->point_ok[g][pl]=!dw4_playerpoint_matrix(f.data,f.len,g,pl,l->point_matrix[g][pl]);
    dungeon=!strncasecmp(l->stage,"dng",3);
    step="camera/material bounds";if(load_control(l,f.data,f.len,!dungeon,1))goto fail;
    if(dungeon) {
        /* The floor's box camera and demo cameras are separate packs: aaacamera.igb (Near) or aaacameral.igb (Far), and acmr_pack.igb. */
        char path[96];uint32_t size;const uint8_t *rig,*demos;
        snprintf(path,sizeof path,"%s/separate/aaacamera%s.igb",l->stage,dw4_options_get()->camera_far?"l":"");
        step="dungeon box camera";if(!(rig=dw4_mount_data(mnt,path,&size)) || load_control(l,rig,size,1,0))goto fail;
        camera_planes(l,rig,size);
        snprintf(path,sizeof path,"%s/separate/acmr_pack.igb",l->stage);
        step="dungeon demo cameras";
        if((demos=dw4_mount_data(mnt,path,&size))) {
            if(dw4_scene_load(&l->camera_pack,demos,size))goto fail;
            l->ext_camera=1;
            if(load_demo_cameras(l,&l->camera_pack,demos,size))goto fail;
        } else {
            /* A floor without acmr_pack.igb (dng102b2) has no demo cameras: its scripts send no SETDEMOCAMERA, only the box rig, and the rig pack's own igCamera
             * (cameraShape00, the one camera_planes reads) is the draw camera. A pack that exists but fails to load still fails above. */
            uint32_t rig_size=0;const uint8_t *again;
            snprintf(path,sizeof path,"%s/separate/aaacamera%s.igb",l->stage,dw4_options_get()->camera_far?"l":"");
            if(!(again=dw4_mount_data(mnt,path,&rig_size)) || dw4_scene_load(&l->camera_pack,again,rig_size))goto fail;
            l->ext_camera=1;
        }
    }
    step="Terminal choreography";if(l->terminal && load_choreography(l,f.data,f.len))goto fail;
    step="demo cameras";if(!l->terminal && !dungeon && load_demo_cameras(l,&l->scene,f.data,f.len))goto fail;
    if(!l->terminal)load_hit_names(l,f.data,f.len);
    step="collision";if(dw4_lobby_collision_open(&l->collision,&l->scene))goto fail;
    dw4_lobby_collision_dynamic_pose(&l->collision,lobby_dynamic_pose,l);
    if(si==5){
        printf("  hub %s: collision %u floor / %u wall triangle(s)\n",l->stage,l->collision.floor.count,l->collision.wall.count);
        if(getenv("DW4_COLLISION_BOUNDS")){
            const dw4_collision_mesh *ms[2]={&l->collision.floor,&l->collision.wall};
            for(int q=0;q<2;q++){float lo[3]={1e9f,1e9f,1e9f},hi[3]={-1e9f,-1e9f,-1e9f};
                for(uint32_t t=0;t<ms[q]->count*3;t++){const float *v=ms[q]->positions+3*ms[q]->indices[t];for(int a=0;a<3;a++){if(v[a]<lo[a])lo[a]=v[a];if(v[a]>hi[a])hi[a]=v[a];}}
                printf("    %s bounds x %g..%g y %g..%g z %g..%g\n",q?"wall":"floor",lo[0],hi[0],lo[1],hi[1],lo[2],hi[2]);}
        }
    }
    step="world environment";if(load_environment(l,f.data,f.len))goto fail;
    step="Terminal effects";if(l->terminal && load_effects(l,f.data,f.len))goto fail;
    step="dialogue/HUD";if(si!=5 && !(l->ui=dw4_lobbyui_open(mnt,&l->scene,f.data,f.len)))goto fail;
    l->stage_file=f;memset(&f,0,sizeof f);
    step="player assets";
    char weapon_path[32];const char *selected_weapon=NULL;
    if(weapon && !*weapon)selected_weapon="";   /* unarmed: dw4_lobby_open_row_stage_unarmed */
    else if(weapon) {
        int len=snprintf(weapon_path,sizeof weapon_path,"%s%s",weapon,strstr(weapon,".igb")?"":".igb");
        if(!*weapon || len<0 || (size_t)len>=sizeof weapon_path)goto fail;
        selected_weapon=weapon_path;
    }
    if(open_player(l,mnt,species,player_asset,selected_weapon))goto fail;
    if (l->terminal && (l->npc_node == UINT32_MAX || l->female_node == UINT32_MAX)) goto fail;
    /* Local co-op: the other joined players take slots 1..3 with their own character pack, weapon, motions and controller, and start at the
     * authored arrival point of their slot (the stage's bePoint01Info rows list one point per player). */
    step="co-op players";
    for(unsigned i=0;i<nothers;i++) {
        const dw4_lobby_member *mb=others+i;unsigned slot=i+1;
        char asset[32],wpath[32];const char *sel=NULL;
        /* The field worlds play the full "p_" pack, the hubs the talk-only "m_" pack (as slot 0 above). */
        if(slot>3 || mb->row<0 || mb->row>15 || !mb->name[0] || !l->point_ok[point<8?point:0][slot] ||
           (l->field?snprintf(asset,sizeof asset,"%s.igb",lobby_models[mb->row])>=(int)sizeof asset:lobby_asset_name(mb->row,asset)))goto fail;
        if(mb->weapon && !*mb->weapon)sel="";
        else if(mb->weapon) {
            int len=snprintf(wpath,sizeof wpath,"%s%s",mb->weapon,strstr(mb->weapon,".igb")?"":".igb");
            if(len<0 || (size_t)len>=sizeof wpath)goto fail;
            sel=wpath;
        }
        l->p=&l->pl[slot];l->p->joined=1;
        snprintf(l->p->player_name,sizeof l->p->player_name,"%s",mb->name);
        memcpy(l->p->player_world,l->point_matrix[point<8?point:0][slot],sizeof l->p->player_world);
        l->p->species=mb->row;
        if(open_player(l,mnt,mb->row,asset,sel)){l->p=l->pl;goto fail;}
        l->p=l->pl;
    }
    l->p->player_previous_start=(((int64_t)LOBBY_PLAYER_ENTRY_DELAY*1000000000LL/60)>>18)<<18;
    l->entry_tick=LOBBY_PLAYER_ENTRY_DELAY;
    l->npc_pos[0] = 69.11f; l->npc_pos[1] = 10; l->npc_pos[2] = -13.79f; l->npc_yaw = -90;
    l->female_pos[0][0] = 60; l->female_pos[0][1] = 10; l->female_pos[0][2] = -10;
    l->female_yaw[0] = 117;
    l->female_pos[1][0] = 63.12f; l->female_pos[1][1] = 10; l->female_pos[1][2] = -55.8f;
    l->female_yaw[1] = 78.8f;
    l->npc_motion_index = l->female_index = 1;
    l->second_index=0;if(l->terminal)walk_start(l,2,0);
    /* Entry placement was resolved through the authored bePoint01Info data
     * list while the stage pack was open, independently of graph traversal. */
    step="world camera";
    l->camera = UINT32_MAX;
    for (j = 0; j < l->scene.ngraph; j++)
        if (l->scene.graph[j].name && !strcmp(l->scene.graph[j].name, "camsp0101"))
            camera_scene = j;
    for (j = 0; j < l->scene.nnode; j++) {
        const dw4_scene_node *n = &l->scene.node[j];
        if (world_scene == UINT32_MAX && n->parent == UINT32_MAX &&
            n->name && !strcmp(n->name, "BG02")) world_scene = n->scene;
        if (!l->ext_camera && l->camera == UINT32_MAX && (l->terminal?n->scene == camera_scene:1) && n->class_name &&
            !strcmp(n->class_name, "igCamera")) l->camera = j;
    }
    for(j=0;l->ext_camera && j<l->camera_pack.nnode;j++)   /* a dungeon floor's camera node is in its separate camera pack */
        if(l->camera_pack.node[j].class_name && !strcmp(l->camera_pack.node[j].class_name,"igCamera")){l->camera=j;break;}
    if (world_scene == UINT32_MAX || l->camera == UINT32_MAX) goto fail;
    l->background_scene=world_scene;
    /* Stage ALLON and the bounded active model instances publish their masks. */
    for(j=0;j<l->scene.nnode;j++) if(l->scene.node[j].switch_mask.off &&
       dw4_scene_switch_set(&l->scene,j,-1,1)) goto fail;
    /* Action2's switch children are RAM slots. Created-card startup generates
     * only slot zero; the commander gate's two ungenerated branches stay off. */
    for(unsigned k=0;l->terminal && k<4;k++) {
        if(dw4_scene_switch_set(&l->scene,l->effect[k].root,-1,0) ||
           dw4_scene_switch_set(&l->scene,l->effect[k].root,0,1))goto fail;
    }
    for (j = 0; j < l->scene.nnode; j++)
        if (l->terminal && l->scene.node[j].scene == camera_scene && l->scene.node[j].has_seq) {
            if (((l->scene.node[j].seq.interpolation_method >> 8) & 255u) != 1) goto fail;
            l->scene.node[j].seq.rotation_euler = 1;
        }
    /* Preallocate the texture cache: draw records retain pointers into it. */
    step="scoped world textures";
    for (j = 0; j < 2; j++) {
        uint32_t size;
        /* Resolve each area's scoped Hard/Soft pair, never a global basename. */
        char texture_path[64];snprintf(texture_path,sizeof texture_path,"%s/separate/%s_pack.igb",l->stage,j?"LS":"LH");
        const uint8_t *blob = dw4_mount_data(mnt, texture_path, &size);
        if(dungeon && !blob)continue;   /* a dungeon floor has no Hard/Soft texture pair; its textures are in the world pack */
                if (!blob || dw4_texpack_open(&l->pack[j], blob, size) ||
            dw4_igb_open(&l->texture_ids[j], blob, size, 0) ||
            dw4_igb_refs_open(&l->texture_ids[j])) goto fail;
    }
    step="world geometry";
    size_t party_images=0,party_nodes=0;
    for(unsigned q=0;q<4;q++)if(l->pl[q].joined){party_images+=l->pl[q].player.nimg+l->pl[q].weapon.nimg;party_nodes+=l->pl[q].player.nnode+l->pl[q].weapon.nnode;}
    l->texture = calloc(l->scene.nimg + party_images + l->pack[0].ntex + l->pack[1].ntex, sizeof *l->texture);
    l->mesh_capacity=2*l->scene.nnode+party_nodes;
    l->mesh = calloc(l->mesh_capacity, sizeof *l->mesh);
    if (!l->texture || !l->mesh) goto fail;
    if(l->terminal) {
        l->stars.tex=texture(l,&l->scene,dw4_scene_node_texture(&l->scene,l->stars.node));
        if(!l->stars.tex) goto fail;
        uint32_t star_src=4,star_dst=5;float star_ref=0;
        dw4_scene_node_blend(&l->scene,l->stars.node,&star_src,&star_dst);
        dw4_scene_node_alpha_ref(&l->scene,l->stars.node,&star_ref);
        l->stars.blend=star_src==4 && star_dst==1?2:1;l->stars.aref=(int)floorf(star_ref*128);
        l->capacity+=3*8*2*10;
    }
    for (j = 0; j < l->scene.nnode; j++) {
        uint32_t mi = dw4_scene_node_mesh(&l->scene, j);
        struct lobby_mesh *m;
        int effect = 0;
        for (unsigned k = 0; l->terminal && k < 4; k++) {
            uint32_t root = l->effect[k].root;
            if (j > root && l->scene.node[j].scene == l->scene.node[root].scene) {
                uint32_t a = j;
                while (a < l->scene.nnode && a != root) a = l->scene.node[a].parent;
                if (a == root) effect = k+1;
            }
        }
        if (mi == UINT32_MAX || (l->scene.node[j].scene != world_scene && !effect)) continue;
        m = &l->mesh[l->nmesh];
        m->node = j; m->effect = effect;
        m->source = &l->scene;
        if (dw4_scene_tris(&l->scene, &l->scene.mesh[mi], &m->tri, &m->nt, NULL)) goto fail;
        l->nmesh++;
        {
            const char *name = dw4_scene_node_texture_name(&l->scene, j);
            m->tex = name ? named_texture(l, name) : texture(l, &l->scene, dw4_scene_node_texture(&l->scene, j));
            if (name && !m->tex) goto fail;
        }
        l->capacity += 15*m->nt;
    }
    if (!l->nmesh) goto fail;
    /* Three authored ring instances, placed by the player's entry presentation. */
    for(unsigned k=0;l->terminal && k<3;k++) {
        uint32_t root=l->rings.node[k];
        memset(l->scene.node[root].m,0,64);
        l->scene.node[root].has_matrix=1;
        float yaw=l->rings.rotation[k][1];
        l->scene.node[root].m[0]=l->scene.node[root].m[10]=cosf(yaw);
        l->scene.node[root].m[2]=-sinf(yaw);l->scene.node[root].m[8]=sinf(yaw);
        l->scene.node[root].m[5]=l->scene.node[root].m[15]=1;
        memcpy(l->scene.node[root].m+12,l->p->player_world+12,12);
        for(unsigned j=0;j<3;j++) l->scene.node[root].m[12+j]+=l->rings.offset[k][j];
        for(j=root+1;j<l->scene.nnode && l->scene.node[j].depth>l->scene.node[root].depth;j++) {
            uint32_t mi=dw4_scene_node_mesh(&l->scene,j);
            if(mi==UINT32_MAX) continue;
            struct lobby_mesh *m=&l->mesh[l->nmesh++];
            m->node=j;m->source=&l->scene;m->arrival=k+1;
            if(dw4_scene_tris(&l->scene,&l->scene.mesh[mi],&m->tri,&m->nt,NULL)) goto fail;
            m->tex=texture(l,&l->scene,dw4_scene_node_texture(&l->scene,j));
            if(!m->tex) goto fail;
            l->capacity+=15*m->nt;
        }
    }
    if(l->terminal)printf("  lobby: BG02 + portal/arrival controllers, %u mesh(es), %u texture(s); camera camsp0101\n",
           l->nmesh, l->ntexture);
    else printf("  hub %s: authored environment, %u mesh(es), %u texture(s); box camera\n",l->stage,l->nmesh,l->ntexture);
    step="actor and shadow geometry";
    if(l->terminal) {
        if(add_actor(l,&l->scene,l->npc_node,1) || add_actor(l,&l->p->player,l->p->player_node,2) ||
           add_actor(l,&l->scene,l->female_node,3) || add_actor(l,&l->scene,l->female_node,4))goto fail;
    } else if(add_actor(l,&l->p->player,l->p->player_node,2))goto fail;
    if(add_actor(l,&l->p->player,l->p->player_shadow_node,2)) goto fail;
    l->mesh[l->nmesh-1].caster_only=1;
    for(unsigned k=0;k<l->p->weapon_count;k++)for(j=0;j<l->p->weapon.nnode;j++) {
        uint32_t ancestor=j;
        while(ancestor<l->p->weapon.nnode && ancestor!=l->p->weapon_roots[k])ancestor=l->p->weapon.node[ancestor].parent;
        if(ancestor==l->p->weapon_roots[k] && dw4_scene_node_mesh(&l->p->weapon,j)!=UINT32_MAX){
            if(add_actor(l,&l->p->weapon,j,2))goto fail;
            l->mesh[l->nmesh-1].attachment=(int)k;
        }
    }
    for(unsigned q=1;q<4;q++) {   /* the co-op players' bodies, shadow casters and weapons, tagged with their slot */
        if(!l->pl[q].joined)continue;
        l->p=&l->pl[q];
        if(add_actor(l,&l->p->player,l->p->player_node,2) || add_actor(l,&l->p->player,l->p->player_shadow_node,2)){l->p=l->pl;goto fail;}
        l->mesh[l->nmesh-1].caster_only=1;
        for(unsigned k=0;k<l->p->weapon_count;k++)for(j=0;j<l->p->weapon.nnode;j++) {
            uint32_t ancestor=j;
            while(ancestor<l->p->weapon.nnode && ancestor!=l->p->weapon_roots[k])ancestor=l->p->weapon.node[ancestor].parent;
            if(ancestor==l->p->weapon_roots[k] && dw4_scene_node_mesh(&l->p->weapon,j)!=UINT32_MAX){
                if(add_actor(l,&l->p->weapon,j,2)){l->p=l->pl;goto fail;}
                l->mesh[l->nmesh-1].attachment=(int)k;
            }
        }
        l->p=l->pl;
    }
    /* Receiver graphs are explicit beShadow01Info references, independent of
     * visible BG02 materials. Submit each graph once, rather than every shared
     * graph path occurrence in the pack. */
    for(unsigned k=0;k<2;k++) {
        uint32_t root;
        if(!l->shadow_receiver[k] && l->field)continue;   /* a field stage may have a single receiver graph */
        for(root=0;root<l->scene.nnode;root++) if(l->scene.node[root].id==l->shadow_receiver[k]) break;
        if(root==l->scene.nnode) goto fail;
        for(j=root;j<l->scene.nnode && (j==root || l->scene.node[j].depth>l->scene.node[root].depth);j++) {
            uint32_t mi=dw4_scene_node_mesh(&l->scene,j);
            if(mi==UINT32_MAX) continue;
            struct lobby_mesh *m=&l->mesh[l->nmesh++];
            m->source=&l->scene;m->node=j;m->shadow=1;m->tex=&l->shadow_tex;
            if(dw4_scene_tris(&l->scene,&l->scene.mesh[mi],&m->tri,&m->nt,NULL)) goto fail;
            l->capacity+=15*m->nt;
        }
    }
    unsigned caster_capacity=0;
    for(unsigned i=0;i<l->nmesh;i++) if(l->mesh[i].actor) caster_capacity+=l->mesh[i].nt;
    l->casters=calloc(caster_capacity,sizeof *l->casters);
    if(!l->casters) goto fail;
    float bone[16];
    if (l->p->weapon_count && dw4_actoranim_bone(l->p->player_idle, l->p->weapon_bone, 0, bone)) goto fail;
    printf("  lobby: starter %s, %s -> %s, attachment %s\n",
           l->p->weapon_count?l->p->weapon_asset:"(unarmed)", l->p->weapon_label, l->p->player_motion, l->p->weapon_count?l->p->weapon_bone:"none");
    l->draw = calloc((size_t)l->capacity*2, sizeof *l->draw);
    if (!l->draw) goto fail;
    if(l->terminal)printf("  lobby: player %s, SQ_ENTR fade 50; Terminal Area flag 500 -> TALKFONT02 39..53\n", l->p->player_name);
    if(!l->terminal) {
        l->camera_time.loaded=1;l->camera_scripted=1;l->control.box_camera=1;
        box_camera_tick(l,0);
    }
    /* A dungeon floor's first.lua never pauses the material regions or restores the HUD (the stag0101 intro does, ending in MATCTRL RESTART):
     * its regions, HUD and controls are live from the start; the entry demo (SETDEMOCAMERA entry, SQ_DEMOWALK) gates the player itself. */
    if(dungeon) {
        l->control.hud=l->control.model_control=l->control.material_updates=1;
        l->control.player_control=1;l->finished=1;
        dw4_lobbyui_restore_hud(l->ui,l->species);
    }
    return l;
fail:
    fprintf(stderr,"  hub preparation %s: %s failed\n",stage?stage:"<null>",step);
    dw4_igfile_close(&f);
    dw4_lobby_close(l);
    return NULL;
}

dw4_lobby *dw4_lobby_open_stage(dw4_mount *mnt,int species,const char *name,const char *stage,int32_t point)
{return species<0||species>3?NULL:open_stage(mnt,lobby_starter_row[species],name,stage,point,NULL,NULL,0);}
dw4_lobby *dw4_lobby_open_stage_equipped(dw4_mount *mnt,int species,const char *name,const char *stage,int32_t point,const char *weapon)
{return weapon && *weapon && species>=0 && species<=3?open_stage(mnt,lobby_starter_row[species],name,stage,point,weapon,NULL,0):NULL;}
dw4_lobby *dw4_lobby_open(dw4_mount *mnt,int species,const char *name)
{return dw4_lobby_open_stage(mnt,species,name,"stagML11",0);}
/* By shinka row (any of the sixteen player models). A starter may omit the weapon (its created-card weapon is used); an evolved form
 * needs the equipped weapon's asset. */
dw4_lobby *dw4_lobby_open_row_stage(dw4_mount *mnt,int row,const char *name,const char *stage,int32_t point,const char *weapon)
{return row<0||row>15||(!(weapon&&*weapon)&&row>3)?NULL:open_stage(mnt,row,name,stage,point,weapon&&*weapon?weapon:NULL,NULL,0);}
dw4_lobby *dw4_lobby_open_row_stage_party(dw4_mount *mnt,int row,const char *name,const char *stage,int32_t point,const char *weapon,const dw4_lobby_member *others,unsigned nothers)
{return row<0||row>15||(!weapon&&row>3)||nothers>3||(nothers&&!others)?NULL:open_stage(mnt,row,name,stage,point,weapon,others,nothers);}
dw4_lobby *dw4_lobby_open_row_stage_unarmed(dw4_mount *mnt,int row,const char *name,const char *stage,int32_t point)
{return row<0||row>15?NULL:open_stage(mnt,row,name,stage,point,"",NULL,0);}
int dw4_lobby_player_row(const dw4_lobby *l){return l?l->species:-1;}
const dw4_hudmeter *dw4_lobby_hud_meter(const dw4_lobby *l,unsigned index){return l?dw4_lobbyui_meter(l->ui,index,NULL):NULL;}

int dw4_lobby_world_info(const dw4_lobby *l,dw4_lobby_world_state *out)
{
    if(!l || !out)return -1;
    *out=(dw4_lobby_world_state){l->stage,l->arrival_point,l->nbox,l->nmaterial,l->collision.floor.count,l->collision.wall.count};return 0;
}

void dw4_lobby_close(dw4_lobby *l)
{
    if(l)for(unsigned q=0;q<4;q++)for(unsigned i=0;i<12;i++)for(unsigned j=0;j<2;j++)dw4_actoranim_close(l->pl[q].player_jump[i][j]);
    unsigned i;
    if (!l) return;
    for(unsigned k=0;k<4;k++)dw4_action2_host_close(&l->effect[k].clock);
    for(unsigned k=0;k<3;k++)dw4_action2_host_close(&l->rings.clock[k]);
    for(unsigned q=0;q<4;q++){dw4_modelctrl_close(l->pl[q].player_controller);
        dw4_actoranim_close(l->pl[q].player_run);dw4_actoranim_close(l->pl[q].player_run_shadow);}
    dw4_lobby_detach_scripts(l);
    dw4_lobbyui_actions(l->ui,NULL,NULL);
    dw4_frontaudio_close(l->audio);
    dw4_gl_layer_close(l->gpu);
    dw4_gl_layer_close(l->shadow_gpu);
    dw4_lobby_collision_close(&l->collision);free(l->dyn_model);
    for (i = 0; i < l->nmesh; i++) free(l->mesh[i].tri);
    for (size_t k = 0; k < l->nwcache; k++) free(l->wcache[k].w);
    free(l->wcache);
    for (i = 0; i < l->ntexture; i++) {
        if (l->texture[i].name) {
            free(l->texture[i].mode_rgba[0]); free(l->texture[i].mode_rgba[1]);
        } else free((void *)l->texture[i].tex.rgba);
    }
    for(unsigned k=0;k<l->nmesh;k++) {
        struct instance_motion *motion=l->mesh[k].motions;
        while(motion){struct instance_motion *next=motion->next;dw4_actoranim_close(motion->animation);free(motion->name);free(motion);motion=next;}
    }
    free(l->instances);free(l->instance_nodes);
    free(l->texture); free(l->mesh); free(l->draw);
    free(l->casters);dw4_fb_free(&l->shadow_fb);
    for (i = 0; i < 2; i++) dw4_igb_close(&l->texture_ids[i]);
    for (i = 0; i < 3; i++) { dw4_actoranim_close(l->npc_motion[i]); dw4_actoranim_close(l->female_motion[i]); }
    for(unsigned q=0;q<4;q++){dw4_actoranim_close(l->pl[q].player_idle);dw4_actoranim_close(l->pl[q].player_shadow);dw4_scene_close(&l->pl[q].weapon);}
    dw4_lobbyui_close(l->ui);
    for(unsigned q=0;q<4;q++)dw4_scene_close(&l->pl[q].player);
    dw4_scene_close(&l->scene);dw4_scene_close(&l->camera_pack);
    free(l->box);
    dw4_igfile_close(&l->stage_file);
    free(l);
}

static void lobby_window_sound(void *user,const char *model,const char *action)
{dw4_lobby_model_action(user,model,action);}
int dw4_lobby_prepare_audio(dw4_lobby *l, dw4_mount *mnt)
{
    if (!l) return -1;
    if (!l->audio && l->field) {
        /* A field stage names its own effects and tracks in its sound pack; the manifest stores the stage lower-case with .igb. */
        char file[24];size_t i;
        for(i=0;l->stage[i] && i<sizeof file-5;i++)file[i]=l->stage[i]>='A' && l->stage[i]<='Z'?(char)(l->stage[i]+32):l->stage[i];
        memcpy(file+i,".igb",5);
        l->audio = dw4_frontaudio_prepare_gameplay(mnt,file);
    }
    if (!l->audio) l->audio = dw4_frontaudio_prepare_lobby_stage(mnt,l->stage);
    if(l->audio)dw4_lobbyui_actions(l->ui,lobby_window_sound,l);
    return l->audio ? 0 : -1;
}
void dw4_lobby_start_audio(dw4_lobby *l)
{
    if (l) dw4_frontaudio_start_lobby(l->audio);
}
int dw4_lobby_start_scripted_audio(dw4_lobby *l)
{return l?dw4_frontaudio_start_scripted(l->audio):-1;}

const char *dw4_lobby_enable_gpu(dw4_lobby *l, int w, int h)
{
    if (!l) return NULL;
    dw4_gl_layer_close(l->gpu);
    dw4_gl_layer_close(l->shadow_gpu);
    l->gpu = dw4_gl_layer_open(w, h);
    l->shadow_gpu=l->gpu?dw4_gl_layer_open(256,256):NULL;
    if(!l->shadow_gpu){dw4_gl_layer_close(l->gpu);l->gpu=NULL;}
    return l->gpu ? dw4_gl_layer_info(l->gpu) : NULL;
}

int dw4_lobby_message(const dw4_lobby *l)
{
    return l ? dw4_lobbyui_message(l->ui) : -1;
}
int dw4_lobby_intro_done(const dw4_lobby *l) { return l && l->finished; }
void dw4_lobby_party_hud(dw4_lobby *l,int party){if(l)dw4_lobbyui_party(l->ui,party);}
void dw4_lobby_status(dw4_lobby *l,int active){if(l){l->status_hold=!!active;dw4_lobbyui_status(l->ui,active);}}
int dw4_lobby_health(dw4_lobby *l,int32_t level,int32_t hp,int32_t mp,int32_t max_hp,int32_t max_mp)
{return l?dw4_lobbyui_health(l->ui,level,hp,mp,max_hp,max_mp):-1;}
const dw4_modelctrl *dw4_lobby_window_model(const dw4_lobby *l,unsigned i){return l?dw4_lobbyui_model(l->ui,i):NULL;}
int dw4_lobby_talk_open(const dw4_lobby *l){return l && dw4_lobbyui_talk_open(l->ui);}
dw4_frontaudio *dw4_lobby_audio(dw4_lobby *l){return l?l->audio:NULL;}
int dw4_lobby_adopt_audio(dw4_lobby *to,dw4_lobby *from)
{return to && from?dw4_frontaudio_adopt_device(to->audio,from->audio):-1;}
int dw4_lobby_sound_service(void *u,const char *m,const dw4_script_value *a,size_t n,dw4_script_value *r,char *e,size_t c)
{dw4_lobby *l=u;return l?dw4_frontaudio_script_service(l->audio,m,a,n,r,e,c):-1;}
int dw4_lobby_attach_scripts(dw4_lobby *l,dw4_mount *mount,dw4_scriptengine *e,
    dw4_be_state *state,uint64_t scope)
{
    if(!l || !e || !state || l->scripts || l->age)return -1;
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_igb pack={0};int rc=-1;
    if(blob && !dw4_igb_open(&pack,blob,size,0) &&
       dw4_script_collect_pack_scoped(dw4_scriptengine_vm(e),scope,&pack)==64 &&
       !dw4_scriptengine_run(e,"func.lua")) {
        rc=dw4_lobby_bind_scripts(l,e,state,scope);
    }
    dw4_igb_close(&pack);return rc;
}
int dw4_lobby_bind_scripts(dw4_lobby *l,dw4_scriptengine *e,dw4_be_state *state,uint64_t scope)
{
    if(!l || !e || !state || l->scripts || l->age)return -1;
    l->scripts=e;l->script_state=state;l->script_scope=scope;
    /* Under the original first.lua the camera is the authored box camera unless the script starts a demo camera: only the first-arrival
     * greeting (flag 501 clear) calls SETDEMOCAMERA camsp0101. A character that has seen it (a called, progressed save) arrives with no
     * demo, as retail does; the native 240-tick stage camera below is the unscripted fallback of the script-less tests. */
    if(!l->camera_scripted){l->camera_time.loaded=1;l->camera_scripted=1;l->camera_demo=0;l->control.box_camera=1;box_camera_tick(l,0);}
    dw4_lobbyui_services_random(l->ui,&state->random,&state->action_rhythm);
    l->guide_model=(dw4_script_model){.ram_no=2,.hp=100,.max_hp=100,.info_name="n_digilff"};
    for(unsigned i=0;i<4;i++)dw4_action2_host_random(&l->effect[i].clock,&state->random,&state->action_rhythm);
    for(unsigned i=0;i<3;i++)dw4_action2_host_random(&l->rings.clock[i],&state->random,&state->action_rhythm);
    return 0;
}
void dw4_lobby_dialogue(dw4_lobby *l,dw4_dialogue *d)
{if(l){l->native_dialogue=d;dw4_lobbyui_dialogue(l->ui,d);}}
void dw4_lobby_detach_scripts(dw4_lobby *l)
{
    if(!l || !l->scripts)return;
    dw4_scriptengine_remove_scope(l->scripts,l->script_scope);
    l->scripts=NULL;l->script_state=NULL;l->guide_ai_started=0;
    dw4_lobbyui_services_random(l->ui,NULL,NULL);
    for(unsigned i=0;i<4;i++)dw4_action2_host_random(&l->effect[i].clock,NULL,NULL);
    for(unsigned i=0;i<3;i++)dw4_action2_host_random(&l->rings.clock[i],NULL,NULL);
}
const char *dw4_lobby_script_error(const dw4_lobby *l) {return l?l->script_error:"no lobby";}
int dw4_lobby_ai(const dw4_lobby *l,dw4_lobby_ai_state *out)
{
    if(!l || !out)return -1;
    *out=(dw4_lobby_ai_state){.hp=l->guide_model.hp,.events=l->guide_events,
        .choices=l->guide_choices,.choice=l->guide_choice};
    memcpy(out->target,l->guide_model.target,sizeof(out->target));return 0;
}
int dw4_lobby_window_service(void *user,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_lobby *l=user;
    return dw4_lobbyui_script_service(l?l->ui:NULL,method,a,n,r,error,cap);
}

void dw4_lobby_services_sample(dw4_lobby *l,uint64_t ns)
{
    if(!l)return;
    dw4_frontaudio_set_clock(l->audio,ns);
    if(l->camera_scripted && l->camera_demo)dw4_camera_time_tick(&l->camera_time,ns);
    dw4_lobbyui_services_sample(l->ui,(int64_t)ns);
    if(l->native_models){l->native_now=ns-l->native_origin;dw4_modelctrl_sample(l->p->player_controller,(int64_t)l->native_now);}
    if(l->native_sd){   /* every joined slot: the KO flow erases and regenerates a downed player's model outside the slot's own receiver */
        for(unsigned q=0;q<4;q++){
            struct lobby_player *P=l->pl+q;
            if(!P->joined || !P->player_token)continue;
            int active=dw4_modelctrl_active(P->player_controller);
            dw4_scriptservices_active(l->native_sd,P->player_token,active);
            dw4_scriptservices_active(l->native_sd,P->player_model_token,active);
        }
    }
}
/* The world-space player-number badge. Retail's beNDMWMdlPlayer::vfunc_44 (3d4390) sends MODELCTRL <player> SETEFFECT
 * i_pcnumic "SQ_OPENP<n>" 480.0 V<0,10,0> true true; the effect model stands 10 units above the player's node. The
 * port drives the same i_pcnumic controller natively: generated while the player is under control (retail shows no badge
 * during the greeting or a conversation), following the player each tick. Player 0 is the only joined player here. */
static int badge_send(dw4_lobby *l,const char *command,const char *value)
{
    dw4_script_value a[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"i_pcnumic",9},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,command,strlen(command)},{0}},r;
    char error[256];size_t n=4;
    if(value){a[4]=(dw4_script_value){DW4_SCRIPT_STRING,0,value,strlen(value)};n=5;}
    return dw4_controllers_send(l->native_models,"i_pcnumic",0,"sd",a,n,&r,error,sizeof error);
}
static int badge_tick(dw4_lobby *l)
{
    if(!l->native_models || dw4_controllers_live(l->native_models,"i_pcnumic",0)<0)return 0;
    int control=l->control.player_control && l->finished && dw4_modelctrl_active(l->p->player_controller);
    /* Retail shows the badge only after 480.0 frames (the SETEFFECT time) without input;
     * measured live 2026-10-20: absent at 420 idle frames, present at 540. */
    if(!control)l->badge_active_ns=l->native_now;
    /* vfunc_44 sends SETEFFECT only while the player's sequence is SQ_WAIT (0x516290), so any other sequence restarts the delay. */
    {const char *seq=dw4_modelctrl_sequence(l->p->player_controller);
     if(!seq || strcmp(seq,"SQ_WAIT"))l->badge_active_ns=l->native_now;}
    int want=control && l->native_now-l->badge_active_ns>=480ull*1000000000ull/60;
    char text[160];
    snprintf(text,sizeof text,"V<%.9g,%.9g,%.9g>/V<0,0,0>",l->p->player_world[12],l->p->player_world[13]+10,l->p->player_world[14]);
    if(want && !l->badge_live) {
        char generate[200];snprintf(generate,sizeof generate,"%s/SQ_OPENP0",text);
        if(badge_send(l,"GENERATE",generate))return -1;
        l->badge_live=1;
    } else if(want) {
        if(badge_send(l,"MOVETRANS",text))return -1;
    } else if(l->badge_live) {
        if(badge_send(l,"REMOVE",NULL))return -1;
        l->badge_live=0;
    }
    return 0;
}
int dw4_lobby_services_tick(dw4_lobby *l,uint64_t ns)
{
    if(!l)return -1;
    dw4_lobby_services_sample(l,ns);
    l->native_frame=dw4_modelsubcom_frame((int64_t)l->native_frame_clock,(int64_t)l->native_now);l->native_frame_clock=l->native_now;
    if(badge_tick(l)){snprintf(l->script_error,sizeof(l->script_error),"player-number badge failed");return -1;}
    if(l->ui && dw4_lobbyui_services_tick(l->ui,(int64_t)ns)) {
        snprintf(l->script_error,sizeof(l->script_error),"window: %s",dw4_lobbyui_services_error(l->ui));return -1;
    }
    return 0;
}
static int script_equal(dw4_script_value v,const char *s)
{
    return v.type==DW4_SCRIPT_STRING && v.string && v.length==strlen(s) && !memcmp(v.string,s,v.length);
}
static unsigned actor_collision(void *user,const float old[3],float position[3],int wall,int floor,const float land[4])
{
    /* Stable scene-owned callback rows, never host pointers in arena fields. */
    struct actor_collision_owner *o=user;
    unsigned hit=dw4_lobby_collision_check_for(&o->lobby->collision,DW4_ACTOR_CHECK_FLAG,old,position,3,4,4,wall,floor);
    o->lobby->contacts[o->actor]|=hit;return hit;
}
static unsigned scene_actor_collision(void *user,const float old[3],float position[3],int wall,int floor,const float land[4])
{
    dw4_lobby *l=user;unsigned flags=(unsigned)land[3];
    if(floor&DW4_COLLIDE_FALLS) {
        /* An enemy: it walks and hops with the player's own solvers, so no floor edge holds it. A step off the floor onto a lower floor reports bit 2 (nothing in the window supports it) and
         * the model starts its SQ_FALL; with no floor below at all it is reported supported and walks on in the air; a falling or hopping enemy lands on the first floor at or below its old height. A stage without floor triangles
         * has nothing to support or drop a model: it keeps the walls only. */
        if(!l->collision.floor.count)return dw4_lobby_collision_check_for(&l->collision,flags,old,position,land[0],land[1],land[2],wall,0);
        unsigned hit=(floor&~DW4_COLLIDE_FALLS)==DW4_COLLIDE_AIR?dw4_lobby_collision_air_for(&l->collision,flags,old,position,land[0],wall,1):
            dw4_lobby_collision_walk_for(&l->collision,flags,old,position,land[0],land[1],land[2],wall,1);
        return hit;
    }
    return dw4_lobby_collision_check_for(&l->collision,flags,old,position,land[0],land[1],land[2],wall,floor);
}
static int lobby_actor_name(const char *name)
{return name && (!strcmp(name,"n_digilfm") || !strcmp(name,"n_digilff") || !strcmp(name,"n_agumon") || !strcmp(name,"n_leomon"));}
static int lobby_near_player(void *user,const float position[3],float target[3])
{
    dw4_lobby *l=user;
    /* The nearest active player to the enemy: with several joined players (local co-op) an enemy turns on whichever stands closest. */
    float best=0;int found=0;
    for(unsigned q=0;q<4;q++) {
        if(!l->pl[q].joined || !dw4_modelctrl_active(l->pl[q].player_controller))continue;
        dw4_modelctrl_actor actor={0};dw4_modelctrl_actor_state(l->pl[q].player_controller,&actor);
        float dx=actor.position[0]-position[0],dy=actor.position[1]-position[1],dz=actor.position[2]-position[2],d=dx*dx+dy*dy+dz*dz;
        if(!found || d<best){best=d;found=1;memcpy(target,actor.position,sizeof actor.position);}
    }
    return found?0:-1;
}
int dw4_lobby_native_models(dw4_lobby *l,dw4_controllers *models,uint64_t origin)
{
    static const char *names[]={"n_digilfm","n_digilff","n_digilff"};
    static const int32_t slots[]={0,2,3};
    if(!l)return -1;
    if(l->native_models) {
        static const char *gates[]={"g_cyexit","g_cytelep1","g_cytrerp2"};
        for(unsigned k=0;k<3;k++)dw4_controllers_nearest(l->native_models,gates[k],0,NULL,NULL);
    }
    if(l->native_models)for(size_t i=0;i<dw4_controllers_count(l->native_models);i++) {
        const dw4_stageobject *info;int32_t slot;
        const dw4_modelctrl *model=dw4_controllers_model(l->native_models,i,&info,&slot);
        if((l->dynamic_world || l->ninstance) && dw4_modelctrl_has_near_map(model))dw4_controllers_nearest(l->native_models,dw4_stageobject_name(info),slot,NULL,NULL);
        if((l->dynamic_world && !strncmp(dw4_stageobject_name(info),"n_",2)) || lobby_actor_name(dw4_stageobject_name(info)))dw4_controllers_collision(l->native_models,dw4_stageobject_name(info),slot,NULL,NULL);
    }
    l->native_models=NULL;l->dyn_owner=NULL;memset(l->native_actor,0,sizeof l->native_actor);
    if(!models && l->native_sd){
        for(unsigned q=0;q<4;q++){
            dw4_scriptservices_unregister(l->native_sd,l->pl[q].player_token);
            dw4_scriptservices_unregister(l->native_sd,l->pl[q].player_model_token);
            l->pl[q].player_token=l->pl[q].player_model_token=0;
        }
        l->native_sd=NULL;
    }
    l->native_fade=NULL;memset(l->native_portal,0,sizeof l->native_portal);
    if(!models)return 0;
    if(l->age)return -1;
    for(unsigned k=0;k<3;k++) {
        for(size_t i=0;i<dw4_controllers_count(models);i++) {
            const dw4_stageobject *info;int32_t slot;
            const dw4_modelctrl *m=dw4_controllers_model(models,i,&info,&slot);
            if(slot==slots[k] && !strcmp(dw4_stageobject_name(info),names[k])){l->native_actor[k]=m;break;}
        }
        if(!l->native_actor[k])return -1;
    }
    l->native_models=models;l->native_origin=origin;l->native_now=0;
    /* Scene-owned startup: the entry effect follows the original scripts' own PLAYER SQ_ENTR (queued with delay 30 on an
     * arrival with flag 501 set, DM delay 180 in the flag-501-clear greeting), not the greeting's generated delay. */
    l->entry_tick=UINT_MAX;
    static const char *portal_names[]={"g_cyexit","g_cyheal","g_cytelep1","g_cytrerp2"};
    for(size_t i=0;i<dw4_controllers_count(models);i++) {
        const dw4_stageobject *info;int32_t slot;
        const dw4_modelctrl *model=dw4_controllers_model(models,i,&info,&slot);
        if(!slot && !strcmp(dw4_stageobject_name(info),"i_fadewn01"))l->native_fade=model;
        for(unsigned k=0;!slot && k<4;k++)if(!strcmp(dw4_stageobject_name(info),portal_names[k])) {
            l->native_portal[k]=model;
            if(k!=1 && dw4_controllers_nearest(models,portal_names[k],slot,lobby_near_player,l))return -1;
        }
        if(lobby_actor_name(dw4_stageobject_name(info)) && dw4_controllers_collision(models,dw4_stageobject_name(info),slot,scene_actor_collision,l))return -1;
    }
    if(!l->native_fade)return -1;
    for(unsigned k=0;k<4;k++)if(!l->native_portal[k])return -1;
    for(unsigned k=0;k<3;k++) {
        l->collision_owner[k].lobby=l;l->collision_owner[k].actor=k;
        if(dw4_controllers_collision(models,names[k],slots[k],actor_collision,l->collision_owner+k))return -1;
    }
    l->hidden_actors=15;return 0;
}
static dw4_actoranim *instance_motion(dw4_lobby *,struct lobby_mesh *,const char *);
static const char *world_layer(const dw4_stageobjects *objects,const dw4_scene *scene,uint32_t id)
{
    for(unsigned root=0;root<scene->nnode;root++)if(scene->node[root].id==id) {
        for(size_t i=0;i<dw4_stageobjects_attachments(objects);i++) {
            const dw4_layer_attachment *a=dw4_stageobjects_attachment(objects,i);
            if(a->info->scene!=scene)continue;
            for(uint32_t n=root;n<scene->nnode;n=scene->node[n].parent)
                if(scene->node[n].id==a->root_id)return dw4_stageobjects_layer(objects,a->layer);
        }
    }
    return NULL;
}
/* One controller model's world instance(s): meshes of its RAM slot's graph, drawn by the instance branch of the lobby draw.
 * Returns 0 (also when the model has no world layer) or -1 with *operation naming the failing step. */
static int add_world_instance(dw4_lobby *l,const dw4_igb *gp,const dw4_stageobjects *objects,const dw4_modelctrl *model,
    const dw4_stageobject *info,int32_t slot,const char **operation)
{
    const char *name=dw4_stageobject_name(info);
        if((info)->igb->data!=l->stage_file.data)return 0;
        *operation="action bank";dw4_igb_record bank={0};
        if(named_record((dw4_igb *)gp,"beAction2Info",name,&bank))return -1;
        uint32_t id=record_slot(&bank,7),database=record_slot(&bank,8);dw4_igb_record_free(&bank);
        const char *layer=world_layer(objects,info->scene,id);
        if(!layer || !strncmp(layer,"WN",2) || !strncmp(layer,"BG",2) || !strcmp(layer,"NONE"))return 0;
        *operation="graph root";uint32_t root;
        for(root=0;root<l->scene.nnode;root++)if(l->scene.node[root].id==id)break;
        if(root==l->scene.nnode)return -1;
        *operation="RAM slot node";
        if(l->scene.node[root].switch_mask.off) {
            unsigned selected=l->scene.node[root].switch_bits>1?(unsigned)slot:0,index=0;
            uint32_t child;
            for(child=root+1;child<l->scene.nnode && l->scene.node[child].depth>l->scene.node[root].depth;child++)
                if(l->scene.node[child].parent==root && index++==selected)break;
            if(child==l->scene.nnode || l->scene.node[child].parent!=root)return -1;
            root=child;
        }
        *operation=l->scene.node[root].class_name;
        if(strcmp(l->scene.node[root].class_name,"beModelCtrlNode2"))return -1;
        uint32_t end=root+1;while(end<l->scene.nnode && l->scene.node[end].depth>l->scene.node[root].depth)end++;
        struct world_instance *rows=realloc(l->instances,(l->ninstance+1)*sizeof *rows);if(!rows)return -1;
        l->instances=rows;unsigned instance=l->ninstance++;
        rows[instance]=(struct world_instance){.model=model,.root=root,.end=end,.database=database};
        snprintf(rows[instance].layer,sizeof rows[instance].layer,"%s",layer);
        snprintf(rows[instance].name,sizeof rows[instance].name,"%s",name);
        for(unsigned n=root;n<end;n++) {
            uint32_t mi=dw4_scene_node_mesh(&l->scene,n);
            if(mi==UINT32_MAX || !dw4_scene_node_visible(&l->scene,n,0))continue;
            if(l->nmesh>=l->mesh_capacity) {
                size_t capacity=l->mesh_capacity*2;struct lobby_mesh *mesh=realloc(l->mesh,capacity*sizeof *mesh);
                if(!mesh)return -1;
                memset(mesh+l->mesh_capacity,0,(capacity-l->mesh_capacity)*sizeof *mesh);l->mesh=mesh;l->mesh_capacity=capacity;
            }
            struct lobby_mesh *m=l->mesh+l->nmesh++;*m=(struct lobby_mesh){.node=n,.source=&l->scene,.instance=instance+1,.casts_shadow=!strncmp(name,"n_",2)};
            *operation="triangles";
            if(dw4_scene_tris(&l->scene,l->scene.mesh+mi,&m->tri,&m->nt,NULL))return -1;
            *operation="texture";const char *texture_name=dw4_scene_node_texture_name(&l->scene,n);
            m->tex=texture_name?named_texture(l,texture_name):texture(l,&l->scene,dw4_scene_node_texture(&l->scene,n));
            if((texture_name || dw4_scene_node_texture(&l->scene,n)) && !m->tex)return -1;
            for(uint32_t a=n;a<l->scene.nnode;a=l->scene.node[a].parent)if(!strcmp(l->scene.node[a].class_name,"igBlendMatrixSelect")){m->skinned=1;break;}
        }
    return 0;
}
int dw4_lobby_native_scene(dw4_lobby *l,dw4_controllers *models,const dw4_stageobjects *objects,uint64_t origin)
{
    if(!l || !models || !objects || l->age || l->native_models || l->gpu || l->dynamic_world)return -1;
    l->dynamic_world=1;l->native_models=models;l->native_origin=origin;
    unsigned keep=0;
    for(unsigned i=0;i<l->nmesh;i++) {
        struct lobby_mesh *m=l->mesh+i;
        if(m->effect || m->arrival || (m->actor && m->actor!=2)){free(m->tri);continue;}
        l->mesh[keep++]=*m;
    }
    l->nmesh=keep;l->hidden_actors=2;for(unsigned q=1;q<4;q++)if(l->pl[q].joined)l->hidden_actors|=1u<<(3+q);
    const char *operation="pack",*current="";int32_t current_slot=-1;
    dw4_igb g={0};if(dw4_igb_open(&g,l->stage_file.data,l->stage_file.len,0) || dw4_igb_refs_open(&g))goto bad;
    for(size_t i=0;i<dw4_controllers_count(models);i++) {
        const dw4_stageobject *info;int32_t slot;
        const dw4_modelctrl *model=dw4_controllers_model(models,i,&info,&slot);
        const char *name=dw4_stageobject_name(info);current=name;current_slot=slot;operation="consumer binding";
        if(!slot && !strcmp(name,"i_fadewn01"))l->native_fade=model;
        const char *kind=dw4_stageobject_kind_string(info);
        if(((!strncmp(name,"n_",2) && kind && !strcmp(kind,"KIND_OBJECT")) || (kind && !strcmp(kind,"KIND_ENEMY"))) &&
           dw4_controllers_collision(models,name,slot,scene_actor_collision,l))goto bad;   /* enemies walk and land on the stage collision */
        if(dw4_modelctrl_has_near_map(model) && dw4_controllers_nearest(models,name,slot,lobby_near_player,l))goto bad;
        if(add_world_instance(l,&g,objects,model,info,slot,&operation))goto bad;
    }
    /* Decode every owned skeletal motion before publishing the destination;
     * unsupported assets must fail while the source session still exists. */
    for(unsigned i=0;i<l->nmesh;i++)if(l->mesh[i].instance && l->mesh[i].skinned) {
        const struct world_instance *instance=l->instances+l->mesh[i].instance-1;
        current=instance->name;operation="skeletal motion preflight";
        size_t count=dw4_modelctrl_motion_count(instance->model);if(!count)goto bad;
        for(size_t k=0;k<count;k++)if(!instance_motion(l,l->mesh+i,dw4_modelctrl_motion_name(instance->model,k)))goto bad;
    }
    current="";operation="screen fade/buffers";
    if(!l->native_fade)goto bad;
    l->capacity=0;size_t casters=0;
    for(unsigned i=0;i<l->nmesh;i++) {
        if(l->mesh[i].nt>(UINT32_MAX-l->capacity)/15)goto bad;
        l->capacity+=15*l->mesh[i].nt;
        if(l->mesh[i].actor || l->mesh[i].casts_shadow)casters+=l->mesh[i].nt;
    }
    dw4_layer_draw *draw=calloc((size_t)l->capacity*2,sizeof *draw),*shadow=calloc(casters?casters:1,sizeof *shadow);
    l->instance_nodes=malloc((size_t)l->scene.nnode*sizeof *l->instance_nodes);
    if(!draw || !shadow || !l->instance_nodes){free(draw);free(shadow);goto bad;}
    free(l->draw);l->draw=draw;free(l->casters);l->casters=shadow;
    /* The stage's default beCameraCtrlInfo owns box data. A first-visit demo
     * may override it in original first.lua; return visits keep this default. */
    dw4_script_value camera[]={{DW4_SCRIPT_STRING,0,"CAMERA",6},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},
        {DW4_SCRIPT_STRING,0,"SETBOXCAMERA",12}},result;
    if(dw4_lobby_camera_service(l,"sd",camera,4,&result,l->script_error,sizeof l->script_error))goto bad;
    dw4_igb_close(&g);return 0;
bad:dw4_igb_close(&g);if(!l->script_error[0])snprintf(l->script_error,sizeof l->script_error,"destination instance %.48s[%d]: %.80s failed",current,current_slot,operation);return -1;
}
static dw4_actoranim *instance_motion(dw4_lobby *l,struct lobby_mesh *mesh,const char *name)
{
    if(!name)return NULL;
    for(struct instance_motion *m=mesh->motions;m;m=m->next)if(!strcmp(m->name,name))return m->animation;
    dw4_actoranim *animation=dw4_actoranim_open_motion_database(l->stage_file.data,l->stage_file.len,&l->scene,mesh->node,name,l->instances[mesh->instance-1].database,l->script_error,sizeof l->script_error);
    if(!animation)return NULL;
    struct instance_motion *m=calloc(1,sizeof *m);char *copy=malloc(strlen(name)+1);
    if(!m || !copy){free(m);free(copy);dw4_actoranim_close(animation);return NULL;}
    strcpy(copy,name);*m=(struct instance_motion){copy,animation,mesh->motions};mesh->motions=m;return animation;
}
/* The scripted first Terminal (dw4_lobby_native_models) draws only the three arrival actors; every other generated NPC (the Call Keeper,
 * the other elves, Agumon) is added here as a world instance, drawn by the same instance branch as the hub's dynamic world. */
int dw4_lobby_native_npcs(dw4_lobby *l,dw4_controllers *models,const dw4_stageobjects *objects)
{
    if(!l || !models || !objects || !l->native_models || l->dynamic_world || l->ninstance)return -1;
    const char *operation="pack";dw4_igb g={0};
    if(dw4_igb_open(&g,l->stage_file.data,l->stage_file.len,0) || dw4_igb_refs_open(&g))return -1;
    for(size_t i=0;i<dw4_controllers_count(models);i++){
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *model=dw4_controllers_model(models,i,&info,&slot);
        const char *name=dw4_stageobject_name(info);
        if(strncmp(name,"n_",2))continue;
        int legacy=(slot==0 && !strcmp(name,"n_digilfm")) || (slot==2 && !strcmp(name,"n_digilff")) || (slot==3 && !strcmp(name,"n_digilff"));
        /* The hub's dynamic world (dw4_lobby_native_scene) gives every NEAR-map model the player as its AI target; without it the
         * Terminal's NPCs (the arrival elves included) never run their authored near/far behaviour (SQ_SILENT/SQ_WAIT by distance). */
        operation="NEAR target";   /* the arrival actors (legacy) are drawn by dw4_lobby_native_models, not as world instances */
        if((dw4_modelctrl_has_near_map(model) && dw4_controllers_nearest(models,name,slot,lobby_near_player,l)) ||
           (!legacy && add_world_instance(l,&g,objects,model,info,slot,&operation))){
            if(!l->script_error[0])snprintf(l->script_error,sizeof l->script_error,"NPC instance %.48s[%d]: %.60s failed",name,slot,operation);
            dw4_igb_close(&g);return -1;
        }
    }
    dw4_igb_close(&g);
    for(unsigned i=0;i<l->nmesh;i++)if(l->mesh[i].instance && l->mesh[i].skinned){
        const struct world_instance *instance=l->instances+l->mesh[i].instance-1;
        size_t count=dw4_modelctrl_motion_count(instance->model);if(!count)return -1;
        for(size_t k=0;k<count;k++)if(!instance_motion(l,l->mesh+i,dw4_modelctrl_motion_name(instance->model,k)))return -1;
    }
    l->capacity=0;size_t casters=0;
    for(unsigned i=0;i<l->nmesh;i++){
        if(l->mesh[i].nt>(UINT32_MAX-l->capacity)/15)return -1;
        l->capacity+=15*l->mesh[i].nt;
        if(l->mesh[i].actor || l->mesh[i].casts_shadow)casters+=l->mesh[i].nt;
    }
    dw4_layer_draw *draw=calloc((size_t)l->capacity*2,sizeof *draw),*shadow=calloc(casters?casters:1,sizeof *shadow);
    dw4_scene_node *nodes=malloc((size_t)l->scene.nnode*sizeof *nodes);
    if(!draw || !shadow || !nodes){free(draw);free(shadow);free(nodes);return -1;}
    free(l->draw);l->draw=draw;free(l->casters);l->casters=shadow;free(l->instance_nodes);l->instance_nodes=nodes;
    return 0;
}
/* A player slot's PLAYER/MODELCTRL receiver (`user` is the slot): the service acts on that slot's controller while it runs. */
static int player_receiver(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    struct lobby_player *P=user;dw4_lobby *l=P->lobby;struct lobby_player *saved=l->p;l->p=P;
    int rc=dw4_lobby_player_service(l,method,a,n,r,error,cap);
    if(l->native_sd){
        int active=dw4_modelctrl_active(P->player_controller);
        dw4_scriptservices_active(l->native_sd,P->player_token,active);
        dw4_scriptservices_active(l->native_sd,P->player_model_token,active);
    }
    l->p=saved;
    return rc;
}
/* Publish every joined slot's model as a PLAYER and MODELCTRL receiver at its slot number (slot 0 under `name`, the others under their own model). */
int dw4_lobby_publish_player(dw4_lobby *l,dw4_scriptservices *sd,uint64_t scope,const char *name)
{
    if(!l || !l->native_models || l->native_sd || !sd || !name)return -1;
    for(unsigned q=0;q<4;q++) {
        struct lobby_player *P=l->pl+q;
        if(!P->joined)continue;
        const char *model=q?lobby_models[P->species]:name;
        if(dw4_controllers_bind_model(l->native_models,model,(int32_t)q,P->player_controller)){
            snprintf(l->script_error,sizeof l->script_error,"cannot bind player model services: %.80s slot %u",model,q);goto bad;
        }
        l->native_sd=sd;
        P->player_token=dw4_scriptservices_register(sd,scope,"PLAYER",model,(int32_t)q,0,player_receiver,P);
        P->player_model_token=dw4_scriptservices_register(sd,scope,"MODELCTRL",model,(int32_t)q,0,player_receiver,P);
        if(!P->player_token || !P->player_model_token)goto bad;
    }
    return 0;
bad:
    for(unsigned q=0;q<4;q++) {
        struct lobby_player *P=l->pl+q;
        if(!P->joined)continue;
        dw4_scriptservices_unregister(sd,P->player_token);dw4_scriptservices_unregister(sd,P->player_model_token);
        dw4_modelctrl_dependencies_bind(P->player_controller,NULL);P->player_token=P->player_model_token=0;
    }
    l->native_sd=NULL;return -1;
}
int dw4_lobby_player_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_lobby *l=user;
    if(!l || !l->p->player_controller)return -1;
    /* SQ_ENTR selects TRNSS1, whose beActionStarterInfo x_100trnsin01 rows start the rings at run frames 0/6/12. */
    if(!strcmp(method,"sd") && n>=4 && script_equal(a[3],"SQ_ENTR") && l->native_models && l->entry_tick==UINT_MAX) {
        l->entry_tick=l->age;
        printf("  lobby: PLAYER SQ_ENTR at lobby tick %u; TRNSS1 entry rings/stars start\n",l->age);
    }
    if(!strcmp(method,"sd") && n==4 && script_equal(a[3],"GENERATE")) {
        if(player_labels(l))return -1;
        int rc=dw4_modelctrl_service(l->p->player_controller,method,a,n,r,error,cap);if(rc)return rc;
        float yaw=atan2f(l->p->player_world[8],l->p->player_world[0])*57.295779513f;
        char pos[160];snprintf(pos,sizeof pos,"V<%.9g,%.9g,%.9g>/V<0,%.9g,0>",l->p->player_world[12],l->p->player_world[13],l->p->player_world[14],yaw);
        dw4_script_value args[5];memcpy(args,a,4*sizeof *a);
        args[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"MOVETRANS",9};args[4]=(dw4_script_value){DW4_SCRIPT_STRING,0,pos,strlen(pos)};
        if(dw4_modelctrl_service(l->p->player_controller,"sd",args,5,r,error,cap))return -1;
        args[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"ONCTRL",6};
        return dw4_modelctrl_service(l->p->player_controller,"sd",args,4,r,error,cap);
    }
    return dw4_modelctrl_service(l->p->player_controller,method,a,n,r,error,cap);
}
int dw4_lobby_material_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_lobby *l=user;*r=(dw4_script_value){0};
    if(!l || strcmp(method,"sd") || n!=4)goto bad;
    if(script_equal(a[3],"PAUSE")){l->control.material_updates=0;return 0;}
    if(script_equal(a[3],"RESTART")) {
        l->control.material_updates=1;
        if(!l->finished){
            l->control.hud=l->control.player_control=l->control.model_control=1;
            l->control.handoff_tick=l->age;l->finished=1;
            dw4_lobbyui_restore_hud(l->ui,l->species);
            puts("  lobby: original first.lua restored HUD, camera, player/model control and materials");
        }
        return 0;
    }
bad:snprintf(error,cap,"unsupported lobby MATCTRL %s",method);return -1;
}
int dw4_lobby_light_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_lobby *l=user;*r=(dw4_script_value){0};
    if(!l || strcmp(method,"sd") || n!=5 || !script_equal(a[3],"SETCOLOR") || a[4].type!=DW4_SCRIPT_STRING ||
       !a[4].string || a[4].length>=256 || memchr(a[4].string,0,a[4].length))goto bad;
    char text[256],name[64];float ambient[3],diffuse[3],specular[3];int used=0;
    memcpy(text,a[4].string,a[4].length);text[a[4].length]=0;
    if(sscanf(text,"%63[^/]/V<%f,%f,%f>/V<%f,%f,%f>/V<%f,%f,%f>%n",name,
       ambient,ambient+1,ambient+2,diffuse,diffuse+1,diffuse+2,specular,specular+1,specular+2,&used)!=10 ||
       (size_t)used!=a[4].length)goto bad;
    for(unsigned i=0;i<3;i++)if(!isfinite(ambient[i]) || !isfinite(diffuse[i]) || !isfinite(specular[i]))goto bad;
    /* Main Lobby's two named rig owners; other lights remain unsupported. */
    if(strcmp(name,"Z0101Light0Shape1") && strcmp(name,"Z0101Light0Shape2"))goto bad;
    if(!strcmp(name,"Z0101Light0Shape1"))memcpy(l->hard_diffuse,diffuse,sizeof diffuse);
    else memcpy(l->hard_ambient,ambient,sizeof ambient);
    dw4_lobby_set_light(l,1);return 0;
bad:snprintf(error,cap,"unsupported lobby LIGHTCTRL %s",method);return -1;
}
int dw4_lobby_camera_service(void *user,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_lobby *l=user;*r=(dw4_script_value){0};
    if(!l || !l->camera_time.loaded || n<4 || n>5)goto unsupported;
    if(!strcmp(method,"querySD") && n==4 && script_equal(a[3],"ISDEMOCAMERA")) {
        int running=l->camera_scripted?l->camera_demo && !l->camera_time.finished:
            !l->control.box_camera && l->age<=240;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,running,NULL,0};return 0;
    }
    if(!strcmp(method,"sd")) {
        if(n==5 && script_equal(a[3],"SETDEMOCAMERA") && script_equal(a[4],"camsp0101")) {
            uint64_t end=l->camera_time.end;
            l->camera_time=(dw4_camera_time){.end=end,.loaded=1};
            l->camera_scripted=l->camera_demo=1;l->control.box_camera=0;return 0;
        }
        for(unsigned k=0;n==5 && !l->terminal && script_equal(a[3],"SETDEMOCAMERA") && k<l->ndemo;k++)if(script_equal(a[4],l->demo[k].name)) {
            /* A named hub demo camera restarts from time zero, as camsp0101 does. */
            l->camera=l->demo[k].node;l->camera_time=(dw4_camera_time){.end=l->demo[k].end,.loaded=1};
            l->camera_scripted=l->camera_demo=1;l->control.box_camera=0;return 0;
        }
        if(n==4 && script_equal(a[3],"SETBOXCAMERA")) {
            l->camera_scripted=1;l->camera_demo=0;l->control.box_camera=1;
            memset(&l->box_camera,0,sizeof l->box_camera);
            l->control.camera_region=0;box_camera_tick(l,0);return 0;
        }
        if(n==5 && script_equal(a[3],"SHAKE") && a[4].type==DW4_SCRIPT_STRING && a[4].string) {
            /* "37/F<0.3>/F<3.0>/F<60.0>": the digits are direction indexes (each a (dx,dy) pair of the 0x4c8820 / 0x4c8850 tables). */
            char code[24];float value,one_time,end;const char *t=a[4].string;size_t len=strcspn(t,"/");
            if(len && len<sizeof code && sscanf(t+len,"/F<%f>/F<%f>/F<%f>",&value,&one_time,&end)==3 && strspn(t,"0123456789")==len) {
                memcpy(code,t,len);code[len]=0;
                l->shake.active=1;memcpy(l->shake.code,code,len+1);l->shake.value=value;l->shake.one_time=one_time;l->shake.end=end;l->shake.start=l->age;
                return 0;
            }
        }
        if(n==4 && (script_equal(a[3],"ONFREEZE") || script_equal(a[3],"OFFREEZE"))) {
            l->camera_time.frozen=script_equal(a[3],"ONFREEZE");return 0;
        }
    }
unsupported:
    snprintf(error,cap,"unsupported lobby CAMERA %s (camsp0101/box only)",method);return -1;
}

void dw4_lobby_tick(dw4_lobby *l, int advance_pressed)
{
    unsigned t;
    if (!l) return;
    if(!l->terminal && !l->native_models) {
        snprintf(l->script_error,sizeof l->script_error,"hub gameplay requires the destination native startup owner");return;
    }
    if(l->status_hold)return;
    t = l->age++;
    int64_t now=(int64_t)t*1000000000LL/60;
    float delta=t ? (float)(now/100*100-((int64_t)(t-1)*1000000000LL/60)/100*100)/16666667.0f : 1;
    float camera_delta=t ? npc_float(ee_f32_div(ee_f32_from_s32((int32_t)
        (now/100*100-((int64_t)(t-1)*1000000000LL/60)/100*100)),npc_bits(16666667.0f))) : 0;
    if(t==l->entry_tick) lobby_fade_start(&l->p->player_alpha,1,npc_bits(l->p->player_fade),now);
    if(t>=l->entry_tick) lobby_fade_tick(&l->p->player_alpha,now);
    if(t==LOBBY_FADE_DELAY) lobby_fade_start(&l->screen_alpha,1,npc_bits(l->arrival_fade.fade_frames),now);
    if(t>=LOBBY_FADE_DELAY) lobby_fade_tick(&l->screen_alpha,now);
    if(l->dynamic_world) {
        int slot0_control=l->control.player_control;   /* l->control.player_control stays slot 0's (the HUD and scripts read it) */
        for(unsigned q=0;q<4;q++) {   /* every joined player walks under its own pad, model state and collision */
            struct lobby_player *P=l->pl+q;if(!P->joined)continue;
            l->p=P;
            dw4_modelctrl_actor player={0};dw4_modelctrl_actor_state(P->player_controller,&player);
            const unsigned hide=q?1u<<(3+q):2u;   /* slot 0 keeps its original actor bit; slots 1-3 use bits 4-6 */
            l->control.player_control=player.enabled;   /* the walk update reads the slot's own control state */
            if(dw4_modelctrl_drawable(P->player_controller))l->hidden_actors&=~hide;else l->hidden_actors|=hide;
            int fail=dw4_modelctrl_active(P->player_controller) && player_walk_tick(l,(int64_t)l->native_now);
            if(q)l->control.player_control=slot0_control;else slot0_control=player.enabled;
            if(fail) {
                snprintf(l->script_error,sizeof l->script_error,"player %u: %s",q,dw4_modelctrl_error(P->player_controller));l->p=l->pl;return;
            }
        }
        l->p=l->pl;l->control.player_control=slot0_control;
        if(l->control.box_camera)box_camera_tick(l,camera_delta);
        if(l->control.material_updates)control_tick(l);
        return;
    }
    /* beModelCtrlSubComBase update (399d90) adds the engine's frame delta
     * before testing runFrame >= startFrame. It is not a rounded tick count. */
    if(t>=l->entry_tick) l->rings.run_frame=ee_f32_add(l->rings.run_frame,npc_bits(delta));
    for(unsigned k=0;k<3;k++) {
        dw4_action2_host *h=&l->rings.clock[k];
        if(t>=l->entry_tick && !dw4_action2_host_started(h) && ee_f32_cmp(l->rings.run_frame,l->rings.delay[k])>=0) {
            dw4_action2_host_start_program(h,l->rings.program.component,l->rings.program.count,now);
            l->rings.active[k]=1;
        }
        if(l->rings.active[k]) {
            int done=dw4_action2_host_tick(h,now);
            if(h->fade_serial!=l->rings.serial[k]) {
                l->rings.serial[k]=h->fade_serial;
                lobby_fade_start(&l->rings.fade[k],h->fade_direction==1,
                                  npc_bits((float)h->fade_frames),now);
            }
            lobby_fade_tick(&l->rings.fade[k],now);
            if(done) l->rings.active[k]=0;
        }
        if(dw4_action2_host_started(h) && !(l->stars.started & (1u<<k))) {
            l->stars.run[k]=ee_f32_add(l->stars.run[k],npc_bits(delta));
            if(ee_f32_cmp(l->stars.run[k],l->stars.delay)>=0) {
                /* The generated ParticleTimer obtains its bias on the next
                 * traversal (retained arrival-clock checkpoints). */
                l->stars.started|=1u<<k;l->stars.start[k]=(int64_t)(t+1)*1000000000LL/60;
            }
        }
    }
    int64_t player_clock=(now>>18)<<18;
    if(!l->p->player_loop && player_clock-l->p->player_previous_start>=dw4_actoranim_duration_ns(l->p->player_idle)) {
        l->p->player_loop=1;l->p->player_idle_start=player_clock;
    }
    for(unsigned k=0;k<4;k++) {
        struct lobby_portal *p=&l->effect[k];
        int done=dw4_action2_host_tick(&p->clock,now);
        lobby_fade_tick(&p->fade,now);
        if(done && (p->action==PORTAL_RISE || p->action==PORTAL_FALL))
            portal_start(p,p->active?PORTAL_ON:PORTAL_OFF,t);
    }
    if(!l->native_models)dw4_frontaudio_set_clock(l->audio, (uint64_t)now);
    if(l->native_models) {
        static const char *motions[]={"walk01","wait01","talk01"};
        for(unsigned k=0;k<3;k++) {
            const dw4_modelctrl *model=l->native_actor[k];
            unsigned bit=k?1u<<(k+1):1;
            if(dw4_modelctrl_drawable(model))l->hidden_actors&=~bit;else l->hidden_actors|=bit;
            if(!dw4_modelctrl_active(model))continue;
            dw4_modelctrl_actor actor={0};dw4_modelctrl_actor_state(model,&actor);
            memcpy(k?l->female_pos[k-1]:l->npc_pos,actor.position,sizeof actor.position);
            if(k)l->female_yaw[k-1]=actor.rotation[1];else l->npc_yaw=actor.rotation[1];
            l->walk[k]=actor.channel[2];l->turn[k]=actor.channel[3];l->native_motion_ns[k]=actor.motion_ns;
            int motion=-1;for(unsigned m=0;actor.motion && m<3;m++)if(!strcmp(actor.motion,motions[m]))motion=(int)m;
            if(motion<0){snprintf(l->script_error,sizeof l->script_error,"actor %u motion is not prepared: %s",k,actor.motion?actor.motion:"none");return;}
            if(k==0)l->npc_motion_index=motion;else if(k==1)l->female_index=motion;else l->second_index=motion;
        }
        dw4_modelctrl_actor player={0};dw4_modelctrl_actor_state(l->p->player_controller,&player);
        l->control.player_control=player.enabled;
        if(dw4_modelctrl_drawable(l->p->player_controller))l->hidden_actors&=~2u;else l->hidden_actors|=2;
        if(player_walk_tick(l,(int64_t)l->native_now)){
            snprintf(l->script_error,sizeof l->script_error,"player: %s",dw4_modelctrl_error(l->p->player_controller));return;
        }
        for(unsigned k=0;k<4;k++) {
            dw4_modelctrl_actor portal={0};dw4_modelctrl_actor_state(l->native_portal[k],&portal);
            memcpy(l->effect[k].pos,portal.position,sizeof portal.position);
            l->effect[k].visible=dw4_modelctrl_drawable(l->native_portal[k]);
        }
        if(l->control.box_camera)box_camera_tick(l,camera_delta);
        if(l->control.material_updates)control_tick(l);
        int message=dw4_lobbyui_message(l->ui);
        if(message>=39 && message<=53 && message!=l->message){
            l->message=message;
            printf("  lobby: original greeting TALKFONT%02d I<%d>\n",message==49 || message==50?1:2,message);
        }
        return;
    }
    /* Sample the same absolute clock for all channels and Action2 timers. */
    if(t==240) {turn_start(l,1);l->phase[1]=1;l->action_start[1]=now;}
    if(t==240+LOBBY_MALE_WALK_DELAY) {turn_start(l,0);l->phase[0]=1;l->action_start[0]=now;}
    int greeting=0;
    if(l->relocation && --l->relocation==0) {
        static const float male[3]={258.187f,40,174},female[3]={240,40,-150};
        memcpy(l->npc_pos,male,sizeof male);l->npc_yaw=180;
        memcpy(l->female_pos[1],female,sizeof female);l->female_yaw[1]=0;
        memset(&l->walk[0],0,sizeof l->walk[0]);memset(&l->walk[2],0,sizeof l->walk[2]);
        memset(&l->turn[0],0,sizeof l->turn[0]);memset(&l->turn[2],0,sizeof l->turn[2]);
        l->phase[0]=l->phase[2]=4;
    }
    guide_departure_tick(l,delta,now);
    for(unsigned i=0;i<3;i++) {
        float *pos=i?l->female_pos[i-1]:l->npc_pos;
        float *yaw=i?&l->female_yaw[i-1]:&l->npc_yaw;
        float old[3];memcpy(old,pos,sizeof old);
        *yaw+=npc_float(dw4_npc_motion_tick(&l->turn[i],npc_bits(delta)));
        float step=npc_float(dw4_npc_motion_tick(&l->walk[i],npc_bits(delta)));
        if(step!=0) {
            float angle=*yaw*0.017453292519943295f;
            pos[0]+=sinf(angle)*step;pos[2]+=cosf(angle)*step;
            /* beHitLandDelivInfoRam_InitFields (0x0035e860): 3 / 4 / 4. */
            l->contacts[i]|=dw4_lobby_collision_move_for(&l->collision,DW4_ACTOR_CHECK_FLAG,old,pos,3,4,4);
        }
    }
    for(unsigned i=0;i<2;i++) if(l->phase[i]==1 &&
        now-l->action_start[i]>(i?l->guide_turn_wait:l->male_turn_wait)) {
        walk_start(l,i,0);l->phase[i]=2;l->action_start[i]=now;
    }
    if(l->phase[1]==2 && now-l->action_start[1]>l->guide_walk_wait) {
        walk_start(l,1,1);l->phase[1]=3;greeting=1;
    }
    if (greeting) {
        dw4_lobbyui_start(l->ui);
        l->message = 0;
        puts("  lobby: guide action complete; Terminal Area greeting group 1, TALKFONT02 I<39>");
    } else if (l->restore) {
        if (--l->restore == 0) {
            l->control.hud = l->control.box_camera = 1;
            l->control.player_control = l->control.model_control = l->control.material_updates = 1;
            l->control.handoff_tick = t;
            l->p->player_start = t; /* PLAYER SQ_WAIT restarts the equipped idle. */
            l->p->player_previous_start=l->p->player_idle_start;
            l->p->player_idle_start=player_clock;
            dw4_lobbyui_restore_hud(l->ui, l->species);
            l->finished = 1;
            puts("  lobby: introduction complete; HUD, box camera, player/model control and materials restored");
        }
    } else if (l->phase[1]==3 && !l->finished) {
        int old = l->message, visible = dw4_lobbyui_message(l->ui);
        dw4_lobbyui_tick(l->ui, advance_pressed);
        l->message = dw4_lobbyui_page(l->ui);
        if (visible != 49 && dw4_lobbyui_message(l->ui) == 49)
            puts("  lobby: terminal message, TALKFONT01 I<49>");
        if (l->message != old) {
            if (l->message == 3 || l->message == 8 || l->message == 12)
                printf("  lobby: Terminal Area greeting group, TALKFONT02 I<%d>\n",39+l->message);
            else if (l->message == 10) {
                dw4_frontaudio_cue(l->audio, lobby_terminal_cue);
                puts("  lobby: terminal beep delay 90");
            }
            else if (l->message == 15) {
                l->restore = LOBBY_RESTORE_DELAY;l->relocation=LOBBY_RELOCATE_DELAY;
                walk_start(l,0,1);walk_start(l,2,1);
                /* ONCTRL/SQ_WALKON is immediate and independent of both
                 * delayed relocations and the global control handoff. */
                memset(&l->turn[1],0,sizeof l->turn[1]);
                walk_start(l,1,0);l->phase[1]=5;
                if(l->scripts) {
                    if(guide_wpos(l))return;
                    l->guide_ai_started=1;l->guide_ai_deadline=now;
                }
                puts("  lobby: greeting closed; guide WALKON, relocation 10, restore delay 120");
            }
        }
    }
    if (l->finished) {
        if(player_walk_tick(l,now)){snprintf(l->script_error,sizeof l->script_error,"player movement: %s",dw4_modelctrl_error(l->p->player_controller));return;}
        box_camera_tick(l,camera_delta);
        control_tick(l);
    }
    {
        int male = l->phase[0]==2 && l->message < 15 ? 0 : 1;
        int female = l->phase[1]==1 ? 1 : l->phase[1]==2 || l->phase[1]==5 ? 0 :
                     dw4_lobbyui_delay(l->ui) || l->message >= 15 ? 1 : 2;
        if(t<240) {
            unsigned last[2]={0,0};int motion[2]={1,1};
            for(unsigned i=0;i<sizeof lobby_opening/sizeof lobby_opening[0];i++) {
                unsigned actor=lobby_opening[i].actor, tick=lobby_opening[i].tick;
                if(t>=tick && tick>=last[actor]) {last[actor]=tick;motion[actor]=lobby_opening[i].motion;}
            }
            male=motion[0];female=motion[1];
        }
        int second=l->message>=15?1:0;
        if(second!=l->second_index) {l->second_index=second;l->second_start=t;}
        if (male != l->npc_motion_index) { l->npc_motion_index = male; l->motion_start = t; }
        if (female != l->female_index) { l->female_index = female; l->female_start = t; }
    }
}

void dw4_lobby_set_light(dw4_lobby *l, int hard)
{
    if (!l || l->light_hard == (hard != 0)) return;
    l->light_hard = hard != 0;
    for (unsigned i = 0; i < l->ntexture; i++) if (l->texture[i].name) {
        l->texture[i].tex.rgba = l->texture[i].mode_rgba[l->light_hard];
        dw4_gl_layer_texture_changed(l->gpu,&l->texture[i].tex);
    }
}

/* Retail's VU1 program CALC_INFINITE_4 rotates the packed light block in place (l <- M3x3 l) on every draw that follows a hardware matrix
 * upload, and the EE re-sends the eye-space block only after a model-view upload; the draw that sees the block rotated k extra times
 * lights with n_eff = n_world . (V3 . R)^k (stag0001's additive floor-grid overlays: k = 1, 2, 3, 3 -> colours (96,87,109), (37,30,50),
 * (40,33,53) against 127 without it).  k comes from the scene walk (dw4_scene_node_light_rot).  Safe scope, binding until a retail dump
 * with k > 0 confirms more: static meshes of the scene's own BG02 root in a field stage (never a Main Lobby hub: its k > 0 meshes are
 * unconfirmed); actors, instances, skinned meshes, shadows, effects and arrival objects set the model-view per draw and stay k = 0; and
 * only where the node's world rotation is the identity with unit scale (a translation is fine), otherwise k = 0.  The rotation is
 * derived per draw: the light itself (l->light_direction) is never changed. */
static unsigned lobby_light_rotations(const dw4_lobby *l, const struct lobby_mesh *item, const float world[16])
{
    static const float identity[9] = {1,0,0, 0,1,0, 0,0,1};
    if (!l->field || !strncasecmp(l->stage, "stagml", 6)) return 0;
    if (item->source != &l->scene || item->actor || item->instance || item->effect || item->arrival || item->skinned || item->shadow) return 0;
    unsigned k = dw4_scene_node_light_rot(item->source, item->node);
    if (!k) return 0;
    for (unsigned i = 0; i < 9; i++) if (fabsf(world[4*(i/3)+i%3]-identity[i]) > 1e-4f) return 0;
    return k;
}

/* Soft retains authored igLightAttr colors; Hard uses chunk 009's override.
 * Direction is igLightAttr at pack 820 +0x491cc. VU1 clamps before GS MODULATE;
 * 127 is unity RGB, alpha uses 128. Normals use inverse-transpose world space. */
static void lobby_vertex_color(const dw4_lobby *l, const float *normal, const float world[16], int lit,
                               const float color[4], const dw4_scene_node *material, const float view[16], unsigned light_k,
                               uint8_t out[4])
{
    float ndl = 0;
    const float *ambient = l->light_hard ? l->hard_ambient : l->soft_ambient;
    if (lit && normal) {
        float a[3] = {world[0],world[1],world[2]};
        float b[3] = {world[4],world[5],world[6]};
        float c[3] = {world[8],world[9],world[10]};
        float cof[3][3] = {
            {b[1]*c[2]-b[2]*c[1], b[2]*c[0]-b[0]*c[2], b[0]*c[1]-b[1]*c[0]},
            {c[1]*a[2]-c[2]*a[1], c[2]*a[0]-c[0]*a[2], c[0]*a[1]-c[1]*a[0]},
            {a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]}};
        float n[3], len, det = a[0]*cof[0][0]+a[1]*cof[0][1]+a[2]*cof[0][2];
        for (int k = 0; k < 3; k++)
            n[k] = (normal[0]*cof[0][k]+normal[1]*cof[1][k]+normal[2]*cof[2][k])*(det < 0 ? -1 : 1);
        /* VU1 in-place light rotation (see lobby_light_rotations): the light is l_k = -L (V^T)^k, i.e. the normal is turned by V k times. */
        for (unsigned r = 0; r < light_k; r++) {
            float t[3];
            for (int k = 0; k < 3; k++) t[k] = n[0]*view[k]+n[1]*view[4+k]+n[2]*view[8+k];
            memcpy(n, t, sizeof n);
        }
        len = sqrtf(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
        if (len > 1e-8f) ndl = fmaxf(0, -(l->light_direction[0]*n[0]+l->light_direction[1]*n[1]+l->light_direction[2]*n[2])/len);
    }
    for (int k = 0; k < 3; k++) {
        float ma = material ? material->material_ambient[k] : 1;
        float md = material ? material->material_diffuse[k] : 1;
        float me = material ? material->material_emission[k] : 0;
        float diffuse = l->light_hard ? l->hard_diffuse[k] : l->soft_diffuse[k];
        float shade = lit && normal ? fminf(1, me+ma*ambient[k]+md*diffuse*ndl) : 1;
        out[k] = (uint8_t)floorf(127.5f*fminf(1, fmaxf(0, shade*color[k])));
    }
    out[3] = (uint8_t)floorf(128*fminf(1, fmaxf(0, color[3])));
}

const dw4_layer_draw *dw4_lobby_last_draws(const dw4_lobby *l, unsigned *count)
{
    if (count) *count = l ? l->ndraw : 0;
    return l ? l->draw : NULL;
}

int dw4_lobby_presentation(const dw4_lobby *l,dw4_lobby_presentation_state *out)
{
    if(!l || !out) return -1;
    unsigned tick=l->age?l->age-1:0;
    int64_t clock=(((int64_t)tick*1000000000LL/60)>>18)<<18;
    int64_t duration=dw4_actoranim_duration_ns(l->p->player_idle);
    *out=(dw4_lobby_presentation_state){.tick=tick,.player_alpha=lobby_fade_alpha(&l->p->player_alpha),
        .screen_alpha=lobby_fade_alpha(&l->screen_alpha),
        .player_motion_ns=l->p->player_loop?(clock-l->p->player_idle_start)%duration:(clock>l->p->player_previous_start?clock-l->p->player_previous_start:0),.player_loop=l->p->player_loop};
    if(l->native_models) {
        dw4_modelctrl_actor actor={0};dw4_modelctrl_actor_state(l->p->player_controller,&actor);
        duration=dw4_actoranim_duration_ns(player_animation(l,actor.motion,0));
        out->player_alpha=dw4_modelctrl_alpha(l->p->player_controller);
        out->screen_alpha=1-dw4_modelctrl_alpha(l->native_fade);
        out->player_loop=actor.motion_loop;
        out->player_motion_ns=actor.motion_loop && duration>0?actor.motion_ns%duration:actor.motion_ns;
    }
    for(unsigned k=0;k<3;k++) if(l->rings.active[k]) {
        out->arrival_mask|=1u<<k;out->arrival_alpha[k]=lobby_fade_alpha(&l->rings.fade[k]);
    }
    for(unsigned k=0;k<3;k++) if((l->stars.started & (1u<<k)) &&
        (int64_t)tick*1000000000LL/60>=l->stars.start[k] &&
        (int64_t)tick*1000000000LL/60-l->stars.start[k]<1000000000LL) out->particle_mask|=1u<<k;
    return 0;
}

static const char *mesh_layer(const struct lobby_mesh *mesh)
{
    static const char *names[]={"BG01","BG02","GM01","GM02","EM01","NP01","PC01","EF01","EF02","EF03","BG03","GM03","WN00","WN01","WN02","WN03","WN04","FONT","LOADING","NONE"};
    /* Runtime actor instances attach to their registered layer. In particular
     * weapon library graphs can have a GM01 prototype root but belong to PC01
     * after player attachment; the prototype name must not override that owner. */
    if(mesh->actor)return mesh->actor==2?"PC01":"NP01";
    const dw4_scene *s=mesh->source;
    for(uint32_t n=mesh->node;n<s->nnode;n=s->node[n].parent){
        if(!s->node[n].name)continue;
        for(unsigned i=0;i<sizeof names/sizeof *names;i++)if(!strcmp(s->node[n].name,names[i]))return names[i];
    }
    return "NONE";
}
static int draw_world(dw4_lobby *,dw4_fb *,unsigned,const dw4_fefont *,dw4_lobby_layer_visible,void *,int);
int dw4_lobby_draw_environment(dw4_lobby *l,dw4_fb *fb)
{return draw_world(l,fb,0,NULL,NULL,NULL,0);}
int dw4_lobby_draw_layers(dw4_lobby *l,dw4_fb *fb,unsigned frame,const dw4_fefont *font,dw4_lobby_layer_visible visible,void *user)
{return draw_world(l,fb,frame,font,visible,user,1);}
int dw4_lobby_draw(dw4_lobby *l,dw4_fb *fb,unsigned frame,const dw4_fefont *font)
{return dw4_lobby_draw_layers(l,fb,frame,font,NULL,NULL);}
static int lobby_gpu_failure(dw4_lobby *l,const char *operation)
{
    if(dw4_gpu_policy_required()){dw4_gpu_policy_fail(operation);return -1;}
    fprintf(stderr,"  lobby: %s failed; explicit reference run reverting to CPU\n",operation);
    dw4_gl_layer_close(l->gpu);l->gpu=NULL;
    dw4_gl_layer_close(l->shadow_gpu);l->shadow_gpu=NULL;
    return 0;
}
static void lobby_shadow_cpu(dw4_lobby *l,unsigned count)
{
    dw4_fb_clear(&l->shadow_fb,0,0,0);dw4_render_zbuf_clear(&l->shadow_fb);
    dw4_render_layer_draws(&l->shadow_fb,l->casters,(int)count,1);
    if(dw4_gpu_policy_cpu(DW4_CPU_COMPOSITE))return;
    for(unsigned p=0;p<256*256;p++){
        uint8_t *v=l->shadow_fb.rgba+4*p;
        unsigned alpha=(unsigned)floorf(v[0]*(128.0f/255)*(1-l->shadow_factor)+.5f);
        v[0]=v[1]=v[2]=0;v[3]=(uint8_t)alpha;
    }
}
/* DW4_FRAME_TRACE phase timers for draw_world (ms, summed since the last take): 0 CPU prep (poses, mesh
 * build), 1 shadow pass, 2 main world draw, 3 native UI, 4 dialogue, 5 everything after.  */
static double lobby_trace_ms[16];
static double lobby_trace_t;
static double lobby_trace_clock(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec*1e3+t.tv_nsec/1e6;}
#define LSUB(i,expr) ({double s_=lobby_trace_clock();__typeof__(expr) r_=(expr);lobby_trace_ms[i]+=lobby_trace_clock()-s_;r_;})
#define LTR(i) do{double n_=lobby_trace_clock();lobby_trace_ms[i]+=n_-lobby_trace_t;lobby_trace_t=n_;}while(0)
void dw4_lobby_trace_take(double out[16]){memcpy(out,lobby_trace_ms,sizeof lobby_trace_ms);memset(lobby_trace_ms,0,sizeof lobby_trace_ms);}
/* Whole-mesh frustum rejection for static geometry.  Every triangle of the mesh lies inside its object-space
 * bounding box, the box's eight corners are transformed exactly like a vertex, and the mesh is skipped only when
 * all eight lie beyond the same clip plane of lobby_clip_depth / lobby_clip_screen (near, far, or one screen side
 * by more than a pixel margin).  The clip stages are convex, so such a mesh would have emitted nothing anyway; a
 * mesh the test cannot decide is drawn normally.  Never used for actors, skinned instances or shadow casters. */
/* Returns a mask: 1 = every triangle is outside the view frustum (draw nothing), 2 = every point is outside the 256x256
 * shadow map (cast nothing).  `dynamic` meshes are posed each frame (actors, skinned instances), so their box is rebuilt
 * from the posed vertices; static meshes cache theirs.  Undecidable cases (non-finite vertices) return 0. */
static unsigned lobby_mesh_cull(const dw4_lobby *l,struct lobby_mesh *item,unsigned num_verts,const float *pos,
                                const float world[16],const float view[16],float fy,float aspect,int w,int h,int dynamic)
{
    const float near=l->near_plane,far=l->far_plane;
    if(dynamic || item->bounds==0) {
        int any=0;
        if(dynamic) {
            for(unsigned vi=0;vi<num_verts;vi++)
                for(int k=0;k<3;k++) {
                    float c=pos[3*vi+k];
                    if(!(c==c) || c>1e30f || c<-1e30f)return 0;
                    if(!any || c<item->bmin[k])item->bmin[k]=c;
                    if(!any || c>item->bmax[k])item->bmax[k]=c;
                    if(k==2)any=1;
                }
        } else for(unsigned t=0;t<3*item->nt;t++) {
            unsigned vi=item->tri[t];
            if(vi>=num_verts)continue;
            for(int k=0;k<3;k++) {
                float c=pos[3*vi+k];
                if(!any || c<item->bmin[k])item->bmin[k]=c;
                if(!any || c>item->bmax[k])item->bmax[k]=c;
            }
            any=1;
        }
        if(!dynamic)item->bounds=any?1:-1;
        else if(!any)return 0;
    }
    if(!dynamic && item->bounds<0)return 0;
    const float margin=8.0f,hw=w*.5f+margin,hh=h*.5f+margin,sm=8.0f;
    int near_out=1,far_out=1,left=1,right=1,top=1,bottom=1;
    int sx_lo=1,sx_hi=1,sy_lo=1,sy_hi=1;
    const float *sb=l->shadow_bounds,*pw=l->p->player_world;
    for(unsigned corner=0;corner<8;corner++) {
        float c[3]={corner&1?item->bmax[0]:item->bmin[0],corner&2?item->bmax[1]:item->bmin[1],corner&4?item->bmax[2]:item->bmin[2]};
        float p[3],v[3];
        for(int k=0;k<3;k++)p[k]=c[0]*world[k]+c[1]*world[4+k]+c[2]*world[8+k]+world[12+k];
        for(int k=0;k<3;k++)v[k]=p[0]*view[k]+p[1]*view[4+k]+p[2]*view[8+k]+view[12+k];
        float zd=-v[2],tol=1e-3f*(fabsf(zd)+1);
        if(!(zd<near-tol))near_out=0;
        if(!(zd>far+tol))far_out=0;
        if(!(v[0]*fy*aspect+hw*zd<-tol*hw))left=0;
        if(!(hw*zd-v[0]*fy*aspect<-tol*hw))right=0;
        if(!(hh*zd-v[1]*fy<-tol*hh))top=0;
        if(!(v[1]*fy+hh*zd<-tol*hh))bottom=0;
        /* the same mapping as the caster vertices: pixel = 9 + 238 * (su, sv) in the 256x256 shadow map */
        float su=(p[2]-pw[14]-sb[1])/(sb[0]-sb[1]),sv=(sb[2]-(p[0]-pw[12]))/(sb[2]-sb[3]);
        float sx=9+238*su,sy=9+238*sv;
        if(!(sx<-sm))sx_lo=0;
        if(!(sx>256+sm))sx_hi=0;
        if(!(sy<-sm))sy_lo=0;
        if(!(sy>256+sm))sy_hi=0;
    }
    unsigned mask=0;
    if(near_out|far_out|left|right|top|bottom)mask|=1;
    if(sx_lo|sx_hi|sy_lo|sy_hi)mask|=2;
    return mask;
}
/* Per-mesh vertex cache for draw_world: a vertex shared by several triangles is transformed, lit and fogged once per
 * mesh instead of once per corner.  `stamp` holds the generation that filled each slot, so nothing is cleared. */
/* Stage A (position): world point p, view-space x/y/depth and a frustum outcode.  Stage B (shading): uv, colour, fog and
 * the shadow-map coordinates, only for vertices a surviving triangle actually uses. */
struct lobby_vcache{float p[3],vp[3];uint8_t oc;float v[10];float su,sv;};
static __thread struct lobby_vcache *lobby_vc;
static __thread uint32_t *lobby_vc_stamp,*lobby_vc_stampa;
static __thread size_t lobby_vc_cap;
static __thread uint32_t lobby_vc_gen;
static int lobby_vc_reserve(size_t n)
{
    if(n<=lobby_vc_cap)return 0;
    struct lobby_vcache *c=realloc(lobby_vc,n*sizeof *c);
    if(!c)return -1;
    lobby_vc=c;
    uint32_t *st=realloc(lobby_vc_stamp,n*sizeof *st),*sa=realloc(lobby_vc_stampa,n*sizeof *sa);
    if(st)lobby_vc_stamp=st;
    if(sa)lobby_vc_stampa=sa;
    if(!st || !sa)return -1;
    memset(st+lobby_vc_cap,0,(n-lobby_vc_cap)*sizeof *st);   /* new slots belong to no generation */
    memset(sa+lobby_vc_cap,0,(n-lobby_vc_cap)*sizeof *sa);
    lobby_vc_cap=n;
    return 0;
}
struct lobby_vctx{const float *pos,*world,*view;float fy,aspect,hw,hh,near,far;const float *wpos;};
static void lobby_vc_position(struct lobby_vcache *cv,unsigned vi,const struct lobby_vctx *c)
{
    float *p=cv->p,*vx=cv->vp;
    if(c->wpos)memcpy(p,c->wpos+3*(size_t)vi,3*sizeof *p); /* world position cached for a mesh whose world matrix has not changed */
    else for(int k=0;k<3;k++)
        p[k]=c->pos[3*vi]*c->world[k]+c->pos[3*vi+1]*c->world[4+k]+c->pos[3*vi+2]*c->world[8+k]+c->world[12+k];
    for(int k=0;k<3;k++)
        vx[k]=p[0]*c->view[k]+p[1]*c->view[4+k]+p[2]*c->view[8+k]+c->view[12+k];
    vx[2]=-vx[2];
    /* Outcode against the planes lobby_clip_depth / lobby_clip_screen cut at (same margins as lobby_mesh_outside). */
    float zd=vx[2],tol=1e-3f*(fabsf(zd)+1);uint8_t oc=0;
    if(zd<c->near-tol)oc|=1;
    if(zd>c->far+tol)oc|=2;
    if(vx[0]*c->fy*c->aspect+c->hw*zd<-tol*c->hw)oc|=4;
    if(c->hw*zd-vx[0]*c->fy*c->aspect<-tol*c->hw)oc|=8;
    if(c->hh*zd-vx[1]*c->fy<-tol*c->hh)oc|=16;
    if(vx[1]*c->fy+c->hh*zd<-tol*c->hh)oc|=32;
    cv->oc=oc;
}
/* A field stage has no lobby UI: the hub's own TEXTCTL text (the drop name labels) is drawn from the shared dialogue when something claimed it. */
static int field_text(dw4_lobby *l,dw4_fb *fb)
{
    if(!l->native_dialogue || !dw4_dialogue_claimed(l->native_dialogue))return 0;
    const dw4_ui_draw *draw;size_t n;
    if(dw4_dialogue_draw(l->native_dialogue,fb->w,fb->h,&draw,&n))return -1;
    if(!n)return 0;
    int wrap=dw4_render_tex_wrap,linear=dw4_render_tex_linear,aref=dw4_render_aref;
    dw4_render_tex_wrap=1;dw4_render_tex_linear=1;dw4_render_aref=12;
    if(l->gpu){if(dw4_gl_layer_ui(l->gpu,fb,draw,(int)n)){dw4_render_tex_wrap=wrap;dw4_render_tex_linear=linear;dw4_render_aref=aref;return -1;}}
    else dw4_gl_layer_ui_or_cpu(&l->gpu,fb,draw,(int)n,8);
    dw4_render_tex_wrap=wrap;dw4_render_tex_linear=linear;dw4_render_aref=aref;
    return 0;
}
static int draw_world_frame(dw4_lobby *l,dw4_fb *fb,unsigned frame,const dw4_fefont *font,
    dw4_lobby_layer_visible visible,void *user,int apply_fade);
/* The GPU passes of one world frame (clear, geometry, native UI, lobby UI, dialogue) run with the frame resident on the
 * GPU and are read back once, instead of one full upload and readback per pass. */
static int draw_world(dw4_lobby *l,dw4_fb *fb,unsigned frame,const dw4_fefont *font,
    dw4_lobby_layer_visible visible,void *user,int apply_fade)
{
    dw4_gl_layer *gpu=l->gpu;
    if(gpu && dw4_gl_layer_defer(gpu,fb,1))gpu=NULL;
    int rc=draw_world_frame(l,fb,frame,font,visible,user,apply_fade);
    /* rc is the triangle count on success, negative on failure */
    if(rc>=0 && gpu && l->gpu==gpu && apply_fade && dw4_fps_overlay>0) {
        if(dw4_render_fps_gpu(gpu,fb,dw4_fps_overlay))rc=lobby_gpu_failure(l,"FPS overlay draw")?-1:rc;
        else dw4_fps_overlay_drawn=1;
    }
    /* A GPU failure that reverted to the CPU renderer closed the layer; the frame was redrawn on the CPU then. */
    if(gpu && l->gpu==gpu && dw4_gl_layer_defer(gpu,fb,0) && rc>=0)rc=lobby_gpu_failure(l,"lobby frame readback")?-1:rc;
    return rc;
}
static int draw_world_frame(dw4_lobby *l,dw4_fb *fb,unsigned frame,const dw4_fefont *font,
    dw4_lobby_layer_visible visible,void *user,int apply_fade)
{
    lobby_trace_t=lobby_trace_clock();
    if(dw4_gpu_policy_error()[0])return -1;
    float view[16], world[16];
    /* The simulation owns all clocks, including diagnostics that render twice
     * or intentionally skip a presentation frame. */
    frame=l->age?l->age-1:0;
    int64_t player_clock=(((int64_t)frame*1000000000LL/60)>>18)<<18;
    int64_t duration=dw4_actoranim_duration_ns(l->p->player_idle);
    int64_t local=l->p->player_loop?(player_clock-l->p->player_idle_start)%duration:(player_clock>l->p->player_previous_start?player_clock-l->p->player_previous_start:0);
    int64_t blend_ns=ee_f32_to_s64(ee_f32_div(ee_f32_mul(0x41000000,0x4e6e6b28),0x42700000));
    float blend=l->p->player_loop?fmaxf(0,1-(float)(player_clock-l->p->player_idle_start)/blend_ns):0;
    /* OS waits for one cycle; the outgoing source continues cycling during
     * WAITS1's eight-frame blend (confirmed at the retail boundary). */
    double previous=(player_clock>l->p->player_previous_start?(player_clock-l->p->player_previous_start)%duration:0)*1e-9;
    dw4_actoranim_blend(l->p->player_idle,previous,blend);
    dw4_actoranim_blend(l->p->player_shadow,previous,blend);
    unsigned i, count = 0, ncasters = 0;
    l->p->weapon_submitted_triangles=0;memset(l->p->weapon_submitted,0,sizeof l->p->weapon_submitted);
    int old_wrap = dw4_render_tex_wrap, old_linear = dw4_render_tex_linear;
    float fy = fb->h / (2.0f*tanf(DW4_SCENE_CAMERA_FOV*0.5f));
    const float aspect = dw4_scene_camera_aspect(fb->w, fb->h);
    /* beCameraDemoData 1800: camsp0101 runs for 4 seconds, then holds.
     * Drive only that graph; the environment has independent model clocks. */
    dw4_scene_set_time(&l->scene, 0);
    for (i = 0; i < l->scene.nnode; i++) {
        dw4_scene_node_drive(&l->scene, i, 0, 0);
        if(l->scene.node[i].scene==l->background_scene && l->scene.node[i].has_seq && l->scene.node[i].seq.duration_ns>0) {
            int64_t time=dw4_scene_node_loop_time(&l->scene,i,(int64_t)frame*1000000000LL/60);
            dw4_scene_node_drive(&l->scene,i,0,time);
        }
        if (!l->ext_camera && l->scene.node[i].scene == l->scene.node[l->camera].scene &&
            l->scene.node[i].has_seq)
            dw4_scene_node_drive(&l->scene, i, 0, l->camera_scripted?(long long)l->camera_time.time:(long long)(frame < 240 ? frame : 240)*1000000000LL/60);
    }
    if(l->ext_camera) {
        dw4_scene_set_time(&l->camera_pack, 0);
        for (i = 0; i < l->camera_pack.nnode; i++) {
            dw4_scene_node_drive(&l->camera_pack, i, 0, 0);
            if (l->camera_pack.node[i].scene == l->camera_pack.node[l->camera].scene && l->camera_pack.node[i].has_seq)
                dw4_scene_node_drive(&l->camera_pack, i, 0, l->camera_scripted?(long long)l->camera_time.time:(long long)(frame < 240 ? frame : 240)*1000000000LL/60);
        }
    }
    /* MATCTRL membership queries resume at handoff; portal model clocks are
     * independent throughout the arrival and keep their WAIT01/OFSW01 windows. */
    for (unsigned k = 0; k < 4; k++) {
        if(!l->terminal)continue;
        uint32_t root = l->effect[k].root;
        int64_t t = dw4_action2_host_node_time(&l->effect[k].clock,
                            (int64_t)(l->age?l->age-1:0)*1000000000LL/60);
        if(l->native_models)t=dw4_modelctrl_time(l->native_portal[k]);
        for (i = root+1; i < l->scene.nnode && l->scene.node[i].depth > l->scene.node[root].depth; i++)
            if (l->scene.node[i].has_seq)
                dw4_scene_node_drive(&l->scene, i, 0, t);
    }
    for(unsigned k=0;k<3;k++) if(l->rings.active[k]) {
        uint32_t root=l->rings.node[k];
        int64_t time=dw4_action2_host_node_time(&l->rings.clock[k],(int64_t)frame*1000000000LL/60);
        for(i=root+1;i<l->scene.nnode && l->scene.node[i].depth>l->scene.node[root].depth;i++)
            if(l->scene.node[i].has_seq) dw4_scene_node_drive(&l->scene,i,0,time);
    }
    dw4_scene_set_engine_time(&l->scene, 0);
    LTR(6);
    if (l->control.box_camera) {
        memcpy(world, l->control.camera_world, sizeof world);
        memset(view, 0, sizeof view); view[15] = 1;
        for (unsigned row = 0; row < 3; row++) for (unsigned col = 0; col < 3; col++)
            view[4*row+col] = world[4*col+row];
    } else if (dw4_scene_node_camera(camera_scene_of(l), l->camera, world, view)) return -1;
    /* Row-vector affine inverse: translation is -t * R^T, using columns
     * of the inverse. The older diagnostic camera helper uses rows here. */
    for (i = 0; i < 3; i++)
        view[12+i] = -(world[12]*view[i]+world[13]*view[4+i]+world[14]*view[8+i]);
    dw4_scene sample=l->scene;unsigned current_instance=0;
    if(l->dynamic_world || l->ninstance){memcpy(l->instance_nodes,l->scene.node,(size_t)l->scene.nnode*sizeof *l->instance_nodes);sample.node=l->instance_nodes;}
    unsigned tr_cat=9;double tr_prev=lobby_trace_clock();
    for (i = 0; i < l->nmesh; i++) {
        struct lobby_mesh *item = &l->mesh[i];
        l->p = &l->pl[item->actor==2 ? item->slot : 0];   /* a player's body, shadow and weapon meshes are posed from their own slot */
        {double tr_now=lobby_trace_clock();lobby_trace_ms[tr_cat]+=tr_now-tr_prev;tr_prev=tr_now;
         tr_cat=item->actor?10:(item->instance?11:((item->effect||item->arrival||item->shadow)?12:9));}
        const char *layer=item->instance?l->instances[item->instance-1].layer:mesh_layer(item);
        if(visible && !visible(user,layer))continue;
        const dw4_scene *source = item->source;
        if(item->instance) {
            struct world_instance *instance=l->instances+item->instance-1;
            if(!dw4_modelctrl_drawable(instance->model))continue;
            if(current_instance!=item->instance) {
                double tr_i0=lobby_trace_clock();
                memcpy(sample.node+instance->root,l->scene.node+instance->root,(instance->end-instance->root)*sizeof *sample.node);
                for(unsigned n=instance->root;n<instance->end;n++)if(sample.node[n].has_seq)
                    dw4_scene_node_drive(&sample,n,0,dw4_modelctrl_time(instance->model));
                dw4_modelctrl_matrix(instance->model,sample.node[instance->root].m);sample.node[instance->root].has_matrix=1;
                current_instance=item->instance;
                lobby_trace_ms[8]+=lobby_trace_clock()-tr_i0;
            }
            source=&sample;
        }
        if(item->effect && !l->effect[item->effect-1].visible) continue;
        if(item->arrival && !l->rings.active[item->arrival-1]) continue;
        if(item->actor && (l->hidden_actors & (item->actor==2 && item->slot ? 1u << (3+item->slot) : 1u << (item->actor-1)))) continue;
        if(item->actor==2 && !l->native_models && frame<LOBBY_PLAYER_ENTRY_DELAY) continue;
        if(!dw4_scene_node_visible(source,item->node,0)) continue;
        const dw4_scene_mesh *m = &source->mesh[dw4_scene_node_mesh(source, item->node)];
        const float *pos = dw4_scene_host(source, m->positions);
        const float *uv = dw4_scene_host(source, m->uvs);
        const float *norm = dw4_scene_host(source, m->normals);
        float color[4] = {1,1,1,1}, ref = 12.0f/128.0f, du = 0, dv = 0;
        int lit = norm != NULL, blend = 0, depth_write = 1;
        uint32_t ancestor;
        unsigned seen = 0;
        const dw4_scene_node *material = NULL;
        dw4_scene_node_alpha_ref(source, item->node, &ref);
        dw4_scene_node_uv_offset(source, item->node, &du, &dv);
        for (ancestor = item->node; ancestor < source->nnode; ancestor = source->node[ancestor].parent) {
            const dw4_scene_node *n = &source->node[ancestor];
            if (!material && n->has_material) material = n;
            if (!(seen & 1) && n->has_color) { memcpy(color, n->color, sizeof color); seen |= 1; }
            if (!(seen & 2) && n->has_lighting) { lit = n->lighting_enabled; seen |= 2; }
            if (!(seen & 4) && n->has_blend_state) { blend = n->blend_enabled; seen |= 4; }
            if (!(seen & 8) && n->has_depth_write) { depth_write = n->depth_write; seen |= 8; }
        }
        if (blend) {
            uint32_t src = 4, dst = 5;
            dw4_scene_node_blend(source, item->node, &src, &dst);
            blend = src == 4 && dst == 1 ? 2 : 1;
        }
        if(item->shadow) {
            lit=0;blend=1;depth_write=0;ref=-1;
            memset(color,0,sizeof color);color[3]=1;
        }
        unsigned q;
        if (!pos || dw4_scene_node_world(source, item->node, world)) continue;
        if (item->effect) {
            const float *p = l->effect[item->effect-1].pos;
            world[12] += p[0]; world[13] += p[1]; world[14] += p[2];
        }
        if (item->actor) {
            dw4_actoranim *motion = item->caster_only ? l->p->player_shadow : l->p->player_idle;
            double motion_time = local*1e-9;
            if(item->actor==2 && dw4_modelctrl_active(l->p->player_controller)) {
                dw4_modelctrl_actor actor={0};dw4_modelctrl_actor_state(l->p->player_controller,&actor);
                motion=player_animation(l,actor.motion,item->caster_only);
                motion_time=actor.motion_ns*1e-9;
                dw4_actoranim_loop(motion,actor.motion_loop);
                dw4_actoranim_blend(motion,0,0);
                if(actor.previous_motion && actor.blend_ns>actor.motion_ns) {
                    dw4_actoranim *from=player_animation(l,actor.previous_motion,item->caster_only);
                    float weight=1-(float)actor.motion_ns/actor.blend_ns;
                    if(dw4_actoranim_blend_motion(motion,from,actor.previous_motion_ns*1e-9,weight))return -1;
                }
            }
            if (item->actor == 1) {
                unsigned t = l->age ? l->age-1 : 0;
                int index = l->npc_motion_index;
                motion_time = (t-l->motion_start)/60.0;
                if(l->native_models)motion_time=l->native_motion_ns[0]*1e-9;
                float angle = l->npc_yaw*0.017453292519943295f;
                motion = l->npc_motion[index];
                memset(world, 0, sizeof world);
                world[0]=world[10]=cosf(angle); world[2]=-sinf(angle); world[8]=sinf(angle);
                world[5]=world[15]=1;
                memcpy(world+12, l->npc_pos, sizeof l->npc_pos);
            } else if (item->actor >= 3) {
                unsigned i = item->actor-3, t = l->age ? l->age-1 : 0;
                float angle = l->female_yaw[i]*0.017453292519943295f;
                motion = l->female_motion[i == 0 ? l->female_index : l->second_index];
                motion_time = (t-(i == 0 ? l->female_start : l->second_start))/60.0;
                if(l->native_models)motion_time=l->native_motion_ns[i+1]*1e-9;
                memset(world, 0, sizeof world);
                world[0]=world[10]=cosf(angle); world[2]=-sinf(angle); world[8]=sinf(angle);
                world[5]=world[15]=1;
                memcpy(world+12, l->female_pos[i], sizeof l->female_pos[i]);
            } else if (source == &l->p->weapon) {
                float bone[16], attached[16];
                if (dw4_actoranim_bone(motion,l->p->weapon_bones[item->attachment],motion_time,bone)) return -1;
                /* Row vectors: weapon graph local * actor bone * player placement. */
                for (unsigned i = 0; i < 16; i++) {
                    unsigned row = i/4, col = i%4;
                    attached[i] = 0;
                    for (unsigned k = 0; k < 4; k++) attached[i] += world[row*4+k]*bone[k*4+col];
                }
                for (unsigned i = 0; i < 16; i++) {
                    unsigned row = i/4, col = i%4;
                    world[i] = 0;
                    for (unsigned k = 0; k < 4; k++) world[i] += attached[row*4+k]*l->p->player_world[k*4+col];
                }
            } else memcpy(world, l->p->player_world, sizeof world);
            if (source != &l->p->weapon && LSUB(7,dw4_actoranim_pose(motion, source, item->node, motion_time, &pos, &norm))) return -1;
        }
        if(item->instance && item->skinned) {
            dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(l->instances[item->instance-1].model,&actor);
            dw4_actoranim *motion=instance_motion(l,item,actor.motion);
            if(!motion){if(!l->script_error[0])snprintf(l->script_error,sizeof l->script_error,"instance %s mesh %s: motion %s unavailable",l->instances[item->instance-1].name,source->node[item->node].name,actor.motion?actor.motion:"<none>");return -1;}
            dw4_actoranim_loop(motion,actor.motion_loop);dw4_actoranim_blend(motion,0,0);
            if(actor.previous_motion && actor.blend_ns>actor.motion_ns) {
                dw4_actoranim *from=instance_motion(l,item,actor.previous_motion);
                if(!from || dw4_actoranim_blend_motion(motion,from,actor.previous_motion_ns*1e-9,1-(float)actor.motion_ns/actor.blend_ns)){snprintf(l->script_error,sizeof l->script_error,"instance %s: previous motion %s unavailable",l->instances[item->instance-1].name,actor.previous_motion);return -1;}
            }
            if(LSUB(7,dw4_actoranim_pose(motion,source,item->node,actor.motion_ns*1e-9,&pos,&norm)))return -1;
        }
        uint32_t mesh_fog_enabled = 1;
        dw4_scene_node_fog(source, item->node, &mesh_fog_enabled);
        const unsigned light_k=lobby_light_rotations(l,item,world);
        unsigned cull=0;
        if(source!=&l->p->weapon && item->nt)
            cull=lobby_mesh_cull(l,item,m->num_verts,pos,world,view,fy,aspect,fb->w,fb->h,item->actor || (item->instance && item->skinned));
        const int view_out=cull&1,shadow_out=(cull&2)!=0;
        const int need_caster=(item->actor || item->casts_shadow) && !shadow_out;
        if(view_out && !need_caster)continue;
        if(lobby_vc_reserve(m->num_verts)){fprintf(stderr,"  lobby: vertex cache allocation failed\n");return -1;}
        if(++lobby_vc_gen==0){memset(lobby_vc_stamp,0,lobby_vc_cap*sizeof *lobby_vc_stamp);memset(lobby_vc_stampa,0,lobby_vc_cap*sizeof *lobby_vc_stampa);lobby_vc_gen=1;}
        struct lobby_vctx vctx={pos,world,view,fy,aspect,fb->w*.5f+8.0f,fb->h*.5f+8.0f,l->near_plane,l->far_plane,NULL};
        /* A static scene mesh whose world matrix is unchanged between frames keeps its world-space positions (the same arithmetic,
         * done once); a mesh whose matrix changes every frame is left to the lazy per-vertex path. */
        if(item->source==&l->scene && !item->actor && !item->instance && !item->effect && !item->arrival && !item->skinned && item->nt>0 && m->num_verts>0) {
            size_t index=(size_t)(item-l->mesh);
            if(index>=l->nwcache) {
                struct world_cache *rows=realloc(l->wcache,l->nmesh*sizeof *rows);
                if(rows){memset(rows+l->nwcache,0,(l->nmesh-l->nwcache)*sizeof *rows);l->wcache=rows;l->nwcache=l->nmesh;}
            }
            if(index<l->nwcache) {
                struct world_cache *wc=l->wcache+index;
                if(wc->node!=item->node+1 || wc->pos!=pos || wc->n!=m->num_verts || memcmp(wc->world,world,sizeof wc->world)) {
                    wc->node=item->node+1;wc->pos=pos;wc->n=m->num_verts;memcpy(wc->world,world,sizeof wc->world);wc->stable=0;
                    free(wc->w);wc->w=NULL;
                } else if(wc->stable<2)wc->stable++;
                if(!wc->w && wc->stable>=2 && m->num_verts<=(1u<<22)) {
                    wc->w=malloc((size_t)m->num_verts*3*sizeof *wc->w);
                    if(wc->w)for(unsigned vi=0;vi<m->num_verts;vi++)for(int k=0;k<3;k++)
                        wc->w[3*(size_t)vi+k]=pos[3*vi]*world[k]+pos[3*vi+1]*world[4+k]+pos[3*vi+2]*world[8+k]+world[12+k];
                }
                vctx.wpos=wc->w;
            }
        }
        lobby_trace_ms[13]+=item->nt;
        for (q = 0; q < item->nt; q++) {
            /* Clip in view space before the perspective divide. Dropping a whole
             * triangle when one corner crosses the camera removed lobby walls. */
            float vertices[3][10], clipped[5][10]; /* XYZ, UV, RGBA, fog */
            unsigned nclip = 0;
            if(!need_caster) {
                /* Trivial reject: all three corners beyond the same clip plane, decided from stage A alone. */
                unsigned oc=0xffu;int valid=1;
                for(int e=0;e<3;e++) {
                    unsigned vi=item->tri[3*q+e];
                    if(vi>=m->num_verts){valid=0;break;}
                    struct lobby_vcache *cv=&lobby_vc[vi];
                    if(lobby_vc_stampa[vi]!=lobby_vc_gen){lobby_vc_position(cv,vi,&vctx);lobby_vc_stampa[vi]=lobby_vc_gen;}
                    oc&=cv->oc;
                }
                if(!valid || oc)continue;
            }
            dw4_layer_draw caster;
            if(need_caster){caster=(dw4_layer_draw){.gs_raster=1,.aref=-1,.straight_rgb=1};memset(caster.rgba,128,sizeof caster.rgba);}
            int e, k;
            for (e = 0; e < 3; e++) {
                unsigned vi = item->tri[3*q+e];
                if (vi >= m->num_verts) break;
                struct lobby_vcache *cv = &lobby_vc[vi];
                if (lobby_vc_stampa[vi] != lobby_vc_gen) {lobby_vc_position(cv,vi,&vctx);lobby_vc_stampa[vi]=lobby_vc_gen;}
                if (lobby_vc_stamp[vi] != lobby_vc_gen) {
                    float vx[10];
                    const float *p=cv->p;
                    uint8_t rgba[4];
                    memcpy(vx,cv->vp,3*sizeof *vx);
                    vx[3] = uv ? uv[2*vi]+du : 0;
                    vx[4] = uv ? uv[2*vi+1]+dv : 0;
                    /* Runtime shader follows the player +200Y, uses an orthographic
                     * +/-100 square and a nine-texel inset (238/256 viewport).
                     * Up=(1,0,0): texture X follows +world Z, Y follows -world X. */
                    cv->su=(p[2]-l->p->player_world[14]-l->shadow_bounds[1])/
                           (l->shadow_bounds[0]-l->shadow_bounds[1]);
                    cv->sv=(l->shadow_bounds[2]-(p[0]-l->p->player_world[12]))/
                           (l->shadow_bounds[2]-l->shadow_bounds[3]);
                    lobby_vertex_color(l, norm ? norm+3*vi : NULL, world, lit, color, material, view, light_k, rgba);
                    if (item->actor == 2) rgba[3] = (uint8_t)(rgba[3]*(l->native_models?
                        dw4_modelctrl_alpha(l->p->player_controller):lobby_fade_alpha(&l->p->player_alpha)));
                    if(item->effect) rgba[3]=(uint8_t)(rgba[3]*(l->native_models?
                        dw4_modelctrl_alpha(l->native_portal[item->effect-1]):portal_alpha(&l->effect[item->effect-1],l->age?l->age-1:0)));
                    if(item->instance)rgba[3]=(uint8_t)(rgba[3]*dw4_modelctrl_alpha(l->instances[item->instance-1].model));
                    if(item->arrival) rgba[3]=(uint8_t)(rgba[3]*lobby_fade_alpha(&l->rings.fade[item->arrival-1]));
                    for (k = 0; k < 4; k++) vx[5+k] = rgba[k];
                    vx[9] = floorf(255*fminf(1, fmaxf(0,
                        (l->fog_end-vx[2])/(l->fog_end-l->fog_start))));
                    memcpy(cv->v, vx, sizeof vx);
                    lobby_vc_stamp[vi] = lobby_vc_gen;
                }
                memcpy(vertices[e], cv->v, sizeof vertices[e]);
                float su=cv->su, sv=cv->sv;
                if(item->shadow) {
                    vertices[e][3]=(9+238*su)/256;
                    vertices[e][4]=(9+238*sv)/256;
                }
                if(need_caster) {
                    caster.v[e][0]=floorf((9+238*su)*16)/16;
                    caster.v[e][1]=floorf((9+238*sv)*16)/16;
                    caster.v[e][4]=1;
                    caster.z[e]=1;
                }
            }
            if (e != 3) continue;
            if(need_caster && (item->actor || item->casts_shadow)) {
                /* Shader override alpha is independent of entry material fade. */
                l->casters[ncasters++]=caster;
            }
            if(item->caster_only || view_out) continue;
            /* A triangle wholly inside [near, far] leaves lobby_clip_depth unchanged (same vertices, same order). */
            const int depth_inside=vertices[0][2]>=l->near_plane && vertices[0][2]<=l->far_plane &&
                vertices[1][2]>=l->near_plane && vertices[1][2]<=l->far_plane &&
                vertices[2][2]>=l->near_plane && vertices[2][2]<=l->far_plane;
            if(depth_inside){memcpy(clipped,vertices,3*sizeof clipped[0]);nclip=3;}
            else nclip=lobby_clip_depth(vertices,l->near_plane,l->far_plane,clipped);
            for (unsigned j = 1; j+1 < nclip; j++) {
                const float *vtx[3] = {clipped[0],clipped[j],clipped[j+1]};
                dw4_layer_draw triangle={0}, *d=&triangle;
                uint32_t fog_enabled = mesh_fog_enabled;
                d->tex = item->tex; d->aref = item->shadow ? -1 : (int)floorf(ref*128);
                d->fog = !item->shadow && fog_enabled ? 2 : 0;
                memcpy(d->fog_color, l->fog_color, 3);
                d->straight_rgb = 1; d->gs_raster=1; d->blend = blend; d->no_depth_write = !depth_write;
                if (item->actor == 2 && (l->native_models?dw4_modelctrl_alpha(l->p->player_controller)<1:l->p->player_alpha.direction!=3)) d->blend = 1;
                /* A world model whose Action2 fade is running (the items' blink-out FADESETs) blends by its alpha. */
                if (item->instance && dw4_modelctrl_alpha(l->instances[item->instance-1].model) < 1) d->blend = 1;
                for (e = 0; e < 3; e++) {
                    const float *v = vtx[e]; float z = v[2];
                    d->v[e][0] = fb->w*.5f + v[0]/z*fy*aspect;
                    d->v[e][1] = fb->h*.5f - v[1]/z*fy;
                    d->v[e][2] = v[3]/z; d->v[e][3] = v[4]/z; d->v[e][4] = 1/z;
                    d->z[e] = 16777216.0f/z; d->f[e] = v[9];
                    for (k = 0; k < 4; k++) d->rgba[e][k] = (uint8_t)v[5+k];
                }
                /* Likewise a triangle wholly inside the screen rectangle comes out of lobby_clip_screen as itself:
                 * one triangle, same vertex order, the same values (colours round-trip through float exactly). */
                unsigned emitted;
                if(d->v[0][0]>=0 && d->v[0][0]<=fb->w && d->v[1][0]>=0 && d->v[1][0]<=fb->w && d->v[2][0]>=0 && d->v[2][0]<=fb->w &&
                   d->v[0][1]>=0 && d->v[0][1]<=fb->h && d->v[1][1]>=0 && d->v[1][1]<=fb->h && d->v[2][1]>=0 && d->v[2][1]<=fb->h) {
                    l->draw[count]=*d;emitted=1;
                } else emitted=lobby_clip_screen(d,fb->w,fb->h,l->draw+count);
                for(unsigned j=0;j<emitted;j++) for(unsigned e=0;e<3;e++) for(unsigned k=0;k<2;k++)
                    l->draw[count+j].v[e][k]=floorf(l->draw[count+j].v[e][k]*16)/16;
                count+=emitted;lobby_trace_ms[14]+=emitted;
                if(source==&l->p->weapon){l->p->weapon_submitted_triangles+=emitted;
                    l->p->weapon_submitted[item->attachment]+=emitted;}
            }
        }
    }

    l->p=l->pl;
    lobby_trace_ms[tr_cat]+=lobby_trace_clock()-tr_prev;
    /* beParticleCtrl2's three independently spawned y_100trnsin01 instances.
     * ParticleArray supplies camera-facing sprites; their curves are authored,
     * not generated positions or a snapshot of one emulator frame. */
    struct lobby_mesh stars={.source=&l->scene,.node=l->stars.node};
    int stars_visible=!visible || visible(user,mesh_layer(&stars));
    for(unsigned group=0;stars_visible && group<3;group++) if(l->stars.started & (1u<<group)) {
        /* ParticleTimer uses the raw world clock, unlike beModelCtrlNode2. */
        int64_t elapsed=(int64_t)frame*1000000000LL/60-l->stars.start[group];
        float time=(float)(elapsed*1e-9);
        if(elapsed<0 || elapsed>=1000000000LL) continue;
        float yaw=l->rings.rotation[group][1],cs=cosf(yaw),sn=sinf(yaw);
        for(unsigned p=0;p<l->stars.count;p++) {
            const float *c=l->stars.curve[p];
            float t=c[36]!=0?fmodf(time+c[36],l->stars.lifetime):time;
            float local[3],position[3],center[3];
            for(unsigned axis=0;axis<3;axis++) local[axis]=lobby_particle_curve(c[axis],c[3+axis],c[6+axis],t);
            position[0]=local[0]*cs+local[2]*sn;
            position[1]=local[1];position[2]=-local[0]*sn+local[2]*cs;
            for(unsigned axis=0;axis<3;axis++) position[axis]+=l->p->player_world[12+axis]+l->rings.offset[group][axis]+l->stars.offset[axis];
            for(unsigned axis=0;axis<3;axis++) center[axis]=position[0]*view[axis]+position[1]*view[4+axis]+position[2]*view[8+axis]+view[12+axis];
            float z=-center[2];if(z<l->near_plane || z>l->far_plane) continue;
            float width=lobby_particle_curve(c[21],c[23],c[25],t),height=lobby_particle_curve(c[22],c[24],c[26],t);
            if(width<=0 || height<=0) continue;
            float x=fb->w*.5f+center[0]/z*fy*aspect,y=fb->h*.5f-center[1]/z*fy;
            float hw=.5f*width/z*fy*aspect,hh=.5f*height/z*fy;
            float u0=lobby_particle_curve(c[27],c[37],c[39],t),v0=lobby_particle_curve(c[28],c[38],c[40],t);
            float u1=lobby_particle_curve(c[29],c[41],c[43],t),v1=lobby_particle_curve(c[30],c[42],c[44],t);
            const float corners[4][4]={{x-hw,y-hh,u0,v0},{x+hw,y-hh,u1,v0},{x+hw,y+hh,u1,v1},{x-hw,y+hh,u0,v1}};
            static const unsigned indices[2][3]={{0,1,2},{0,2,3}};
            uint8_t color[4];
            for(unsigned axis=0;axis<4;axis++) {
                color[axis]=(uint8_t)lobby_particle_color(lobby_particle_curve(c[9+axis],c[13+axis],c[17+axis],t),axis==3);
            }
            for(unsigned tri=0;tri<2;tri++) {
                dw4_layer_draw d={.tex=l->stars.tex,.gs_raster=1,.straight_rgb=1,.blend=l->stars.blend,.no_depth_write=1,.aref=l->stars.aref};
                for(unsigned e=0;e<3;e++) {
                    const float *v=corners[indices[tri][e]];
                    d.v[e][0]=v[0];d.v[e][1]=v[1];d.v[e][2]=v[2]/z;d.v[e][3]=v[3]/z;d.v[e][4]=1/z;
                    d.z[e]=16777216.0f/z;memcpy(d.rgba[e],color,4);
                }
                unsigned emitted=lobby_clip_screen(&d,fb->w,fb->h,l->draw+count);
                for(unsigned j=0;j<emitted;j++) for(unsigned e=0;e<3;e++) for(unsigned axis=0;axis<2;axis++) l->draw[count+j].v[e][axis]=floorf(l->draw[count+j].v[e][axis]*16)/16;
                count+=emitted;
            }
        }
    }

    /* Retail submits opaque geometry before the additive/alpha overlay passes.
     * A depth-tested glow with ZMSK=1 must see the completed opaque depth buffer. */
    {
        dw4_layer_draw *ordered = l->draw+l->capacity;
        unsigned n = 0;
        for (int pass = 0; pass < 2; pass++)
            for (unsigned j = 0; j < count; j++)
                if ((l->draw[j].blend != 0) == pass) ordered[n++] = l->draw[j];
        memcpy(l->draw, ordered, (size_t)count*sizeof *l->draw);
    }
    /* Opaque caster union prevents overlapping triangles or actors from
     * darkening a shadow multiple times. Bilinear receiver sampling softens the
     * 256-square map edges. Re-upload this mutable texture on both GPU paths. */
retry_raster:
    LTR(0);
    dw4_render_tex_wrap=old_wrap;dw4_render_tex_linear=old_linear;
    if(!l->gpu && dw4_gpu_policy_required())return lobby_gpu_failure(l,"lobby GPU unavailable");
    if(l->gpu){
        if(!l->shadow_gpu || dw4_gl_layer_clear(l->shadow_gpu,&l->shadow_fb,0,0,0,255) ||
           dw4_gl_layer_draw(l->shadow_gpu,&l->shadow_fb,l->casters,(int)ncasters,old_wrap,old_linear,dw4_render_alpha_ref) ||
           dw4_gl_layer_transform(l->shadow_gpu,&l->shadow_fb,DW4_GL_SHADOW_ALPHA,l->shadow_factor)){
            if(lobby_gpu_failure(l,"shadow GPU pass"))return -1;
            goto retry_raster;
        }
    }else lobby_shadow_cpu(l,ncasters);
    LTR(1);
    dw4_gl_layer_texture_changed(l->gpu,&l->shadow_tex);
    l->ndraw = count;
    if(l->gpu){
        if(dw4_gl_layer_clear(l->gpu,fb,l->fog_color[0],l->fog_color[1],l->fog_color[2],255)){
            if(lobby_gpu_failure(l,"lobby GPU clear"))return -1;
            goto retry_raster;
        }
    }else dw4_fb_clear(fb,l->fog_color[0],l->fog_color[1],l->fog_color[2]);
    dw4_render_tex_wrap = dw4_render_tex_linear = 1;
    if(l->gpu){
        if(dw4_gl_layer_draw(l->gpu,fb,l->draw,(int)count,1,1,-1)){
            if(lobby_gpu_failure(l,"lobby GPU draw")){
                dw4_render_tex_wrap=old_wrap;dw4_render_tex_linear=old_linear;return -1;
            }
            goto retry_raster;
        }
    }else{
        dw4_render_zbuf_clear(fb);
        dw4_render_layer_draws(fb,l->draw,(int)count,8);
    }
    LTR(2);
    dw4_render_tex_wrap = old_wrap; dw4_render_tex_linear = old_linear;
    int gpu_frame=l->gpu!=NULL;
    /* The lobby UI's models (HUD panels, message window) are drawn first and the window-layer models after them: the speaker's
     * face stands on the message window and the stage-change iris (i_fadewn01) covers the HUD, as in retail. The text (the
     * original's FONT layer) goes between the window layers: over WN00/WN01, so the point-message name stands on its band
     * (i_stpnl06, WN01) and that band's chevrons are not covered by the HUD panels (i_stpnl00, also WN01); under WN02, whose
     * full-screen models (the iris i_fadewn01, i_bgclear, i_stback) must hide a label left open over a stage change. */
    const int talk_first=l->native_ui!=NULL; /* always: the HUD, windows and speaker face sit under the window-layer models, the stage fade among them */
    if(talk_first && apply_fade && (l->native_ui || (font && font->have))){
        if(dw4_lobbyui_draw_parts(l->ui, fb, &l->gpu, DW4_LOBBYUI_MODELS)<0)return -1;
    }
    if(apply_fade && l->native_ui) for(int part=1;part<=2;part++) {
        const dw4_ui_draw *draw;size_t n;
        {   /* The scene camera for the point-message cursor: row vectors, view space +Z forward, the lobby's projection. */
            float projection[16];const float t=tanf(DW4_SCENE_CAMERA_FOV*.5f),nr=l->near_plane,fr=l->far_plane;
            memset(projection,0,sizeof projection);
            projection[0]=dw4_scene_camera_aspect(fb->w,fb->h)*fb->h/fb->w/t;projection[5]=1/t;
            projection[10]=(fr+nr)/(fr-nr);projection[11]=1;projection[14]=-2*fr*nr/(fr-nr);
            float forward[16];memcpy(forward,view,sizeof forward);
            for(unsigned row=0;row<4;row++)forward[4*row+2]=-forward[4*row+2]; /* the lobby negates camera Z after this view */
            dw4_modelview_camera(l->native_ui,forward,projection);
            dw4_modelview_hide_labels(l->native_ui,dw4_lobbyui_talk_open(l->ui));
        }
        dw4_dialogue_talk_late(l->native_dialogue,!l->ui);
        dw4_modelview_layer_split(l->native_ui,"WN02",part);
        int rc=dw4_modelview_draw(l->native_ui,fb->w,fb->h,&draw,&n,l->script_error,sizeof l->script_error);
        dw4_modelview_layer_split(l->native_ui,NULL,0);
        if(rc)return -1;
        /* The window models' textures are authored REPEAT (igTextureAttr _wrapS/_wrapT = 1, as the lobby UI and the front-end draw them): the tutorial window's rules
         * slide their UVs to u < 0 and their alpha fade comes from the wrapped texture (clamped, the rules came out opaque and full length). */
        const int ui_wrap=dw4_render_tex_wrap;dw4_render_tex_wrap=1;
        if(l->gpu) {
            if(dw4_gl_layer_ui(l->gpu,fb,draw,(int)n)){dw4_render_tex_wrap=ui_wrap;return -1;}
        }else {
            dw4_render_zbuf_clear(fb);
            dw4_gl_layer_ui_or_cpu(&l->gpu,fb,draw,(int)n,8);
        }
        dw4_render_tex_wrap=ui_wrap;
        dw4_dialogue_text_split(l->native_dialogue,"WN02",part);
        int text_rc=l->ui?dw4_lobbyui_draw_parts(l->ui, fb, &l->gpu, DW4_LOBBYUI_TEXT):field_text(l,fb);
        dw4_dialogue_text_split(l->native_dialogue,NULL,0);
        if(text_rc<0)return -1;
    }
    LTR(3);
    if (!talk_first && apply_fade && (l->native_ui || (font && font->have))) {
        if(dw4_lobbyui_draw_backend(l->ui, fb, &l->gpu)<0)return -1;
    }
    LTR(4);
    if(apply_fade && l->native_ui && l->status_hold) {
        const dw4_ui_draw *draw;size_t n;
        if(dw4_dialogue_draw(l->native_dialogue,fb->w,fb->h,&draw,&n))return -1;
        if(l->gpu) {
            if(dw4_gl_layer_ui(l->gpu,fb,draw,(int)n))return -1;
        }else dw4_gl_layer_ui_or_cpu(&l->gpu,fb,draw,(int)n,8);
    }
    LTR(5);
    if(dw4_gpu_policy_error()[0])return -1;
    if(gpu_frame && !l->gpu){lobby_gpu_failure(l,"lobby UI GPU draw");goto retry_raster;}
    /* Original Lua schedules SQ_BLIN60 five ticks after stage publication. */
    float screen_alpha=l->native_models?1-dw4_modelctrl_alpha(l->native_fade):lobby_fade_alpha(&l->screen_alpha);
    /* The generic WN view includes the original fade geometry, JOINTSET color
     * and FADESET opacity. Its half-opacity dim belongs behind confirmation
     * windows. Applying the legacy full-frame multiplier again erases them. */
    if (apply_fade && !l->native_ui && screen_alpha<1) {
        if(l->gpu){
            if(dw4_gl_layer_transform(l->gpu,fb,DW4_GL_FADE_RGB,screen_alpha)){
                if(lobby_gpu_failure(l,"lobby GPU fade"))return -1;
                goto retry_raster;
            }
        }else{
            if(dw4_gpu_policy_cpu(DW4_CPU_COMPOSITE))return -1;
            for(size_t p=0;p<(size_t)fb->w*fb->h;p++)
                for(i=0;i<3;i++)fb->rgba[4*p+i]=(unsigned)(fb->rgba[4*p+i]*screen_alpha);
        }
    }
    return (int)count;
}

int dw4_lobby_npc(const dw4_lobby *l,unsigned actor,dw4_lobby_npc_state *s)
{
    if(!l || !s || actor>=3) return -1;
    memcpy(s->position,actor?l->female_pos[actor-1]:l->npc_pos,sizeof s->position);
    s->yaw=actor?l->female_yaw[actor-1]:l->npc_yaw;
    s->speed=npc_float(l->walk[actor].speed);s->turn_speed=npc_float(l->turn[actor].speed);
    s->phase=l->phase[actor];s->contacts=l->contacts[actor];
    s->motion=actor==1?l->female_index:actor==2?l->second_index:l->npc_motion_index;return 0;
}

int dw4_lobby_portal_command(dw4_lobby *l,unsigned portal,const char *command)
{
    if(!l || portal>=4 || !command) return -1;
    struct lobby_portal *p=&l->effect[portal];
    unsigned tick=l->age?l->age-1:0;
    if(!strcmp(command,"SQ_POWERON")) {p->powered=1;p->active=0;portal_start(p,PORTAL_OFF,tick);}
    else if(!strcmp(command,"SQ_POWEROF")) {p->powered=p->active=0;portal_start(p,PORTAL_WAIT,tick);}
    else if(!strcmp(command,"SQ_SWON")) {
        if(p->powered && !p->active) {p->active=1;portal_start(p,PORTAL_RISE,tick);}
    } else if(!strcmp(command,"SQ_SWOF")) {
        if(p->active) {p->active=0;portal_start(p,PORTAL_FALL,tick);}
    } else return -1;
    return p->clock.error?-1:0;
}
int dw4_lobby_portal(const dw4_lobby *l,unsigned portal,dw4_lobby_portal_state *out)
{
    if(!l || portal>=4 || !out) return -1;
    const struct lobby_portal *p=&l->effect[portal];
    *out=(dw4_lobby_portal_state){p->powered,p->active,p->visible,p->action,
        dw4_action2_host_node_time(&p->clock,(int64_t)(l->age?l->age-1:0)*1000000000LL/60)};
    if(l->native_models) {
        const dw4_modelctrl *m=l->native_portal[portal];const char *a=dw4_modelctrl_action(m);
        out->animation_ns=dw4_modelctrl_time(m);out->visible=dw4_modelctrl_drawable(m);
        if(a){
            out->action=!strcmp(a,"OFF2ON")?PORTAL_RISE:!strcmp(a,"ON2OFF")?PORTAL_FALL:
                !strcmp(a,"ONSW01")?PORTAL_ON:!strcmp(a,"OFSW01")?PORTAL_OFF:PORTAL_WAIT;
            out->powered=out->action!=PORTAL_WAIT;
            out->active=out->action==PORTAL_RISE || out->action==PORTAL_ON;
        }
    }
    return p->clock.error?-1:0;
}
int dw4_lobby_portal_slots(const dw4_lobby *l,unsigned portal,dw4_lobby_portal_instances *out)
{
    if(!l || portal>=4 || !out)return -1;
    *out=(dw4_lobby_portal_instances){0};uint32_t root=l->effect[portal].root;
    memcpy(out->position,l->effect[portal].pos,sizeof out->position);
    for(uint32_t n=root+1;n<l->scene.nnode && l->scene.node[n].depth>l->scene.node[root].depth;n++)
        if(l->scene.node[n].parent==root && !strcmp(l->scene.node[n].class_name,"beModelCtrlNode2")) {
            out->slots++;
            if(l->effect[portal].visible && dw4_scene_node_visible(&l->scene,n,0))out->visible_slots++;
        }
    return 0;
}
int dw4_lobby_actor_visible(dw4_lobby *l,unsigned actor,int visible)
{
    if(!l || actor>=4) return -1;
    if(visible) l->hidden_actors &= ~(1u<<actor);
    else l->hidden_actors |= 1u<<actor;
    return 0;
}
int dw4_lobby_portal_visible(dw4_lobby *l,unsigned portal,int visible)
{
    if(!l || portal>=4) return -1;
    l->effect[portal].visible=!!visible;return 0;
}

const dw4_tex *dw4_lobby_shadow_map(const dw4_lobby *l)
{
    return l?&l->shadow_tex:NULL;
}

void dw4_lobby_model_action(dw4_lobby *l,const char *model,const char *action)
{if(l)dw4_frontaudio_action(l->audio,model,action);}

int dw4_lobby_health_publish(dw4_lobby *l,const dw4_playerhealth *h)
{return l?dw4_lobbyui_health_publish(l->ui,h):-1;}

const char *dw4_lobby_gpu_info(const dw4_lobby *l)
{return l && l->gpu?dw4_gl_layer_info(l->gpu):NULL;}

dw4_modelctrl *dw4_lobby_player_model(dw4_lobby *l){return l?l->p->player_controller:NULL;}
/* Local co-op: the per-player entry points above (input, jump, request, model, walk state) act on the selected slot; slot 0 is the default. A slot nobody
 * joined cannot be selected. */
int dw4_lobby_select_player(dw4_lobby *l,unsigned slot){if(!l || slot>3 || !l->pl[slot].joined)return -1;l->p=l->pl+slot;return 0;}
unsigned dw4_lobby_player_count(const dw4_lobby *l){unsigned n=0;for(unsigned q=0;l && q<4;q++)n+=l->pl[q].joined;return n;}
int dw4_lobby_player_joined(const dw4_lobby *l,unsigned slot){return l && slot<4 && l->pl[slot].joined;}

/* A sequence request as the player update writes it (work+116): applied when it differs from the current sequence. */
int dw4_lobby_player_request(dw4_lobby *l,const char *sequence)
{
    if(!l || !l->p->player_controller || !sequence)return -1;
    const char *current=dw4_modelctrl_sequence(l->p->player_controller);
    if(current && !strcmp(current,sequence))return 0;
    return dw4_modelctrl_start(l->p->player_controller,sequence);
}
void dw4_lobby_clear_script_error(dw4_lobby *l){if(l)l->script_error[0]=0;}

/* PLAYERgetDataStr(group, player, 0): the authored arrival point of a player as the "V<x,y,z>/V<0,yaw,0>" placement string MOVETRANS takes. */
int dw4_lobby_point_string(const dw4_lobby *l,int group,int player,char *out,size_t cap)
{
    if(!l || group<0 || group>=8 || player<0 || player>=4 || !l->point_ok[group][player])return -1;
    const float *m=l->point_matrix[group][player];
    float yaw=atan2f(m[8],m[10])*57.295779513f;
    snprintf(out,cap,"V<%.9g,%.9g,%.9g>/V<0,%.9g,0>",m[12],m[13],m[14],yaw);return 0;
}
