#include "dw4/actoranim.h"
#include "../third_party/enbrip/enbaya.h"
#include "dw4/igb.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#undef free

#define BONES 128   /* Blossomon's rig has 67 bones over 52 joints; a joint index is still < 64 (seen_joints is a 64-bit mask) */
#define TRANS_BIT(a,i) (((a)->translations[(i)/64]>>((i)%64))&1)
#define PALETTE 128   /* a skin's blend-matrix palette lists joints, repeating some: Blossomon's has 66 entries over 52 joints */
struct dw4_actoranim {
    enb_anim_context *ctx;
    uint8_t *stream;
    uint32_t n, joints, nv, parent[BONES], bm[BONES], track[BONES], palette[PALETTE];
    uint32_t npalette;uint64_t translations[BONES/64];   /* bit i: bone i's motion carries translation */
    float rest[BONES][3], inverse[BONES][16];
    char bone_name[BONES][64];
    const uint8_t *indices,*weights;uint32_t influences;
    float *pos, *norm;
    double duration;
    int64_t duration_ns;
    int once;
    double blend_from;
    float blend_weight;
    dw4_actoranim *blend_motion;
};
static uint32_t u32(const void *p)
{
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static uint32_t val(const dw4_igb_record *r, unsigned slot)
{
    uint32_t i;
    for (i = 0; i < r->nvalues; i++)
        if (r->values[i].ordinal == slot)
            return r->values[i].raw;
    return UINT32_MAX;
}
static int rec(const dw4_igb *g, uint32_t id, dw4_igb_record *r)
{
    uint32_t off;
    memset(r, 0, sizeof *r);
    return dw4_igb_ref(g, id, &off, NULL) == 2 && dw4_igb_decode(g, off, r);
}
static const uint8_t *list(const dw4_igb *g, uint32_t id, uint32_t *n)
{
    dw4_igb_record r;
    const uint8_t *p = NULL;
    uint32_t len = 0;
    *n = 0;
    if (rec(g, id, &r)) {
        p = dw4_igb_block(g, val(&r, 4), &len);
        if (p && val(&r, 2) <= len / 4)
            *n = val(&r, 2);
        else
            p = NULL;
        dw4_igb_record_free(&r);
    }
    return p;
}
static void mul(float *out, const float *a, const float *b)
{
    float m[16];
    int i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            m[i * 4 + j] = 0;
            for (k = 0; k < 4; k++)
                m[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
        }
    memcpy(out, m, sizeof m);
}
static void matrix(float *m, const quat_trans *qt, const float *t)
{
    float x = qt->quat.x, y = qt->quat.y, z = qt->quat.z, w = qt->quat.w;
    /* Same quaternion convention as scene.c's transform sequences. */
    m[0] = 1 - 2 * (y * y + z * z);
    m[1] = 2 * (x * y - z * w);
    m[2] = 2 * (x * z + y * w);
    m[3] = 0;
    m[4] = 2 * (x * y + z * w);
    m[5] = 1 - 2 * (x * x + z * z);
    m[6] = 2 * (y * z - x * w);
    m[7] = 0;
    m[8] = 2 * (x * z - y * w);
    m[9] = 2 * (y * z + x * w);
    m[10] = 1 - 2 * (x * x + y * y);
    m[11] = 0;
    m[12] = t[0];
    m[13] = t[1];
    m[14] = t[2];
    m[15] = 1;
}

static dw4_actoranim *open_motion(const uint8_t *blob, uint32_t size, const dw4_scene *s, uint32_t node, const char *motion,uint32_t database,char *error,size_t cap)
{
    dw4_igb g;
    dw4_igb_record r;
    dw4_actoranim *a = NULL;
    const char *step="palette";
    const uint8_t *p;
    uint32_t j, k, n, len, skel = UINT32_MAX, anim = UINT32_MAX, tracklist = 0, bind = 0,
                           streamid = UINT32_MAX;
    if (node >= s->nnode || dw4_igb_open(&g, blob, size, 0))
        return NULL;
    if (dw4_igb_refs_open(&g)) {
        dw4_igb_close(&g);
        return NULL;
    }
    a = calloc(1, sizeof *a);
    if (!a)
        goto fail;
    for (j = node; j < s->nnode; j = s->node[j].parent)
        if (s->node[j].class_name && !strcmp(s->node[j].class_name, "igBlendMatrixSelect"))
            break;
    if (j >= s->nnode || !rec(&g, s->node[j].id, &r))
        goto fail;
    p = list(&g, val(&r, 10), &n);
    dw4_igb_record_free(&r);
    if (!p || !n || n > PALETTE)
        goto fail;
    a->npalette = n;
    for (j = 0; j < n; j++) {
        a->palette[j] = u32(p + 4 * j);
        if (a->palette[j] >= BONES)
            goto fail;
        if (a->palette[j] >= a->joints)
            a->joints = a->palette[j] + 1;
    }
    step="skeleton selection";
    const uint8_t *skeletons=NULL,*animations=NULL;uint32_t nskeletons=g.table_n,nanimations=g.table_n;
    if(database!=UINT32_MAX) {
        if(!rec(&g,database,&r))goto fail;
        int valid=!strcmp(r.class_name,"igAnimationDatabase");
        uint32_t skeleton_list=val(&r,5),animation_list=val(&r,6);dw4_igb_record_free(&r);
        if(!valid || !(skeletons=list(&g,skeleton_list,&nskeletons)) ||
           !(animations=list(&g,animation_list,&nanimations)))goto fail;
    }
    /* A full area pack contains rigs with equal joint counts. The owning
     * Action2 database bounds both skeleton and motion selection. Legacy
     * standalone preview callers retain their unique-rig contract. */
    for(uint32_t candidate=0;candidate<nskeletons;candidate++) {
        j=skeletons?u32(skeletons+4*candidate):candidate;
        if(j<g.table_n && g.id_kind[j]==2 && rec(&g,j,&r)) {
            int match=!strcmp(r.class_name,"igSkeleton") && val(&r,6)==a->joints;
            dw4_igb_record_free(&r);
            if(match){if(skel!=UINT32_MAX)goto fail;skel=j;}
        }
    }
    step="skeleton layout";
    if (!rec(&g, skel, &r))
        goto fail;
    uint32_t restid = val(&r, 3), boneid = val(&r, 4), invid = val(&r, 5);
    dw4_igb_record_free(&r);
    p = list(&g, boneid, &a->n);
    if (!p || !a->n || a->n > BONES)
        goto fail;
    uint64_t seen_joints = 0;
    for (j = 0; j < a->n; j++) {
        if (!rec(&g, u32(p + 4 * j), &r))
            goto fail;
        a->parent[j] = val(&r, 3);
        a->bm[j] = val(&r, 4);
        if (r.name) snprintf(a->bone_name[j], sizeof a->bone_name[j], "%s", r.name);
        dw4_igb_record_free(&r);
        if (a->parent[j] != UINT32_MAX && a->parent[j] >= j)
            goto fail;
        if (a->bm[j] != UINT32_MAX) {
            if (a->bm[j] >= a->joints || (seen_joints & (UINT64_C(1) << a->bm[j])))
                goto fail;
            seen_joints |= UINT64_C(1) << a->bm[j];
        }
    }
    if (a->joints >= 64 || seen_joints != (UINT64_C(1) << a->joints) - 1)
        goto fail;
    p = dw4_igb_block(&g, restid, &len);
    if (!p || len != a->n * 12)
        goto fail;
    memcpy(a->rest, p, len);
    p = dw4_igb_block(&g, invid, &len);
    if (!p || len != a->joints * 64)
        goto fail;
    memcpy(a->inverse, p, len);
    step="bound motion";
    for (uint32_t candidate=0;candidate<nanimations;candidate++) {
        j=animations?u32(animations+4*candidate):candidate;
        if (j<g.table_n && g.id_kind[j] == 2 && rec(&g, j, &r)) {
            uint32_t bl = val(&r, 4), tl = val(&r, 5), bits = val(&r, 10);
            int match = !strcmp(r.class_name, "igAnimation") && r.name && motion && !strcmp(r.name, motion);
            dw4_igb_record_free(&r);
            if (!match)
                continue;
            p = list(&g, bl, &n);
            if (!p || n != 1 || !rec(&g, u32(p), &r))
                continue;
            match = val(&r, 2) == skel;
            uint32_t bi = val(&r, 3);
            dw4_igb_record_free(&r);
            if (match) {
                anim = j;
                tracklist = tl;
                bind = bi;
                if (bits == UINT32_MAX) {
                    memset(a->translations, 0, sizeof a->translations);
                    break;
                }
                if (!rec(&g, bits, &r))
                    goto fail;
                uint32_t bit_count=val(&r,5);
                p = dw4_igb_block(&g, val(&r, 4), &len);
                dw4_igb_record_free(&r);
                step="translation mask";
                if(bit_count==UINT32_MAX)goto fail;
                unsigned needed=(bit_count<BONES?bit_count:BONES)+31;needed/=32;
                if(needed && (!p || len<needed*4))goto fail;
                memset(a->translations,0,sizeof a->translations);
                for(unsigned w=0;w<needed;w++)a->translations[w/2]|=(uint64_t)u32(p+4*w)<<(32*(w%2));
                for(unsigned bit=bit_count;bit<BONES;bit++)a->translations[bit/64]&=~(UINT64_C(1)<<(bit%64));
                break;
            }
        }
    }
    step="motion duration/binding";
    if (anim == UINT32_MAX)
        goto fail;
    if (!rec(&g, anim, &r)) goto fail;
    for (j=0;j<r.nvalues;j++) if (r.values[j].ordinal==9)
        memcpy(&a->duration_ns,g.data+r.values[j].voff,8);
    dw4_igb_record_free(&r);
    if (a->duration_ns<=0) goto fail;
    p = dw4_igb_block(&g, bind, &len);
    if (!p || len != a->n * 4)
        goto fail;
    uint32_t binding[BONES];
    memcpy(binding, p, len);
    p = list(&g, tracklist, &n);
    if (!p || n > BONES)
        goto fail;
    uint32_t tracks[BONES];
    memcpy(tracks, p, n * 4);
    for (j = 0; j < a->n; j++) {
        if (binding[j] >= n || !rec(&g, tracks[binding[j]], &r))
            goto fail;
        k = val(&r, 3);
        dw4_igb_record_free(&r);
        if (!rec(&g, k, &r))
            goto fail;
        a->track[j] = val(&r, 2);
        k = val(&r, 3);
        dw4_igb_record_free(&r);
        if (!rec(&g, k, &r))
            goto fail;
        k = val(&r, 2);
        dw4_igb_record_free(&r);
        if (streamid != UINT32_MAX && streamid != k)
            goto fail;
        streamid = k;
    }
    step="compressed stream";
    p = dw4_igb_block(&g, streamid, &len);
    if (!p || len < 80)
        goto fail;
    /* Header lengths are byte lengths, including the bit-packed channels. */
    uint64_t total = 80;
    for (j = 5; j <= 18; j++)
        total += u32(p + 4 * j);
    if (total != len || u32(p + 4) > BONES || !u32(p + 4) || u32(p + 16) != 30)
        goto fail;
    for (j = 0; j < a->n; j++)
        if (a->track[j] >= u32(p + 4))
            goto fail;
    a->stream = malloc(len);
    if (!a->stream)
        goto fail;
    memcpy(a->stream, p, len);
    float duration;
    memcpy(&duration, p + 12, 4);
    a->duration = duration;
    if (!isfinite(duration) || duration <= 0 || duration > 10 || enb_initialize(a->stream, &a->ctx))
        goto fail;
    step="vertex weights";
    const dw4_scene_mesh *mesh = &s->mesh[s->node[node].mesh];
    a->nv = mesh->num_verts;
    if (!rec(&g, mesh->vertex_array_id, &r))
        goto fail;
    uint32_t wi = val(&r, 7), ii = val(&r, 8);
    dw4_igb_record_free(&r);
    p = dw4_igb_block(&g, wi, &len);
    if(!a->nv || a->nv>UINT32_MAX/4 || !p || len%(a->nv*4))goto fail;
    a->influences=len/(a->nv*4);
    if(!a->influences || a->influences>4)goto fail;
    a->weights=p;
    for(size_t i=0;i<(size_t)a->nv*a->influences;i++) {
        float w;memcpy(&w,p+4*i,4);if(!isfinite(w))goto fail;
    }
    step="skin indices";
    a->indices = dw4_igb_block(&g, ii, &len);
    if(!a->indices || len!=(size_t)a->nv*a->influences)goto fail;
    for(size_t i=0;i<len;i++)if(a->indices[i]>=a->npalette)goto fail;
    a->pos = malloc(a->nv * 3 * sizeof(float));
    a->norm = malloc(a->nv * 3 * sizeof(float));
    if (!a->pos || !a->norm)
        goto fail;
    printf("  preview animation: %s %s, %u bones, %.3fs, %u weight(s)\n", mesh->name, motion, a->n, a->duration,a->influences);
    dw4_igb_close(&g);
    return a;
fail:
    if(error && cap)snprintf(error,cap,"animation %s: %s failed (%u bones / %u joints)",motion?motion:"<none>",step,a?a->n:0,a?a->joints:0);
    dw4_actoranim_close(a);
    dw4_igb_close(&g);
    return NULL;
}
dw4_actoranim *dw4_actoranim_open_motion(const uint8_t *blob,uint32_t size,const dw4_scene *s,uint32_t node,const char *motion)
{return open_motion(blob,size,s,node,motion,UINT32_MAX,NULL,0);}
dw4_actoranim *dw4_actoranim_open_motion_database(const uint8_t *blob,uint32_t size,const dw4_scene *s,uint32_t node,const char *motion,uint32_t database,char *error,size_t cap)
{return open_motion(blob,size,s,node,motion,database,error,cap);}
dw4_actoranim *dw4_actoranim_open(const uint8_t *blob, uint32_t size, const dw4_scene *s, uint32_t node)
{
    return dw4_actoranim_open_motion(blob, size, s, node, "waitC");
}
double dw4_actoranim_duration(const dw4_actoranim *a) { return a ? a->duration : 0; }
int64_t dw4_actoranim_duration_ns(const dw4_actoranim *a) { return a ? a->duration_ns : 0; }
void dw4_actoranim_loop(dw4_actoranim *a,int enabled) { if(a) a->once=!enabled; }
void dw4_actoranim_blend(dw4_actoranim *a,double from,float weight)
{ if(a) {a->blend_from=from;a->blend_weight=weight;a->blend_motion=NULL;} }
int dw4_actoranim_blend_motion(dw4_actoranim *a,dw4_actoranim *source,double from,float weight)
{
    if(!a || !source || a->n!=source->n || !isfinite(from) || !isfinite(weight))return -1;
    for(unsigned i=0;i<a->n;i++)if(strcmp(a->bone_name[i],source->bone_name[i]) || a->parent[i]!=source->parent[i])return -1;
    a->blend_from=from;a->blend_weight=fmaxf(0,fminf(1,weight));a->blend_motion=source;return 0;
}
void dw4_actoranim_close(dw4_actoranim *a)
{
    if (!a)
        return;
    enb_free(&a->ctx);
    free(a->stream);
    free(a->pos);
    free(a->norm);
    free(a);
}
static void bone_matrices(dw4_actoranim *a, double seconds, float world[BONES][16])
{
    float t = (float)(a->once ? fmin(fmax(0,seconds),a->duration) :
                              fmod(fmax(0, seconds), a->duration));
    for (uint32_t i = 0; i < a->n; i++) {
        quat_trans qt;
        enb_get_component_values(a->ctx, t, a->track[i], &qt, QUAT_TRANS_INTERP_SLERP,
                                 QUAT_TRANS_INTERP_LERP);
        if(a->blend_weight>0) {
            quat_trans previous, mixed;
            dw4_actoranim *source=a->blend_motion?a->blend_motion:a;
            float pt=(float)(source->once?fmin(fmax(0,a->blend_from),source->duration):fmod(fmax(0,a->blend_from),source->duration));
            enb_get_component_values(source->ctx,pt,source->track[i],&previous,
                                     QUAT_TRANS_INTERP_SLERP,QUAT_TRANS_INTERP_LERP);
            if(!TRANS_BIT(a,i))memcpy(&qt.trans.x,a->rest[i],sizeof a->rest[i]);
            if(!TRANS_BIT(source,i))memcpy(&previous.trans.x,source->rest[i],sizeof source->rest[i]);
            interp_quat_trans(&qt,&previous,&mixed,a->blend_weight,
                              QUAT_TRANS_INTERP_SLERP,QUAT_TRANS_INTERP_LERP);
            qt=mixed;
        }
        matrix(world[i], &qt, (a->blend_weight>0 || TRANS_BIT(a,i)) ? &qt.trans.x : a->rest[i]);
        if (a->parent[i] != UINT32_MAX)
            mul(world[i], world[i], world[a->parent[i]]);
    }
}
int dw4_actoranim_bone(dw4_actoranim *a, const char *name, double seconds, float out[16])
{
    float world[BONES][16];
    if (!a || !name || !out || !isfinite(seconds)) return -1;
    for (uint32_t i = 0; i < a->n; i++) if (!strcmp(a->bone_name[i], name)) {
        bone_matrices(a, seconds, world);
        memcpy(out, world[i], sizeof world[i]);
        return 0;
    }
    return -1;
}
int dw4_actoranim_pose(dw4_actoranim *a, const dw4_scene *s, uint32_t node, double seconds,
                       const float **positions, const float **normals)
{
    float world[BONES][16], skin[BONES][16];
    uint32_t i, j;
    if (!a || node >= s->nnode || !isfinite(seconds)) return -1;
    const dw4_scene_mesh *m = &s->mesh[s->node[node].mesh];
    const float *p = dw4_scene_host(s, m->positions), *n = dw4_scene_host(s, m->normals);
    bone_matrices(a, seconds, world);
    for (i = 0; i < a->n; i++) if (a->bm[i] != UINT32_MAX)
        mul(skin[a->bm[i]], a->inverse[a->bm[i]], world[i]);
    for(i=0;i<a->nv;i++)for(j=0;j<3;j++) {
        float position=0,normal=0;
        for(unsigned k=0;k<a->influences;k++) {
            size_t index=(size_t)i*a->influences+k;float weight;
            memcpy(&weight,a->weights+4*index,4);
            const float *mat=skin[a->palette[a->indices[index]]];
            position+=weight*(p[i*3]*mat[j]+p[i*3+1]*mat[4+j]+p[i*3+2]*mat[8+j]+mat[12+j]);
            if(n)normal+=weight*(n[i*3]*mat[j]+n[i*3+1]*mat[4+j]+n[i*3+2]*mat[8+j]);
        }
        a->pos[i*3+j]=position;a->norm[i*3+j]=normal;
    }
    *positions = a->pos;
    *normals = a->norm;
    return 0;
}
