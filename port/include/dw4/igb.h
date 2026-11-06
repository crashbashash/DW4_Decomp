/* dw4/igb.h — igBinary (IGB) container reader.
 *
 * The container is documented in DW4_Decomp/docs/engine/igbinary-format.md and the
 * decoder it was recovered with is DW4_Decomp/scripts/igb_dir.py + igb_inst.py.
 * This header is the port's C reader for the same layout.
 *
 *   +0x00  u32[12] header   magic 0x00000100, version, ..., [3] class count,
 *                          [5] type-directory offset, [9] string count
 *   +0x30  string table     n_strings * { u32 len, u32 tag, u32 pad } then the bytes
 *   +dir   class directory  { NUL-terminated name }{pad to even}{ 6-byte triples }
 *                          repeated; the walk is validated because no count is stored
 *   +recs  instance records { u32 classIndex }{ u32 recordSize }{ value per descriptor }
 *                          with `recordSize` making each decode self-checking
 *
 * A record carries one value per descriptor, in ordinal order, and the descriptor
 * states its own width — a value occupies `align4(size)` bytes.  Type 4 is a
 * length-prefixed string (`{ u32 len }{ bytes }`, len a multiple of 4) and is the only
 * variable-length value.
 */
#ifndef DW4_IGB_H
#define DW4_IGB_H

#include <stddef.h>
#include <stdint.h>

#define DW4_IGB_MAGIC   0x00000100u
#define DW4_IGB_MAXSFX  48u          /* descriptor type ids are < 48 */

/* The descriptor's type id IS the value's kind (measured): a type-0 value is always
 * an object id or NULL and a type-7 value always a pool-block id or NULL -- 0.0% "neither" over
 * 163,482 values of six packs -- while every other type has values outside the id space (floats
 * 88%, matrices 100%).  So a loader rewrites exactly these two kinds and reads the kind from the
 * value's own descriptor, with no (class, offset) table and no reflection. */
#define DW4_IGB_TY_OBJECTREF 0u      /* igObjectRef: an object id -> a handle */
#define DW4_IGB_TY_MEMREF    7u      /* igMemoryRef: a pool-block id -> a handle */

typedef struct {
    uint16_t type;      /* descriptor type id */
    uint16_t ordinal;   /* 1-based slot number (slot 2 is the inherited name) */
    uint16_t size;      /* this value's byte size in *this* pack */
} dw4_igb_triple;

typedef struct {
    char *name;
    uint32_t off;               /* where the name starts */
    dw4_igb_triple *triples;
    uint32_t ntriples;
} dw4_igb_class;

typedef struct {
    uint32_t type;
    uint32_t raw;               /* the value's first 4 bytes, little-endian */
    uint64_t raw64;             /* the full value for the 8-byte types (12/31) and vectors */
    const char *str;            /* for type 4: pointer into the blob, NUL-terminated */
    uint32_t ordinal;
    uint32_t voff;              /* the value's byte offset in the blob (for a full-width copy) */
    uint32_t vsize;             /* its width there: the declared size padded to 4 */
} dw4_igb_value;

typedef struct {
    uint32_t off;
    uint32_t class_index;
    uint32_t size;              /* recordSize, including the 8-byte header */
    const char *class_name;
    const char *name;           /* first type-4 value, if any */
    dw4_igb_value *values;
    uint32_t nvalues;
    uint32_t end;               /* off + size */
} dw4_igb_record;

typedef struct dw4_igb {
    const uint8_t *data;        /* blob (may point into an AFS entry) */
    size_t size;
    uint32_t header[12];
    uint32_t nclasses;
    uint32_t nstrings;
    dw4_igb_class *classes;
    const char **strings;       /* string table, NUL-terminated views into the blob */
    uint32_t dir_off;
    uint32_t dir_end;

    /* The pack's reference tables.  A pack holds two object
     * chains: section 1 is the memory/object directory and section 2 the objects.
     * Between them sits the id remap table -- {u32 tableBytes}{u32 idCount} plus
     * idCount u16 -- whose entries index section 1.  Entries landing on an
     * igObjectDirEntry are the objects, in exactly section-2 record order; entries
     * landing on an igMemoryDirEntry are the objects' pool blocks, and the id's
     * position is the global id.  `id_kind[id]` says which, and `id_off`/`id_len`
     * then hold either the pool slice or the section-2 record. */
    uint32_t chain1_off, chain1_n;   /* section 1: the directory */
    uint32_t chain2_off, chain2_n;   /* section 2: the objects */
    uint32_t table_off, table_n;     /* the id remap table (0 when absent) */
    uint32_t pool_off, pool_sum;     /* content pool start, bytes accounted for */
    uint32_t *id_off;                /* [id]: pool offset (block) or record offset (object) */
    uint32_t *id_len;                /* [id]: block or record length */
    uint8_t *id_kind;                /* [id]: 0 unknown, 1 pool block, 2 object */
} dw4_igb;

/* Parse the header + string table + class directory.  `start` is the type-directory
 * offset; pass 0 to locate it (the base class `igObject` anchors the walk). */
int  dw4_igb_open(dw4_igb *g, const uint8_t *blob, size_t size, uint32_t start);
void dw4_igb_close(dw4_igb *g);

const dw4_igb_class *dw4_igb_find_class(const dw4_igb *g, const char *name);

/* Decode the record at `off`, or return 0 when `off` is not a record start (the
 * `recordSize` check is what rejects a false start).  `out` borrows into the blob. */
int  dw4_igb_decode(const dw4_igb *g, uint32_t off, dw4_igb_record *out);
void dw4_igb_record_free(dw4_igb_record *r);

/* Walk the contiguous chain that starts at `off`.  Returns how many records *tile* until a
 * decode fails (the total chain length, which may exceed `cap`); when `out` is not NULL it fills
 * at most `cap` records, so a caller must iterate `min(returned, cap)` -- reading past that is an
 * out-of-bounds read of `out`. */
uint32_t dw4_igb_chain(const dw4_igb *g, uint32_t off, dw4_igb_record *out, uint32_t cap);

/* Find the longest record chain at or after `lo` (records tile without gaps, so a
 * decode failure ends a chain).  Returns the chain's start offset. */
uint32_t dw4_igb_find_chain(const dw4_igb *g, uint32_t lo);

/* Validate one record and return its end offset, without building values.  Public so a
 * caller can enumerate *all* chains rather than only the longest. */
int dw4_igb_record_end(const dw4_igb *g, uint32_t off, uint32_t *end_out);

/* ---- references: the id remap table and the content pool ---
 *
 * Locate the two object chains, the remap table between them and the pool block
 * offsets, and build the id -> {pool block | object} map.  Returns 0 on success and
 * -1 when the pack has no such table (the manifest, for one).  Idempotent. */
int  dw4_igb_refs_open(dw4_igb *g);

/* Resolve reference `id`.  Fills `off`/`len` with the pool slice for a memory block
 * or the record offset/size for an object, and returns 1 (block), 2 (object) or 0
 * (unknown id, or the tables were not built).  `off`/`len` may be NULL. */
int  dw4_igb_ref(const dw4_igb *g, uint32_t id, uint32_t *off, uint32_t *len);

/* The bytes of a pool block, or NULL.  `len_out` receives the block length. */
const uint8_t *dw4_igb_block(const dw4_igb *g, uint32_t id, uint32_t *len_out);

#endif /* DW4_IGB_H */
