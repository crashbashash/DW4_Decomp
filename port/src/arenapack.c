/* dw4/arenapack.c — a pack's objects as typed instances in the game arena (porting P1, docs/arena-object-model.md).
 *
 * Pass 1 allocates a block for every pool block and every object (the object's bytes come from dw4_object_from_record, which
 * already lays values out at the reflected offsets and stamps the header); string fields get their own blocks. Pass 2 rewrites the
 * reference fields from pack ids into handles. Types 0 and 7 are the reference descriptors (finding #482). */
#include "dw4/arenapack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw4/object.h"

/* The generated schema lists only a class's own fields; a pack record holds the ancestors' values too. A merged copy of the class
 * (ancestors' fields first, offsets are absolute) is built once per class. */
static const dw4_metaobject *merged_class(const dw4_metaobject **cache, const dw4_metaobject *mo)
{
    const dw4_metaobject *chain[32];
    dw4_metaobject *m;
    dw4_metafield *f;
    uint32_t n = 0, nf = 0, i;
    size_t idx;
    const dw4_metaobject *c;

    if (!mo) return NULL;
    idx = (size_t)(mo - dw4_metaobjects);
    if (idx >= (size_t)dw4_nmetaobjects) return mo;
    if (cache[idx]) return cache[idx];
    for (c = mo; c && n < 32; c = c->parent && c->parent[0] ? dw4_metaobject_find(c->parent) : NULL) {
        chain[n++] = c;
        nf += c->nfields;
    }
    m = (dw4_metaobject *)calloc(1, sizeof *m + (nf ? nf : 1) * sizeof *f);
    if (!m) return mo;
    f = (dw4_metafield *)(m + 1);
    *m = *mo;
    m->fields = f;
    m->nfields = nf;
    for (i = n; i-- > 0;) {
        if (chain[i]->nfields) memcpy(f, chain[i]->fields, chain[i]->nfields * sizeof *f);
        f += chain[i]->nfields;
    }
    cache[idx] = m;
    return m;
}

/* The element kind of a list's pool block belongs to the list class, not to the block (scene.h): the igObjectList family
 * (169 classes, igNamedObjectList among them) stores object ids, which become handles here. Other list families (int, string,
 * vector...) keep their raw contents until something reads them as references. */
static int is_object_list(const dw4_metaobject *mo)
{
    unsigned depth;
    for (depth = 0; mo && depth < 32; depth++) {
        if (!strcmp(mo->name, "igObjectList")) return 1;
        mo = (mo->parent && mo->parent[0]) ? dw4_metaobject_find(mo->parent) : NULL;
    }
    return 0;
}

typedef struct {
    uint32_t id;
    dw4_handle h;
    const dw4_metaobject *mo;
    uint32_t size;
} loaded_obj;

static void put_u32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

static uint32_t get_u32(const uint8_t *p) { return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }

dw4_handle dw4_arena_pack_handle(const dw4_arena_pack *p, uint32_t id)
{
    dw4_handle none = {0};
    return (p && p->map && id < p->nids) ? p->map[id] : none;
}

void dw4_arena_pack_free(dw4_arena_pack *p)
{
    if (!p) return;
    free(p->map);
    free(p->owned.h);
    memset(p, 0, sizeof *p);
}

void dw4_arena_pack_release(dw4_arena *a, dw4_arena_pack *p)
{
    if (!p) return;
    dw4_arena_owned_release(a, &p->owned);
    dw4_arena_pack_free(p);
}

static int fail(char *error, size_t cap, const char *what, uint32_t id)
{
    if (error && cap) snprintf(error, cap, "arena pack load: %s (id %u)", what, id);
    return -1;
}

static int load_impl(dw4_arena *a, dw4_region region, const dw4_igb *g, const uint32_t *roots, size_t nroots, int shallow,
                     dw4_arena_pack *out, char *error, size_t cap);

int dw4_arena_pack_load(dw4_arena *a, dw4_region region, const dw4_igb *g, dw4_arena_pack *out, char *error, size_t cap)
{
    return load_impl(a, region, g, NULL, 0, 0, out, error, cap);
}

int dw4_arena_pack_load_from(dw4_arena *a, dw4_region region, const dw4_igb *g, const uint32_t *roots, size_t nroots,
                             dw4_arena_pack *out, char *error, size_t cap)
{
    return load_impl(a, region, g, roots, nroots, 0, out, error, cap);
}

int dw4_arena_pack_load_roots(dw4_arena *a, dw4_region region, const dw4_igb *g, const uint32_t *roots, size_t nroots,
                              dw4_arena_pack *out, char *error, size_t cap)
{
    return load_impl(a, region, g, roots, nroots, 1, out, error, cap);
}

static int load_impl(dw4_arena *a, dw4_region region, const dw4_igb *g, const uint32_t *roots, size_t nroots, int shallow,
                     dw4_arena_pack *out, char *error, size_t cap)
{
    loaded_obj *objs = NULL;
    const dw4_metaobject **classes = NULL;
    uint8_t *done_blocks = NULL;
    size_t nobj = 0, cobj = 0, k, qi, qn = 0;
    uint32_t id, *queue = NULL;
    uint8_t *queued = NULL;
    int rc = -1;

    if (error && cap) error[0] = 0;
    if (!a || !g || !out || !g->id_kind || !g->table_n) return fail(error, cap, "the pack's id tables are not open", 0);
    memset(out, 0, sizeof *out);
    out->nids = g->table_n;
    out->map = (dw4_handle *)calloc(out->nids, sizeof *out->map);
    classes = (const dw4_metaobject **)calloc((size_t)dw4_nmetaobjects + 1u, sizeof *classes);
    queue = (uint32_t *)calloc(out->nids, sizeof *queue);
    queued = (uint8_t *)calloc(out->nids, 1);
    if (!out->map || !classes || !queue || !queued) {
        free(out->map);
        free(classes);
        free(queue);
        free(queued);
        memset(out, 0, sizeof *out);
        return fail(error, cap, "out of memory", 0);
    }

#define ENQUEUE(i) do { uint32_t q_ = (i); if (q_ < out->nids && !queued[q_]) { queued[q_] = 1; queue[qn++] = q_; } } while (0)
    /* the roots (or every id), then whatever they reach: reference fields and, for an object list, the ids in its block */
    if (roots) {
        for (k = 0; k < nroots; k++) ENQUEUE(roots[k]);
    } else {
        for (id = 0; id < g->table_n; id++) ENQUEUE(id);
    }
    for (qi = 0; qi < qn; qi++) {
        uint32_t off = 0, len = 0;
        int kind;
        id = queue[qi];
        kind = dw4_igb_ref(g, id, &off, &len);
        if (kind == 1) {                                  /* a pool block */
            uint32_t n = 0;
            const uint8_t *src = dw4_igb_block(g, id, &n);
            dw4_handle h;
            if (!src) {
                out->skipped++;
                continue;
            }
            h = dw4_arena_alloc(a, region, n ? n : 1u);
            if (!h.off || dw4_arena_owned_add(&out->owned, h)) {
                rc = fail(error, cap, h.off ? "out of memory" : dw4_arena_status_text(dw4_arena_status_last(a)), id);
                goto done;
            }
            if (n) memcpy(dw4_arena_at(a, h, n), src, n);
            out->map[id] = h;
            out->blocks++;
        } else if (kind == 2) {                           /* an object record */
            dw4_igb_record r = {0};
            dw4_object o = {0};
            dw4_handle h;
            uint32_t j;
            if (!dw4_igb_decode(g, off, &r)) {
                out->skipped++;
                continue;
            }
            if (dw4_object_from_record_with(&o, g, &r, merged_class(classes, dw4_metaobject_find(r.class_name)))) {
                dw4_igb_record_free(&r);
                rc = fail(error, cap, "out of memory", id);
                goto done;
            }
            dw4_igb_record_free(&r);
            h = dw4_arena_alloc(a, region, o.size);
            if (!h.off || dw4_arena_owned_add(&out->owned, h)) {
                dw4_object_free(&o);
                rc = fail(error, cap, h.off ? "out of memory" : dw4_arena_status_text(dw4_arena_status_last(a)), id);
                goto done;
            }
            memcpy(dw4_arena_at(a, h, o.size), o.data, o.size);
            for (j = 0; o.mo && j < o.mo->nfields; j++) {   /* string fields: a handle to a NUL-terminated block */
                const dw4_metafield *f = &o.mo->fields[j];
                dw4_handle s = {0};
                if (f->tid != 4 || !o.str || !o.str[j] || f->offset + 4u > o.size) continue;
                s = dw4_arena_alloc(a, region, (uint32_t)strlen(o.str[j]) + 1u);
                if (!s.off || dw4_arena_owned_add(&out->owned, s)) {
                    dw4_object_free(&o);
                    rc = fail(error, cap, s.off ? "out of memory" : dw4_arena_status_text(dw4_arena_status_last(a)), id);
                    goto done;
                }
                memcpy(dw4_arena_at(a, s, (uint32_t)strlen(o.str[j]) + 1u), o.str[j], strlen(o.str[j]) + 1u);
                put_u32((uint8_t *)dw4_arena_at(a, h, o.size) + f->offset, s.off);
                out->strings++;
            }
            if (nobj == cobj) {
                loaded_obj *n = (loaded_obj *)realloc(objs, (cobj ? cobj * 2 : 1024) * sizeof *n);
                if (!n) {
                    dw4_object_free(&o);
                    rc = fail(error, cap, "out of memory", id);
                    goto done;
                }
                objs = n;
                cobj = cobj ? cobj * 2 : 1024;
            }
            objs[nobj].id = id;
            objs[nobj].h = h;
            objs[nobj].mo = o.mo;
            objs[nobj].size = o.size;
            nobj++;
            out->map[id] = h;
            out->objects++;
            if (roots && o.mo && !shallow) {                    /* discover what this object reaches */
                int list = is_object_list(o.mo);
                uint32_t block_id = 0xffffffffu, count = 0;
                for (j = 0; j < o.mo->nfields; j++) {
                    const dw4_metafield *f = &o.mo->fields[j];
                    uint32_t v;
                    if (!dw4_object_field_is_ref(f->tid) || f->offset + 4u > o.size) continue;
                    v = get_u32(o.data + f->offset);
                    ENQUEUE(v);
                    if (list && f->tid == 7 && !strcmp(f->name, "_data")) block_id = v;
                }
                if (list && block_id != 0xffffffffu && o.size >= 12) {
                    uint32_t bytes = 0, e;
                    const uint8_t *blk = dw4_igb_block(g, block_id, &bytes);
                    count = get_u32(o.data + 8);
                    for (e = 0; blk && e < count && (e + 1u) * 4u <= bytes; e++) ENQUEUE(get_u32(blk + 4u * e));
                }
            }
            dw4_object_free(&o);
        } else {
            out->skipped++;
        }
    }

    /* pass 2: rewrite every reference field from a pack id into a handle; an object list's block holds object ids too */
    done_blocks = (uint8_t *)calloc(out->nids, 1);
    if (!done_blocks) {
        rc = fail(error, cap, "out of memory", 0);
        goto done;
    }
    for (k = 0; k < nobj; k++) {
        uint32_t j;
        uint8_t *base;
        int object_list;
        if (!objs[k].mo) continue;
        base = (uint8_t *)dw4_arena_at(a, objs[k].h, 1);
        object_list = is_object_list(objs[k].mo);
        for (j = 0; j < objs[k].mo->nfields; j++) {
            const dw4_metafield *f = &objs[k].mo->fields[j];
            uint32_t v;
            if (!dw4_object_field_is_ref(f->tid) || f->offset + 4u > objs[k].size) continue;
            v = get_u32(base + f->offset);
            if (object_list && f->tid == 7 && !strcmp(f->name, "_data") && v < out->nids && out->map[v].off && !done_blocks[v]) {
                uint32_t count = get_u32(base + 8), n, e;       /* igDataList: _count at +8 */
                uint8_t *blk = (uint8_t *)dw4_arena_at(a, out->map[v], 4);
                done_blocks[v] = 1;                             /* a shared block is converted once */
                if (blk) {
                    n = count;
                    while (n && !dw4_arena_at(a, out->map[v], n * 4u)) n--;   /* only what the block holds */
                    for (e = 0; e < n; e++) {
                        uint32_t id2 = get_u32(blk + 4u * e);
                        put_u32(blk + 4u * e, (id2 == 0xffffffffu || id2 >= out->nids) ? 0u : out->map[id2].off);
                    }
                }
            }
            put_u32(base + f->offset, (v == 0xffffffffu || v >= out->nids) ? 0u : out->map[v].off);
        }
    }
    rc = 0;
done:
    free(objs);
    free(done_blocks);
    free(queue);
    free(queued);
    if (classes) {
        for (k = 0; k < (size_t)dw4_nmetaobjects; k++)
            if (classes[k]) free((void *)classes[k]);
        free(classes);
    }
    if (rc) dw4_arena_pack_release(a, out);
    return rc;
}
