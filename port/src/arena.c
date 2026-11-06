/* The game arena, class registry and igObject reference counting. Layout: [0, DW4_ARENA_BASE) is
 * never handed out, the persistent region grows up from there, the stage region grows down from
 * the end. Every block is a 16-byte header followed by a 16-byte aligned payload; the handle is
 * the payload's offset, so the header sits at handle - 16 and a handle is validated by finding a
 * live header there. */
#include "dw4/arena.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw4/object.h"
#include "dw4/reflected.h"   /* the decomp's authoritative igObject layout */

#define HDR 16u
#define MAGIC_LIVE 0xa11c0de1u
#define MAGIC_FREE 0xf4eeb10cu
#define MAX_CLASS_PAYLOAD 65536u            /* free lists are exact-size classes up to this payload */
#define NCLASS (MAX_CLASS_PAYLOAD / DW4_ARENA_ALIGN + 1)
#define REFS_MASK 0x007fffffu               /* low 23 bits of igObject::_refCount; the rest are flags (igObject_InitHeader) */
#define MAX_SLOTS 256u

typedef struct {
    uint32_t size;      /* payload bytes (a multiple of 16) */
    uint32_t magic;
    uint32_t next;      /* free-list link (header offset), 0 = end */
    uint32_t region;
} block_hdr;

typedef struct {
    uint32_t vtable, parent, size;
    char name[64];
    dw4_slot_fn *slots;
    unsigned nslots;
    int used;
} class_entry;

struct dw4_arena {
    pthread_mutex_t lock;    /* every entry point takes it: loaders and the simulation may share the session arena */
    uint8_t *mem;
    uint32_t len;
    uint32_t pers_top;       /* next persistent header offset */
    uint32_t stage_bottom;   /* lowest stage header offset (== len when empty) */
    uint32_t free_head[NCLASS];
    uint32_t big_head;
    uint32_t live[2];
    uint32_t used[2];
    dw4_arena_status status;
    class_entry *classes;    /* open-addressing table keyed by vtable word */
    size_t class_cap, class_count;
};

#define LOCK(a) pthread_mutex_lock(&(a)->lock)
#define UNLOCK(a) pthread_mutex_unlock(&(a)->lock)

static uint32_t round16(uint32_t n) { return (n + (DW4_ARENA_ALIGN - 1u)) & ~(DW4_ARENA_ALIGN - 1u); }

static void fail(dw4_arena *a, dw4_arena_status s) { a->status = s; }

const char *dw4_arena_status_text(dw4_arena_status s)
{
    switch (s) {
    case DW4_ARENA_OK: return "ok";
    case DW4_ARENA_EXHAUSTED: return "arena exhausted";
    case DW4_ARENA_BAD_SIZE: return "bad allocation size";
    case DW4_ARENA_BAD_HANDLE: return "bad handle";
    case DW4_ARENA_NOT_LIVE: return "block is not live";
    case DW4_ARENA_TOO_SMALL: return "access larger than the block";
    case DW4_ARENA_BAD_CLASS: return "unknown class";
    case DW4_ARENA_COUNT_RANGE: return "reference count out of range";
    }
    return "?";
}

dw4_arena_status dw4_arena_status_last(const dw4_arena *a) { return a ? a->status : DW4_ARENA_BAD_HANDLE; }

dw4_arena *dw4_arena_open(size_t bytes, char *error, size_t cap)
{
    dw4_arena *a;
    const uint32_t probe = 1u;

    if (error && cap) error[0] = 0;
    if (*(const uint8_t *)&probe != 1) {
        if (error && cap) snprintf(error, cap, "the arena needs a little-endian host");
        return NULL;
    }
    if (!bytes) bytes = DW4_ARENA_RETAIL_BYTES;
    if (bytes < DW4_ARENA_BASE + 4u * HDR || bytes > 0xffff0000u) {
        if (error && cap) snprintf(error, cap, "arena size %zu is out of range", bytes);
        return NULL;
    }
    bytes &= ~(size_t)(DW4_ARENA_ALIGN - 1u);
    a = (dw4_arena *)calloc(1, sizeof *a);
    if (a) a->mem = (uint8_t *)calloc(1, bytes);
    if (!a || !a->mem) {
        if (error && cap) snprintf(error, cap, "cannot allocate %zu arena bytes", bytes);
        if (a) free(a->mem);
        free(a);
        return NULL;
    }
    {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&a->lock, &attr);
        pthread_mutexattr_destroy(&attr);
    }
    a->len = (uint32_t)bytes;
    a->pers_top = DW4_ARENA_BASE;
    a->stage_bottom = a->len;
    return a;
}

void dw4_arena_close(dw4_arena *a)
{
    size_t i;
    if (!a) return;
    for (i = 0; i < a->class_cap; i++) free(a->classes[i].slots);
    free(a->classes);
    free(a->mem);
    pthread_mutex_destroy(&a->lock);
    free(a);
}

/* The header of a live block starting at `h`, or NULL (status set). */
static block_hdr *locate(dw4_arena *a, dw4_handle h)
{
    block_hdr *b;
    if (h.off < DW4_ARENA_BASE + HDR || (h.off & (DW4_ARENA_ALIGN - 1u)) || h.off >= a->len) {
        fail(a, DW4_ARENA_BAD_HANDLE);
        return NULL;
    }
    b = (block_hdr *)(a->mem + h.off - HDR);
    if (b->magic != MAGIC_LIVE) {
        fail(a, b->magic == MAGIC_FREE ? DW4_ARENA_NOT_LIVE : DW4_ARENA_BAD_HANDLE);
        return NULL;
    }
    return b;
}

static uint32_t class_of(uint32_t payload) { return payload / DW4_ARENA_ALIGN; }

static dw4_handle dw4_arena_alloc_nl(dw4_arena *a, dw4_region region, uint32_t bytes)
{
    dw4_handle none = {0};
    dw4_handle h;
    uint32_t payload, off = 0;
    block_hdr *b;

    if (!a) return none;
    if (!bytes || bytes > a->len) {
        fail(a, DW4_ARENA_BAD_SIZE);
        return none;
    }
    payload = round16(bytes);
    if (region == DW4_REGION_PERSISTENT) {
        if (class_of(payload) < NCLASS && a->free_head[class_of(payload)]) {   /* an exact-size free block */
            off = a->free_head[class_of(payload)];
            a->free_head[class_of(payload)] = ((block_hdr *)(a->mem + off))->next;
        } else if (payload > MAX_CLASS_PAYLOAD && a->big_head) {                /* first fit among the large free blocks */
            uint32_t prev = 0, cur = a->big_head;
            while (cur) {
                block_hdr *c = (block_hdr *)(a->mem + cur);
                if (c->size >= payload) {
                    if (prev) ((block_hdr *)(a->mem + prev))->next = c->next;
                    else a->big_head = c->next;
                    off = cur;
                    break;
                }
                prev = cur;
                cur = c->next;
            }
        }
        if (!off) {
            if ((uint64_t)a->pers_top + HDR + payload > a->stage_bottom) {
                fail(a, DW4_ARENA_EXHAUSTED);
                return none;
            }
            off = a->pers_top;
            a->pers_top += HDR + payload;
            b = (block_hdr *)(a->mem + off);
            b->size = payload;
            a->used[DW4_REGION_PERSISTENT] += HDR + payload;
        }
    } else {
        if ((uint64_t)a->stage_bottom < (uint64_t)a->pers_top + HDR + payload) {
            fail(a, DW4_ARENA_EXHAUSTED);
            return none;
        }
        a->stage_bottom -= HDR + payload;
        off = a->stage_bottom;
        b = (block_hdr *)(a->mem + off);
        b->size = payload;
        a->used[DW4_REGION_STAGE] += HDR + payload;
    }
    b = (block_hdr *)(a->mem + off);
    b->magic = MAGIC_LIVE;
    b->next = 0;
    b->region = (uint32_t)region;
    memset(a->mem + off + HDR, 0, b->size);
    a->live[region]++;
    h.off = off + HDR;
    return h;
}

static int dw4_arena_free_nl(dw4_arena *a, dw4_handle h)
{
    block_hdr *b;
    uint32_t off;
    if (!a) return -1;
    b = locate(a, h);
    if (!b) return -1;
    off = h.off - HDR;
    b->magic = MAGIC_FREE;
    a->live[b->region]--;
    if (b->region == DW4_REGION_PERSISTENT) {
        if (class_of(b->size) < NCLASS) {
            b->next = a->free_head[class_of(b->size)];
            a->free_head[class_of(b->size)] = off;
        } else {
            b->next = a->big_head;
            a->big_head = off;
        }
    }
    return 0;
}

static void * dw4_arena_at_nl(dw4_arena *a, dw4_handle h, uint32_t bytes)
{
    block_hdr *b;
    if (!a) return NULL;
    b = locate(a, h);
    if (!b) return NULL;
    if (bytes > b->size) {
        fail(a, DW4_ARENA_TOO_SMALL);
        return NULL;
    }
    return a->mem + h.off;
}

static uint32_t dw4_arena_stage_reset_nl(dw4_arena *a)
{
    uint32_t leaked, off;
    if (!a) return 0;
    leaked = a->live[DW4_REGION_STAGE];
    for (off = a->stage_bottom; off < a->len;) {       /* invalidate every stage handle so none validates after the reset */
        block_hdr *b = (block_hdr *)(a->mem + off);
        uint32_t step = HDR + b->size;
        b->magic = MAGIC_FREE;
        off += step;
    }
    a->stage_bottom = a->len;
    a->live[DW4_REGION_STAGE] = 0;
    a->used[DW4_REGION_STAGE] = 0;
    return leaked;
}

uint32_t dw4_arena_live(const dw4_arena *a, dw4_region r) { return a ? a->live[r] : 0; }
uint32_t dw4_arena_used(const dw4_arena *a, dw4_region r) { return a ? a->used[r] : 0; }

/* ---- the class registry ---------------------------------------------------------------------------------------------- */

static class_entry *class_find(const dw4_arena *a, uint32_t vtable)
{
    size_t i;
    if (!a || !vtable || !a->class_cap) return NULL;
    for (i = (vtable * 2654435761u) & (a->class_cap - 1); a->classes[i].used; i = (i + 1) & (a->class_cap - 1))
        if (a->classes[i].vtable == vtable) return &a->classes[i];
    return NULL;
}

static int class_grow(dw4_arena *a)
{
    size_t ncap = a->class_cap ? a->class_cap * 2 : 256, i;
    class_entry *n = (class_entry *)calloc(ncap, sizeof *n);
    if (!n) return -1;
    for (i = 0; i < a->class_cap; i++) {
        size_t j;
        if (!a->classes[i].used) continue;
        for (j = (a->classes[i].vtable * 2654435761u) & (ncap - 1); n[j].used; j = (j + 1) & (ncap - 1)) {}
        n[j] = a->classes[i];
    }
    free(a->classes);
    a->classes = n;
    a->class_cap = ncap;
    return 0;
}

static int dw4_class_register_nl(dw4_arena *a, uint32_t vtable, const char *name, uint32_t parent, uint32_t size)
{
    size_t i;
    if (!a || !vtable || !name || class_find(a, vtable)) return -1;
    if (a->class_count * 2 >= a->class_cap && class_grow(a)) return -1;
    for (i = (vtable * 2654435761u) & (a->class_cap - 1); a->classes[i].used; i = (i + 1) & (a->class_cap - 1)) {}
    memset(&a->classes[i], 0, sizeof a->classes[i]);
    a->classes[i].vtable = vtable;
    a->classes[i].parent = parent;
    a->classes[i].size = size;
    a->classes[i].used = 1;
    snprintf(a->classes[i].name, sizeof a->classes[i].name, "%s", name);
    a->class_count++;
    return 0;
}

static int dw4_class_register_schema_nl(dw4_arena *a)
{
    int i, n = 0;
    if (!a) return -1;
    for (i = 0; i < dw4_nmetaobjects; i++) {
        const dw4_metaobject *mo = &dw4_metaobjects[i];
        const dw4_metaobject *p = mo->parent && mo->parent[0] ? dw4_metaobject_find(mo->parent) : NULL;
        if (!mo->vtable) continue;
        if (!dw4_class_register(a, mo->vtable, mo->name, p ? p->vtable : 0, mo->size)) n++;
    }
    return n;
}

static int dw4_class_set_slot_nl(dw4_arena *a, uint32_t vtable, unsigned slot, dw4_slot_fn fn)
{
    class_entry *c = class_find(a, vtable);
    if (!c || slot >= MAX_SLOTS) return -1;
    if (slot >= c->nslots) {
        dw4_slot_fn *n = (dw4_slot_fn *)realloc(c->slots, (slot + 1) * sizeof *n);
        unsigned k;
        if (!n) return -1;
        for (k = c->nslots; k <= slot; k++) n[k] = NULL;
        c->slots = n;
        c->nslots = slot + 1;
    }
    c->slots[slot] = fn;
    return 0;
}

static dw4_slot_fn dw4_class_slot_nl(const dw4_arena *a, uint32_t vtable, unsigned slot)
{
    unsigned depth;
    const class_entry *c = class_find(a, vtable);
    for (depth = 0; c && depth < 64; depth++) {   /* the registry is a tree; the bound only stops a corrupt cycle */
        if (slot < c->nslots && c->slots[slot]) return c->slots[slot];
        c = class_find(a, c->parent);
    }
    return NULL;
}

static int dw4_class_is_nl(const dw4_arena *a, uint32_t vtable, uint32_t ancestor)
{
    unsigned depth;
    const class_entry *c = class_find(a, vtable);
    for (depth = 0; c && depth < 64; depth++) {
        if (c->vtable == ancestor) return 1;
        c = class_find(a, c->parent);
    }
    return 0;
}

static const char * dw4_class_name_nl(const dw4_arena *a, uint32_t vtable)
{
    const class_entry *c = class_find(a, vtable);
    return c ? c->name : NULL;
}

static uint32_t dw4_class_size_nl(const dw4_arena *a, uint32_t vtable)
{
    const class_entry *c = class_find(a, vtable);
    return c ? c->size : 0;
}

/* ---- objects ---------------------------------------------------------------------------------------------------------- */

static dw4_handle dw4_arena_object_new_nl(dw4_arena *a, dw4_region region, uint32_t vtable)
{
    dw4_handle none = {0};
    dw4_handle h;
    igObject *o;
    uint32_t size = dw4_class_size(a, vtable);

    if (!a) return none;
    if (size < sizeof(igObject)) {
        fail(a, DW4_ARENA_BAD_CLASS);
        return none;
    }
    h = dw4_arena_alloc(a, region, size);
    if (!h.off) return none;
    o = DW4_ARENA_OBJ(a, igObject, h);
    dw4_object_init_header(o);       /* count 1, flags clear, top byte 0, base vtable */
    o->_vtable = (int)vtable;        /* then the class's own vtable word */
    return h;
}

static igObject *object_at(dw4_arena *a, dw4_handle h) { return a ? DW4_ARENA_OBJ(a, igObject, h) : NULL; }

static int dw4_arena_object_refcount_nl(dw4_arena *a, dw4_handle h)
{
    igObject *o = object_at(a, h);
    return o ? (int)(o->_refCount & REFS_MASK) : -1;
}

static uint32_t dw4_arena_object_vtable_nl(dw4_arena *a, dw4_handle h)
{
    igObject *o = object_at(a, h);
    return o ? (uint32_t)o->_vtable : 0;
}

static int dw4_arena_object_is_nl(dw4_arena *a, dw4_handle h, uint32_t vtable)
{
    igObject *o = object_at(a, h);
    return o ? dw4_class_is(a, (uint32_t)o->_vtable, vtable) : 0;
}

static int dw4_arena_object_addref_nl(dw4_arena *a, dw4_handle h)
{
    igObject *o = object_at(a, h);
    uint32_t refs;
    if (!o) return -1;
    refs = o->_refCount & REFS_MASK;
    if (!refs || refs == REFS_MASK) {
        fail(a, DW4_ARENA_COUNT_RANGE);
        return -1;
    }
    o->_refCount = (o->_refCount & ~REFS_MASK) | (refs + 1u);
    return (int)(refs + 1u);
}

static int dw4_arena_object_release_nl(dw4_arena *a, dw4_handle h)
{
    igObject *o = object_at(a, h);
    uint32_t refs, vtable;
    static const unsigned order[3] = {DW4_SLOT_DESTRUCT_A, DW4_SLOT_DESTRUCT_B, DW4_SLOT_DESTRUCT_C};
    unsigned i;

    if (!o) return -1;
    refs = o->_refCount & REFS_MASK;
    if (!refs) {
        fail(a, DW4_ARENA_COUNT_RANGE);
        return -1;
    }
    refs--;
    o->_refCount = (o->_refCount & ~REFS_MASK) | refs;
    if (refs) return (int)refs;
    /* igObject_Destroy: the destructor slots 08, 10, 00 in that order, then the buffer is freed */
    vtable = (uint32_t)o->_vtable;
    for (i = 0; i < 3; i++) {
        dw4_slot_fn fn = dw4_class_slot(a, vtable, order[i]);
        if (fn) ((dw4_destruct_fn)fn)(a, h);
    }
    return dw4_arena_free(a, h) ? -1 : 0;
}

/* ---- the public entry points: each takes the arena lock (recursive: the implementations call each other) --------------------- */

dw4_handle dw4_arena_alloc(dw4_arena *a, dw4_region region, uint32_t bytes)
{
    dw4_handle r;
    if (!a) return dw4_arena_alloc_nl(a, region, bytes);
    LOCK(a);
    r = dw4_arena_alloc_nl(a, region, bytes);
    UNLOCK(a);
    return r;
}

int dw4_arena_free(dw4_arena *a, dw4_handle h)
{
    int r;
    if (!a) return dw4_arena_free_nl(a, h);
    LOCK(a);
    r = dw4_arena_free_nl(a, h);
    UNLOCK(a);
    return r;
}

void * dw4_arena_at(dw4_arena *a, dw4_handle h, uint32_t bytes)
{
    void * r;
    if (!a) return dw4_arena_at_nl(a, h, bytes);
    LOCK(a);
    r = dw4_arena_at_nl(a, h, bytes);
    UNLOCK(a);
    return r;
}

uint32_t dw4_arena_stage_reset(dw4_arena *a)
{
    uint32_t r;
    if (!a) return dw4_arena_stage_reset_nl(a);
    LOCK(a);
    r = dw4_arena_stage_reset_nl(a);
    UNLOCK(a);
    return r;
}

int dw4_class_register(dw4_arena *a, uint32_t vtable, const char *name, uint32_t parent, uint32_t size)
{
    int r;
    if (!a) return dw4_class_register_nl(a, vtable, name, parent, size);
    LOCK(a);
    r = dw4_class_register_nl(a, vtable, name, parent, size);
    UNLOCK(a);
    return r;
}

int dw4_class_register_schema(dw4_arena *a)
{
    int r;
    if (!a) return dw4_class_register_schema_nl(a);
    LOCK(a);
    r = dw4_class_register_schema_nl(a);
    UNLOCK(a);
    return r;
}

int dw4_class_set_slot(dw4_arena *a, uint32_t vtable, unsigned slot, dw4_slot_fn fn)
{
    int r;
    if (!a) return dw4_class_set_slot_nl(a, vtable, slot, fn);
    LOCK(a);
    r = dw4_class_set_slot_nl(a, vtable, slot, fn);
    UNLOCK(a);
    return r;
}

dw4_slot_fn dw4_class_slot(const dw4_arena *a, uint32_t vtable, unsigned slot)
{
    dw4_slot_fn r;
    if (!a) return dw4_class_slot_nl(a, vtable, slot);
    LOCK((dw4_arena *)a);
    r = dw4_class_slot_nl(a, vtable, slot);
    UNLOCK((dw4_arena *)a);
    return r;
}

int dw4_class_is(const dw4_arena *a, uint32_t vtable, uint32_t ancestor)
{
    int r;
    if (!a) return dw4_class_is_nl(a, vtable, ancestor);
    LOCK((dw4_arena *)a);
    r = dw4_class_is_nl(a, vtable, ancestor);
    UNLOCK((dw4_arena *)a);
    return r;
}

const char * dw4_class_name(const dw4_arena *a, uint32_t vtable)
{
    const char * r;
    if (!a) return dw4_class_name_nl(a, vtable);
    LOCK((dw4_arena *)a);
    r = dw4_class_name_nl(a, vtable);
    UNLOCK((dw4_arena *)a);
    return r;
}

uint32_t dw4_class_size(const dw4_arena *a, uint32_t vtable)
{
    uint32_t r;
    if (!a) return dw4_class_size_nl(a, vtable);
    LOCK((dw4_arena *)a);
    r = dw4_class_size_nl(a, vtable);
    UNLOCK((dw4_arena *)a);
    return r;
}

dw4_handle dw4_arena_object_new(dw4_arena *a, dw4_region region, uint32_t vtable)
{
    dw4_handle r;
    if (!a) return dw4_arena_object_new_nl(a, region, vtable);
    LOCK(a);
    r = dw4_arena_object_new_nl(a, region, vtable);
    UNLOCK(a);
    return r;
}

int dw4_arena_object_refcount(dw4_arena *a, dw4_handle h)
{
    int r;
    if (!a) return dw4_arena_object_refcount_nl(a, h);
    LOCK(a);
    r = dw4_arena_object_refcount_nl(a, h);
    UNLOCK(a);
    return r;
}

uint32_t dw4_arena_object_vtable(dw4_arena *a, dw4_handle h)
{
    uint32_t r;
    if (!a) return dw4_arena_object_vtable_nl(a, h);
    LOCK(a);
    r = dw4_arena_object_vtable_nl(a, h);
    UNLOCK(a);
    return r;
}

int dw4_arena_object_is(dw4_arena *a, dw4_handle h, uint32_t vtable)
{
    int r;
    if (!a) return dw4_arena_object_is_nl(a, h, vtable);
    LOCK(a);
    r = dw4_arena_object_is_nl(a, h, vtable);
    UNLOCK(a);
    return r;
}

int dw4_arena_object_addref(dw4_arena *a, dw4_handle h)
{
    int r;
    if (!a) return dw4_arena_object_addref_nl(a, h);
    LOCK(a);
    r = dw4_arena_object_addref_nl(a, h);
    UNLOCK(a);
    return r;
}

int dw4_arena_object_release(dw4_arena *a, dw4_handle h)
{
    int r;
    if (!a) return dw4_arena_object_release_nl(a, h);
    LOCK(a);
    r = dw4_arena_object_release_nl(a, h);
    UNLOCK(a);
    return r;
}

/* ---- the session arena and owner block lists ------------------------------------------------------------------------------ */

static dw4_arena *g_session;
static pthread_mutex_t g_session_lock = PTHREAD_MUTEX_INITIALIZER;

dw4_arena *dw4_session_arena(void)
{
    dw4_arena *a;
    char error[128];
    pthread_mutex_lock(&g_session_lock);
    if (!g_session) {
        a = dw4_arena_open(0, error, sizeof error);
        if (a && dw4_class_register_schema(a) <= 0) {
            dw4_arena_close(a);
            a = NULL;
        }
        g_session = a;
    }
    a = g_session;
    pthread_mutex_unlock(&g_session_lock);
    return a;
}

void dw4_session_arena_close(void)
{
    pthread_mutex_lock(&g_session_lock);
    dw4_arena_close(g_session);
    g_session = NULL;
    pthread_mutex_unlock(&g_session_lock);
}

int dw4_arena_owned_add(dw4_arena_owned *o, dw4_handle h)
{
    if (!o || !h.off) return -1;
    if (o->n == o->cap) {
        uint32_t ncap = o->cap ? o->cap * 2 : 256;
        dw4_handle *n = (dw4_handle *)realloc(o->h, ncap * sizeof *n);
        if (!n) return -1;
        o->h = n;
        o->cap = ncap;
    }
    o->h[o->n++] = h;
    return 0;
}

void dw4_arena_owned_move(dw4_arena_owned *to, dw4_arena_owned *from)
{
    uint32_t i;
    if (!to || !from) return;
    for (i = 0; i < from->n; i++) dw4_arena_owned_add(to, from->h[i]);
    free(from->h);
    memset(from, 0, sizeof *from);
}

void dw4_arena_owned_release(dw4_arena *a, dw4_arena_owned *o)
{
    uint32_t i;
    if (!o) return;
    for (i = 0; a && i < o->n; i++) dw4_arena_free(a, o->h[i]);
    free(o->h);
    memset(o, 0, sizeof *o);
}
