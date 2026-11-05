/* dw4/engine.c — the native host runtime; see include/dw4/engine.h.
 *
 * init -> build the object graph -> per-frame update -> present.  The frame loop is the engine's
 * shape; the update step runs the one engine function that is decompiled and portable today
 * (`igObject_InitHeader`, ported as `dw4_object_init_header`) and advances the clock, and the
 * present step draws the loaded geometry with the port's renderer.
 */
#define _GNU_SOURCE
#include "dw4/playertransactions.h"
#include "dw4/engine.h"
#include "dw4/gpupolicy.h"
#include "dw4/simulation.h"
#include "dw4/scriptservices.h"
#include "dw4/filelist.h"
#include "dw4/stageobjects.h"
#include "dw4/titleservices.h"
#include "dw4/controllers.h"
#include "dw4/playerrecords.h"
#include "dw4/memcard.h"
#include "dw4/savescene.h"
#include "dw4/saveintf.h"
#include "dw4/playerinit.h"
#include "dw4/playerhealth.h"
#include "dw4/database.h"
#include "dw4/statusmenu.h"
#include "dw4/statusscene.h"
#include "dw4/statusui.h"
#include "dw4/modelview.h"
#include "dw4/hubruntime.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "dw4/igb.h"
#include "dw4/igfile.h"
#include "dw4/fefont.h"
#include "dw4/options.h"
#include "dw4/titlehost.h"
#include "dw4/frontopt.h"
#include "dw4/frontchr.h"
#include "dw4/lobby.h"
#include "dw4/loadjob.h"
#include "dw4/frontend.h"
#include "dw4/frontaudio.h"
#include "dw4/input.h"
#include "dw4/padrepeat.h"
#include "dw4/stageinput.h"
#include "dw4/mount.h"
#include "dw4/object.h"
#include "dw4/platform.h"
#include "dw4/png.h"
#include "dw4/render.h"
#include "dw4/gl_render.h"
#include "dw4/gl_layer.h"
#include "dw4/scene.h"
#include "dw4/texpack.h"
#include "dw4/frontlayer.h"
#include "dw4/frontui.h"
#include "dw4/window.h"
#include "dw4/vk_present.h"

/* DW4_SHOT_FRAMES="a,b,c" limits the headless per-frame PNGs to the listed frame numbers (unset = every frame). */
/* DW4_DEV_TALK="<world frame>:<model>:<slot>" (inspection/e2e aid): stand the player 12 units in front of that NPC, facing it. Frames
 * count in the hub runtime, or in the scripted first Terminal when no DW4_DEV_WARP is set; there each Cross probe is also logged. */
static int dev_talk_place(dw4_lobby *world,const dw4_controllers *models,const char *model,int slot)
{
    for(size_t i=0;world && models && i<dw4_controllers_count(models);i++){
        const dw4_stageobject *info;int32_t s;const dw4_modelctrl *m=dw4_controllers_model(models,i,&info,&s);
        if(s!=slot || strcmp(dw4_stageobject_name(info),model))continue;
        if(!dw4_modelctrl_active(m))return -1; /* not generated in this stage */
        dw4_modelctrl_actor a={0};dw4_modelctrl_actor_state(m,&a);
        float r=a.rotation[1]*0.0174533f;
        fprintf(stderr,"dev talk: %s[%d] at %g %g %g yaw %g\n",model,slot,a.position[0],a.position[1],a.position[2],a.rotation[1]);
        return dw4_lobby_place_player(world,a.position[0]+12*sinf(r),a.position[1],a.position[2]+12*cosf(r),a.rotation[1]+180);
    }
    return -1;
}
static int dev_talk_due(unsigned *frames,char *model,size_t cap,int *slot)
{
    static int done;const char *e=getenv("DW4_DEV_TALK");unsigned at;char name[64];int sl;
    if(!e || done)return 0;
    if(sscanf(e,"%u:%63[^:]:%d",&at,name,&sl)!=3)return 0;
    if(++*frames<at)return 0;
    done=1;snprintf(model,cap,"%s",name);*slot=sl;return 1;
}
static int dev_shot_wanted(int frame)
{
    static const char *list;static int init;
    if(!init){list=getenv("DW4_SHOT_FRAMES");init=1;}
    if(!list)return 1;
    for(const char *p=list;*p;){
        char *e;long v=strtol(p,&e,10);
        if(e==p){p++;continue;}
        if(v==frame)return 1;
        p=e;
    }
    return 0;
}

static double now_ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000.0 + t.tv_nsec / 1e6;
}

/* Pace the loop to the game's own rate.  The PS2 game ticks at 60 Hz, so the port must not run its
 * loop -- and the frame counter the engine advances -- at whatever the display happens to refresh
 * (165 Hz on this machine).  `t0_ms` is the loop's start, `i` the frame index; sleeps only when the
 * frame finished early, so a slow frame never accumulates debt.  `fps` <= 0 leaves the loop free. */
static void frame_pace(double t0_ms, int i, int fps)
{
    double due, now, ms;
    struct timespec ts;
    if (fps <= 0)
        return;
    due = t0_ms + (double)(i + 1) * 1000.0 / (double)fps;
    now = now_ms();
    if (now >= due)
        return;
    ms = due - now;
    ts.tv_sec = (time_t)(ms / 1000.0);
    ts.tv_nsec = (long)((ms - (double)ts.tv_sec * 1000.0) * 1e6);
    if (ts.tv_nsec > 999999999L)
        ts.tv_nsec = 999999999L;
    nanosleep(&ts, NULL);
}

/* Live pacing on an absolute schedule: each call advances the due time by exactly one tick, so an early or
 * late frame does not shift the frames after it (the per-iteration form measured from the loop top, which let
 * a blocking vblank wait feed straight into the next frame).  Falls back to a fresh origin after a stall of
 * more than three ticks so a hitch (window drag, load) never turns into a burst of catch-up frames.  The last
 * half millisecond is spun, because nanosleep overshoots by about as much. */
void dw4_lobby_trace_take(double out[16]);
static char trace_stage[40]="boot";   /* DW4_FRAME_TRACE: the stage the loop is presenting */
/* Next "Stage:point" entry of a DW4_DEV_WARP list; returns the list tail or NULL at the end. */
static const char *dev_warp_next(const char *list,char *stage,size_t cap,int32_t *point)
{
    if(!list || !*list)return NULL;
    const char *colon=strchr(list,':'),*comma=strchr(list,',');
    size_t len=colon?(size_t)(colon-list):(comma?(size_t)(comma-list):strlen(list));
    if(len==0 || len>=cap)return NULL;
    memcpy(stage,list,len);stage[len]=0;*point=colon && (!comma || colon<comma)?(int32_t)atoi(colon+1):0;
    return comma?comma+1:list+strlen(list);
}

static void frame_pace_sched(double *due, int fps)
{
    double tick, now;
    if (fps <= 0)
        return;
    tick = 1000.0 / (double)fps;
    now = now_ms();
    if (*due <= 0.0 || now > *due + 3.0 * tick)
        *due = now;
    *due += tick;
    while ((now = now_ms()) < *due) {
        double ms = *due - now - 0.5;
        if (ms > 0.0) {
            struct timespec ts;
            ts.tv_sec = (time_t)(ms / 1000.0);
            ts.tv_nsec = (long)((ms - (double)ts.tv_sec * 1000.0) * 1e6);
            nanosleep(&ts, NULL);
        }
    }
}

static float rdf(const uint8_t *p)
{
    float f;
    memcpy(&f, p, 4);
    return f;
}

/* --- init: the platform seam and the object graph -------------------------------------------------
 *
 * The engine's `main` builds an app object and registers the managers; the port has the seam as an
 * inventory (P2.1) and builds the object graph from the pack through the reflection object model
 * (P2.6).  This prints both so a boot is inspectable. */
static int build_objects(const uint8_t *blob, size_t len, uint32_t *nobj, uint32_t *nfield,
                         uint32_t *nclass)
{
    dw4_igb g;
    uint32_t chain, n, k, obj = 0, fields = 0, classes = 0;
    dw4_igb_record *recs;
    char *seen = NULL;

    if (dw4_igb_open(&g, blob, len, 0) != 0)
        return -1;
    chain = dw4_igb_find_chain(&g, 0x800);
    n = chain ? dw4_igb_chain(&g, chain, NULL, 0) : 0;
    recs = n ? (dw4_igb_record *)calloc(n, sizeof(*recs)) : NULL;
    seen = (char *)calloc((size_t)dw4_nmetaobjects, 1);
    if (recs && seen && dw4_igb_chain(&g, chain, recs, n) == n) {
        for (k = 0; k < n; k++) {
            dw4_object o;
            if (dw4_object_from_record(&o, &g, &recs[k]) == 0) {
                if (o.mo) {
                    fields += o.mo->nfields;
                    if (!seen[o.mo - dw4_metaobjects]) {
                        seen[o.mo - dw4_metaobjects] = 1;
                        classes++;
                    }
                }
                obj++;
                dw4_object_free(&o);
            }
            dw4_igb_record_free(&recs[k]);
        }
    }
    free(seen);
    free(recs);
    dw4_igb_close(&g);
    *nobj = obj;
    *nfield = fields;
    *nclass = classes;
    return 0;
}

/* --- update: the one engine function ported so far -------------------------------------------------
 *
 * `dw4_object_init_header` is a verbatim port of `igObject_InitHeader` (`0x2fef20`).  Running it on
 * a scratch buffer each frame is the pointer-model's "one ported function" test: the header word it
 * produces must be the base igObject vtable and the flags must read `...1`.  On a 32-bit guest the
 * engine writes it into every instance; here it is verified and then the loop advances the frame
 * clock (the app object's `+0xe8` counter in `FUN_0025a580`, which the real loop increments). */
static int engine_frame(unsigned frame, uint32_t *last_header, uint32_t *last_flags)
{
    uint8_t scratch[16];
    uint32_t hdr, flags;

    memset(scratch, 0, sizeof(scratch));
    dw4_object_init_header(scratch);
    memcpy(&hdr, scratch, 4);
    memcpy(&flags, scratch + 4, 4);
    *last_header = hdr;
    *last_flags = flags & 0x7fffu;
    (void)frame;
    return 0;
}

/* --- boot: the engine's own main, phase by phase --------------------------------------------------
 *
 * `FUN_002595e0` (the game's `main`) is undecompiled, but the call graph is mapped in
 * `docs/engine/engine-boot.md` (finding #502) and every callee on the manager path is decompiled
 * and byte-matched in the decompilation repo.  This runs the boot in the engine's own order and
 * constructs the parts the port has a model for:
 *
 *   phase                 engine call            port
 *   --------------------  ---------------------  ----------------------------------------------
 *   process/argv setup    0x259a20 / 0x259cd0    no argv model yet
 *   core init             0x2d16a0               represented (matched in the decomp; it builds a
 *                                                928-byte engine core object, not modelled yet)
 *   app object            0x234900 / 0x234d70    app config struct (not yet)
 *   managers              0x1a1ae0 / 0x1a7cc0 / ** constructed here **
 *                         0x1a67c0
 *   frame object          0x1007e0 / 0x238110   frame counter at `+0xe8`
 *   loop                  0x25a580 / 0x25a8c0   update/present split
 *   shutdown              0x25a330 / 0x234b90 / not yet
 *                         0x2d1770
 *
 * The manager trio is the engine's Insight core: `main` acquires the current core (`FUN_002f8a20`),
 * releases the old manager, calls the class's `_Create` and stores the result in the class's
 * global.  Each `_Create` is `igMetaObject_RunStaticInit(<Class>_Register)` followed by
 * `igMetaObject_CreateInstance(<Class> MetaObject, owner)`; both are already matched in the decomp
 * (`0x1a1ae0`/`0x1a7cc0`/`0x1a67c0`), so the port reproduces exactly that: allocate an instance of
 * the class's reflected size, run `igObject_InitHeader` on it, stamp its vtable.  It is
 * `igMetaObject_CreateInstance` at the semantic level -- the port's object model is the schema the
 * decompilation recovered, so no guest MetaObject pointer is needed to identify the class. */
typedef struct {
    const char *cls;       /* the class whose MetaObject global the engine's `_Create` uses */
    uint32_t    global;    /* the guest global `main` stores the constructed manager in */
    uint32_t    via;       /* the matched `_Create` function that built it */
} boot_manager;

/* `main`'s three manager constructions, in order (finding #503).  The globals are the ones the
 * disassembly stores to: `sw v0,0x2718(at)` after `jal 0x1a1ae0`, etc. */
static const boot_manager boot_managers[3] = {
    { "igEnbayaContextPool",             0x562718u, 0x001a1ae0u },
    { "igAnimationCombinerBoneInfoPool", 0x562528u, 0x001a7cc0u },
    { "igAnimationStatePool",            0x562540u, 0x001a67c0u },
};

/* The guest's frame object (`*(0x57dc50)`, 0xf0 bytes, created lazily by 0x1007e0/0x238110), whose
 * `+0xe8` word `FUN_0025a580` increments every tick. */
#define DW4_FRAME_OBJECT_SIZE 0xf0u
#define DW4_FRAME_COUNTER_OFF 0xe8u

/* The fields `FUN_0025a580` writes each tick (finding #506), kept after the frame object is freed
 * so the boot report can print the values the engine actually produced. */
typedef struct {
    uint32_t counter;       /* the peak `+0xe8` value seen during a tick (always 1) */
    float    f94, f98, f9c, a0;
    uint8_t  b5, b5c, b5e, ba8, bb4, bd5;
} frame_fields;

typedef struct {
    void    *manager[3];    /* one instance per boot_managers row */
    uint8_t *app;           /* the app object `FUN_0025a580` gates on (`+0x18` must be non-NULL) */
    uint8_t *frame;         /* the frame object while a tick holds it */
    uint32_t ticks;         /* how many ticks acquired the frame context */
    frame_fields last;      /* the last tick's fields, for the report */
} boot_state;

/* `igMetaObject_CreateInstance` (`0x2fda40`), semantically: allocate the class's instance size,
 * run the header init, stamp the class vtable.  The port's schema is the recovered reflection, so
 * the class is named rather than addressed. */
static void *create_instance(const dw4_metaobject *mo)
{
    void *p;

    if (!mo || mo->size == 0)
        return NULL;
    p = calloc(1, mo->size);
    if (!p)
        return NULL;
    dw4_object_init_header(p);
    if (mo->vtable) {
        uint32_t vt = mo->vtable;
        memcpy(p, &vt, 4);
    }
    return p;
}

static void put_u32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static void put_f32(uint8_t *p, float v) { memcpy(p, &v, 4); }

/* `FUN_0025a580`'s frame tick: gate on the app's `+0x18` (0x25a594), then lazily create the frame
 * object (`0x1007e0`/`0x238110`), run the per-frame field setup at `0x25a5f0` (`+0xe8` = 1,
 * `+0x94`/`+0x98`/`+0x9c` = 0.1f, `+0xa0` = 1.0f, `+0x5e`/`+0xa8` = 1, `+0x5c`/`+5`/`+0xb4`/
 * `+0xd5` = 0), and release the context (finding #506): `+0xe8` is decremented back to 0 and the
 * object's refs are released and it is freed, so the frame context is **one-shot** -- acquire,
 * run, release, every tick.  The values are snapshotted for the report before the free. */
static uint32_t frame_tick(boot_state *b)
{
    uint8_t *fr;

    if (!b->app || *(void **)(b->app + 0x18) == NULL)
        return 0;
    fr = (uint8_t *)calloc(1, DW4_FRAME_OBJECT_SIZE);
    if (!fr)
        return 0;
    b->frame = fr;
    put_u32(fr + DW4_FRAME_COUNTER_OFF, 1);
    fr[0x5c] = 0;
    fr[0x5e] = 1;
    fr[5] = 0;
    fr[0xb4] = 0;
    fr[0xd5] = 0;
    fr[0xa8] = 1;
    put_f32(fr + 0x94, 0.1f);
    put_f32(fr + 0x98, 0.1f);
    put_f32(fr + 0x9c, 0.1f);
    put_f32(fr + 0xa0, 1.0f);
    b->last.counter = 1;
    b->last.f94 = 0.1f;
    b->last.f98 = 0.1f;
    b->last.f9c = 0.1f;
    b->last.a0 = 1.0f;
    b->last.b5 = fr[5];
    b->last.b5c = fr[0x5c];
    b->last.b5e = fr[0x5e];
    b->last.ba8 = fr[0xa8];
    b->last.bb4 = fr[0xb4];
    b->last.bd5 = fr[0xd5];
    b->ticks++;
    put_u32(fr + DW4_FRAME_COUNTER_OFF, 0);   /* the one-shot release (0x25a63c..0x25a6c8) */
    free(fr);
    b->frame = NULL;
    return b->last.counter;
}

static int engine_boot(boot_state *b)
{
    unsigned i;

    memset(b, 0, sizeof(*b));
    printf("  boot: FUN_002595e0 (the game's main, 0x2595e0)\n");
    printf("    phase core init   0x2d16a0  (matched in the decomp; builds a 928-byte core object)\n");
    printf("    phase app object  0x234900/0x234d70\n");
    for (i = 0; i < 3; i++) {
        const dw4_metaobject *mo = dw4_metaobject_find(boot_managers[i].cls);
        uint32_t hdr = 0, flags = 0;
        b->manager[i] = create_instance(mo);
        if (b->manager[i]) {
            memcpy(&hdr, b->manager[i], 4);
            memcpy(&flags, (uint8_t *)b->manager[i] + 4, 4);
        }
        printf("    manager %-32s @0x%06x via 0x%06x: %s size 0x%x, "
               "+0 = 0x%06x, flags = 0x%x\n",
               boot_managers[i].cls, boot_managers[i].global, boot_managers[i].via,
               b->manager[i] ? "created" : "MISSING", mo ? mo->size : 0, hdr, flags & 0x7fffu);
        if (!b->manager[i])
            return -1;
    }
    /* the app object's `+0x18` is the frame-context source `FUN_0025a580` gates on; the real
     * initialiser is `0x234900`/`0x234d70`, so the port builds a minimal one and points `+0x18`
     * at the first manager (any non-NULL value passes the gate) */
    b->app = (uint8_t *)calloc(1, 0x40);
    if (b->app)
        memcpy(b->app + 0x18, &b->manager[0], sizeof(b->manager[0]));
    printf("    app object: %s, +0x18 = %s (FUN_0025a580's gate)\n",
           b->app ? "constructed" : "MISSING",
           (b->app && *(void **)(b->app + 0x18)) ? "set" : "NULL");
    printf("    phase frame object 0x1007e0/0x238110 (counter at +0xe8, size 0x%x)\n",
           DW4_FRAME_OBJECT_SIZE);
    return 0;
}

static void engine_boot_shutdown(boot_state *b)
{
    unsigned i;

    for (i = 0; i < 3; i++)
        free(b->manager[i]);
    free(b->app);
    free(b->frame);
    b->manager[0] = b->manager[1] = b->manager[2] = NULL;
    b->app = NULL;
    b->frame = NULL;
}

/* --- present: merge the loaded geometry and draw one frame ------------------------------------------ */

typedef struct {
    float *pos, *nrm, *uv;
    uint32_t *tris;
    uint32_t nv, nt;
} meshbuf;

typedef struct {
    char name[128];
    float m[16];
    int32_t ids[16];         /* pack attr ids (capture_scene --pack); empty = join by name */
    int nids;
} capture_row;

/* A live scene capture (finding #487): one row per placed node -- the model's DCC name and its world
 * matrix.  The pack has no placement (finding #484), so without this every mesh sits at the origin. */
static capture_row *load_capture(const char *path, uint32_t *nout)
{
    FILE *fp = fopen(path, "r");
    capture_row *rows = NULL;
    uint32_t n = 0, cap = 0;
    char line[8192];
    *nout = 0;
    if (!fp)
        return NULL;
    while (fgets(line, sizeof(line), fp)) {
        char *fld[6], *p = line;
        capture_row r;
        int nf = 0;
        memset(&r, 0, sizeof(r));
        while (nf < 6 && p && *p && *p != '\n') {
            fld[nf++] = p;
            p = strchr(p, '\t');
            if (p)
                *p++ = 0;
        }
        if (nf < 2)
            continue;
        snprintf(r.name, sizeof(r.name), "%s", fld[0]);
        if (sscanf(fld[1], "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                   &r.m[0], &r.m[1], &r.m[2], &r.m[3], &r.m[4], &r.m[5], &r.m[6], &r.m[7],
                   &r.m[8], &r.m[9], &r.m[10], &r.m[11], &r.m[12], &r.m[13], &r.m[14],
                   &r.m[15]) != 16)
            continue;
        if (nf >= 5 && fld[4][0]) {
            char *q = fld[4];
            while (*q && r.nids < 16) {
                char *end;
                long v = strtol(q, &end, 0);
                if (end == q)
                    break;
                r.ids[r.nids++] = (int32_t)v;
                q = end;
                if (*q == ',')
                    q++;
                else
                    break;
            }
        }
        if (n == cap) {
            cap = cap * 2 + 64;
            rows = (capture_row *)realloc(rows, (size_t)cap * sizeof(*rows));
        }
        if (rows)
            rows[n++] = r;
    }
    fclose(fp);
    *nout = n;
    return rows;
}

/* Append one mesh instance to the merged buffer, transformed by `mm` (NULL = identity). */
static int append_mesh(const dw4_scene *sc, uint32_t mi, const float *mm, meshbuf *m)
{
    const dw4_scene_mesh *g = &sc->mesh[mi];
    const uint8_t *p = (const uint8_t *)dw4_scene_host(sc, g->positions);
    const uint8_t *n = (const uint8_t *)dw4_scene_host(sc, g->normals);
    const uint8_t *u = (const uint8_t *)dw4_scene_host(sc, g->uvs);
    uint32_t *t = NULL, nts = 0, k;
    const char *why = NULL;

    if (!p || dw4_scene_tris(sc, g, &t, &nts, &why) != 0)
        return 0;                         /* an unresolvable mesh is skipped, not fatal */
    m->pos = (float *)realloc(m->pos, (size_t)(m->nv + g->num_verts) * 3 * sizeof(float));
    m->nrm = (float *)realloc(m->nrm, (size_t)(m->nv + g->num_verts) * 3 * sizeof(float));
    m->uv  = (float *)realloc(m->uv,  (size_t)(m->nv + g->num_verts) * 2 * sizeof(float));
    m->tris = (uint32_t *)realloc(m->tris, (size_t)(m->nt + nts) * 3 * sizeof(uint32_t));
    if (!m->pos || !m->nrm || !m->uv || !m->tris) {
        free(t);
        return -1;
    }
    for (k = 0; k < g->num_verts; k++) {
        float x = rdf(p + 12 * k), y = rdf(p + 12 * k + 4), z = rdf(p + 12 * k + 8);
        float nx = 0, ny = 0, nz = 0;
        if (n) {
            nx = rdf(n + 12 * k);
            ny = rdf(n + 12 * k + 4);
            nz = rdf(n + 12 * k + 8);
        }
        if (mm) {
            m->pos[3 * (m->nv + k)] = mm[0] * x + mm[1] * y + mm[2] * z + mm[12];
            m->pos[3 * (m->nv + k) + 1] = mm[4] * x + mm[5] * y + mm[6] * z + mm[13];
            m->pos[3 * (m->nv + k) + 2] = mm[8] * x + mm[9] * y + mm[10] * z + mm[14];
            {
                float ax = nx, ay = ny, az = nz;
                nx = mm[0] * ax + mm[1] * ay + mm[2] * az;
                ny = mm[4] * ax + mm[5] * ay + mm[6] * az;
                nz = mm[8] * ax + mm[9] * ay + mm[10] * az;
            }
        } else {
            m->pos[3 * (m->nv + k)] = x;
            m->pos[3 * (m->nv + k) + 1] = y;
            m->pos[3 * (m->nv + k) + 2] = z;
        }
        {
            float len = sqrtf(nx * nx + ny * ny + nz * nz);
            if (len > 1e-9f) { nx /= len; ny /= len; nz /= len; }
        }
        m->nrm[3 * (m->nv + k)] = nx;
        m->nrm[3 * (m->nv + k) + 1] = ny;
        m->nrm[3 * (m->nv + k) + 2] = nz;
        /* UVs are object-space and are not transformed; a mesh with no UV stream gets (0,0) */
        m->uv[2 * (m->nv + k)] = u ? rdf(u + 8 * k) : 0.0f;
        m->uv[2 * (m->nv + k) + 1] = u ? rdf(u + 8 * k + 4) : 0.0f;
    }
    for (k = 0; k < nts; k++) {
        m->tris[3 * (m->nt + k)] = t[3 * k] + m->nv;
        m->tris[3 * (m->nt + k) + 1] = t[3 * k + 1] + m->nv;
        m->tris[3 * (m->nt + k) + 2] = t[3 * k + 2] + m->nv;
    }
    m->nv += g->num_verts;
    m->nt += nts;
    free(t);
    return 0;
}

static int merge_scene(const dw4_scene *sc, const capture_row *cap, uint32_t ncap, meshbuf *m,
                       uint32_t limit)
{
    uint32_t i, j;
    memset(m, 0, sizeof(*m));
    if (cap) {
        /* One instance per capture row: a stage places the same model many times, and each row is
         * a placement (findings #484/#487).  Collapsing by mesh name (one instance per mesh) is
         * what left the host frame a fragment of the stage. */
        for (i = 0; i < ncap; i++)
            for (j = 0; j < sc->nmesh; j++) {
                const dw4_scene_mesh *g = &sc->mesh[j];
                int hit;
                if (cap[i].nids) {
                    int k;
                    hit = 0;
                    for (k = 0; k < cap[i].nids; k++)
                        if ((int32_t)g->attr_id == cap[i].ids[k]) {
                            hit = 1;
                            break;
                        }
                } else {
                    hit = g->name && strcmp(g->name, cap[i].name) == 0;
                }
                if (hit && append_mesh(sc, j, cap[i].m, m) != 0)
                    return -1;
            }
        return 0;
    }
    if (limit == 0 || limit > sc->nmesh)
        limit = sc->nmesh;
    for (i = 0; i < limit; i++)
        if (append_mesh(sc, i, NULL, m) != 0)
            return -1;
    return 0;
}

int dw4_engine_run(const dw4_engine_opts *o)
{
    dw4_mount mnt;
    dw4_igfile f;
    dw4_scene sc;
    dw4_fb fb;
    dw4_window *win = NULL;
    dw4_vk *vk = NULL;      /* --vulkan: present through a Vulkan swapchain instead of SDL */
    dw4_gl_layer *overlay=NULL;
    int previous_gpu_policy=dw4_gpu_policy_required();
    dw4_gl *gl = NULL;
    float viewneg[16];
    int have_neg = 0;
    meshbuf mb;
    boot_state boot;
    capture_row *cap = NULL;
    uint32_t ncap = 0;
    uint32_t nobj = 0, nfield = 0, nclass = 0;
    uint32_t hdr = 0, flags = 0;
    float cam_view[16];
    int have_view = 0;
    int frames = o->frames > 0 ? o->frames : 1;
    int forever = o->frames <= 0;      /* --frames 0: run until the window closes (a live session) */
    int w = o->w > 0 ? o->w : 1280;
    int h = o->h > 0 ? o->h : 960;
    const char *out_dir = o->out_dir ? o->out_dir : ".";
    double t0, t1;
    int i, rc = 0;

    dw4_light sun;
    /* The same legible placeholder rig the asset renderer uses: the game's light values are
     * runtime-only (finding #499), so this keeps a host frame readable, not authentic.  A caller
     * rig (`--ambient`/`--light`/`--lights`) replaces it, for the GL path too. */
    float amb_builtin[3] = { 0.22f, 0.22f, 0.25f };
    const float *amb = o->ambient ? o->ambient : amb_builtin;
    const dw4_light *rig = o->lights;
    int nrig = o->nlights;
    int gl_fit = 0;                    /* --gl with no camera: fit each frame, like the software path */
    uint8_t *tex_rgba = NULL;
    dw4_tex tex;
    int have_tex = 0;

    memset(&tex, 0, sizeof(tex));
    memset(&fb, 0, sizeof(fb));        /* so the `done:` cleanup is safe before fb_init */
    printf("dw4 host: booting\n");
    printf("  platform seam: %u interface(s), %u still a stub\n",
           dw4_platform_ifaces(), dw4_platform_status(0));

    if (engine_boot(&boot) != 0) {
        fprintf(stderr, "  boot: could not construct the managers\n");
        engine_boot_shutdown(&boot);
        return 1;
    }

    memset(&mnt, 0, sizeof(mnt));
    memset(&f, 0, sizeof(f));
    if (dw4_mount_open(&mnt, o->roms) != 0) {
        fprintf(stderr, "  cannot mount %s\n", o->roms);
        return 1;
    }
    if (dw4_igfile_open_stage_ref(&f, &mnt, o->stage, o->ref) != 0) {
        fprintf(stderr, "  cannot open %s ref %u\n", o->stage, o->ref);
        dw4_mount_close(&mnt);
        return 1;
    }
    printf("  stage %s [ref %u]: %zu bytes\n", o->stage, o->ref, dw4_igfile_size(&f));

    if (build_objects(dw4_igfile_data(&f), dw4_igfile_size(&f), &nobj, &nfield, &nclass) != 0)
        fprintf(stderr, "  object graph: not an igBinary pack\n");
    else
        printf("  object graph: %u object(s) over %u type(s), %u reflected field(s)\n",
               nobj, nclass, nfield);

    if (dw4_scene_load(&sc, dw4_igfile_data(&f), dw4_igfile_size(&f)) != 0) {
        fprintf(stderr, "  scene: not a loadable pack\n");
        dw4_igfile_close(&f);
        dw4_mount_close(&mnt);
        return 1;
    }
    printf("  scene: %u mesh(es), %u node(s), %u scene graph(s)\n", sc.nmesh, sc.nnode, sc.ngraph);

    if (o->use_camera) {
        float cw[16];
        int node = dw4_scene_camera(&sc, o->camera, cw, cam_view);
        if (node < 0) {
            fprintf(stderr, "  camera: no igCamera %s in %s\n",
                    o->camera ? o->camera : "(stage)", o->stage);
            dw4_scene_close(&sc);
            dw4_igfile_close(&f);
            dw4_mount_close(&mnt);
            engine_boot_shutdown(&boot);
            return 1;
        }
        have_view = 1;
        printf("  camera %-20s node %d at (%8.3f %8.3f %8.3f)\n",
               sc.node[node].name ? sc.node[node].name : "-", node,
               (double)cw[12], (double)cw[13], (double)cw[14]);
    }

    cap = o->scene_tsv ? load_capture(o->scene_tsv, &ncap) : NULL;
    if (o->scene_tsv)
        printf("  capture %s: %u placed node(s)\n", o->scene_tsv, ncap);

    if (merge_scene(&sc, cap, ncap, &mb, 0) != 0 || mb.nv == 0) {
        fprintf(stderr, "  no geometry to draw\n");
        free(cap);
        dw4_scene_close(&sc);
        dw4_igfile_close(&f);
        dw4_mount_close(&mnt);
        return 1;
    }
    printf("  merged geometry: %u vertices, %u triangles\n", mb.nv, mb.nt);

    if (dw4_fb_init(&fb, w, h) != 0) {
        rc = 1;
        goto done;
    }
    dw4_gpu_policy_begin(!o->software && (o->gl || (o->window && !o->headless)));
    if (o->window) {
        int order;
        if (o->vulkan) {
            /* the same present path the render tool uses (src/vk_present.c); with --headless the
             * backend initialises the loader and a device only, which is what the suite checks */
            vk = dw4_vk_open(w, h, "dw4", o->headless ? 1 : 0);
            if (vk) {
                char gpu[128], fmt[64];
                int swz = 0;
                dw4_vk_report(vk, gpu, sizeof(gpu), fmt, sizeof(fmt), &swz);
                printf("  vulkan: %s via %s (%s)%s\n",
                       o->headless ? "device only (no surface)" : "presenting", gpu, fmt,
                       swz ? " [R/B swizzled]" : "");
            } else {
                fprintf(stderr, "  vulkan: unavailable, falling back to SDL\n");
            }
        }
        if (!vk) {
            win = dw4_window_open(w, h, "dw4", o->headless);
            printf("  window: SDL2 %s, %dx%d %s\n",
                   dw4_window_built() ? "compiled in" : "not compiled in", w, h,
                   o->headless ? "(headless/dummy)" : (win ? "(visible)" : "(open failed)"));
            /* present a test colour and read it back: a wrong SDL pixel format shows red as blue in
             * the window while the PNG from the same buffer is right (that happened once). */
            order = dw4_window_order_ok(win);
            printf("  window: pixel order %s\n",
                   order == 1 ? "ok (R,G,B,A preserved)"
                              : (order == 0 ? "WRONG (the present path reorders the channels)"
                                            : "not checked"));
        }
    }

    if(dw4_gpu_policy_required() && o->window && !o->headless && !win && !vk){
        dw4_gpu_policy_fail("stage hardware presentation unavailable");rc=1;goto done;
    }
    /* the ported engine header init, once, so the boot reports what the engine writes at +0/+4 */
    engine_frame(0, &hdr, &flags);
    printf("  igObject_InitHeader: +0 = 0x%06x, +4 flags = 0x%x\n", hdr, flags);

    /* a default rig, since the light values are runtime-only (finding #499) */
    if (!rig) {
        memset(&sun, 0, sizeof(sun));
        sun.type = DW4_LIGHT_DIRECTIONAL;
        sun.dir[0] = 0.42f; sun.dir[1] = -0.62f; sun.dir[2] = -0.66f;
        sun.diffuse[0] = sun.diffuse[1] = sun.diffuse[2] = 0.78f;
        sun.att_const = 1.0f;
        rig = &sun;
        nrig = 1;
    }
    dw4_render_set_ambient(amb[0], amb[1], amb[2]);
    dw4_render_set_lights(rig, nrig);
    dw4_render_set_fog(o->fog);

    /* an optional texture for the GL path, from a texture pack's own name (the mesh -> texture
     * binding is a load-time assignment, #485, so the caller names one) */
    if ((o->gl || dw4_gpu_policy_required()) && o->texname) {
        char afs[4096];
        dw4_igfile tf;
        dw4_texpack tp;
        snprintf(afs, sizeof(afs), "%s/NDMW.AFS", o->roms);
        if (dw4_igfile_open_afs(&tf, afs, o->texentry ? o->texentry : 625) == 0) {
            if (dw4_texpack_open(&tp, dw4_igfile_data(&tf), dw4_igfile_size(&tf)) == 0) {
                const dw4_texpack_tex *t = dw4_texpack_find(&tp, o->texname);
                if (t) {
                    tex_rgba = (uint8_t *)malloc((size_t)t->w * t->h * 4);
                    if (tex_rgba && dw4_texpack_rgba(&tp, t->image_id, t->clut_id, tex_rgba) == 0) {
                        tex.rgba = tex_rgba;
                        tex.w = (int)t->w;
                        tex.h = (int)t->h;
                        have_tex = 1;
                        printf("  texture %s: %ux%u from entry %u\n", t->name, t->w, t->h,
                               o->texentry ? o->texentry : 625);
                    } else {
                        fprintf(stderr, "  texture: decode of %s failed\n", o->texname);
                    }
                } else {
                    fprintf(stderr, "  texture: no %s in entry %u\n", o->texname,
                            o->texentry ? o->texentry : 625);
                }
                dw4_texpack_close(&tp);
            }
            dw4_igfile_close(&tf);
        } else {
            fprintf(stderr, "  texture: cannot open %s\n", afs);
        }
    }

    /* the engine's own camera when supplied (the renderer's projection divides by +z, so the view's
     * third row is negated, exactly as the render command does) */
    if (have_view || o->view) {
        const float *src = have_view ? cam_view : o->view;
        int k;
        memcpy(viewneg, src, sizeof(viewneg));
        for (k = 0; k < 4; k++)
            viewneg[8 + k] = -viewneg[8 + k];
        have_neg = 1;
        dw4_render_set_view(viewneg, o->fov > 0 ? o->fov : DW4_SCENE_CAMERA_FOV,
                            o->aspect > 0 ? o->aspect : dw4_scene_camera_aspect(w, h));
    }
    if ((o->gl || dw4_gpu_policy_required()) && !o->software) {
        /* With no view the software path fits the geometry each frame; the GPU path does the same,
         * so `--gl` no longer requires a camera. */
        if (!have_neg)
            gl_fit = 1;
        gl = dw4_gl_open(w, h);
        printf("  gl: %s, %dx%d offscreen FBO%s\n",
               dw4_gl_built() ? (gl ? dw4_gl_info(gl) : "context FAILED") : "not compiled in",
               w, h, gl ? "" : " (software fallback)");
    }

    if(dw4_gpu_policy_required()){
        overlay=dw4_gl_layer_open(w,h);
        if(!gl || !overlay || dw4_gpu_policy_error()[0]){dw4_gpu_policy_fail("stage GPU preparation");rc=1;goto done;}
    }
    t0 = now_ms();
    double fps_ema = 0.0;               /* the smoothed frame rate for the `--fps` readout */
    double frame_prev = 0.0;            /* the previous frame's start, so the rate includes present */
    for (i = 0; forever || i < frames; i++) {
        char path[4096];
        float tint[3] = { 0.92f, 0.90f, 0.86f };
        float yaw = 0.5f + (float)(i * o->spin * 3.14159265 / 180.0);
        uint32_t h2 = 0, f2 = 0;
        double nowm;

        /* update: FUN_0025a580 advances the frame object's counter */
        engine_frame((unsigned)i, &h2, &f2);
        frame_tick(&boot);
        /* present: FUN_0025a8c0 draws */
        if (gl) {
            float fv[16];
            const float *gview = viewneg;
            float gfov = o->fov > 0 ? o->fov : DW4_SCENE_CAMERA_FOV;
            float gaspect = o->aspect > 0 ? o->aspect : dw4_scene_camera_aspect(w, h);
            if (gl_fit) {
                dw4_render_fit_view((const uint8_t *)mb.pos, mb.nv, yaw, 0.32f, fv, &gfov,
                                    &gaspect);
                gview = fv;
            }
            if (dw4_gl_render(gl, &fb, mb.pos, mb.nrm, mb.uv, mb.tris, mb.nv, mb.nt, gview,
                              gfov, gaspect, amb, rig, nrig, tint,
                              have_tex ? &tex : NULL) != 0)
                {dw4_gpu_policy_fail("stage mesh draw");rc=1;goto done;}
        } else {
            dw4_fb_clear(&fb, 18, 22, 30);
            dw4_render_mesh_n(&fb, (const uint8_t *)mb.pos, (const uint8_t *)mb.nrm, NULL,
                              mb.nv, mb.tris, mb.nt, yaw, 0.32f, tint, NULL);
        }
        if (!win || o->headless) {
            snprintf(path, sizeof(path), "%s/frame_%04d.png", out_dir, i);
            if (dw4_png_write(path, fb.rgba, fb.w, fb.h) != 0)
                rc = 1;
        } else {
            path[0] = '\0';
        }
        if (o->fps != 0 && (o->fps == 1 || vk || (win && !o->headless))) {
            /* the *interval between frames*, not the draw time: a counter that excludes the
             * present reads the draw cost (~250 fps) while the display shows 60 */
            nowm = now_ms();
            if (frame_prev > 0.0) {
                double dt = nowm - frame_prev;
                if (dt > 0.0) {
                    double inst = 1000.0 / dt;
                    fps_ema = fps_ema > 0.0 ? fps_ema * 0.9 + inst * 0.1 : inst;
                }
            }
            frame_prev = nowm;
            if (fps_ema > 0.0){
                if(dw4_gpu_policy_required()){
                    if(dw4_render_fps_gpu(overlay,&fb,fps_ema)){dw4_gpu_policy_fail("stage FPS draw");rc=1;goto done;}
                }else dw4_render_fps(&fb,fps_ema);
            }
        }
        if (vk) {
            if (dw4_vk_present(vk, &fb) < 0){dw4_gpu_policy_fail("stage Vulkan presentation");rc=1;goto done;}
            if (!dw4_vk_pump(vk))
                break;
        } else if (win) {
            if(dw4_window_present(win,&fb)<0){dw4_gpu_policy_fail("stage SDL presentation");rc=1;goto done;}
            if (!dw4_window_pump(win, NULL))
                break;
        }
        /* the game ticks at 60 Hz, not at the display's own refresh */
        if (win || vk)
            frame_pace(t0, i, o->fps_lock);
    }
    t1 = now_ms();
    if (win && !o->headless)
        printf("  ran %d frame(s) in %.1f ms (%.2f ms/frame) -> window (frames shown live)\n",
               i, t1 - t0, (t1 - t0) / (i > 0 ? i : 1));
    else
        printf("  ran %d frame(s) in %.1f ms (%.2f ms/frame) -> %s/frame_%04d.png\n",
               i, t1 - t0, (t1 - t0) / (i > 0 ? i : 1), out_dir, i > 0 ? i - 1 : 0);

    printf("  update: FUN_0025a580 x %d, frame context acquire/release per tick, "
           "+0xe8 peak = %u, +0x94 = %.2f, +0xa0 = %.2f, +0x5e = %u, +0xa8 = %u\n",
           i, boot.last.counter, (double)boot.last.f94, (double)boot.last.a0,
           boot.last.b5e, boot.last.ba8);
done:
    if(dw4_gpu_policy_error()[0])fprintf(stderr,"stage graphics: %s\n",dw4_gpu_policy_error());
    if(getenv("DW4_GPU_POLICY_TRACE"))fprintf(stderr,"GPU policy CPU audit: UI %llu layer %llu mesh %llu fill %llu composite %llu\n",
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_UI),(unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_LAYER),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_MESH),(unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_FILL),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_COMPOSITE));
    dw4_gl_layer_close(overlay);
    if (gl)
        dw4_gl_close(gl);
    if (win)
        dw4_window_close(win);
    dw4_vk_close(vk);
    if (fb.rgba || fb.z)
        dw4_fb_free(&fb);
    free(cap);
    free(mb.pos);
    free(mb.nrm);
    free(mb.uv);
    free(mb.tris);
    free(tex_rgba);
    dw4_scene_close(&sc);
    dw4_igfile_close(&f);
    dw4_mount_close(&mnt);
    engine_boot_shutdown(&boot);
    dw4_gpu_policy_begin(previous_gpu_policy);
    return rc;
}

/* --------------------------------------------------------------- the boot (front-end) ---------- */

/* A vertical gradient, written straight to the framebuffer: the title screen's own dark field. */
static void fill_vgrad(dw4_fb *fb, const uint8_t c0[3], const uint8_t c1[3])
{
    if(dw4_gpu_policy_cpu(DW4_CPU_FILL))return;
    int x, y;
    for (y = 0; y < fb->h; y++) {
        float t = fb->h > 1 ? (float)y / (float)(fb->h - 1) : 0.0f;
        uint8_t r = (uint8_t)(c0[0] + (c1[0] - c0[0]) * t);
        uint8_t g = (uint8_t)(c0[1] + (c1[1] - c0[1]) * t);
        uint8_t b = (uint8_t)(c0[2] + (c1[2] - c0[2]) * t);
        uint8_t *row = fb->rgba + (size_t)y * fb->w * 4;
        for (x = 0; x < fb->w; x++) {
            row[4 * x + 0] = r; row[4 * x + 1] = g; row[4 * x + 2] = b; row[4 * x + 3] = 255;
        }
    }
}

/* An untextured quad (the title band, the cursor): the renderer's glyph primitive with no texture. */
static void engine_ui_triangles(dw4_fb *fb,dw4_gl_layer *gpu,const float vertices[][4],unsigned n,const uint8_t rgba[3][4])
{
    if(dw4_gpu_policy_required()){
        dw4_ui_draw draw[2]={{0}};
        for(unsigned t=0;t<n;t++){
            draw[t].stq=1;draw[t].blend=1;
            for(unsigned v=0;v<3;v++){
                memcpy(draw[t].v[v],vertices[t*3+v],4*sizeof(float));draw[t].v[v][4]=1;
                memcpy(draw[t].rgba[v],rgba[v],4);
            }
        }
        if(!gpu || dw4_gl_layer_ui(gpu,fb,draw,(int)n))dw4_gpu_policy_fail("front-end primitive draw");
    }else for(unsigned t=0;t<n;t++)dw4_render_ui_tri(fb,vertices[t*3],vertices[t*3+1],vertices[t*3+2],rgba,NULL,1);
}
static void ui_quad(dw4_fb *fb,dw4_gl_layer *gpu, float x0, float y0, float x1, float y1, const uint8_t rgba[3][4])
{
    float v0[4] = { x0, y0, 0.0f, 0.0f }, v1[4] = { x1, y0, 0.0f, 0.0f };
    float v2[4] = { x1, y1, 0.0f, 0.0f }, v3[4] = { x0, y1, 0.0f, 0.0f };
    float vertices[6][4];memcpy(vertices[0],v0,sizeof v0);memcpy(vertices[1],v1,sizeof v1);
    memcpy(vertices[2],v2,sizeof v2);memcpy(vertices[3],v0,sizeof v0);memcpy(vertices[4],v2,sizeof v2);memcpy(vertices[5],v3,sizeof v3);
    engine_ui_triangles(fb,gpu,vertices,2,rgba);
}

/* A triangle (the menu cursor): the renderer's UI primitive. */
static void ui_tri(dw4_fb *fb,dw4_gl_layer *gpu, float x0, float y0, float x1, float y1, float x2, float y2,
                   const uint8_t rgba[3][4])
{
    float a[4] = { x0, y0, 0.0f, 0.0f }, b[4] = { x1, y1, 0.0f, 0.0f };
    float c[4] = { x2, y2, 0.0f, 0.0f };
    float vertices[3][4];memcpy(vertices[0],a,sizeof a);memcpy(vertices[1],b,sizeof b);memcpy(vertices[2],c,sizeof c);
    engine_ui_triangles(fb,gpu,vertices,1,rgba);
}

static void engine_font(dw4_fb *fb,dw4_gl_layer *gpu,const dw4_fefont *font,float x,float y,float scale,
    const char *text,const uint8_t rgba[3][4])
{
    if(dw4_gpu_policy_required()){
        if(dw4_fefont_draw_gpu(gpu,fb,font,x,y,scale,text,rgba)<0)dw4_gpu_policy_fail("front-end font draw");
    }else dw4_fefont_draw(fb,font,x,y,scale,text,rgba);
}

/* Draw the title: the pack's own geometry as a faint backdrop over the dark field, the game's own
 * glyphs for the rows, and a cursor on the selected one.  `native_ui` = the recovered UI tree
 * (`dw4_frontui`, the pack's own logo/copyright/rows) is drawn separately, so the hand-placed
 * glyph rows and the placeholder title are skipped -- the recovered layout takes their place. */
static void draw_title(dw4_fb *fb,dw4_gl_layer *gpu, const dw4_fefont *font, const dw4_title_menu *menu,
                       const meshbuf *mb, float yaw, int frame, int layer, int native_ui)
{
    static const uint8_t grad0[3] = { 10, 12, 28 }, grad1[3] = { 2, 3, 9 };
    const uint8_t white[3][4] = { {128,128,128,128},{128,128,128,128},{128,128,128,128} };
    const uint8_t dim[3][4]   = { {96,100,116,128},{96,100,116,128},{96,100,116,128} };
    const uint8_t cursor[3][4]= { {150,150,150,128},{150,150,150,128},{150,150,150,128} };
    float tint[3] = { 0.34f, 0.38f, 0.62f };
    int k;

    /* `layer` = the pack-derived front-end layer was drawn underneath: it already carries the dark
     * field and the backdrop, so only the interactive rows go on top of it. */
    if (!layer) {
        fill_vgrad(fb, grad0, grad1);
        if (mb && mb->nv)
            dw4_render_mesh_n(fb, (const uint8_t *)mb->pos, (const uint8_t *)mb->nrm, NULL,
                              mb->nv, mb->tris, mb->nt, yaw, 0.32f, tint, NULL);
    }
    if (native_ui)
        return;                          /* the recovered UI tree draws the logo, rows and cursor */
    if (!font || !font->have)
        return;

    /* the title, in the game's own font — the pack layer already carries the logo art, so it is
     * drawn only for the placeholder title (no layer) */
    if (!layer) {
        const char *t = "DIGIMON WORLD 4";
        float tw = 0.0f, th = 0.0f;
        dw4_fefont_size(font, t, 1.6f, &tw, &th);
        engine_font(fb,gpu, font, (fb->w - tw) * 0.5f, fb->h * 0.16f, 1.6f, t, white);
    }
    for (k = 0; k < menu->nrow; k++) {
        float rw = 0.0f, rh = 0.0f;
        /* placed where the captured menu's own rows sit (x 210..430, y 254..342 at 640x448), so the
         * port's interactive rows take their place in the captured layer */
        float x = fb->w * 0.323f;
        float y = fb->h * 0.565f + k * (fb->h * 0.116f);
        dw4_fefont_size(font, menu->row[k].label, 1.6f, &rw, &rh);
        if (k == menu->sel) {
            /* the game's own selection cursor: a chevron just left of the row (the captured menu
             * draws a `>` before the selected one), so the port's live selection reads the same */
            float cx = x - 26.0f, cy = y + rh * 0.5f;
            ui_tri(fb,gpu, cx, cy - 10.0f, cx, cy + 10.0f, cx + 11.0f, cy, cursor);
            ui_quad(fb,gpu, cx, cy - 2.0f, cx + 9.0f, cy + 2.0f, cursor);
        }
        engine_font(fb,gpu, font, x, y, 1.6f, menu->row[k].label,
                        k == menu->sel ? white : dim);
    }
    (void)frame;
}

/* The Option screen (the manual's two settings).  A translucent panel over the title, a chevron on the
 * highlighted row, `< value >` on the right; the layout is the port's until the real screen is captured. */
static void draw_options(dw4_fb *fb,dw4_gl_layer *gpu, const dw4_fefont *font, int sel, const dw4_options *op)
{
    static const char *const label[2] = { "Dungeon camera", "Light" };
    const char *value[2];
    const uint8_t panel[3][4] = { {4,4,12,124},{4,4,12,124},{4,4,12,124} };
    const uint8_t rule[3][4]  = { {128,128,128,110},{128,128,128,110},{128,128,128,110} };
    const uint8_t white[3][4] = { {128,128,128,128},{128,128,128,128},{128,128,128,128} };
    const uint8_t dim[3][4]   = { {96,100,116,128},{96,100,116,128},{96,100,116,128} };
    const float sc = (float)fb->h / 448.0f, fs = 1.3f * sc;
    float px0 = 110.0f * sc, px1 = 530.0f * sc, py0 = 150.0f * sc, py1 = 300.0f * sc;
    int k;

    value[0] = op->camera_far ? "Far" : "Near";
    value[1] = op->light_hard ? "Hard" : "Soft";
    ui_quad(fb,gpu, px0, py0, px1, py1, panel);
    ui_quad(fb,gpu, px0, py0, px1, py0 + 2.0f * sc, rule);
    ui_quad(fb,gpu, px0, py1 - 2.0f * sc, px1, py1, rule);
    if (!font || !font->have)
        return;
    {
        const char *t = "Option";
        float tw = 0.0f, th = 0.0f;

        dw4_fefont_size(font, t, fs, &tw, &th);
        engine_font(fb,gpu, font, (px0 + px1 - tw) * 0.5f, py0 + 10.0f * sc, fs, t, white);
    }
    for (k = 0; k < 2; k++) {
        char buf[32];
        float lw = 0.0f, lh = 0.0f, vw = 0.0f, vh = 0.0f;
        float y = py0 + (56.0f + 44.0f * (float)k) * sc;

        snprintf(buf, sizeof buf, "< %s >", value[k]);
        dw4_fefont_size(font, label[k], fs, &lw, &lh);
        dw4_fefont_size(font, buf, fs, &vw, &vh);
        if (k == sel) {
            float cx = px0 + 18.0f * sc, cy = y + lh * 0.5f;

            ui_tri(fb,gpu, cx, cy - 9.0f * sc, cx, cy + 9.0f * sc, cx + 10.0f * sc, cy, white);
        }
        engine_font(fb,gpu, font, px0 + 40.0f * sc, y, fs, label[k], k == sel ? white : dim);
        engine_font(fb,gpu, font, px1 - 30.0f * sc - vw, y, fs, buf, k == sel ? white : dim);
    }
}

typedef struct {
    dw4_mount *mount;
    const char *roms;
    int species, fps, audio, light_hard;
    int call_slot;           /* >= 0: "Call Digimon" - load this memory-card slot instead of creating a character */
    int row;                 /* the player model: shinka row 0..15 (a created starter, or the called character's form) */
    char weapon[32];         /* the called character's equipped weapon asset ("" = the starter's created-card weapon) */
    char name[9], stage[64];
} lobby_load_context;

/* The front-end screens (title trails, title UI, Option, Game Start) decode while the opening movie plays: one worker runs the four
 * opens in turn, since scene decoding is one walk at a time and the movie decodes no scene. */
typedef struct {const dw4_mount *mount;dw4_frontlayer *layer;dw4_frontui *ui;dw4_frontopt *opt;dw4_frontchr *chr;} front_screens;
static void *open_front_screens(void *arg)
{
    front_screens *f=arg;
    f->layer=dw4_frontlayer_open(f->mount);
    f->ui=dw4_frontui_open(f->mount);
    f->opt=dw4_frontopt_open(f->mount);
    f->chr=dw4_frontchr_open(f->mount);
    return f;
}

/* DW4_FRAME_TRACE=1: milliseconds since the opening movie returned, at each step of the title's set-up. */
static double boot_mark_origin;
#define BOOT_MARK(label) do{if(getenv("DW4_FRAME_TRACE")){double m_=now_ms();if(boot_mark_origin<=0)boot_mark_origin=m_;fprintf(stderr,"  boot: %7.0f ms  %s\n",m_-boot_mark_origin,label);}}while(0)

static void menu_sound_action(void *user, const char *model, const char *action)
{
    if (getenv("DW4_SOUND_TRACE")) {
        const char *sound = dw4_frontaudio_action_sound(*(dw4_frontaudio **)user, model, action);
        fprintf(stderr, "  sound: %s %s -> %s\n", model, action, sound ? sound : "(none)");
    }
    dw4_frontaudio_action(*(dw4_frontaudio **)user, model, action);
}

/* The Game Start slot screen's LoadIntf2 scene (DW4_SCENE_TITLE): opened when the slot screen opens and warmed until the base panels
 * and the Create/Call window are up, so its first frame is the settled Create/Call screen. Returns 0 (scene open), 1 (no save
 * library or scene: the character UI's own Create/Call window stays) or -1 (GPU policy failure). */
static int slot_scene_open(dw4_mount *mnt,dw4_playerrecords *players,dw4_be_state *state,dw4_gl_layer *gpu,dw4_frontaudio **audio,
                           dw4_savescene **scene,dw4_memcard **card,uint64_t *ns)
{
    char dir[420],err[512]="";
    if(dw4_memcard_default_directory(dir,sizeof dir,1) || !(*card=dw4_memcard_open(dir))){
        printf("  title: slot screen: the save library is unavailable; Call Digimon is disabled\n");return 1;
    }
    dw4_savescene_source src={players,state,0,*card,DW4_SCENE_TITLE};
    *scene=dw4_savescene_open(mnt,&src,err,sizeof err);
    if(!*scene){fprintf(stderr,"  title: slot screen: %s\n",err);dw4_memcard_close(*card);*card=NULL;return 1;}
    dw4_savescene_set_sound(*scene,menu_sound_action,audio);
    if(gpu && !dw4_savescene_use_gpu(*scene,gpu)){dw4_gpu_policy_fail("slot screen GPU sharing");return -1;}
    *ns=16666667ULL;
    int warm=dw4_savescene_warm(*scene,*ns,16666667ULL,900);
    if(warm<0){
        fprintf(stderr,"  title: slot screen: %s\n",dw4_savescene_error(*scene));
        dw4_savescene_close(*scene);*scene=NULL;dw4_memcard_close(*card);*card=NULL;return 1;
    }
    *ns+=(uint64_t)warm*16666667ULL;
    printf("  title: slot screen: Create/Call window (LoadIntf2 control state 3) up after %d ticks\n",warm);
    return 0;
}

static void *prepare_lobby(void *arg)
{
    lobby_load_context *c = arg;
    if (dw4_frontend_game_start(c->roms, c->stage, sizeof c->stage, c->fps)) return NULL;
    dw4_lobby *l = dw4_lobby_open_row_stage(c->mount, c->row, c->name, "stagML11", 0, c->weapon);
    dw4_lobby_set_light(l, c->light_hard);
    if (l && dw4_lobby_prepare_audio(l, c->mount)) {
        dw4_lobby_close(l); return NULL;
    }
    return l;
}

typedef struct {
    dw4_mount *mount;dw4_hubruntime_source source;
    char destination[128],error[512];int32_t point;int light_hard;
} hub_load_context;
static void *prepare_hub(void *arg)
{
    hub_load_context *c=arg;
    return dw4_hubruntime_prepare(c->mount,&c->source,c->destination,c->point,c->light_hard,c->error,sizeof c->error);
}
static int engine_clear_fb(dw4_fb *fb,dw4_gl_layer *gpu,uint8_t r,uint8_t g,uint8_t b)
{
    if(dw4_gpu_policy_required()){
        if(!gpu || dw4_gl_layer_clear(gpu,fb,r,g,b,255)){dw4_gpu_policy_fail("main framebuffer clear");return -1;}
    }else dw4_fb_clear(fb,r,g,b);
    return 0;
}
static void draw_loading(dw4_fb *fb,dw4_gl_layer *gpu, dw4_frontui *art, const dw4_fefont *font,
                         unsigned frame, int failed)
{
    static const uint8_t white[3][4] = {{128,128,128,128},{128,128,128,128},{128,128,128,128}};
    const int resident = gpu && !dw4_gl_layer_defer(gpu, fb, 1);   /* card, text and counter share one resident frame */
    if(engine_clear_fb(fb,gpu,0,0,0)){if(resident)dw4_gl_layer_defer(gpu,fb,0);return;}
    if (art) {
        dw4_frontui_loading_sample(art, (uint64_t)frame * 1000000000ULL / 60);
        dw4_frontui_draw(art, fb, -1);
    }
    if (failed || !art) {
        const char *text = failed==2 ? "Destination not available" : failed ? "Cannot load destination" : "Now Loading";
        float scale = fb->h / 448.0f, width;
        dw4_fefont_size(font, text, scale, &width, NULL);
        engine_font(fb,gpu, font, (fb->w-width)*0.5f, fb->h*0.44f, scale, text, white);
        if (failed) {
            text = failed==2 ? "Circle: Back" : "Cross: Retry    Circle: Back";
            dw4_fefont_size(font, text, scale, &width, NULL);
            engine_font(fb,gpu, font, (fb->w-width)*0.5f, fb->h*0.54f, scale, text, white);
        }
    }
    if (resident) {
        if (dw4_fps_overlay > 0 && !dw4_fps_overlay_drawn && !dw4_render_fps_gpu(gpu, fb, dw4_fps_overlay))
            dw4_fps_overlay_drawn = 1;
        dw4_gl_layer_defer(gpu, fb, 0);
    }
}

/* Script services share simulation time, never presentation time. */
typedef struct { dw4_lobby *lobby; const char *name; uint64_t token; dw4_scriptservices *sd; } session_window;
typedef struct {
    dw4_frontaudio **audio;
    uint64_t audio_origin,world_ns;
    dw4_scriptservices *sd;
    dw4_scriptengine *scripts;
    dw4_be_state *state;
    dw4_simulation *simulation;
    dw4_title_services *title;
    dw4_mount *mount;
    dw4_filelist *files;
    dw4_stageobjects *objects;
    dw4_controllers *controllers;
    dw4_dialogue *dialogue;
    dw4_playerrecords *players;
    dw4_databases *databases;
    session_window window[5];
    dw4_statusscene status_scene;dw4_statusstats status_stats;
    dw4_modelview *status_models;dw4_statuspage_input status_input;
    dw4_gl_layer *status_gpu;
    dw4_stageinput stage_input;dw4_stagetravel travel;
    dw4_modelview *travel_models;dw4_hubruntime *hub;
    dw4_padrepeat status_analog,status_digital;
    dw4_lobby_control_state held_world;dw4_lobby_presentation_state held_presentation;
    dw4_lobby_ai_state held_ai;dw4_lobby_npc_state held_npc[3];int status_held;

} session_services;
static int session_sound(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
static int health_fields(const char *v,int32_t fields[4])
{
    if(!v)return -1;
    unsigned count=0;
    while(v && *v && count<4) {
        if(v[0]!='I' || v[1]!='<')return -1;
        const char *start=v+2;char *end;errno=0;long value=strtol(start,&end,10);
        if(end==start || *end!='>' || errno || value<INT32_MIN || value>INT32_MAX)return -1;
        fields[count++]=(int32_t)value;v=end+1;
        if(!*v)break;
        if(*v++!='/')return -1;
    }
    return *v || count<2?-1:(int)count;
}
static int session_gameram(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    session_services *s=user;
    if(n>=4 && a[3].type==DW4_SCRIPT_STRING &&
       (!strcmp(a[3].string,"ADDHP") || !strcmp(a[3].string,"ADDMP"))) {
        int32_t values[4]={0,0,0,-1};int fields;
        if(strcmp(method,"sd") || n!=5 || a[4].type!=DW4_SCRIPT_STRING || !a[4].string ||
           strlen(a[4].string)!=a[4].length || !s->window[0].lobby)goto bad;
        fields=health_fields(a[4].string,values);
        if(fields<0 || values[0]!=0 || (!strcmp(a[3].string,"ADDMP") && fields==4))goto bad;
        if(dw4_playerhealth_add(s->players,values[0],!strcmp(a[3].string,"ADDMP"),values[1],values[3],error,cap))return -1;
        dw4_playerhealth h;
        if(dw4_playerhealth_restore(s->players,values[0],&h,error,cap) || dw4_lobby_health_publish(s->window[0].lobby,&h))return -1;
        *r=(dw4_script_value){0};return 0;
    }
    return dw4_playerrecords_service(s->players,method,a,n,r,error,cap);
bad:snprintf(error,cap,"lobby ADDHP/ADDMP requires valid player-zero integer fields");return -1;
}
static dw4_statusview_context session_status_view(session_services *s,int player)
{return (dw4_statusview_context){.sd=s->sd,.engine=s->scripts,.players=s->players,.scope=dw4_scriptengine_scope(s->scripts),.player=player};}
static int session_layer_visible(const session_services *s,const char *name)
{
    for(size_t i=0;i<dw4_stageobjects_layers(s->objects);i++)if(!strcmp(dw4_stageobjects_layer(s->objects,i),name))return dw4_stageobjects_layer_visible(s->objects,i);
    return 0;
}
static int session_world_layer_visible(void *user,const char *name)
{return session_layer_visible(user,name);}
static int session_status_generators_available(const session_services *s)
{
    /* The lobby adapter publishes no generator Work. Do not claim support for
     * spawn jobs in another scene until their actual owner is integrated. */
    if(!s->objects)return 0;
    for(size_t i=0;i<dw4_stageobjects_count(s->objects);i++)if(!strcmp(dw4_stageobject_class(dw4_stageobjects_at(s->objects,i)),"beGeneraterInfo"))return 0;
    return 1;
}
static int session_status_input(void *user,int32_t player,dw4_statuspage_input *out)
{session_services *s=user;if(player)return -1;*out=dw4_stageinput_slot(&s->stage_input,player)==4?(dw4_statuspage_input){0}:s->status_input;return 0;}
static int session_status_appearance(void *user,int32_t player,char *error,size_t cap)
{
    session_services *s=user;dw4_property_folder *f=dw4_playerrecords_get(s->players,"GETPLAYER",player);
    if(player || !f)return -1;
    /* WEAPONRECNO caches the first equipped weapon's database row. The
     * appearance refresh owns power socket zero, not that database index. */
    const char *model=dw4_property_string_at(f,"POWERSOCKETNAME",0);
    int rc=dw4_lobby_weapon(s->window[0].lobby,s->mount,model?model:"",error,cap);
    if(!rc){dw4_lobby_player_state appearance;
        if(dw4_lobby_player(s->window[0].lobby,&appearance))return -1;
        printf("  STATUS appearance: player %d weapon %s pose %s\n",player,appearance.weapon_asset,appearance.motion);
    }
    return rc;
}
static int session_status_scene(void *user,const dw4_statusscene_command *c,char *error,size_t cap)
{
    session_services *s=user;dw4_lobby *l=s->window[0].lobby;
    if(!l)return -1;
    if(c->op==DW4_STATUSSCENE_HOLD){
        int hold=!strcmp(c->value,"1");
        if(hold){
            if(dw4_lobby_control(l,&s->held_world) || dw4_lobby_presentation(l,&s->held_presentation) || dw4_lobby_ai(l,&s->held_ai))return -1;
            for(unsigned i=0;i<3;i++)if(dw4_lobby_npc(l,i,&s->held_npc[i]))return -1;
            s->status_held=1;
        }else{
            dw4_lobby_control_state world;dw4_lobby_presentation_state presentation;dw4_lobby_ai_state ai;
            if(!s->status_held || dw4_lobby_control(l,&world) || dw4_lobby_presentation(l,&presentation) || dw4_lobby_ai(l,&ai) ||
               presentation.tick!=s->held_presentation.tick || world.material_ticks!=s->held_world.material_ticks ||
               memcmp(world.camera_world,s->held_world.camera_world,sizeof world.camera_world) || ai.events!=s->held_ai.events || ai.choices!=s->held_ai.choices){
                snprintf(error,cap,"STATUS world/AI clock advanced while held");return -1;
            }
            for(unsigned i=0;i<3;i++){
                dw4_lobby_npc_state npc;if(dw4_lobby_npc(l,i,&npc) || memcmp(npc.position,s->held_npc[i].position,sizeof npc.position) || npc.yaw!=s->held_npc[i].yaw || npc.speed!=s->held_npc[i].speed){
                    snprintf(error,cap,"STATUS NPC %u moved while held",i);return -1;
                }
            }
            s->status_held=0;
        }
        dw4_lobby_status(l,hold);return 0;
    }
    if(c->op==DW4_STATUSSCENE_HEALTH){
        dw4_playerhealth h;if(c->player || dw4_playerhealth_restore(s->players,c->player,&h,error,cap))return -1;
        return dw4_lobby_health_publish(l,&h);
    }
    if(!strcmp(c->category,"GENERATER")){
        if(strcmp(c->key,"ONFREEZE") && strcmp(c->key,"OFFREEZE"))return -1;
        if(!session_status_generators_available(s)){snprintf(error,cap,"STATUS requires the scene's active generator Work owner");return -1;}
        return 0; /* Retail ON/OFFFREEZE is a no-op when no Work exists. */
    }
    if(!strcmp(c->category,"LAYERCTL")){
        char value[96];snprintf(value,sizeof value,"%s/%s",c->name,c->value);
        dw4_statusview_context v=session_status_view(s,0);
        return dw4_statusui_call(&v,0,"LAYERCTL",NULL,-1,c->key,value,error,cap);
    }
    dw4_statusview_context v=session_status_view(s,0);
    return dw4_statusui_call(&v,0,c->category,c->name,-1,c->key,c->value,error,cap);
}
static int session_status_prepare(void *user,int32_t mode,int32_t player,dw4_menu_window **out,char *error,size_t cap)
{
    session_services *s=user;dw4_lobby *l=s->window[0].lobby;int32_t joined;
    if(mode || player || !l || !dw4_lobby_intro_done(l) || !s->status_models || !session_status_generators_available(s) ||
       dw4_property_number(dw4_playerrecords_get(s->players,"GETPLAYER",player),"ISUSE",&joined) || !(uint8_t)joined){
        snprintf(error,cap,"STATUS requires a joined player after lobby handoff");return -1;
    }
    s->status_scene=(dw4_statusscene){.players=s->players,.io=session_status_scene,.user=s};
    /* Clear the borrowed RAM link before replacing an owned Work, including on allocation failure. */
    if(dw4_subwindows_bind_work(dw4_dialogue_subwindows(s->dialogue),0,(dw4_handle){0}))return -1;
    dw4_statusstats_close(&s->status_stats);
    s->status_stats=(dw4_statusstats){.players=s->players,.sd=s->sd,.dialogue=s->dialogue,.name=dw4_databases_shinka_name,.database=s->databases};
    if(dw4_statusstats_bind(&s->status_stats,(dw4_handle){0}) ||
       dw4_subwindows_bind_work(dw4_dialogue_subwindows(s->dialogue),0,s->status_stats.work)){
        snprintf(error,cap,"STATUS Work allocation/binding failed");return -1;
    }
    dw4_statusmenu_context c={.gear={.view=session_status_view(s,player),.databases=s->databases,.stats=&s->status_stats,
        .input=session_status_input,.appearance=session_status_appearance,.user=s},.dialogue=s->dialogue};
    *out=dw4_statusmenu_window_open(&c);return *out?0:-1;
}
static int session_status_update(void *user,int32_t player,char *error,size_t cap)
{
    session_services *s=user;
    if(!s->status_scene.phase || player){snprintf(error,cap,"SUBWND UPDATE requires the active lobby STATUS owner");return -1;}
    return dw4_statusstats_refresh(&s->status_stats,player,error,cap);
}
static int session_status_preview(void *user,int32_t player,int on,char *error,size_t cap)
{
    session_services *s=user;
    if(!s->status_scene.phase || player){snprintf(error,cap,"SUBWND preview requires the active lobby STATUS owner");return -1;}
    return dw4_statusstats_compare(&s->status_stats,player,on,error,cap);
}
static void session_status_action(void *user,const char *model,const char *action)
{session_services *s=user;dw4_lobby_model_action(s->window[0].lobby,model,action);}
static int session_status_activate(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)mode;(void)player;session_services *s=user;return dw4_statusscene_freeze(&s->status_scene,error,cap);}
static int session_status_begin(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)mode;(void)player;session_services *s=user;return dw4_statusscene_enter(&s->status_scene,error,cap);}
static int session_status_end(void *user,int32_t mode,int32_t player,char *error,size_t cap)
{(void)mode;(void)player;session_services *s=user;int rc=dw4_statusscene_restore(&s->status_scene,error,cap);
    if(!rc){printf("  STATUS: root closed; world/NPC clocks preserved; health/HUD restored\n");}
    return rc;}
static int session_library(session_services *services,const char *stage,uint64_t scope)
{
    if(services->objects)return -1;
    dw4_stageobjects *objects=dw4_stageobjects_open();
    if(!objects)return -1;
    if(dw4_filelist_begin(services->files,services->scripts,stage,scope) ||
       dw4_filelist_shared(services->files) ||
       dw4_filelist_route_assets(services->files,dw4_stageobjects_route,objects) ||
       dw4_filelist_bind_layers(services->files,dw4_stageobjects_bind_layers,objects) ||
       dw4_stageobjects_publish(objects,services->sd,scope)) {
        fprintf(stderr,"session file-list: %s; native objects: %s\n",
            dw4_filelist_error(services->files),dw4_stageobjects_error(objects));
        dw4_stageobjects_close(objects);return -1;
    }
    char db_error[256];
    services->databases=dw4_databases_open(objects,db_error,sizeof db_error);
    if(!services->databases){
        fprintf(stderr,"session database: %s\n",db_error);
        dw4_scriptservices_remove_scope(services->sd,scope);
        dw4_stageobjects_close(objects);return -1;
    }
    if(dw4_databases_publish(services->databases,services->sd,scope)){
        dw4_databases_close(services->databases);services->databases=NULL;
        dw4_scriptservices_remove_scope(services->sd,scope);dw4_stageobjects_close(objects);return -1;
    }
    static const char *title_names[]={"j_startlogo","j_startmenu01","j_startmenu02","j_startback",
        "j_optionwin02","j_optioncursor11","j_optioncursor12","i_fadewn01"};
    static const char *window_names[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky",
        "p_agumon","p_vmon","p_girumon","p_dorumon","p_weregaru","p_hekabut","p_wargrey","p_angelr","p_beelzeb","p_alpha","p_bwargrey",
        "p_impdrafm","p_impdrapm","p_metalgaru","p_dukecrim","p_susanoo"};   /* the player's model controller: any of the sixteen forms */
    int title_scene=!strcmp(stage,"stagIS10");
    services->controllers=dw4_controllers_open(services->sd,scope,objects,
        title_scene?title_names:window_names,title_scene?8:21,
        &services->state->random,&services->state->action_rhythm,services->scripts);
    if(!services->controllers) {
        dw4_databases_close(services->databases);services->databases=NULL;
        dw4_scriptservices_remove_scope(services->sd,scope);
        dw4_stageobjects_close(objects);return -1;
    }
    services->dialogue=dw4_dialogue_open(services->sd,scope,objects);
    if(!services->dialogue) {
        dw4_databases_close(services->databases);services->databases=NULL;
        dw4_controllers_close(services->controllers);services->controllers=NULL;
        dw4_scriptservices_remove_scope(services->sd,scope);dw4_stageobjects_close(objects);return -1;
    }
    dw4_controllers_sample(services->controllers,(int64_t)services->world_ns);
    services->objects=objects;
    printf("  session file-list: %s; %zu resident packs; original func/boot complete\n",
        stage,dw4_filelist_count(services->files));
    size_t generator_infos=0;
    for(size_t i=0;i<dw4_stageobjects_count(objects);i++)generator_infos+=!strcmp(dw4_stageobject_class(dw4_stageobjects_at(objects,i)),"beGeneraterInfo");
    printf("  session generator roster: %zu authored infos\n",generator_infos);
    printf("  session native objects: %zu infos; %zu layers; %zu authored attachments\n",
        dw4_stageobjects_count(objects),dw4_stageobjects_layers(objects),dw4_stageobjects_attachments(objects));
    return 0;
}
static int session_reset(session_services *services)
{
    dw4_scriptengine_record_flags(services->scripts,0);
    if(dw4_scriptengine_reset_scene(services->scripts,services->sd))return -1;
    /* Retail manager cleanup precedes releasing borrowed controller owners. */
    dw4_gl_layer_close(services->status_gpu);services->status_gpu=NULL;
    dw4_modelview_close(services->status_models);services->status_models=NULL;
    if(services->window[0].lobby)dw4_lobby_native_ui(services->window[0].lobby,NULL);
    dw4_modelview_close(services->travel_models);services->travel_models=NULL;
    dw4_title_services_close(services->title);services->title=NULL;
    if(services->window[0].lobby){dw4_lobby_native_models(services->window[0].lobby,NULL,0);dw4_lobby_dialogue(services->window[0].lobby,NULL);}
    dw4_dialogue_close(services->dialogue);services->dialogue=NULL;
    dw4_statusstats_close(&services->status_stats);
    dw4_controllers_close(services->controllers);services->controllers=NULL;
    dw4_databases_close(services->databases);services->databases=NULL;
    dw4_stageobjects_close(services->objects);services->objects=NULL;
    memset(services->window,0,sizeof(services->window));
    if(!dw4_scriptservices_register(services->sd,0,"SOUND",NULL,-1,1,session_sound,services))return -1;
    if(!dw4_scriptservices_register(services->sd,0,"GAMERAM",NULL,-1,1,session_gameram,services))return -1;
    return dw4_scriptservices_register(services->sd,0,"STAGECTL",NULL,-1,1,dw4_stagetravel_service,&services->travel) &&
        dw4_scriptservices_register(services->sd,0,"PLAYERPOINT",NULL,-1,1,dw4_stagetravel_service,&services->travel)?0:-1;
}
static int session_window_call(void *user,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *r,char *error,size_t cap)
{
    session_window *w=user;dw4_script_value args[5];
    if(n<4 || n>5)return -1;
    memcpy(args,a,n*sizeof(*a));
    args[1]=(dw4_script_value){DW4_SCRIPT_STRING,0,w->name,strlen(w->name)};
    args[2]=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    int rc=dw4_lobby_window_service(w->lobby,method,args,n,r,error,cap);
    if(!rc && !strcmp(method,"sd")) {
        args[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"ISRUN",5};
        dw4_script_value state={0};
        if(!dw4_lobby_window_service(w->lobby,"querySD",args,4,&state,error,cap))
            dw4_scriptservices_active(w->sd,w->token,state.number!=0);
    }
    return rc;
}
static int session_sound(void *user,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *r,char *error,size_t cap)
{
    session_services *services=user;
    if(services->window[0].lobby)return dw4_lobby_sound_service(services->window[0].lobby,method,a,n,r,error,cap);
    return dw4_frontaudio_script_service(*services->audio,method,a,n,r,error,cap);
}
static int session_service(void *user,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *r,char *error,size_t cap)
{
    session_services *services=user;
    int player_result=dw4_playerrecords_call(services->players,method,a,n,r,error,cap);
    if(player_result>0)player_result=dw4_playertransactions_folder_call(services->players,method,a,n,r,error,cap);
    if(player_result<=0)return player_result;
    if(services->window[0].lobby){
        int material=dw4_lobby_material_call(services->window[0].lobby,method,a,n,r,error,cap);
        if(material<=0)return material;
    }
    if(!strcmp(method,"MsgBox")){*r=(dw4_script_value){0};return 0;}   /* the script's debug message box */
    if(!strcmp(method,"MDLisLive") && n==2) {
        dw4_script_value args[]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},a[0],a[1],
            {DW4_SCRIPT_STRING,0,"ISRUN",5}};
        return dw4_scriptservices_any(services->sd,args,4,r,error,cap);
    }
    if(!strcmp(method,"MDLisStatus") && n==3 && a[2].type==DW4_SCRIPT_STRING) {
        dw4_script_value args[]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},a[0],a[1],{DW4_SCRIPT_STRING,0,"CHECKSTATUS",11},a[2]};
        int rc=dw4_scriptservices_call(services->sd,"querySD",args,5,r,error,cap);
        if(!rc && r->type!=DW4_SCRIPT_NUMBER)*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
        return rc;
    }
    /* Normal creation selects bePoint01's entry zero; imported/re-entry
     * placement requires a separate session owner before admitting that path. */
    if(services->window[0].lobby && !strcmp(method,"PLAYERgetPos") && !n){
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};return 0;
    }
    if(!strcmp(method,"SYSgetLightMode") && !n) {
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,dw4_options_get()->light_hard,NULL,0};return 0;
    }
    dw4_scriptservices_scope(services->sd,dw4_scriptengine_scope(services->scripts));
    return dw4_scriptservices_call(services->sd,method,a,n,r,error,cap);
}
static int session_lobby_start(session_services *s,dw4_lobby *l,char *error,size_t cap)
{
    size_t flags_count;
    const uint8_t *flags=dw4_property_bytes(dw4_playerrecords_get(s->players,"GETCOMMON",0),"FLAG",&flags_count);
    if(!flags || flags_count!=sizeof s->state->flag)goto fail;
    memcpy(s->state->flag,flags,flags_count);
    dw4_scriptengine_record_flags(s->scripts,1);
    if(dw4_lobby_native_models(l,s->controllers,s->world_ns) || dw4_lobby_native_npcs(l,s->controllers,s->objects))goto fail;
    const char *name=dw4_property_string(dw4_playerrecords_get(s->players,"GETPLAYER",0),"DIGIMONNAME");
    int found=0;for(int i=0;name && i<16;i++)found|=!strcmp(name,dw4_lobby_model_name(i));
    if(!found || dw4_lobby_publish_player(l,s->sd,2,name) ||
       !dw4_scriptservices_register(s->sd,2,"MATCTRL",NULL,-1,1,dw4_lobby_material_service,l) ||
       !dw4_scriptservices_register(s->sd,2,"LIGHTCTRL",NULL,-1,1,dw4_lobby_light_service,l) ||
       !dw4_scriptservices_register(s->sd,2,"SWITCHCTRL",NULL,-1,1,dw4_stageobjects_switch_service,s->objects))goto fail;
    /* These managers have no matching infos in this prepared fresh lobby.
     * Reject a broader roster rather than replacing its consumers with no-ops. */
    for(size_t i=0;i<dw4_stageobjects_count(s->objects);i++) {
        const dw4_stageobject *o=dw4_stageobjects_at(s->objects,i);
        if(!strcmp(dw4_stageobject_class(o),"beNDMWPanelWazaInfo"))goto fail;
        const char *kind=dw4_stageobject_kind_string(o);
        if(kind && (!strcmp(kind,"KIND_ENEMY") || !strcmp(kind,"KIND_PLAYER2")))goto fail;
    }
    if(dw4_scriptservices_category(s->sd,"ENEMY") || dw4_scriptservices_category(s->sd,"PLAYER2") ||
       dw4_scriptservices_category(s->sd,"NDMWPANEL"))goto fail;
    dw4_lobby_services_sample(l,s->world_ns);
    if(dw4_filelist_start(s->files) || dw4_filelist_first(s->files)) {
        snprintf(error,cap,"original start/first: %.180s",dw4_filelist_error(s->files));return -1;
    }
    puts("  lobby: original scene start.lua -> first.lua; scene-owned actors/player/materials");return 0;
fail:snprintf(error,cap,"lobby startup has an unavailable owner or unsupported roster");return -1;
}
static void session_clock(void *user,uint64_t ns)
{
    session_services *services=user;
    services->world_ns=ns;
    if(services->hub)return; /* Its private VM/SD/model pump runs once below. */
    dw4_frontaudio *audio=*services->audio;
    dw4_frontaudio_set_clock(audio,ns);
    dw4_title_services_tick(services->title,ns);
    dw4_controllers_sample(services->controllers,(int64_t)ns);
    if(services->window[0].token)dw4_lobby_services_sample(services->window[0].lobby,ns);
    for(unsigned i=0;i<5;i++)if(services->window[i].token) {
        dw4_script_value a[]={ {DW4_SCRIPT_STRING,0,"MODELCTRL",9},
            {DW4_SCRIPT_NIL,0,NULL,0},{DW4_SCRIPT_NUMBER,0,NULL,0},
            {DW4_SCRIPT_STRING,0,"ISRUN",5} },r={0};char error[256];
        if(session_window_call(services->window+i,"querySD",a,4,&r,error,sizeof(error))) {
            fprintf(stderr,"session window: %s\n",error);services->simulation->failed=1;return;
        }
        dw4_scriptservices_active(services->sd,services->window[i].token,r.number!=0);
    }
    if(dw4_scriptservices_tick(services->sd,ns)) {
        services->simulation->failed=1;
        return;
    }
    uint64_t age=ns-services->audio_origin;
    dw4_frontaudio_tick(audio,(unsigned)(age/1000000000*60+(age%1000000000)*60/1000000000));
}
int dw4_engine_boot(const dw4_engine_opts *o, const char *input_script,
                    char *stage_out, size_t stage_cap)
{
    dw4_mount mnt;
    dw4_igfile f;
    dw4_scene sc;
    dw4_fb fb;
    dw4_window *win = NULL;
    dw4_vk *vk = NULL;
    meshbuf mb;
    boot_state boot;
    dw4_fefont font;
    dw4_title_menu menu;
    dw4_title_host title={0};
    dw4_frontlayer *flayer = NULL;
    dw4_frontui *fui = NULL;
    dw4_frontopt *fopt = NULL;       /* the Option screen's own window graphs (finding #724) */
    front_screens front = {0};
    dw4_loadjob *front_job = NULL;   /* the front-end screens decoding during the opening movie */
    dw4_loadjob *audio_job = NULL;   /* the title audio decode that runs during the opening movie */
    dw4_frontchr *fchr = NULL;       /* the Game Start slot screen (pack 806's panels and windows) */
    dw4_lobby *lobby = NULL;
    dw4_frontui *loading_art = NULL;
    dw4_gl *title_mesh=NULL;
    dw4_gl_layer *frame_gpu=NULL;
    dw4_loadjob *load_job = NULL;
    dw4_lobby *prepared_lobby = NULL;
    int load_ready = 0;
    double loading_start_ms = -1.0;
    lobby_load_context load_context = {0};
    int loading = 0, load_failed = 0, load_locked = 0;
    dw4_hubruntime *hub=NULL,*prepared_hub=NULL;
    dw4_loadjob *hub_job=NULL;dw4_frontui *hub_art=NULL;
    hub_load_context hub_context={0};
    int hub_loading=0,hub_ready=0,hub_failed=0,hub_locked=0;
    unsigned hub_frames=0;double hub_start_ms=-1;
    unsigned loading_frames = 0;
    dw4_frontaudio *audio = NULL;
    dw4_be_state script_state;
    dw4_scriptengine *scripts = NULL;
    dw4_simulation simulation;
    session_services services={.audio=&audio,.simulation=&simulation,.mount=&mnt,.state=&script_state};
    int logging_in = 0, lobby_frame = 0;
    dw4_input_state in, in_prev;
    dw4_input_state mates[3], mates_prev[3];   /* the pads of co-op players 2-4 (dw4/pads.h): read only while a hub runs */
    long long skip_ns = 0;          /* the opening skipped: the layer/UI clock runs this far ahead of the frame count */
    dw4_light sun;
    float amb_builtin[3] = { 0.22f, 0.22f, 0.30f };
    int w = o->w > 0 ? o->w : 1280, h = o->h > 0 ? o->h : 960;
    int frames = o->frames;
    const char *out_dir = o->out_dir ? o->out_dir : ".";
    int i, rc = 0, chose = 0, have_scene = 0, frames_run = 0;
    float ly_prev = 0.0f, lx_prev = 0.0f, yaw = 0.6f;
    int chr_species = -1;
    int name_hold_x = 0, name_hold_y = 0;
    int chr_open = 0, chr_sel = 0;     /* the slot screen is up / Create (0) or Call (1) */
    /* The slot screen: the title's LoadCtrl2/LoadIntf2 screens (the Create/Call window; Create's starter choice, name entry and
     * GAMESTART; Call's card chooser, data select, difficulty; the log-in prompt) run in their own scene over the stagIS13 pack. The
     * character UI (frontchr) keeps a fallback Create flow for a host without a save library. */
    dw4_savescene *call_scene = NULL;dw4_memcard *call_card = NULL;uint64_t call_ns = 0;
    int call_unavailable = 0, call_control = -1;   /* the slot scene could not open / its last control state */
    int call_created = 0;int32_t call_unique = 0;   /* the scene created the character (GAMESTART): its UNIQUE word */
    int call_sub = -1, call_species = -1, call_named = 0;   /* log transitions of the Create states */
    int call_slot = -1;                /* the card area being logged in (>= 0: Call Digimon, no new character) */
    int call_finished = 0;             /* the scene reported START: no further login animation, straight to the loading card */
    int call_difficulty = 0;           /* the difficulty row chosen on the Call screens */
    int call_row = -1;char call_weapon[32] = "";   /* the called character's player model row and equipped weapon */
    int opt_open = 0, opt_sel = 0;     /* the Option screen is up / its highlighted row */
    double t0, t1;
    int previous_gpu_policy=dw4_gpu_policy_required();

    memset(&fb, 0, sizeof(fb));
    memset(&mb, 0, sizeof(mb));
    memset(&sc, 0, sizeof(sc));
    memset(&f, 0, sizeof(f));
    memset(&mnt, 0, sizeof(mnt));
    memset(&font, 0, sizeof(font));
    memset(&menu, 0, sizeof(menu));
    dw4_input_init(&in);
    dw4_input_init(&in_prev);
    for (int k = 0; k < 3; k++) { dw4_input_init(&mates[k]); dw4_input_init(&mates_prev[k]); }

    printf("dw4 host: boot (front-end -> title)\n");
    printf("  platform seam: %u interface(s), %u still a stub\n",
           dw4_platform_ifaces(), dw4_platform_status(0));

    if (engine_boot(&boot) != 0) {
        fprintf(stderr, "  boot: could not construct the managers\n");
        engine_boot_shutdown(&boot);
        return -1;
    }
    if (dw4_mount_open(&mnt, o->roms) != 0) {
        fprintf(stderr, "  cannot mount %s\n", o->roms);
        engine_boot_shutdown(&boot);
        return -1;
    }

    dw4_gpu_policy_begin(!o->software && (o->gl || (o->window && !o->headless)));
    if(dw4_gpu_policy_required()){
        dw4_gl_layer *probe=dw4_gl_layer_open(1,1);
        if(!probe){dw4_gpu_policy_fail("hardware GPU initialization");rc=-1;goto done;}
        printf("  graphics policy: hardware GPU required (%s)\n",dw4_gl_layer_info(probe));
        dw4_gl_layer_close(probe);
    }

    /* The boot's window is opened *before* the front-end runs, because the opening FMV presents
     * into it: the FMV and the title are one window, so closing it during the movie ends the run
     * instead of a second window appearing at the title. */
    if (o->window) {
        if (o->vulkan) {
            vk = dw4_vk_open(w, h, "dw4", o->headless ? 1 : 0);
            if (!vk)
                fprintf(stderr, "  vulkan: unavailable, falling back to SDL\n");
        }
        if (!vk) {
            win = dw4_window_open(w, h, "dw4", o->headless);
            printf("  window: SDL2 %s %dx%d %s\n",
                   dw4_window_built() ? "compiled in" : "not compiled in", w, h,
                   o->headless ? "(headless/dummy)" : (win ? "(visible)" : "(open failed)"));
        }
    } else {
        printf("  window: offscreen %dx%d (no window; frames -> %s/frame_NNNN.png)\n", w, h, out_dir);
    }
    if (o->fps_lock > 0)
        printf("  frame lock: %d fps (the game's own tick; --fps-lock 0 for the display rate)\n",
               o->fps_lock);

    /* the front-end sequencer: power-on -> the title, stopping there for input */
    if(dw4_gpu_policy_required() && o->window && !win && !vk){dw4_gpu_policy_fail("hardware presentation unavailable");rc=-1;goto done;}
    /* The title's audio decode (about two seconds) runs on a worker while the opening movie plays. */
    if ((win || vk) && !o->headless) audio_job = dw4_loadjob_start(dw4_frontaudio_prepare_work, &mnt, 1);
    front.mount=&mnt;
    front_job = dw4_loadjob_start(open_front_screens, &front, 1);
    rc = dw4_frontend_boot(o->roms, &menu, stage_out, stage_cap,
                           o->window && !o->headless, o->fps, win, vk, input_script, o->skip_logos);
    if (rc == -2) {
        /* the user closed the window during the FMV: a clean exit, not an error */
        printf("  window closed during the opening FMV\n");
        rc = 0;
        goto done;
    }
    if (rc != 0) {
        rc=-1;goto done;
    }

    BOOT_MARK("movie returned");
    if (front_job) {dw4_loadjob_close(front_job);front_job=NULL;}   /* joins; the result is `front` */
    BOOT_MARK("front-end screens decoded (worker)");
    /* the game's own font, from the disc (bectext.igb), for the menu text */
    if (dw4_fefont_load(&font, o->roms) == 0) {
        printf("  font: %s %dx%d atlas, %d glyph(s) from bectext.igb\n",
               font.name[0] ? font.name : "font00.png", font.aw, font.ah, font.nglyph);
    } else {
        fprintf(stderr, "  font: bectext.igb did not decode; the title draws no text\n");
    }

    BOOT_MARK("font loaded");
    /* the title pack's own geometry as the backdrop (its 2D/additive layer is finding #610-#612) */
    memset(&sc, 0, sizeof(sc));
    if (dw4_igfile_open_stage_ref(&f, &mnt, "stagml11.igb", 0) == 0) {
        if (dw4_scene_load(&sc, dw4_igfile_data(&f), dw4_igfile_size(&f)) == 0 &&
            merge_scene(&sc, NULL, 0, &mb, 0) == 0 && mb.nv > 0) {
            have_scene = 1;
            printf("  backdrop: stagml11.igb [ref 0], %u mesh(es), %u triangles\n",
                   sc.nmesh, mb.nt);
        }
        dw4_igfile_close(&f);
    }
    if (!have_scene)
        printf("  backdrop: stagml11.igb unavailable; drawing the dark field only\n");

    BOOT_MARK("stagml11 backdrop decoded");
    /* The front-end trail layer, generated from the pack's own model controller (findings
     * #610/#614/#619): AREA.AFS entry 620's `j_startback` graph, its JOINTSET schedule and its
     * `sback00` texture.  No capture and no flag: the asset root supplies it. */
    flayer = front.layer;
    if (flayer)
        printf("  front-end layer: j_startback, %d mesh(es)%s\n", dw4_frontlayer_meshes(flayer),
               " (generated from AREA.AFS 620)");
    else
        fprintf(stderr, "  front-end layer: j_startback unavailable; the placeholder title stays\n");

    BOOT_MARK("front layer opened");    if (flayer && !o->software && (o->gl || (o->window && !o->headless))) {
        const char *gpu = dw4_frontlayer_enable_gpu(flayer, w, h);
        printf("  title trails: %s%s\n", gpu ? "GPU via " : "CPU (GPU unavailable)", gpu ? gpu : "");
    } else if (flayer) {
        printf("  title trails: CPU\n");
    }
    /* The recovered composition order (findings #609/#610/#632/#636): the static stagML11 backdrop
     * is composed UNDER the layer and the UI, through the same recovered title camera, not the
     * placeholder fit/spin the no-layer path uses.  Reported once so a check can pin it. */
    if (flayer && have_scene)
        printf("  front-end title: stagML11 backdrop composed under the layer"
               " (%u mesh(es), %u triangles) via the recovered camera\n", sc.nmesh, mb.nt);

    /* The title's own UI tree, also from AREA.AFS 620 (findings #632/#633): the `j_startlogo`
     * graph's `rogo`/`kenri` quads (logo.png / mojips.png) and the `j_startmenu01`/`02` rows, each
     * geometry's texture resolved through the pack's material chain.  No captured texture. */
    fui = front.ui;
    fopt = front.opt;
    fchr = front.chr;
    BOOT_MARK("front UI, option and character screens opened");
    if(dw4_gpu_policy_required() && (!flayer || !fui || !fopt || !fchr)){
        dw4_gpu_policy_fail("essential front-end assets unavailable");rc=-1;goto done;
    }
    dw4_frontchr_set_sound(fchr, menu_sound_action, &audio);
    BOOT_MARK("character screen sound bound");
    /* Resolve loading assets before any background scene walk begins. The
     * current scene loader allows one walk at a time; loading draws only sample
     * this resident graph while the worker prepares the destination. */
    {
        loading_art = dw4_frontui_open_loading(&mnt, "stagML11");
        if (!loading_art) fprintf(stderr, "  loading: original stage card unavailable; using text\n");
        if(loading_art && dw4_gpu_policy_required() && !dw4_frontui_enable_gpu(loading_art,w,h))
            dw4_gpu_policy_fail("loading card GPU unavailable");
    }
    if (!o->software && (o->gl || (o->window && !o->headless))) {
        const char *ug = dw4_frontui_enable_gpu(fui, w, h);
        const char *cg = dw4_frontchr_enable_gpu(fchr, w, h);
        const char *og = dw4_frontopt_enable_gpu(fopt, w, h);
        printf("  menus: title=%s, character=%s, options=%s\n",
               ug ? "GPU" : "CPU", cg ? "GPU" : "CPU", og ? "GPU" : "CPU");
    }
    if(dw4_gpu_policy_error()[0]){rc=-1;goto done;}
    if (fui) {
        dw4_fb probe;
        float rect[4], rect0[4];
        int t, ntex = dw4_frontui_textures(fui);
        printf("  front-end UI: %d item(s), %d texture(s):", dw4_frontui_items(fui), ntex);
        for (t = 0; t < ntex; t++)
            printf(" %s", dw4_frontui_texture_at(fui, t) ? dw4_frontui_texture_at(fui, t) : "-");
        printf("\n");
        printf("  front-end UI: logo=%s\n",
               dw4_frontui_logo_texture(fui) ? dw4_frontui_logo_texture(fui) : "-");
        /* the recovered title state: the game opens on the press-start screen (finding #605/#639) */
        printf("  front-end UI: state=press-start (%d visible item(s)); START -> menu\n",
               dw4_frontui_visible(fui));
        if (dw4_fb_init(&probe, w, h) == 0) {
            /* the recovered OPEN pop-in: at t = 0 the logo node's sequence scale is 0, so the quad
             * is degenerate -- then it settles to the resting rectangle. */
            dw4_frontui_set_engine(fui, 0);
            if (dw4_frontui_logo_rect(fui, &probe, rect0) == 0)
                printf("  front-end UI: logo rect at OPEN t=0 x %.1f..%.1f y %.1f..%.1f\n",
                       rect0[0], rect0[2], rect0[1], rect0[3]);
            dw4_frontui_set_engine(fui, 2000000000LL);   /* past the pop-in: the resting pose */
            if (dw4_frontui_logo_rect(fui, &probe, rect) == 0)
                printf("  front-end UI: logo rect x %.1f..%.1f y %.1f..%.1f (at %dx%d)\n",
                       rect[0], rect[2], rect[1], rect[3], w, h);
            dw4_fb_free(&probe);
        }
    } else {
        fprintf(stderr, "  front-end UI: AREA.AFS 620 title graphs unavailable; keeping the glyphs\n");
    }

    if (dw4_fb_init(&fb, w, h) != 0) {
        rc = -1;
        goto done;
    }
    if(dw4_gpu_policy_required()){
        frame_gpu=dw4_gl_layer_open(w,h);title_mesh=dw4_gl_open(w,h);
        if(!frame_gpu || !title_mesh){dw4_gpu_policy_fail("main/title GPU preparation");rc=-1;goto done;}
        dw4_gl_clear_color(title_mesh,0,0,0,255);
        /* The title layer and UI draw through the frame's own renderer so a title frame stays resident on the GPU. */
        if(flayer && !dw4_frontlayer_use_gpu(flayer,frame_gpu)){dw4_gpu_policy_fail("title layer GPU sharing");rc=-1;goto done;}
        if(fui && !dw4_frontui_use_gpu(fui,frame_gpu)){dw4_gpu_policy_fail("title UI GPU sharing");rc=-1;goto done;}
        if(fchr && !dw4_frontchr_use_gpu(fchr,frame_gpu)){dw4_gpu_policy_fail("character UI GPU sharing");rc=-1;goto done;}
        if(fopt && !dw4_frontopt_use_gpu(fopt,frame_gpu)){dw4_gpu_policy_fail("option UI GPU sharing");rc=-1;goto done;}
        if(loading_art && !dw4_frontui_use_gpu(loading_art,frame_gpu)){dw4_gpu_policy_fail("loading card GPU sharing");rc=-1;goto done;}
    }
    memset(&sun, 0, sizeof(sun));
    sun.type = DW4_LIGHT_DIRECTIONAL;
    sun.dir[0] = 0.42f; sun.dir[1] = -0.62f; sun.dir[2] = -0.66f;
    sun.diffuse[0] = sun.diffuse[1] = sun.diffuse[2] = 0.78f;
    sun.att_const = 1.0f;
    dw4_render_set_ambient(amb_builtin[0], amb_builtin[1], amb_builtin[2]);
    dw4_render_set_lights(&sun, 1);
    dw4_render_set_fog(NULL);

    double boot_fps_ema = 0.0;      /* hoisted: an EMA reset each frame is the instantaneous rate */
    double boot_frame_prev = 0.0;   /* the previous frame's start, so the rate includes the present */
    dw4_title_host_init(&title, dw4_options_get()->camera_far, dw4_options_get()->light_hard);
    title.sound_action = menu_sound_action; title.sound_user = &audio;
    dw4_frontui_bind_title(fui, &title);
    dw4_frontopt_bind_title(fopt, &title);
    if (audio_job) { audio = dw4_frontaudio_open_session_prepared(dw4_loadjob_close(audio_job)); audio_job = NULL; }
    else if ((win || vk) && !o->headless) audio = dw4_frontaudio_open_session(&mnt);
    BOOT_MARK("title audio opened");
    dw4_be_init(&script_state);
    dw4_padrepeat_init(&services.status_analog);dw4_padrepeat_init(&services.status_digital);
    services.travel.input=&services.stage_input;
    services.players=dw4_playerrecords_open();
    if(!services.players){rc=-1;goto done;}
    services.sd=dw4_scriptservices_open();
    if(!services.sd || !dw4_scriptservices_register(services.sd,0,"SOUND",NULL,-1,1,
                                                   session_sound,&services) ||
       !dw4_scriptservices_register(services.sd,0,"GAMERAM",NULL,-1,1,session_gameram,&services) ||
       !dw4_scriptservices_register(services.sd,0,"STAGECTL",NULL,-1,1,dw4_stagetravel_service,&services.travel) ||
       !dw4_scriptservices_register(services.sd,0,"PLAYERPOINT",NULL,-1,1,dw4_stagetravel_service,&services.travel)) {
        rc=-1;goto done;
    }
    scripts=dw4_scriptengine_open(&script_state,session_service,&services);
    services.scripts=scripts;
    services.files=dw4_filelist_open(&mnt);
    if(!scripts || !services.files){rc=-1;goto done;}
    dw4_scriptengine_filelist(scripts,services.files);
    if (!scripts) { rc=-1;goto done; }
    {
        if (session_library(&services,"stagIS10",1) ||
            (audio && dw4_scriptengine_queue_event(scripts,"snd_j_startback.lua"))) {
            fprintf(stderr,"session Lua: %s\n",dw4_scriptengine_error(scripts));
            rc=-1;goto done;
        }
    }
    if(flayer) {
        services.title=dw4_title_services_open_prepared(services.sd,1,&title,flayer,services.objects);
        if(!services.title){rc=-1;goto done;}
    }
    dw4_simulation_init(&simulation,scripts,&services,session_clock);
    BOOT_MARK("session library (stagIS10) and title services ready");
    /* Audio preroll decodes the title tracks synchronously. Start pacing only
     * after it finishes, or the opening races through frames to catch up with
     * time spent loading rather than presenting the blue traces at 60 Hz. */
    t0 = now_ms();
    double pace_origin = t0;
    BOOT_MARK("audio preroll done, title loop starts");
    double sched_due = 0.0;     /* live absolute pacing schedule (frame_pace_sched) */
    /* DW4_DEV_WARP="StagML12:0,StagML13:1" (profiling aid): after each arrival, wait DW4_DEV_WARP_FRAMES (default 900)
     * and queue the next stage change as the world's own exit would.  Unset = no effect. */
    const char *dev_warp = getenv("DW4_DEV_WARP");
    const char *dev_warp_frames_env = getenv("DW4_DEV_WARP_FRAMES");
    int dev_warp_frames = dev_warp_frames_env ? atoi(dev_warp_frames_env) : 900, dev_warp_wait = 0;
    double tr_tick = 0.0, tr_draw = 0.0, tr_present = 0.0, tr_post = 0.0, tr_draw_end = 0.0;   /* DW4_FRAME_TRACE phase sums (ms, this second) */
    int ui_first = 0;               /* the first frame the title UI actually draws (finding #640) */
    for (i = 0; frames <= 0 || i < frames; i++) {
        double iteration_start = now_ms();
        dw4_fps_overlay=(o->fps != 0 && (o->fps == 1 || vk || (win && !o->headless)) && dw4_gpu_policy_required())?boot_fps_ema:-1;
        dw4_fps_overlay_drawn=0;
        int stop = 0;
        int soft_stop = 0;
        long long ui_ns;            /* the title UI's own clock, offset past the layer's opening */
        long long eng_ns;           /* the layer's clock: frame time plus any skipped opening */
        float menu_lx, menu_ly;
        int ui_flash_frame = 0;     /* first frame the white flash (SQ_WTIN60) is drawn on */

        /* The layer's opening plays alone (finding #640): the game shows no title UI until the
         * 209-frame SQ_OPEN has finished, so the UI's own OPEN is timed from there rather than from
         * the boot.  At ui_ns 0 every UI node is still degenerate (scale 0), i.e. not yet drawn. */
        eng_ns = (long long)i * 1000000000LL / 60 + skip_ns;
        ui_ns = eng_ns;
        if (flayer) {
            ui_ns -= dw4_frontlayer_open_ns();
            if (ui_ns < 0)
                ui_ns = 0;
        }

        /* input: a scripted pad (a headless check) or the live window pad */
        if (!hub) for (int k = 0; k < 3; k++) { dw4_input_init(&mates[k]); dw4_input_init(&mates_prev[k]); }   /* outside a hub the extra pads are menu pads of player 1 */
        if (input_script) {
            dw4_input_script(&in, input_script, i);
            for (int k = 0; k < 3; k++) if (hub) dw4_input_script(&mates[k], o->pad_script[k], i);
            /* A scripted run still owns a real window when it is not headless: keep answering the compositor (no
             * "not responding" prompt) and honour its close request.  The events feed a scratch state, so the
             * script stays the only source of pad input. */
            if (!o->headless && (win || vk)) {
                dw4_input_state scratch;
                dw4_input_init(&scratch);
                stop = win ? !dw4_window_pump(win, &scratch) : !dw4_vk_pump_in(vk, &scratch);
                if (scratch.quit) stop = 1;
            }
        } else if (win)
            stop = !dw4_window_pump_mates(win, &in, hub ? mates : NULL);
        else if (vk)
            stop = !dw4_vk_pump_mates(vk, &in, hub ? mates : NULL);
        else {
            /* offscreen with no script: draw one frame, then stop (so a headless probe still gets a
             * frame with no capture, no window and no input) */
            if (i > 0) { frames_run = i; break; }
            soft_stop = 1;
        }

        if (in.quit)
            stop = 1;
        if (stop) { frames_run = i; break; }

        if ((win || vk) && !o->headless && !input_script) {
            uint64_t host=(uint64_t)(now_ms()*1000000.0);
            unsigned holds=simulation.holds;
            /* Focus changes are informational: simulation, presentation and
             * audio continue in the background. Manual/device holds persist. */
            if (in.disconnected) holds|=DW4_HOLD_DISCONNECT;
            else holds&=~DW4_HOLD_DISCONNECT;
            if (in.pause) holds^=DW4_HOLD_PAUSE;
            if (in.resume && !in.focus_lost) holds&=~DW4_HOLD_PAUSE;
            in.pause=in.resume=in.focus_pause=0;
            dw4_simulation_hold(&simulation,holds,host);
            if (!dw4_simulation_due(&simulation,host)) {
                if (simulation.holds) in_prev=in;
                i--;
                /* Pump and present held state without advancing any adapter. */
                if((win && dw4_window_present(win,&fb)<0) || (vk && dw4_vk_present(vk,&fb)<0)){
                    dw4_gpu_policy_fail("held-state presentation");rc=-1;goto done;
                }
                struct timespec idle={0,1000000};nanosleep(&idle,NULL);
                continue;
            }
        } else simulation.due=1; /* Deterministic frame-indexed headless checks. */
        float dialogue_x=0,dialogue_y=0,walk_x=0,walk_y=0;dw4_input_menu_axes(&in,&dialogue_x,&dialogue_y);dw4_input_walk_axes(&in,&walk_x,&walk_y);
        uint32_t directions=dw4_pad_directions(dialogue_x,dialogue_y);
        uint32_t digital=dw4_input_digital(&in);
        if(hub_loading) {
            /* Consume presentation cadence without advancing the session tick
             * or either VM. Loading wall time never becomes arrival time. */
            simulation.due=0;goto hub_load_update;
        }
        if(hub) {
            {   /* DW4_DEV_PLACE inside a connected hub (after DW4_DEV_WARP): frames counted from the hub's own start. */
                static int hub_placed=0;static unsigned hub_frames=0;const char *pl=getenv("DW4_DEV_PLACE");
                unsigned at=0;float x,y,z;
                if(pl && !hub_placed && ++hub_frames && sscanf(pl,"%u:%f,%f,%f",&at,&x,&y,&z)==4 && hub_frames>=at){
                    hub_placed=1;dw4_lobby_place_player(dw4_hubruntime_world(hub),x,y,z,getenv("DW4_DEV_YAW")?(float)atof(getenv("DW4_DEV_YAW")):0);
                    fprintf(stderr,"dev place (hub): %g %g %g\n",x,y,z);
                }
            }
            uint32_t pressed=(in.cross && !in_prev.cross?0x4000u:0)|(in.circle && !in_prev.circle?0x2000u:0)|
                (in.square && !in_prev.square?0x8000u:0)|(in.start && !in_prev.start?8u:0);
            dw4_hubruntime_input(hub,walk_x,walk_y,directions,digital,pressed);
            dw4_hubruntime_input_mates(hub,mates,mates_prev);
            if(dw4_simulation_step(&simulation) || dw4_hubruntime_tick(hub,dw4_clock_host_world(&simulation.clock))) {
                fprintf(stderr,"hub runtime: %s\n",dw4_hubruntime_error(hub));rc=-1;goto done;
            }
            {static const void *seen;static unsigned tf;char nm[64];int sl;
             if(seen!=hub){seen=hub;tf=0;}
             if(dev_talk_due(&tf,nm,sizeof nm,&sl)){int rc2=dev_talk_place(dw4_hubruntime_world(hub),dw4_hubruntime_models(hub),nm,sl);fprintf(stderr,"dev talk: %s[%d] %s at frame %d\n",nm,sl,rc2?"not found":"placed",i);}}
            if(dev_warp && !dw4_hubruntime_travel(hub)->pending && ++dev_warp_wait>dev_warp_frames) {
                char st[64];int32_t pt;const char *rest=dev_warp_next(dev_warp,st,sizeof st,&pt);
                if(rest){dw4_hubruntime_dev_travel(hub,st,pt);dev_warp=rest;dev_warp_wait=0;
                    fprintf(stderr,"dev warp: %s point %d\n",st,(int)pt);}
            }
            if(dw4_hubruntime_travel(hub)->pending)goto begin_hub_load;
            engine_frame((unsigned)i,&(uint32_t){0},&(uint32_t){0});frame_tick(&boot);
            if(!simulation.due && dw4_hubruntime_draw(hub,&fb,&font)<0) {
                fprintf(stderr,"hub draw: %s\n",dw4_hubruntime_error(hub));rc=-1;goto done;
            }
            in_prev=in;memcpy(mates_prev,mates,sizeof mates);goto present_frame;
        }
        dw4_padrepeat_tick(&services.status_analog,directions);dw4_padrepeat_tick(&services.status_digital,digital);
        services.status_input=(dw4_statuspage_input){.analog=directions,
            .horizontal=services.status_analog.trigger|services.status_analog.repeat,
            .digital=services.status_digital.trigger|services.status_digital.repeat};
        int input_enabled=dw4_stageinput_slot(&services.stage_input,0)!=4;
        dw4_dialogue_input(services.dialogue,0,input_enabled?directions:0,0,
            input_enabled?((in.cross && !in_prev.cross?0x4000:0)|(in.circle && !in_prev.circle?0x2000:0)):0);
        if (dw4_simulation_step(&simulation)) {
            const char *error=dw4_scriptservices_error(services.sd);
            fprintf(stderr,"session Lua tick: %s\n",*error?error:dw4_scriptengine_error(scripts));
            rc=-1;goto done;
        }
        uint64_t world_ns=dw4_clock_host_world(&simulation.clock);
        if(dw4_controllers_tick(services.controllers,(int64_t)world_ns)) {
            fprintf(stderr,"session controller tick: %s\n",dw4_controllers_error(services.controllers));
            rc=-1;goto done;
        }
        if(services.window[0].token && dw4_lobby_services_tick(services.window[0].lobby,world_ns)) {
            fprintf(stderr,"session window tick: %s\n",dw4_lobby_script_error(services.window[0].lobby));
            rc=-1;goto done;
        }
        if(dw4_dialogue_tick(services.dialogue)) {
            fprintf(stderr,"session dialogue tick: %s\n",dw4_dialogue_error(services.dialogue));rc=-1;goto done;
        }
        {   /* DW4_DEV_PLACE="frame:x,y,z" (profiling/inspection aid): stand the player there once, that many lobby frames after the world opens. */
            static int placed=0;static unsigned lobby_frames=0;const char *pl=getenv("DW4_DEV_PLACE");
            if(pl && lobby && !placed && ++lobby_frames){
                unsigned at=0;float x,y,z;
                if(sscanf(pl,"%u:%f,%f,%f",&at,&x,&y,&z)==4 && lobby_frames>=at){placed=1;dw4_lobby_place_player(lobby,x,y,z,getenv("DW4_DEV_YAW")?(float)atof(getenv("DW4_DEV_YAW")):0);fprintf(stderr,"dev place: %g %g %g\n",x,y,z);}
            }
        }
        if(dev_warp && lobby && !services.travel.pending && ++dev_warp_wait>dev_warp_frames) {
            char st[64];int32_t pt;const char *rest=dev_warp_next(dev_warp,st,sizeof st,&pt);
            if(rest){
                snprintf(services.travel.destination,sizeof services.travel.destination,"%s",st);
                services.travel.generate_pos=pt;services.travel.pending=1;dev_warp=rest;dev_warp_wait=0;
                fprintf(stderr,"dev warp: %s point %d\n",st,(int)pt);
            }
        }
        if(lobby && services.travel.pending)goto begin_hub_load;
        if (logging_in && !loading && !lobby && (call_finished || dw4_frontchr_login_done(fchr))) {
            dw4_scriptservices_cancel(services.sd,0);
            dw4_frontaudio_close(audio); audio = NULL;
            loading = 1; loading_frames = 0; load_failed = 0;
            load_ready = load_locked = 0; loading_start_ms = -1.0;
            load_context.mount = &mnt; load_context.roms = o->roms;
            load_context.audio = (win || vk) && !o->headless;
            load_context.species = chr_species; load_context.fps = o->fps; load_context.call_slot = call_slot;
            {static const int starter_row[4] = {3, 0, 1, 2};   /* the created starters: dorumon, agumon, vmon, girumon */
             load_context.row = call_slot >= 0 ? call_row : starter_row[chr_species];
             snprintf(load_context.weapon, sizeof load_context.weapon, "%s", call_slot >= 0 ? call_weapon : "");}
            load_context.light_hard = dw4_options_get()->light_hard;
            snprintf(load_context.name, sizeof load_context.name, "%s", dw4_frontchr_name(fchr));
            printf("  loading: Main Lobby; original USA stage preview and title\n");
        }
        if (loading) {
            void *result = NULL;
            int ready = 0;
            /* Present the loading screen once before touching destination assets.
             * Headless probes run CPU preparation on the following tick, keeping
             * scripted arrival timing independent of worker scheduling. */
            if (!load_failed && !load_ready && loading_frames > 0) {
                if (!load_job) {
                    load_job = dw4_loadjob_start(prepare_lobby, &load_context,
                                                (win || vk) && !o->headless);
                    if (!load_job) {
                        load_failed = 1;
                        fprintf(stderr, "  loading: cannot start asset worker; Retry/Back\n");
                    }
                }
                if (load_job) ready = dw4_loadjob_poll(load_job, &result);
            }
            if (ready) {
                prepared_lobby = dw4_loadjob_close(load_job); load_job = NULL;
                load_ready = 1;
                load_failed = !prepared_lobby;
                if (load_failed) fprintf(stderr, "  loading: Main Lobby assets unavailable; Retry/Back\n");
            }
            int can_finish = prepared_lobby && dw4_frontui_loading_ready(loading_art) && loading_start_ms >= 0.0 &&
                             now_ms() - loading_start_ms >= o->loading_min_seconds * 1000.0;
            if (can_finish && loading_art && !load_locked) {
                dw4_frontui_loading_lock(loading_art); load_locked = 1; can_finish = 0;
            }
            double tr_act0=now_ms(), tr_gpu_ms=0;
            if(can_finish) {
                static const char *models[]={"p_dorumon","p_agumon","p_vmon","p_girumon"};
                char init_error[256];
                if(load_context.call_slot>=0){
                    char dir[420];dw4_memcard *card=NULL;
                    if(dw4_memcard_default_directory(dir,sizeof dir,0) || !(card=dw4_memcard_open(dir)) ||
                       dw4_memcard_restore(card,services.players,services.databases,0,load_context.call_slot,init_error,sizeof init_error)){
                        fprintf(stderr,"  loading: cannot call the saved character: %s\n",init_error);dw4_memcard_close(card);rc=-1;goto done;
                    }
                    dw4_memcard_close(card);
                    printf("  loading: called %s from memory card slot %d\n",load_context.name,load_context.call_slot+1);
                } else if(dw4_playerrecords_create(services.players,services.databases,0,
                   models[load_context.species],load_context.name,init_error,sizeof init_error)){
                    fprintf(stderr,"  loading: %s\n",init_error);rc=-1;goto done;
                } else if(call_created &&   /* LoadIntf2's GAMESTART set UNIQUE from the world clock */
                   dw4_property_set_number(dw4_playerrecords_get(services.players,"GETPLAYER",0),"UNIQUE",call_unique)){
                    fprintf(stderr,"  loading: GETPLAYER UNIQUE could not be set\n");rc=-1;goto done;
                }
                {   /* LoadCtrl2's title hand-off runs the title pack's gameStart.lua (3f1a80 state 3): it clears the mission flags and rebuilds
                     * them, the flag folders and the counters from the snapshot flags of the chosen difficulty (SYSgetDifficulty). */
                    size_t fn=0;const uint8_t *fl=dw4_property_bytes(dw4_playerrecords_get(services.players,"GETCOMMON",0),"FLAG",&fn);
                    unsigned before=0,after=0;for(size_t k=0;fl&&k<fn;k++)before+=fl[k]!=0;
                    script_state.difficulty=call_slot>=0?call_difficulty:0;
                    if(dw4_scriptengine_run(scripts,"gameStart.lua")){
                        fprintf(stderr,"  loading: gameStart.lua: %s\n",dw4_scriptengine_error(scripts));rc=-1;goto done;
                    }
                    fl=dw4_property_bytes(dw4_playerrecords_get(services.players,"GETCOMMON",0),"FLAG",&fn);
                    for(size_t k=0;fl&&k<fn;k++)after+=fl[k]!=0;
                    printf("  loading: gameStart.lua (difficulty %d): %u story flag(s) set before, %u after\n",(int)script_state.difficulty,before,after);
                }
                if(session_reset(&services)){rc=-1;goto done;}
                if(session_library(&services,"stagML11",2) ||
                   dw4_lobby_bind_scripts(prepared_lobby,scripts,&script_state,2)) {
                    fprintf(stderr,"  loading: stage script unavailable: %s; Retry/Back\n",
                        dw4_script_error(dw4_scriptengine_vm(scripts)));
                    dw4_lobby_close(prepared_lobby);prepared_lobby=NULL;load_failed=1;can_finish=0;
                    if(dw4_playerrecords_join(services.players,0,0)){rc=-1;goto done;}
                    if(session_reset(&services) || session_library(&services,"stagIS10",1)) {
                        rc=-1;goto done;
                    }
                    if(flayer) {
                        services.title=dw4_title_services_open_prepared(services.sd,1,&title,flayer,services.objects);
                        if(!services.title){rc=-1;goto done;}
                    }
                }
            }
            if (can_finish) {
                lobby = prepared_lobby; prepared_lobby = NULL;
                dw4_playerhealth published_health;char health_error[256]={0};
                if(dw4_playerhealth_restore(services.players,0,&published_health,health_error,sizeof health_error) ||
                   dw4_lobby_health_publish(lobby,&published_health)){
                    fprintf(stderr,"  loading: player health publication failed: %s\n",health_error);rc=-1;goto done;
                }
                dw4_lobby_dialogue(lobby,services.dialogue);
                static const char *window_names[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky"};
                for(unsigned k=0;k<5;k++) {
                    const dw4_stageobject *native=dw4_stageobjects_find(services.objects,"beModelCtrlInfo",window_names[k],0);
                    if(!native) {
                        fprintf(stderr,"session missing authored window controller: %s\n",window_names[k]);
                        rc=-1;goto done;
                    }
                    services.window[k]=(session_window){lobby,dw4_stageobject_name(native),0,services.sd};
                    services.window[k].token=dw4_scriptservices_register(services.sd,2,"MODELCTRL",dw4_stageobject_name(native),0,0,
                        session_window_call,services.window+k);
                    if(!services.window[k].token){rc=-1;goto done;}
                }
                if(!dw4_stageobjects_find(services.objects,"beCameraCtrlInfo","camsp0101",0) ||
                   !dw4_scriptservices_register(services.sd,2,"CAMERA",NULL,-1,1,
                        dw4_lobby_camera_service,lobby)){rc=-1;goto done;}
                /* Exclude the lobby-owned five greeting peers from this view;
                 * the full STATUS view below is prepared after they are added. */
                services.travel_models=dw4_modelview_open(services.objects,services.controllers,health_error,sizeof health_error);
                if(!services.travel_models){rc=-1;goto done;}
                dw4_lobby_native_ui(lobby,services.travel_models);dw4_lobby_exit_events(lobby,1);
                for(unsigned k=0;k<5;k++)if(dw4_controllers_external(services.controllers,services.objects,window_names[k],0,dw4_lobby_window_model(lobby,k))){rc=-1;goto done;}
                services.status_models=dw4_modelview_open(services.objects,services.controllers,health_error,sizeof health_error);
                if(!services.status_models){fprintf(stderr,"STATUS model preparation: %s\n",health_error);rc=-1;goto done;}
                if(!o->software && (o->gl || (o->window && !o->headless))){
                    services.status_gpu=dw4_gl_layer_open(w,h);
                    if(!services.status_gpu){fprintf(stderr,"STATUS GPU renderer unavailable; cannot enter the lobby\n");rc=-1;goto done;}
                    printf("  STATUS renderer: GPU via %s\n",dw4_gl_layer_info(services.status_gpu));
                }
                dw4_controllers_actions(services.controllers,session_status_action,&services);
                dw4_controllers_audio(services.controllers,dw4_lobby_audio(lobby));
                dw4_subwindow_factory factory={.prepare=session_status_prepare,.begin=session_status_begin,.end=session_status_end,.user=&services,.activate=session_status_activate,.update=session_status_update,.preview=session_status_preview};
                if(dw4_subwindows_factory(dw4_dialogue_subwindows(services.dialogue),&factory)){rc=-1;goto done;}
                dw4_statusview_context layer_context=session_status_view(&services,0);
                if(dw4_statusui_call(&layer_context,0,"LAYERCTL",NULL,-1,"SWITCH","ALL/SET",health_error,sizeof health_error) ||
                   dw4_statusui_call(&layer_context,0,"LAYERCTL",NULL,-1,"SWITCH","LOADING/CLR",health_error,sizeof health_error)){rc=-1;goto done;}
                int startup_error=0;
                if(load_context.audio && dw4_lobby_start_scripted_audio(lobby)) {
                    snprintf(health_error,sizeof health_error,"cannot open lobby audio device");startup_error=1;
                } else startup_error=session_lobby_start(&services,lobby,health_error,sizeof health_error)!=0;
                if(startup_error) {
                    fprintf(stderr,"  loading: %s; Retry/Back\n",health_error);
                    if(session_reset(&services)){rc=-1;goto done;}
                    dw4_lobby_close(lobby);lobby=NULL;load_failed=1;
                    if(dw4_playerrecords_join(services.players,0,0)){rc=-1;goto done;}
                    services.stage_input.disabled=0;
                    if(session_library(&services,"stagIS10",1)){rc=-1;goto done;}
                    if(flayer){
                        services.title=dw4_title_services_open_prepared(services.sd,1,&title,flayer,services.objects);
                        if(!services.title){rc=-1;goto done;}
                    }
                    draw_loading(&fb,frame_gpu,loading_art,&font,loading_frames++,1);
                    in_prev=in;goto present_frame;
                }
                if (o->loading_min_seconds > 0)
                    printf("  loading: visible for %.3f seconds (minimum %.3f)\n",
                           (now_ms() - loading_start_ms) / 1000.0, o->loading_min_seconds);
                if (!o->software && (o->gl || (o->window && !o->headless))) {
                    double tr_g0=now_ms();
                    const char *gpu = dw4_lobby_enable_gpu(lobby, w, h);
                    tr_gpu_ms=now_ms()-tr_g0;
                    printf("  lobby renderer: %s%s\n", gpu ? "GPU via " : "CPU (GPU unavailable)",
                           gpu ? gpu : "");
                }
                if (stage_out && stage_cap) snprintf(stage_out, stage_cap, "%s", load_context.stage);
                loading = 0; chr_open = 0;
                /* Loading must not advance arrival or replay held confirm presses. */
                in_prev = in;
                pace_origin = now_ms() - (o->fps_lock > 0 ? i * 1000.0 / o->fps_lock : 0);
                printf("  loading: complete after %u presented frame(s)\n", loading_frames);
                printf("  entering the first playable stage: %s\n", load_context.stage);
                if(getenv("DW4_FRAME_TRACE"))fprintf(stderr,"  handoff: first lobby activation %.0f ms (lobby GPU layers %.0f ms)\n",now_ms()-tr_act0,tr_gpu_ms);
                snprintf(trace_stage,sizeof trace_stage,"%s","StagML11");
                printf("  lobby: first-arrival introduction; original Lua and native owners\n");
            } else {
                draw_loading(&fb,frame_gpu, loading_art, &font, loading_frames++, load_failed);
                if (load_failed && in.cross && !in_prev.cross) {
                    load_failed = 0; loading_frames = 0;
                    load_ready = load_locked = 0; loading_start_ms = -1.0;
                    printf("  loading: retry Main Lobby\n");
                } else if (load_failed && in.circle && !in_prev.circle) {
                    loading = logging_in = 0;
                    dw4_frontchr_cancel_login(fchr);
                    if ((win || vk) && !o->headless) {
                        audio = dw4_frontaudio_open_session(&mnt);
                        services.audio_origin=dw4_clock_host_world(&simulation.clock);
                        if (audio && dw4_scriptengine_queue_event(scripts,"snd_j_startback.lua")) {
                            rc=-1;goto done;
                        }
                    }
                    printf("  loading: back to created card\n");
                }
                in_prev = in;
                goto present_frame;
            }
        }
        if (lobby) {
            engine_frame((unsigned)i, &(uint32_t){0}, &(uint32_t){0});
            frame_tick(&boot);
            dw4_lobby_input(lobby,input_enabled && !services.status_scene.phase?walk_x:0,
                input_enabled && !services.status_scene.phase?walk_y:0);
            dw4_lobby_jump(lobby,input_enabled && !services.status_scene.phase && in.circle && !in_prev.circle);
            /* The first Terminal's Cross talk probe: the same HITPLAYERTALK receivers and gate as the hub runtime (dw4_hubruntime_input). */
            int talk_probe=input_enabled && !services.status_scene.phase && !services.travel.pending && in.cross && !in_prev.cross;
            dw4_lobby_talk(lobby,talk_probe);
            {double tr0=now_ms();
            dw4_lobby_tick(lobby, (in.cross && !in_prev.cross) || (in.circle && !in_prev.circle));
            tr_tick+=now_ms()-tr0;}
            if(talk_probe && getenv("DW4_DEV_TALK"))fprintf(stderr,"dev talk: Cross probe at frame %d hit %d receiver(s)\n",i,dw4_lobby_talk_result(lobby));
            {static unsigned tf;char nm[64];int sl;   /* DW4_DEV_TALK in the scripted first Terminal (lobby frames since it opened); a warp run places in the hub instead */
             if(!getenv("DW4_DEV_WARP") && dev_talk_due(&tf,nm,sizeof nm,&sl)){int rc2=dev_talk_place(lobby,services.controllers,nm,sl);fprintf(stderr,"dev talk: %s[%d] %s at frame %d\n",nm,sl,rc2?"not found":"placed",i);}}
            dw4_lobby_control_state start_control={0};   /* as the hub: STATUS opens only with player control (not over an NPC talk) */
            if(input_enabled && dw4_lobby_intro_done(lobby) && in.start && !in_prev.start && services.status_scene.phase==0 &&
               !dw4_lobby_control(lobby,&start_control) && start_control.player_control && !services.travel.pending){
                dw4_statusview_context context=session_status_view(&services,0);char error[256];
                if(dw4_statusui_call(&context,0,"SUBWND",NULL,0,"GENERATE","STATUS/I<0>",error,sizeof error)){
                    fprintf(stderr,"STATUS entry: %s\n",error);rc=-1;goto done;
                }
                printf("  STATUS: accepted Start for player 0\n");
            }
            if(dw4_lobby_script_error(lobby)[0]) {
                fprintf(stderr,"  lobby script: %s\n",dw4_lobby_script_error(lobby));
                rc=-1;goto done;
            }
            if (simulation.due) { lobby_frame++;in_prev=in;goto present_frame; }
            dw4_lobby_native_ui(lobby,services.status_scene.phase?NULL:services.travel_models);
            int world_visible=session_layer_visible(&services,"BG02");
            {double tr0=now_ms();int dr=dw4_lobby_draw_layers(lobby,&fb,(unsigned)lobby_frame,&font,session_world_layer_visible,&services);tr_draw+=now_ms()-tr0;tr_draw_end=now_ms();
            if(dr<0){rc=-1;goto done;}}
            lobby_frame++;
            if(services.status_scene.phase){
                if(getenv("DW4_STATUS_TRACE") && i%30==0){
                    const dw4_subwindows *windows=dw4_dialogue_subwindows(services.dialogue);
                    dw4_subwindow_state state=dw4_subwindows_at(windows,0);
                    printf("STATUS trace frame %d scene %d manager %d/%d fonts %zu world_visible %d\n",i,services.status_scene.phase,dw4_subwindows_count(windows)?state.state:-1,dw4_subwindows_count(windows)?state.sub:-1,dw4_dialogue_text_count(services.dialogue),world_visible);
                    for(size_t m=0;m<dw4_controllers_count(services.controllers);m++){
                        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *model=dw4_controllers_model(services.controllers,m,&info,&slot);
                        if(model && dw4_modelctrl_active(model) && info && dw4_stageobject_name(info) && !strncmp(dw4_stageobject_name(info),"i_st",4))printf("STATUS model %s slot %d seq %s\n",dw4_stageobject_name(info),slot,dw4_modelctrl_sequence(model));
                    }
                }
                const dw4_ui_draw *draw;size_t count;char error[256];
                if(!services.status_gpu)dw4_render_zbuf_clear(&fb);
                if(dw4_modelview_draw(services.status_models,fb.w,fb.h,&draw,&count,error,sizeof error)){
                    fprintf(stderr,"STATUS drawing: %s\n",error);rc=-1;goto done;
                }
                if(services.status_gpu){
                    if(dw4_gl_layer_ui(services.status_gpu,&fb,draw,(int)count)){
                        fprintf(stderr,"STATUS GPU model draw failed\n");rc=-1;goto done;
                    }
                }else dw4_gl_layer_ui_or_cpu(&services.status_gpu,&fb,draw,(int)count,8);
                if(dw4_dialogue_draw(services.dialogue,fb.w,fb.h,&draw,&count)){rc=-1;goto done;}
                if(services.status_gpu){
                    if(dw4_gl_layer_ui(services.status_gpu,&fb,draw,(int)count)){
                        fprintf(stderr,"STATUS GPU text draw failed\n");rc=-1;goto done;
                    }
                }else dw4_gl_layer_ui_or_cpu(&services.status_gpu,&fb,draw,(int)count,8);
            }
            in_prev = in;
            goto present_frame;
        }

        dw4_input_menu_axes(&in, &menu_lx, &menu_ly);


        /* The title (finding #605/#639).  Buttons are edge-triggered: one press is one action (the key
         * that skipped the movie is still down when the title loop starts, and a level-triggered read
         * took it for START and then for Cross, straight into Game Start).
         *
         *   opening playing       input is ignored (headless test runs may skip it)
         *   press-start           START opens the Game Start / Option rows after model waits
         *   menu                  the left stick or D-pad moves the selection, Cross confirms
         * START and Cross do nothing while the opening plays and the title is not yet up. */
        if (i == 0)
            in_prev = in;       /* a key still held from the movie skip is not a new press */
        {
#define EDGE(f) (in.f && !in_prev.f)
            const int any_press = EDGE(start) || EDGE(cross) || EDGE(circle) || EDGE(square) ||
                                  EDGE(triangle) || EDGE(select);
            const int opening = flayer && eng_ns < dw4_frontlayer_open_ns();

            if (opening) {
                /* Retail cannot skip the opening: input is ignored until SQ_OPEN ends. Only headless
                 * (scripted test) runs may skip it, to keep their short input scripts valid. */
                if (any_press && fui && o->headless) {
                    skip_ns += dw4_frontlayer_open_ns() - eng_ns;   /* jump to the end of SQ_OPEN: the flash
                                                                      * and the UI's own OPEN play from here */
                    eng_ns = dw4_frontlayer_open_ns();
                    ui_ns = 0;
                    printf("  title: opening skipped at frame %d -> 'Press START button'\n", i);
                }
            } else if (logging_in) {
                /* Creation is committed; button edges cannot reopen the title. */
            } else if (chr_open && call_scene) {
                /* The slot screen: LoadIntf2 runs in its own scene (the Create/Call window, Create and Call Digimon); the pad words are the hub's. */
                uint32_t pressed=(EDGE(cross)?0x4000u:0)|(EDGE(circle)?0x2000u:0)|(EDGE(start)?8u:0);
                dw4_savescene_input(call_scene,directions,digital,pressed);
                call_ns+=16666667ULL;
                if(dw4_savescene_tick(call_scene,call_ns)){
                    fprintf(stderr,"  title: Call Digimon: %s\n",dw4_savescene_error(call_scene));rc=-1;goto done;
                }
                {
                    dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(dw4_savescene_intf(call_scene),0,&t);
                    if(t.control==6&&call_control==3)printf("  title: slot screen: Call Digimon -> memory card chooser\n");
                    if(t.control==3&&call_control==6)printf("  title: memory card chooser -> Create/Call window\n");
                    /* Create (LoadIntf2 states 4, 5 and 8's GAMESTART); the species names are the character UI's (Dorumon first). */
                    dw4_saveintf_create_trace cr;dw4_saveintf_create_diagnostics(dw4_savescene_intf(call_scene),0,&cr);
                    int fc=(cr.species+1)&3;char typed[DW4_CHR_NAME_MAX+1]={0};
                    for(int k=0;k<DW4_CHR_NAME_MAX&&cr.name[k];k++)typed[k]=dw4_name_char(cr.name[k]);
                    if(t.control==4&&call_control==3)printf("  title: slot screen: Create Digimon. (LoadIntf2 starter choice)\n");
                    if(t.control==4&&t.control_sub>=1&&(call_control!=4||fc!=call_species))printf("  title: species: %s\n",dw4_frontchr_species_name(fc));
                    if(t.control==3&&call_control==4)printf("  title: species -> slot screen\n");
                    if(t.control==5&&call_control==4)printf("  title: species confirmed: %s -> name entry\n",dw4_frontchr_species_name(fc));
                    if(t.control==4&&call_control==5)printf("  title: name entry -> species\n");
                    if(t.control==5&&t.control_sub==2&&call_sub!=2)printf("  title: name question: %s\n",typed);
                    if(t.control==5&&call_control==8)printf("  title: log-in prompt -> name entry\n");
                    if(t.control==5&&call_control!=5)call_named=0;
                    if(t.control==8&&call_control==5)call_named=1;
                    if(t.control==8&&call_named==1&&t.control_sub>=1){
                        call_named=2;chr_species=fc;
                        printf("  title: created %s named %s (LoadIntf2 GAMESTART); log-in prompt\n",dw4_frontchr_species_name(fc),typed);
                    }
                    call_control=t.control;call_sub=t.control_sub;call_species=t.control==4&&t.control_sub>=1?fc:-1;
                }
                int cs=-1,area=-1,dif=0;char stage[64];int pos=0;
                int ts=dw4_savescene_title_state(call_scene,&cs,&area,&dif);
                if(dw4_savescene_exit(call_scene,stage,sizeof stage,&pos)){
                    if(ts==1){
                        dw4_property_folder *rec=dw4_playerrecords_get(dw4_savescene_records(call_scene),"GETPLAYER",0);
                        const char *model=dw4_property_string(rec,"DIGIMONNAME");
                        dw4_unicode_object name={0};dw4_property_unicode_object(rec,"PLAYERNAME",0,&name);
                        char nm[DW4_CHR_NAME_MAX+1]={0};
                        for(size_t k=0;k<name.count&&k<DW4_CHR_NAME_MAX&&name.codes[k];k++)nm[k]=dw4_name_char(name.codes[k]);
                        call_row=-1;
                        for(int k=0;model&&k<16;k++)if(!strcmp(model,dw4_lobby_model_name(k)))call_row=k;
                        const char *weapon=dw4_property_string_at(rec,"POWERSOCKETNAME",0);
                        if(call_row<0||!weapon||!*weapon){
                            fprintf(stderr,"  title: Call Digimon: %s cannot be played (no player model or equipped weapon)\n",model?model:"(none)");
                            dw4_savescene_close(call_scene);call_scene=NULL;dw4_memcard_close(call_card);call_card=NULL;
                            goto call_scene_done;
                        }
                        snprintf(call_weapon,sizeof call_weapon,"%s",weapon);
                        chr_species=call_row==3?0:call_row==0?1:call_row==1?2:call_row==2?3:0;   /* the character screen's card shows a starter on a retry */
                        call_created=area<0;call_unique=0;
                        if(call_created){   /* Create: GAMESTART built the record in the scene; the session rebuilds it with the same API */
                            int32_t u=0;dw4_property_number(rec,"UNIQUE",&u);call_unique=u;
                            if(call_row>3){fprintf(stderr,"  title: Create: %s is not a starter\n",model);rc=-1;goto done;}
                            if(o->created_player){o->created_player->valid=1;o->created_player->species=chr_species;
                                snprintf(o->created_player->name,sizeof o->created_player->name,"%s",nm);}
                            dif=0;
                        }
                        call_slot=call_created?-1:area;call_finished=1;call_difficulty=dif;script_state.difficulty=dif;
                        dw4_property_set_number(dw4_playerrecords_get(services.players,"GETCOMMON",0),"DIFFICULTY",dif);
                        snprintf(load_context.name,sizeof load_context.name,"%s",nm);
                        dw4_frontchr_set_called(fchr,chr_species,nm);
                        logging_in=1;
                        if(call_created)printf("  title: logging in %s named %s (%s, UNIQUE %d)\n",dw4_frontchr_species_name(chr_species),nm,model,(int)call_unique);
                        else printf("  title: called %s (%s) from memory card area %d, difficulty row %d; logging in\n",nm,model,area+1,dif);
                    }
                    dw4_savescene_close(call_scene);call_scene=NULL;dw4_memcard_close(call_card);call_card=NULL;
                }
                call_scene_done:;
            } else if (chr_open) {   /* the fallback character UI (no save library: the slot scene could not open) */
                if (dw4_frontchr_phase(fchr) != DW4_CHR_SELECT) {
                    int horizontal = (menu_lx > 0.5f && lx_prev <= 0.5f) -
                                     (menu_lx < -0.5f && lx_prev >= -0.5f);
                    int vertical = (menu_ly > 0.5f && ly_prev <= 0.5f) -
                                   (menu_ly < -0.5f && ly_prev >= -0.5f);
                    /* Naming repeats while a menu direction is held. Delay and
                     * cadence are estimates from the supplied 30 fps recording. */
                    if (dw4_frontchr_phase(fchr) == DW4_CHR_NAME) {
                        name_hold_x = fabsf(menu_lx) > 0.5f ? (horizontal ? 1 : name_hold_x + 1) : 0;
                        name_hold_y = fabsf(menu_ly) > 0.5f ? (vertical ? 1 : name_hold_y + 1) : 0;
                        if (name_hold_x >= 20 && (name_hold_x - 20) % 6 == 0)
                            horizontal = menu_lx > 0 ? 1 : -1;
                        if (name_hold_y >= 20 && (name_hold_y - 20) % 6 == 0)
                            vertical = menu_ly > 0 ? 1 : -1;
                    } else name_hold_x = name_hold_y = 0;
                    if (dw4_frontchr_name_input(fchr, horizontal, vertical,
                                               EDGE(cross), EDGE(circle), EDGE(start))) {
                        if (o->created_player) {
                            o->created_player->valid = 1;
                            o->created_player->species = chr_species;
                            snprintf(o->created_player->name, sizeof(o->created_player->name),
                                     "%s", dw4_frontchr_name(fchr));
                        }
                        logging_in = 1;
                        dw4_frontchr_begin_login(fchr);
                        printf("  title: logging in %s named %s; CLOSE 70..100, 101..130\n",
                               dw4_frontchr_species_name(chr_species), dw4_frontchr_name(fchr));
                    }
                    if (dw4_frontchr_phase(fchr) == DW4_CHR_SELECT) {
                        chr_species = -1;
                        printf("  title: species -> slot screen\n");
                    }
                } else if (chr_species >= 0) {
                    int move = (menu_lx > 0.5f && lx_prev <= 0.5f) -
                               (menu_lx < -0.5f && lx_prev >= -0.5f);
                    if (EDGE(circle)) {
                        dw4_frontaudio_action(audio, "j_linewin01", "CANCEL");
                        chr_species = -1;
                        printf("  title: species -> slot screen\n");
                    } else if (move) {
                        chr_species = (chr_species + move + 4) % 4;
                        printf("  title: species: %s\n", dw4_frontchr_species_name(chr_species));
                    } else if (EDGE(cross)) {
                        printf("  title: species confirmed: %s -> name entry\n",
                               dw4_frontchr_species_name(chr_species));
                        dw4_frontchr_begin_name(fchr);
                    }
                    dw4_frontchr_species(fchr, chr_species);
                } else {
                    if ((menu_ly > 0.5f && ly_prev <= 0.5f) || (menu_ly < -0.5f && ly_prev >= -0.5f)) {
                        dw4_frontaudio_action(audio, "j_chrselmesswin", "LINEDW01");
                        chr_sel = (chr_sel + 1) % 2;
                    }
                    if (EDGE(cross)) {
                        dw4_frontaudio_action(audio, "j_chrselmesswin", chr_sel ? "LINEON01" : "LINEON00");
                        if (chr_sel == 0) {
                            call_slot = -1;
                            chr_species = 0;
                            dw4_frontchr_species(fchr, chr_species);
                            printf("  title: slot screen: Create Digimon.\n");
                            printf("  title: species: Dorumon\n");
                        } else {
                            printf("  title: Call Digimon: the save library is unavailable\n");
                        }
                    }
                }
            } else {
                Dw4TitleInput pad = {0};
                int old_state = title.ctrl._st0;
                int old_camera = title.option._dispComConf, old_light = title.option._dispLightConf;
                int was_option = opt_open;
                /* The pad producer remains a host edge sampler. The recovered
                 * controller owns direction priority, clamping and button meaning. */
                if (menu_ly > 0.5f && ly_prev <= 0.5f) pad.direction_a |= 1;
                if (menu_ly < -0.5f && ly_prev >= -0.5f) pad.direction_a |= 4;
                if (menu_lx > 0.5f && lx_prev <= 0.5f) pad.direction_a |= 2;
                if (menu_lx < -0.5f && lx_prev >= -0.5f) pad.direction_a |= 8;
                if (EDGE(start)) pad.pressed |= 8;
                if (EDGE(cross)) pad.pressed |= 0x4000;
                if (EDGE(circle)) pad.pressed |= 0x2000;
                dw4_title_host_tick(&title, &pad, 1);
                if (title.error) {
                    fprintf(stderr, "title: unsupported controller operation 0x%x\n", title.error);
                    rc = -1; break;
                }
                menu.sel = title.ctrl._gameMenuCnt;
                opt_sel = title.option._ctrlPos == 3 ? 2 : title.option._ctrlPos;
                opt_open = dw4_title_host_model(&title, T_j_optionwin02)->active;
                if (opt_open && !was_option) {
                    dw4_frontopt_reset(fopt, 0);
                    printf("  title: option screen opened\n");
                }
                if (old_state == 4 && title.ctrl._st0 == 2)
                    printf("  title: option screen closed -> main menu\n");
                if (old_state == 1 && title.ctrl._st0 == 2)
                    printf("  title: press-start -> main menu ('Game Start' / 'Option')\n");
                if (title.ctrl._st0 == 2 && title.ctrl._st1 == 0 && title.ctrl._st2 == 1)
                    if (dw4_title_host_model(&title, T_j_startmenu02)->age == 0)
                        printf("  title: state=menu (%d visible item(s))\n", dw4_frontui_visible(fui));
                if (old_camera != title.option._dispComConf || old_light != title.option._dispLightConf)
                    printf("  title: option: Dungeon camera = %s, Light = %s\n",
                           title.option._dispComConf ? "Far" : "Near", title.option._dispLightConf ? "Hard" : "Soft");
                dw4_options_get()->camera_far = title.camera;
                dw4_options_get()->light_hard = title.light;
                if (old_state == 4 && title.ctrl._st0 == 2) {
                    while (dw4_options_save() < 0) {
                        if (o->headless || !(win || vk) ||
                            !dw4_window_retry("Cannot save configuration", dw4_options_path()))
                            break;
                    }
                    /* Modal retry/back time must not become simulation catch-up. */
                    dw4_simulation_hold(&simulation,DW4_HOLD_PAUSE,(uint64_t)(now_ms()*1000000.0));
                    dw4_simulation_hold(&simulation,0,(uint64_t)(now_ms()*1000000.0));
                    pace_origin = now_ms() - (o->fps_lock > 0 ? (i + 1) * 1000.0 / o->fps_lock : 0);
                }
                if (title.handoff) {
                    if (!fchr) { fprintf(stderr, "title: character screen unavailable\n"); rc = -1; break; }
                    chr_open = 1; chr_sel = 0; call_slot = -1; call_finished = 0; call_created = 0; chr_species = -1;
                    dw4_frontchr_reset(fchr);
                    printf("  title: Game Start -> slot screen\n");
                    call_unavailable = 0;   /* the slot scene opens below, before this frame draws */
                }
                if (title.next_stage) {
                    if (title.next_stage != T_stagIS09) {
                        fprintf(stderr, "title: unsupported stage request 0x%x\n", title.next_stage);
                        rc = -1; break;
                    }
                    printf("  title: attract -> stagIS09\n");
                    if(session_reset(&services)){rc=-1;goto done;}
                    dw4_frontaudio_close(audio); audio = NULL;
                    rc = dw4_frontend_attract(o->roms, &menu, o->window && !o->headless, o->fps, win, vk);
                    if (rc) { if (rc == -2) rc = 0; break; }
                    if(session_library(&services,"stagIS10",1)){rc=-1;goto done;}
                    dw4_title_host_close(&title);
                    dw4_title_host_init(&title, dw4_options_get()->camera_far, dw4_options_get()->light_hard);
                    title.sound_action = menu_sound_action; title.sound_user = &audio;
                    if(flayer) {
                        services.title=dw4_title_services_open_prepared(services.sd,1,&title,flayer,services.objects);
                        if(!services.title){rc=-1;goto done;}
                    }
                    if ((win || vk) && !o->headless) {
                        audio = dw4_frontaudio_open_session(&mnt);
                        services.audio_origin=dw4_clock_host_world(&simulation.clock);
                        if (audio && dw4_scriptengine_queue_event(scripts,"snd_j_startback.lua")) {
                            rc=-1;goto done;
                        }
                    }
                    skip_ns = -(long long)(i + 1) * 1000000000LL / 60;
                    ui_first = 0;
                    pace_origin = now_ms() - (o->fps_lock > 0 ? (i + 1) * 1000.0 / o->fps_lock : 0);
                    boot_frame_prev = boot_fps_ema = 0;
                    in_prev = in; lx_prev = menu_lx; ly_prev = menu_ly;
                    continue;
                }
            }
#undef EDGE
        }
        /* The slot screen belongs to the LoadIntf2 scene: it opens with the slot screen. Without a save library the character UI keeps
         * its own Create/Call window and Create flow. */
        if (chr_open && fchr && !logging_in && chr_species < 0 && dw4_frontchr_phase(fchr) == DW4_CHR_SELECT &&
            !call_scene && !call_unavailable) {
            int r = slot_scene_open(&mnt,services.players,&script_state,frame_gpu,&audio,&call_scene,&call_card,&call_ns);
            if (r < 0) { rc = -1; goto done; }
            call_unavailable = r != 0; call_control = -1; call_sub = -1; call_species = -1; call_named = 0;
        }
        if (logging_in && call_scene) {   /* a fallback-created character logs in: the slot scene is no longer needed */
            dw4_savescene_close(call_scene);call_scene=NULL;dw4_memcard_close(call_card);call_card=NULL;
        }
        in_prev = in;
        ly_prev = menu_ly;
        lx_prev = menu_lx;

        engine_frame((unsigned)i, &(uint32_t){0}, &(uint32_t){0});
        if (logging_in) {
            frame_tick(&boot);
            {
                int res = frame_gpu && !dw4_gl_layer_defer(frame_gpu, &fb, 1);
                if(engine_clear_fb(&fb,frame_gpu,0,0,0)){if(res)dw4_gl_layer_defer(frame_gpu,&fb,0);rc=-1;goto done;}
                if (!call_finished) dw4_frontchr_draw(fchr, &fb, chr_sel, &font);   /* a called character's windows already closed in the scene */
                if (res) {
                    if (dw4_fps_overlay > 0 && !dw4_fps_overlay_drawn && !dw4_render_fps_gpu(frame_gpu, &fb, dw4_fps_overlay))
                        dw4_fps_overlay_drawn = 1;
                    if (dw4_gl_layer_defer(frame_gpu, &fb, 0)) {dw4_gpu_policy_fail("login frame readback");rc=-1;goto done;}
                }
            }
            goto present_frame;
        }
        if (simulation.due && !chr_open) goto present_frame;
        yaw += 0.15f;
        if (fui)
            dw4_frontui_set_engine(fui, ui_ns);
        /* The UI is gated on the layer's opening (finding #640): report the first frame it draws, so
         * a check can hold the port to the game's sequence (opening alone, then the title). */
        if (fui && !ui_first) {
            float r0[4];
            if (dw4_frontui_logo_rect(fui, &fb, r0) == 0 && r0[2] - r0[0] > 1.0f) {
                printf("  title: UI first drawn at frame %d (after the layer's %.2f s opening)\n",
                       i, dw4_frontlayer_open_ns() / 1e9);
                ui_first = 1;
            }
        }
        int opt_run = 0;                  /* the title's resident frame stays open for the Option screen to draw on */
        if (!(chr_open && fchr)) {
            int title_resident = 0;
            if (flayer) {
                /* The controller runs on the game's own 60 fps tick: one frame's worth of the engine
                 * clock (int64 ns) per presented frame, so the layer moves every frame (#619). */
                {   /* the backdrop mesh pass begins by clearing to the same black, so a separate clear would be a wasted pass */
                    const char *bg0=getenv("DW4_TITLE_BACKDROP");float cv0[16],fp0;
                    int mesh_pass=title_mesh && have_scene && !(bg0 && bg0[0]=='0') && dw4_frontlayer_view(flayer,cv0,&fp0)==0;
                    if(!mesh_pass && engine_clear_fb(&fb,frame_gpu,0,0,0)){rc=-1;goto done;}
                }
                /* Probes: DW4_TITLE_BACKDROP=0 / DW4_TITLE_LAYER=0 drop one of the two title layers so a
                 * comparison run can attribute what is on screen to each (finding #641). */
                {
                    const char *bg = getenv("DW4_TITLE_BACKDROP");
                    const char *ly = getenv("DW4_TITLE_LAYER");
                    int want_bg = !(bg && bg[0] == '0');
                    int want_ly = !(ly && ly[0] == '0');
                    /* The recovered composition order (findings #609/#610/#632): the static stagML11
                     * backdrop first, then the generated additive j_startback trail, then the title UI.
                     * The backdrop is the stage's own merged geometry composed through the recovered title
                     * camera (finding #628, the same `entry` chain the layer uses), so it sits with the
                     * tunnel instead of the placeholder fit/spin the no-layer path uses. */
                    if (have_scene && want_bg) {
                        float cview[16], fpr;
                        if (dw4_frontlayer_view(flayer, cview, &fpr) == 0) {
                            float bgtint[3] = { 0.34f, 0.38f, 0.62f };
                            float bfov = 2.0f * (float)atan(1.0 / (2.0 * (double)fpr));
                            if(title_mesh){
                                if(dw4_gl_render(title_mesh,&fb,mb.pos,mb.nrm,NULL,mb.tris,mb.nv,mb.nt,
                                    cview,bfov,1,amb_builtin,&sun,1,bgtint,NULL)){
                                    dw4_gpu_policy_fail("title backdrop draw");rc=-1;goto done;
                                }
                            }else{
                                dw4_render_set_view(cview, bfov, 1.0f);
                                dw4_render_mesh_n(&fb, (const uint8_t *)mb.pos, (const uint8_t *)mb.nrm,
                                                  NULL, mb.nv, mb.tris, mb.nt, 0.0f, 0.0f, bgtint, NULL);
                                dw4_render_clear_view();
                            }
                        }
                    }
                    if (frame_gpu && !dw4_gl_layer_defer(frame_gpu, &fb, 1))
                        title_resident = 1;       /* layer, UI, flash, fade and counter share one resident frame */
                    dw4_frontlayer_set_engine(flayer, eng_ns);
                    if (want_ly)
                        dw4_frontlayer_draw(flayer, &fb);
                }
                if (fui)
                    dw4_frontui_draw(fui, &fb, menu.sel);
            } else {
                if (fui)
                    dw4_frontui_draw(fui, &fb, menu.sel);
                draw_title(&fb,frame_gpu, &font, &menu, have_scene ? &mb : NULL, yaw, i, 0, fui != NULL);
            }
            /* The white flash (finding #642).  The title stage's own Lua runs, once `j_startback`'s
             * `SQ_OPEN` has finished and `SYSgetArea() == -1` (the front-end),
             * `MODELCTRL i_fadewn01 GENERATE SQ_WTIN60`
             * (`DW4_Decomp/lua/00-title-menus/04-title-screen_e806/004-layer-setup-2.lua`).  That action
             * selects the fade model's joint 45 -- its white node -- and runs
             * `beAction2FADESET OUT _fadeTime=60 _fadeValue=1.0` (`NDMW.AFS` entry 806, scene 3
             * `i_fadewn01`, `beAction2Info` id 796 @0x1248c, action `WTIN60` @0x12474): a full-screen
             * white overlay at alpha 1.0 fading to 0 over 60 frames.  Its `BLIN30` is the same action on
             * joint 5, the black node, 30 frames -- the fade the title fades in from.  The overlay is
             * the last thing drawn, over both the layer and the UI. */
            if (flayer) {
                long long flash_ns = eng_ns - dw4_frontlayer_open_ns();
                long long flash_len = 60LL * 1000000000LL / 60;      /* FADESET fadeTime 60 frames */
                if (flash_ns >= 0 && flash_ns < flash_len) {
                    uint8_t fl_rgba[3][4], fl_a = (uint8_t)(128 - (int)(128LL * flash_ns / flash_len));
                    fl_rgba[0][0] = fl_rgba[0][1] = fl_rgba[0][2] = 128;   /* the fade node is white */
                    fl_rgba[1][0] = fl_rgba[1][1] = fl_rgba[1][2] = 128;
                    fl_rgba[2][0] = fl_rgba[2][1] = fl_rgba[2][2] = 128;
                    fl_rgba[0][3] = fl_rgba[1][3] = fl_rgba[2][3] = fl_a;
                    ui_quad(&fb,frame_gpu, 0.0f, 0.0f, (float)fb.w, (float)fb.h, fl_rgba);
                    if (i == ui_flash_frame || ui_flash_frame == 0) {
                        ui_flash_frame = (int)i;
                        printf("  title: white flash (SQ_WTIN60) alpha %u at frame %d\n",
                               (unsigned)fl_a, i);
                    }
                }
            }
            if (!chr_open) {
                const dw4_title_model *fade = dw4_title_host_model(&title, T_i_fadewn01);
                if (fade->active) {
                    unsigned char rgb = fade->sequence == T_SQ_WTOUT60 ? 128 : 0;
                    unsigned char alpha = (unsigned char)dw4_title_model_alpha(fade);
                    const uint8_t colour[3][4] = {{rgb,rgb,rgb,alpha},{rgb,rgb,rgb,alpha},{rgb,rgb,rgb,alpha}};
                    ui_quad(&fb,frame_gpu, 0, 0, (float)fb.w, (float)fb.h, colour);
                }
            }
            if (title_resident) {
                if (opt_open) opt_run = 1;
                else {
                    if (!chr_open && dw4_fps_overlay > 0 && !dw4_fps_overlay_drawn) {
                        if (dw4_render_fps_gpu(frame_gpu, &fb, dw4_fps_overlay)) {dw4_gpu_policy_fail("FPS overlay draw");rc=-1;goto done;}
                        dw4_fps_overlay_drawn = 1;
                    }
                    if (dw4_gl_layer_defer(frame_gpu, &fb, 0)) {dw4_gpu_policy_fail("title frame readback");rc=-1;goto done;}
                }
            }
        } /* Character UI replaces the title; skip the hidden title render. */
        if (chr_open && fchr) {
            int res = frame_gpu && !dw4_gl_layer_defer(frame_gpu, &fb, 1);   /* one resident frame for the whole character screen */
            if(engine_clear_fb(&fb,frame_gpu,24,28,36)){if(res)dw4_gl_layer_defer(frame_gpu,&fb,0);rc=-1;goto done;}               /* field beneath the pack-derived BG02 backdrop */
            if (call_scene) {
                if (dw4_savescene_draw(call_scene, &fb) < 0) {fprintf(stderr,"  title: Call Digimon draw: %s\n",dw4_savescene_error(call_scene));rc=-1;goto done;}
                /* The starter choice's 3D preview (h_<species> between SQ_ENTR and SQ_EXIT) through the character UI's actor renderer. */
                dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(dw4_savescene_intf(call_scene),0,&t);
                if (t.control == 4 && t.control_sub <= 3) {
                    dw4_saveintf_create_trace c;dw4_saveintf_create_diagnostics(dw4_savescene_intf(call_scene),0,&c);
                    dw4_frontchr_draw_preview(fchr, &fb, (c.species + 1) & 3);   /* MakeChr agumon/vmon/girumon/dorumon -> Dorumon first */
                } else dw4_frontchr_species(fchr, -1);
            } else dw4_frontchr_draw(fchr, &fb, chr_sel, &font);
            if (res) {
                if (!opt_open && dw4_fps_overlay > 0 && !dw4_fps_overlay_drawn && !dw4_render_fps_gpu(frame_gpu, &fb, dw4_fps_overlay))
                    dw4_fps_overlay_drawn = 1;
                if (dw4_gl_layer_defer(frame_gpu, &fb, 0)) {dw4_gpu_policy_fail("character frame readback");rc=-1;goto done;}
            }
        }
        if (opt_open) {
            const int opt_res = opt_run || (frame_gpu && !dw4_gl_layer_defer(frame_gpu, &fb, 1));
            if (fopt)
                dw4_frontopt_draw(fopt, &fb, opt_sel, &font, (title.text & (1u << 3)) != 0,
                                  (title.text & (1u << 5)) != 0);
            else
                draw_options(&fb,frame_gpu, &font, opt_sel, &(dw4_options){title.option._dispComConf, title.option._dispLightConf});
            if (opt_res) {
                if (dw4_fps_overlay > 0 && !dw4_fps_overlay_drawn && !dw4_render_fps_gpu(frame_gpu, &fb, dw4_fps_overlay))
                    dw4_fps_overlay_drawn = 1;
                if (dw4_gl_layer_defer(frame_gpu, &fb, 0)) {dw4_gpu_policy_fail("option frame readback");rc=-1;goto done;}
            }
        }
        goto present_frame;
begin_hub_load: {
            const dw4_stagetravel *request=hub?dw4_hubruntime_travel(hub):&services.travel;
            hub_context=(hub_load_context){.mount=&mnt,.light_hard=dw4_options_get()->light_hard};
            if(dw4_stagetravel_pending(request,hub_context.destination,sizeof hub_context.destination,&hub_context.point)!=1){rc=-1;goto done;}
            hub_context.source=hub?(dw4_hubruntime_source){dw4_hubruntime_records(hub),dw4_hubruntime_state(hub),
                dw4_hubruntime_input_state(hub),dw4_hubruntime_time(hub)}:
                (dw4_hubruntime_source){services.players,services.state,&services.stage_input,services.world_ns};
            /* Scene decoding is single-owner: load the card before the CPU
             * worker can begin, then only sample its resident presentation. */
            dw4_frontui_close(hub_art);hub_art=dw4_frontui_open_loading(&mnt,hub_context.destination);
            if(hub_art && dw4_gpu_policy_required() && !(frame_gpu?dw4_frontui_use_gpu(hub_art,frame_gpu):dw4_frontui_enable_gpu(hub_art,w,h))) {
                dw4_gpu_policy_fail("hub loading card GPU preparation");rc=-1;goto done;
            }
            hub_loading=1;hub_frames=0;hub_ready=hub_failed=hub_locked=0;hub_start_ms=-1;
            printf("  hub loading: %s point %d; retaining source session\n",hub_context.destination,hub_context.point);
            /* A destination with no runtime (the Terminal gates' field and dungeon stages): no worker, no Retry. The card
             * says "Destination not available" and Circle returns to the retained source like a failed load's Back. */
            if(!dw4_hubruntime_destination_available(hub_context.destination)) {
                hub_failed=2;hub_ready=1;
                snprintf(hub_context.error,sizeof hub_context.error,"%.60s is not available in this build",hub_context.destination);
                fprintf(stderr,"hub loading: %s; Back\n",hub_context.error);
            }
        }
hub_load_update: {
            if(!hub_failed && !hub_ready && hub_frames) {
                if(!hub_job)hub_job=dw4_loadjob_start(prepare_hub,&hub_context,(win || vk) && !o->headless);
                if(!hub_job){hub_failed=1;snprintf(hub_context.error,sizeof hub_context.error,"cannot start destination worker");}
                void *result=NULL;
                if(hub_job && dw4_loadjob_poll(hub_job,&result)) {
                    prepared_hub=dw4_loadjob_close(hub_job);hub_job=NULL;hub_ready=1;hub_failed=!prepared_hub;
                    if(hub_failed)fprintf(stderr,"hub loading: %s; Retry/Back\n",hub_context.error);
                }
            }
            int activate=prepared_hub && dw4_frontui_loading_ready(hub_art) && hub_start_ms>=0 &&
                now_ms()-hub_start_ms>=o->loading_min_seconds*1000;
            if(activate && hub_art && !hub_locked){dw4_frontui_loading_lock(hub_art);hub_locked=1;activate=0;}
            if(activate) {
                double t_act0=now_ms();
                if(!o->software && (o->gl || (o->window && !o->headless)) && !dw4_hubruntime_enable_gpu(prepared_hub,w,h)) {
                    dw4_gpu_policy_fail("hub destination GPU preparation");rc=-1;goto done;
                }
                if(getenv("DW4_FRAME_TRACE"))fprintf(stderr,"  handoff: destination GPU layers %.0f ms\n",now_ms()-t_act0);
                if((win || vk) && !o->headless && dw4_hubruntime_adopt_audio(prepared_hub,hub,hub?NULL:lobby)) {
                    snprintf(hub_context.error,sizeof hub_context.error,"cannot transfer source audio device");
                    dw4_hubruntime_close(prepared_hub);prepared_hub=NULL;hub_failed=1;activate=0;
                }
            }
            if(activate) {
                double t_cl0=now_ms();
                if(hub)dw4_hubruntime_close(hub);
                else {
                    if(session_reset(&services)){rc=-1;goto done;}
                    dw4_lobby_close(lobby);lobby=NULL;
                }
                if(getenv("DW4_FRAME_TRACE"))fprintf(stderr,"  handoff: source teardown %.0f ms\n",now_ms()-t_cl0);
                hub=prepared_hub;prepared_hub=NULL;services.hub=hub;simulation.scripts=NULL;
                hub_loading=0;in_prev=in;
                simulation.last_host=(uint64_t)(now_ms()*1000000);simulation.credit=simulation.due=0;
                pace_origin=now_ms()-(o->fps_lock>0?i*1000.0/o->fps_lock:0);
                if(stage_out && stage_cap)snprintf(stage_out,stage_cap,"%s",hub_context.destination);
                printf("  hub publication: %s point %d after %u loading presentations; source released\n",hub_context.destination,hub_context.point,hub_frames);
                snprintf(trace_stage,sizeof trace_stage,"%s",hub_context.destination);
                /* Retain the locked card for this frame. Destination arrival
                 * begins on the next admitted simulation sample. */
            }else {
                draw_loading(&fb,frame_gpu,hub_art,&font,hub_frames++,hub_failed);
                if(hub_failed==1 && in.cross && !in_prev.cross) {
                    hub_ready=hub_failed=hub_locked=0;hub_frames=0;hub_start_ms=-1;
                    printf("  hub loading: retry %s\n",hub_context.destination);
                }else if(hub_failed && in.circle && !in_prev.circle) {
                    char error[256];int failed=hub?dw4_hubruntime_cancel_travel(hub):
                        dw4_stagetravel_restore(services.sd,2,&services.travel,error,sizeof error);
                    if(failed){fprintf(stderr,"hub Back: %s\n",hub?dw4_hubruntime_error(hub):error);rc=-1;goto done;}
                    if(!hub)services.travel.generate_pos=0;
                    hub_loading=0;simulation.last_host=(uint64_t)(now_ms()*1000000);simulation.credit=simulation.due=0;
                    printf("  hub loading: back to retained source; records preserved\n");
                }
                in_prev=in;
            }
            goto present_frame;
        }
present_frame:
        if(dw4_gpu_policy_error()[0]){rc=-1;goto done;}
        /* Loading counts presented samples and gates destination work on the
         * first one. Catch-up must not consume its reveal/lock frames offscreen. */
        if (simulation.due && !simulation.holds && !loading && !hub_loading) { frames_run=i+1;continue; }
        if (o->fps != 0 && (o->fps == 1 || vk || (win && !o->headless))) {
            /* the interval between frames (present included), not the draw time */
            double nowm = now_ms();
            if (boot_frame_prev > 0.0) {
                double dt = nowm - boot_frame_prev;
                if (dt > 0.0) {
                    double inst = 1000.0 / dt;
                    boot_fps_ema = boot_fps_ema > 0.0 ? boot_fps_ema * 0.9 + inst * 0.1 : inst;
                }
            }
            boot_frame_prev = nowm;
            if (boot_fps_ema > 0.0){
                if(dw4_gpu_policy_required()){
                    if(!dw4_fps_overlay_drawn && dw4_render_fps_gpu(frame_gpu,&fb,boot_fps_ema)){dw4_gpu_policy_fail("FPS overlay draw");rc=-1;goto done;}
                }else dw4_render_fps(&fb, boot_fps_ema);
            }
        }
        if (vk) {
            {double tr0=now_ms();if(tr_draw_end>0){tr_post+=tr0-tr_draw_end;tr_draw_end=0;}int pr=dw4_vk_present(vk, &fb);tr_present+=now_ms()-tr0;
            if (pr < 0) { dw4_gpu_policy_fail("boot Vulkan presentation");rc=-1;goto done; }}
        } else if (win) {
            if(dw4_window_present(win,&fb)<0){dw4_gpu_policy_fail("boot SDL presentation");rc=-1;goto done;}
        }
        if (((!win && !vk) || o->headless) && dev_shot_wanted(i)) {
            char path[4096];
            snprintf(path, sizeof(path), "%s/frame_%04d.png", out_dir, i);
            if (dw4_png_write(path, fb.rgba, fb.w, fb.h) != 0)
                rc = -1;
        }
        if (loading && loading_start_ms < 0.0) loading_start_ms = now_ms();
        if(hub_loading && hub_start_ms<0)hub_start_ms=now_ms();
        if (win || vk) {
            {
                /* DW4_FRAME_TRACE=1: per-second work-time summary on stderr, taken just before the pacing
                 * sleep.  Work above one tick (16.7 ms) is a frame the port could not build in time; work
                 * below it with a low fps means pacing or presentation, not the renderer. */
                static int tr = -1, n = 0, over = 0, nload = 0, scr[6];
                static double sum = 0.0, mx = 0.0, t_log = 0.0;
                if (tr < 0) tr = getenv("DW4_FRAME_TRACE") != NULL;
                if (tr) {
                    double w = now_ms() - iteration_start;
                    n++; sum += w; if (w > mx) mx = w; if (w > 1000.0 / 60.0) over++;
                    if (loading || hub_loading) nload++;
                    scr[(loading || hub_loading) ? 4 : (!lobby && !hub) ? (logging_in ? 2 : chr_open ? 1 : opt_open ? 3 : 0) : 5]++;
                    if (t_log == 0.0) t_log = iteration_start;
                    if (iteration_start - t_log >= 1000.0) {
                        fprintf(stderr, "frame-trace: %d frames/s, work avg %.2f ms max %.2f ms, %d over 16.7 ms"
                                " | lobby tick %.2f draw %.2f post-draw %.2f present %.2f ms avg%s\n",
                                n, sum / n, mx, over, tr_tick / n, tr_draw / n, tr_post / n, tr_present / n,
                                nload ? (nload == n ? " [loading]" : " [partly loading]") : "");
                        fprintf(stderr, "  stage: %s screens: title %d chr %d login %d options %d loading %d world %d\n", trace_stage,
                                scr[0], scr[1], scr[2], scr[3], scr[4], scr[5]);
                        memset(scr, 0, sizeof scr);
                        nload = 0;
                        {double lt[16];dw4_lobby_trace_take(lt);
                         fprintf(stderr, "  mesh split: static %.2f actors %.2f instances %.2f effects/shadow %.2f ms; triangles/frame in %.0f out %.0f\n",
                                 lt[9]/n, lt[10]/n, lt[11]/n, lt[12]/n, lt[13]/n, lt[14]/n);
                         fprintf(stderr, "  draw split: node-drive %.2f mesh-loop %.2f (pose %.2f instances %.2f) shadow %.2f world %.2f native-ui %.2f dialogue/ui %.2f tail %.2f ms avg\n",
                                 lt[6]/n, lt[0]/n, lt[7]/n, lt[8]/n, lt[1]/n, lt[2]/n, lt[3]/n, lt[4]/n, lt[5]/n);}
                        tr_tick = tr_draw = tr_present = tr_post = 0.0;
                        n = over = 0; sum = mx = 0.0; t_log = iteration_start;
                    }
                }
            }
            /* Live windows (scripted or not) use the resettable schedule: the fixed-origin form catches a slow stretch
             * up by running flat out afterwards (a 140 fps burst after a hub load). Headless runs keep the
             * frame-indexed origin their checks depend on. */
            if (!o->headless)
                frame_pace_sched(&sched_due, o->fps_lock);
            else frame_pace(pace_origin, i, o->fps_lock);
        }
        frames_run = i + 1;
        if (soft_stop)
            break;
    }
    t1 = now_ms();
    printf("  title: presented %d frame(s) in %.0f ms; state=%s, selection %d = '%s'\n",
           frames_run, t1 - t0,
           (fui && dw4_frontui_state(fui) == DW4_FRONTUI_MENU) ? "menu" : "press-start",
           menu.sel, menu.nrow ? menu.row[menu.sel].label : "-");

    if (logging_in) {
        printf("  login: %s; %d lobby frame(s) presented in the boot window\n",
               lobby ? "arrived" : "closing", lobby_frame);
        rc = rc < 0 ? rc : 0;
    } else if (chose && menu.nrow > 0 && menu.sel == 0) {
        printf("  title: Cross on '%s' -> Game Start\n", menu.row[0].label);
        {
            int gr = dw4_frontend_game_start(o->roms, stage_out, stage_cap, o->fps);
            rc = (gr == 0) ? 1 : -1;
        }
    } else if (chose) {
        printf("  title: Cross on '%s' -> (no screen yet; the menu does not leave the title)\n",
               menu.row[menu.sel].label);
        rc = 0;
    } else {
        printf("  title: no confirmation; stopped at the title, awaiting input\n");
        rc = 0;
    }

done:
    if(dw4_gpu_policy_error()[0]){fprintf(stderr,"graphics: %s\n",dw4_gpu_policy_error());rc=-1;}
    if(getenv("DW4_GPU_POLICY_TRACE"))fprintf(stderr,
        "GPU policy CPU audit: UI %llu layer %llu mesh %llu fill %llu composite %llu\n",
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_UI),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_LAYER),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_MESH),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_FILL),
        (unsigned long long)dw4_gpu_policy_cpu_count(DW4_CPU_COMPOSITE));
    /* A transition worker still borrows source records/state. Join it before
     * cancelling or releasing any source owner, including on window close. */
    dw4_hubruntime_close(dw4_loadjob_close(hub_job));hub_job=NULL;
    if(scripts)dw4_scriptengine_remove_all(scripts,services.sd);
    else if(services.sd)dw4_scriptservices_remove_all(services.sd);
    /* Worker borrows the mount/context. Join before releasing either, and
     * reclaim an unpublished destination when the window closes mid-load. */
    dw4_hubruntime_close(prepared_hub);dw4_hubruntime_close(hub);dw4_frontui_close(hub_art);
    dw4_lobby_close(dw4_loadjob_close(load_job));
    dw4_lobby_close(prepared_lobby);
    dw4_frontui_close(loading_art);
    dw4_title_host_close(&title);
    dw4_gl_close(title_mesh);dw4_gl_layer_close(frame_gpu);
    dw4_lobby_detach_scripts(lobby);
    dw4_scriptengine_filelist(scripts,NULL);
    dw4_scriptengine_close(scripts);
    dw4_filelist_close(services.files);
    dw4_gl_layer_close(services.status_gpu);
    dw4_lobby_native_ui(lobby,NULL);
    dw4_modelview_close(services.travel_models);
    dw4_modelview_close(services.status_models);
    dw4_title_services_close(services.title);
    dw4_lobby_dialogue(lobby,NULL);
    dw4_dialogue_close(services.dialogue);
    dw4_statusstats_close(&services.status_stats);
    dw4_lobby_native_models(lobby,NULL,0);
    dw4_controllers_close(services.controllers);
    dw4_databases_close(services.databases);
    dw4_stageobjects_close(services.objects);
    dw4_scriptservices_close(services.sd);
    dw4_playerrecords_close(services.players);
    dw4_frontaudio_close(audio);
    if (win)
        dw4_window_close(win);
    dw4_vk_close(vk);
    if (fb.rgba || fb.z)
        dw4_fb_free(&fb);
    free(mb.pos);
    free(mb.nrm);
    free(mb.uv);
    free(mb.tris);
    dw4_fefont_free(&font);
    dw4_frontopt_close(fopt);
    dw4_savescene_close(call_scene);dw4_memcard_close(call_card);
    if (audio_job) dw4_frontaudio_close(dw4_loadjob_close(audio_job));
    if (front_job) {   /* left before the movie returned: the screens it opened are ours to close */
        dw4_loadjob_close(front_job);
        if(!flayer)dw4_frontlayer_close(front.layer);
        if(!fui)dw4_frontui_close(front.ui);
        if(!fopt)dw4_frontopt_close(front.opt);
        if(!fchr)dw4_frontchr_close(front.chr);
    }
    dw4_frontchr_close(fchr);
    dw4_lobby_close(lobby);
    dw4_frontlayer_close(flayer);
    dw4_frontui_close(fui);
    dw4_scene_close(&sc);
    dw4_mount_close(&mnt);
    engine_boot_shutdown(&boot);
    dw4_gpu_policy_begin(previous_gpu_policy);
    return rc;
}
