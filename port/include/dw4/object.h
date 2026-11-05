/* dw4/object.h — a runtime object model (porting P2.6).
 *
 * The asset layer loads a pack into an arena of opaque payloads; this is the layer that turns a
 * pack **record** into a typed `igObject` whose fields can be read and written by name.  It is the
 * engine's shape, not a new one:
 *
 *   * a class is an `igMetaObject` (its MetaField list and instance size),
 *   * a field is an `igMetaField` (name, type, absolute offset),
 *   * an instance stores its fields at those offsets and its class at `+0`,
 *   * a pack record is `{u32 classIndex}{u32 recordSize}{value per descriptor}` (findings
 *     #417/#418), and a descriptor is `{type, ordinal, size}` with `ordinal = declaredIndex + K + 1`
 *     (#290).  `K` is the inherited-slot count; construction recovers it by the type match that
 *     `DW4_Decomp/scripts/igb_inst.py:find_K` uses, so the port names the same fields the Python
 *     reference does.
 *
 * The schema (class names, field names, offsets, descriptor types) is generated from
 * `DW4_Decomp/data/reflection.json` by `tools/gen_reflection.py` into `src/reflection_data.c`; the
 * pack supplies the *values*.  Pointer-model option (b): fields hold 32-bit ids/handles, and a
 * string field holds a borrowed pointer into the blob (`dw4_object_get_str`).
 */
#ifndef DW4_OBJECT_H
#define DW4_OBJECT_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/igb.h"

typedef struct {
    const char *name;
    uint8_t tid;        /* igBinary descriptor type id; 0xff = a type igb_inst does not name */
    uint32_t offset;    /* absolute byte offset in the instance */
} dw4_metafield;

typedef struct {
    const char *name;
    const char *parent;
    uint32_t size;      /* instance size in bytes (ancestors included) */
    uint32_t vtable;    /* the class's vtable address (finding #359), 0 when unknown */
    const dw4_metafield *fields;
    uint32_t nfields;
} dw4_metaobject;

/* The generated tables (src/reflection_data.c). */
extern const dw4_metaobject dw4_metaobjects[];
extern const int dw4_nmetaobjects;

/* The class named `name`, or NULL. */
const dw4_metaobject *dw4_metaobject_find(const char *name);

typedef struct {
    const dw4_metaobject *mo;   /* the class (NULL for an unknown/untyped record) */
    uint8_t *data;              /* the instance bytes, `size` long */
    uint32_t size;
    const char **str;           /* [mo->nfields] a string field's borrowed pointer, else NULL */
    int K;                      /* the inherited-slot count recovered from the record */
    uint32_t class_index;       /* the pack's class index */
    const char *name;           /* the record's own name (inherited `igNamedObject._name`) */
    const dw4_igb *igb;         /* borrowed: the blob the strings point into */
} dw4_object;

/* Construct an instance from a decoded record (values are the record's descriptors, matched to
 * declared fields by ordinal and type).  Returns 0, or -1 when the record's class is unknown. */
int  dw4_object_from_record(dw4_object *o, const dw4_igb *g, const dw4_igb_record *r);
/* The same, against an explicit class description instead of the generated one by name. The arena pack loader passes a metaobject whose
 * field list is the ancestors' fields followed by the class's own (the generated schema lists only a class's own fields, so a class
 * whose fields are all inherited, such as an igNamedObjectList, would otherwise receive no values). */
int  dw4_object_from_record_with(dw4_object *o, const dw4_igb *g, const dw4_igb_record *r, const dw4_metaobject *mo);
void dw4_object_free(dw4_object *o);

const dw4_metafield *dw4_object_field(const dw4_object *o, const char *name);

/* A verbatim port of the engine's `igObject_InitHeader` (`0x2fef20`): stamp the base igObject
 * vtable (`0x52f0f0`), OR bit 0 into the header flags at `+4`, clear bit 7 at `+6`, zero `+7`.
 * This is the first engine function the port runs (pointer-model option (b): it is all 4-byte
 * offsets, so it ports unchanged).  `dw4_object_from_record` calls it, then stamps the class's own
 * vtable at `+0` when the generated schema knows it.  Returns `o`. */
void *dw4_object_init_header(void *o);

/* Typed reflection access.  A missing field, or one of the wrong type, returns 0 / NULL. */
int32_t     dw4_object_get_i32(const dw4_object *o, const char *name);
int32_t     dw4_object_get_int(const dw4_object *o, const char *name);
float       dw4_object_get_f32(const dw4_object *o, const char *name);
void        dw4_object_get_vec3(const dw4_object *o, const char *name, float v[3]);
void        dw4_object_get_vec4(const dw4_object *o, const char *name, float v[4]);
const char *dw4_object_get_str(const dw4_object *o, const char *name);
uint32_t    dw4_object_get_ref(const dw4_object *o, const char *name);
int32_t     dw4_object_get_i32_at(const dw4_object *o, uint32_t off);

/* Writes are width-checked against the field's descriptor type. */
int dw4_object_set_i32(dw4_object *o, const char *name, int32_t v);
int dw4_object_set_f32(dw4_object *o, const char *name, float v);
int dw4_object_set_vec3(dw4_object *o, const char *name, const float v[3]);
int dw4_object_set_ref(dw4_object *o, const char *name, uint32_t id);

/* The value's kind, from the igBinary type id (finding #482): is it a reference id? */
int dw4_object_field_is_ref(uint8_t tid);

#endif /* DW4_OBJECT_H */
