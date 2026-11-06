/* dw4/models.h — offline model-geometry reader for a stage's model pack. A model pack states its
 * own addressing, so geometry comes out of the file with no running game, no RAM dump and no load
 * replay. The chain: igGeometryAttr1_5 _vertexArray (+0x0c) -> an igObjectRef id _indexArray
 * (+0x10) -> 0 (NULL; there is no index buffer) _primType (+0x14) -> 3 list / 4 strip _numPrims
 * (+0x18) _stripLengths (+0x30) -> igPrimLengthArray1_1 igVertexArray1_1 _vdata (+0x08) -> a
 * memory block listing this array's streams _numVerts (+0x0c) igPrimLengthArray1_1 _lengthData
 * (+0x08) -> the u32 primitive lengths _numStrips (+0x0c) -> their count The offsets are the
 * reflection schema's (a base class declares its own fields, at absolute offsets within the
 * object, so `igGeometryAttr`/`igVertexArray`/ `igPrimLengthArray` hold most of them). A stream
 * block's `_memSize` is its content size exactly — `12*_numVerts` for the positions, `8*_numVerts`
 * for the UVs — and the pool places every block on a 4-byte boundary (`offset(id) = pool_start +
 * sum(align4(_memSize) ...)`), so a stream starts at its block's offset and no search is needed.
 * Every value read below is then checked with the format's own arithmetic — the `_vdata` block
 * must list a stream of exactly `12*_numVerts` bytes and the lengths must sum to `_numVerts` — so
 * a wrong offset shows up as a skipped attribute rather than as bad geometry. */
#ifndef DW4_MODELS_H
#define DW4_MODELS_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "dw4/igb.h"

#define DW4_MODELS_MAX 4096

typedef struct {
    uint32_t rec_off;       /* the igGeometryAttr1_5 record */
    uint32_t id;            /* its id in the pack's own table */
    uint32_t vertex_array;  /* _vertexArray, an id */
    uint32_t prim_type;     /* 3 list, 4 strip */
    uint32_t num_prims;
    uint32_t vdata;         /* igVertexArray1_1._vdata: the stream-list block id (0 = none) */
    uint32_t num_verts;     /* igVertexArray1_1._numVerts */
    uint32_t lengths_id;    /* block holding the u32 lengths (0 = none) */
    uint32_t num_lengths;
    const char *name;       /* the M_*Shape's DCC part name (borrowed from the blob), or NULL */
} dw4_model;

typedef struct {
    const uint8_t *b;       /* borrowed: the whole pack */
    size_t len;
    dw4_igb igb;            /* the container + its reference tables */
    uint32_t pool_off;
    uint32_t n;
    dw4_model m[DW4_MODELS_MAX];
} dw4_models;

/* Parse a pack and collect its geometry attributes.  Returns 0 on success, -1 when the pack
 * is not an igBinary container or has no id remap table (the manifest, a texture pack). */
int  dw4_models_open(dw4_models *m, const uint8_t *blob, size_t len);
void dw4_models_close(dw4_models *m);

const dw4_model *dw4_models_find(const dw4_models *m, uint32_t vertex_array_id);

/* `model_<name>.obj` when the pack names the shape, else `model_<vertexArrayId>.obj`; writes the
 * basename part (no directory) into `out`.  A name goes into a filename, so anything outside
 * `A-Za-z0-9._-` becomes `_`. */
void dw4_models_obj_basename(const dw4_model *g, char *out, size_t cap);

/* The stream ids a `_vdata` block lists, in order.  Returns how many were written. */
uint32_t dw4_models_streams(const dw4_models *m, uint32_t vdata, uint32_t *ids, uint32_t cap);

/* Borrowed pointers into the blob: the positions stream (12*_numVerts bytes) and the UV
 * stream (8*_numVerts), chosen by their declared size.  `uv` receives NULL when the array has
 * no UV stream.  Returns 0, or -1 when the attribute resolved no streams. */
int dw4_models_arrays(const dw4_models *m, const dw4_model *g, const uint8_t **pos,
                      const uint8_t **uv);

/* The triangle list (3*ntris u32 vertex indices), malloc'd for the caller to free.  Fails,
 * with `*why` set to a static reason, when the counts do not add up: a list needs
 * `3*_numPrims <= _numVerts`, a strip's lengths must sum to `_numVerts`. */
int dw4_models_tris(const dw4_models *m, const dw4_model *g, uint32_t **tris, uint32_t *ntris,
                    const char **why);

/* Write one model as a Wavefront OBJ (positions, UVs, triangles — the same text the Python
 * decoder writes).  Returns 0, or -1 when the attribute does not resolve. */
int dw4_models_write_obj(const dw4_models *m, const dw4_model *g, FILE *f);

#endif /* DW4_MODELS_H */
