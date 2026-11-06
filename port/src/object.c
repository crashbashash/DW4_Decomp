/* The reflection-driven runtime object model. The class schema is the generated reflection_data.c;
 * the values come from a decoded `dw4_igb_record`. Construction recovers the inherited-slot count
 * `K` by a type match, so the port names the same fields the reference decoder names, then copies
 * each value to its declared offset at the width its own type states. */
#include "dw4/object.h"
#include "dw4/reflected.h"   /* the decomp's authoritative class layouts (../include) */

#include <stdlib.h>
#include <string.h>

static int mo_cmp(const void *key, const void *elem)
{
    return strcmp((const char *)key, ((const dw4_metaobject *)elem)->name);
}

const dw4_metaobject *dw4_metaobject_find(const char *name)
{
    if (!name)
        return NULL;
    return (const dw4_metaobject *)bsearch(name, dw4_metaobjects, (size_t)dw4_nmetaobjects,
                                           sizeof(dw4_metaobjects[0]), mo_cmp);
}

/* The element width a field's descriptor type states (the doc's table; the descriptor's own size
 * is the packed slot width, which pads a bool to 4 and must not be copied wholesale). */
static uint32_t type_width(uint32_t tid)
{
    switch (tid) {
    case 2: case 3: case 8:                    /* bool, char, uchar */
        return 1;
    case 10: case 17:                          /* ushort, short */
        return 2;
    case 12: case 31:                          /* long, double */
        return 8;
    case 36: return 12;                        /* vec3f */
    case 37: return 8;                         /* vec2f */
    case 38: return 16;                        /* vec4f */
    case 39: return 4;                         /* vec4uc */
    case 40: return 64;                        /* matrix44f */
    case 45: return 4;                         /* vec3uc */
    default: return 4;                         /* int/float/enum/refs/string-id */
    }
}

int dw4_object_field_is_ref(uint8_t tid) { return tid == 0 || tid == 7; }

/* `igObject_InitHeader` (0x2fef20), retargeted from its matched C (src/unmatched/igObject_InitHeader.c) onto the
 * decomp's authoritative `igObject` (include/dw4/reflected.h; technical specification: source-level retarget, four-byte
 * references in an arena).  The engine stamps the base igObject vtable (0x52f0f0, a four-byte reference) at +0 and
 * initialises the header word at +4: the 23-bit reference count to 1, the flag bit above it cleared and the top byte
 * zeroed.  The matched C writes those three fields separately, so the whole word becomes 1.  Returns `o`. */
#define DW4_IGOBJECT_VTABLE_BASE 0x52f0f0u
#define DW4_IGOBJECT_REFS_MASK   0x007fffffu   /* low 23 bits of _refCount; the bit above is a flag, the top byte is b7 */

void *dw4_object_init_header(void *o)
{
    igObject *g = (igObject *)o;

    g->_vtable = (int)DW4_IGOBJECT_VTABLE_BASE;
    g->_refCount = 1u & DW4_IGOBJECT_REFS_MASK;
    return o;
}

/* `ordinal = declaredIndex + K + 1`: find the K that makes every descriptor with
 * `ordinal > K` land on a declared field whose type matches.  0xff fields never match, exactly as
 * `igb_inst.TID2REF.get` returns None, so a class with an array field behaves the same both ways. */
static int find_K(const dw4_metaobject *mo, const dw4_igb_record *r)
{
    int K, ok, n;
    uint32_t j;

    if (!mo || !mo->nfields)
        return 0;
    for (K = 0; K < 14; K++) {
        ok = 1; n = 0;
        for (j = 0; j < r->nvalues; j++) {
            const dw4_igb_value *v = &r->values[j];
            int i;
            if ((int)v->ordinal <= K)
                continue;
            i = (int)v->ordinal - 1 - K;
            if (i < 0 || i >= (int)mo->nfields || mo->fields[i].tid != v->type) {
                ok = 0;
                break;
            }
            n++;
        }
        if (ok && n > 0)
            return K;
    }
    return 0;
}

int dw4_object_from_record(dw4_object *o, const dw4_igb *g, const dw4_igb_record *r)
{
    return dw4_object_from_record_with(o, g, r, dw4_metaobject_find(r->class_name));
}

int dw4_object_from_record_with(dw4_object *o, const dw4_igb *g, const dw4_igb_record *r, const dw4_metaobject *mo)
{
    uint32_t cap, j;

    memset(o, 0, sizeof(*o));
    o->mo = mo;
    o->class_index = r->class_index;
    o->name = r->name;
    o->igb = g;
    o->K = find_K(o->mo, r);

    cap = o->mo ? o->mo->size : 16;
    if (cap < 16)
        cap = 16;
    /* the class size is the generated ancestor-inclusive one; grow it if a value reaches past it */
    for (j = 0; j < r->nvalues; j++) {
        const dw4_igb_value *v = &r->values[j];
        int i;
        uint32_t end;
        if ((int)v->ordinal <= o->K)
            continue;
        i = (int)v->ordinal - 1 - o->K;
        if (i < 0 || !o->mo || i >= (int)o->mo->nfields)
            continue;
        end = o->mo->fields[i].offset + type_width(v->type);
        if (end > cap)
            cap = end;
    }
    o->size = cap;
    o->data = (uint8_t *)calloc(1, o->size);
    if (o->mo && o->mo->nfields)
        o->str = (const char **)calloc(o->mo->nfields, sizeof(char *));
    if (!o->data || (o->mo && o->mo->nfields && !o->str)) {
        dw4_object_free(o);
        return -1;
    }
    /* the engine's own header init, then the class's vtable at +0 */
    dw4_object_init_header(o->data);
    if (o->mo && o->mo->vtable) {
        uint32_t vt = o->mo->vtable;
        memcpy(o->data, &vt, 4);
    }

    for (j = 0; j < r->nvalues; j++) {
        const dw4_igb_value *v = &r->values[j];
        const dw4_metafield *f;
        uint32_t w, stride;
        int i;
        if ((int)v->ordinal <= o->K)
            continue;
        i = (int)v->ordinal - 1 - o->K;
        if (i < 0 || !o->mo || i >= (int)o->mo->nfields)
            continue;
        f = &o->mo->fields[i];
        if (f->tid != v->type)
            continue;                       /* the schema could not name this slot */
        if (v->type == 4) {                 /* a string: keep the borrowed pointer */
            o->str[i] = v->str;
            continue;
        }
        /* copy the element width, never past the next declared field (a bool shares a word with
         * the field after it, so the packed 4-byte slot must not be copied wholesale) */
        stride = (i + 1 < (int)o->mo->nfields) ? (o->mo->fields[i + 1].offset - f->offset)
                                               : (o->size > f->offset ? o->size - f->offset : 4);
        w = type_width(v->type);
        if (w > stride)
            w = stride;
        if (f->offset + w > o->size || v->voff + w > g->size)
            continue;
        memcpy(o->data + f->offset, g->data + v->voff, w);
    }
    return 0;
}

void dw4_object_free(dw4_object *o)
{
    free(o->data);
    free((void *)o->str);
    o->data = NULL;
    o->str = NULL;
}

const dw4_metafield *dw4_object_field(const dw4_object *o, const char *name)
{
    uint32_t i;
    if (!o->mo || !name)
        return NULL;
    for (i = 0; i < o->mo->nfields; i++)
        if (strcmp(o->mo->fields[i].name, name) == 0)
            return &o->mo->fields[i];
    return NULL;
}

int32_t dw4_object_get_i32_at(const dw4_object *o, uint32_t off)
{
    int32_t v = 0;
    if (o->data && off + 4 <= o->size)
        memcpy(&v, o->data + off, 4);
    return v;
}

int32_t dw4_object_get_i32(const dw4_object *o, const char *name)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    if (!f)
        return 0;
    return dw4_object_get_i32_at(o, f->offset);
}

/* The field's value widened to i32 at its declared width (a bool is one byte even though it sits
 * in a 4-byte packed slot, so a plain 4-byte read would swallow the fields after it). */
int32_t dw4_object_get_int(const dw4_object *o, const char *name)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    uint32_t w = f ? type_width(f->tid) : 0;
    int32_t v = 0;
    if (!f || f->offset + w > o->size)
        return 0;
    if (w == 1)
        v = (int32_t)o->data[f->offset];
    else if (w == 2) {
        int16_t s;
        memcpy(&s, o->data + f->offset, 2);
        v = s;
    } else {
        memcpy(&v, o->data + f->offset, 4);
    }
    return v;
}

float dw4_object_get_f32(const dw4_object *o, const char *name)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    float v = 0;
    if (f && f->tid == 16 && f->offset + 4 <= o->size)
        memcpy(&v, o->data + f->offset, 4);
    return v;
}

static void get_vec(const dw4_object *o, const dw4_metafield *f, float *v, int n)
{
    int k;
    for (k = 0; k < n; k++)
        memcpy(&v[k], o->data + f->offset + 4 * k, 4);
}

void dw4_object_get_vec3(const dw4_object *o, const char *name, float v[3])
{
    const dw4_metafield *f = dw4_object_field(o, name);
    v[0] = v[1] = v[2] = 0;
    if (f && (f->tid == 36 || f->tid == 40))
        get_vec(o, f, v, 3);
}

void dw4_object_get_vec4(const dw4_object *o, const char *name, float v[4])
{
    const dw4_metafield *f = dw4_object_field(o, name);
    v[0] = v[1] = v[2] = v[3] = 0;
    if (f && f->tid == 38)
        get_vec(o, f, v, 4);
}

const char *dw4_object_get_str(const dw4_object *o, const char *name)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    if (!f || !o->str)
        return NULL;
    return o->str[f - o->mo->fields];
}

uint32_t dw4_object_get_ref(const dw4_object *o, const char *name)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    if (!f)
        return 0;
    return (uint32_t)dw4_object_get_i32_at(o, f->offset);
}

int dw4_object_set_i32(dw4_object *o, const char *name, int32_t v)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    if (!f || o->data == NULL || f->offset + 4 > o->size)
        return -1;
    memcpy(o->data + f->offset, &v, 4);
    return 0;
}

int dw4_object_set_f32(dw4_object *o, const char *name, float v)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    if (!f || f->tid != 16 || o->data == NULL || f->offset + 4 > o->size)
        return -1;
    memcpy(o->data + f->offset, &v, 4);
    return 0;
}

int dw4_object_set_vec3(dw4_object *o, const char *name, const float v[3])
{
    const dw4_metafield *f = dw4_object_field(o, name);
    if (!f || f->tid != 36 || o->data == NULL || f->offset + 12 > o->size)
        return -1;
    memcpy(o->data + f->offset, v, 12);
    return 0;
}

int dw4_object_set_ref(dw4_object *o, const char *name, uint32_t id)
{
    const dw4_metafield *f = dw4_object_field(o, name);
    if (!f || !dw4_object_field_is_ref(f->tid) || o->data == NULL || f->offset + 4 > o->size)
        return -1;
    memcpy(o->data + f->offset, &id, 4);
    return 0;
}
