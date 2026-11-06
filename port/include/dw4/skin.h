/* A skinned character mesh read from a live EE RAM dump. The model pack carries the bind-pose
 * geometry but only a 4-byte stub for the per-vertex blend stream; the real data is runtime-
 * allocated, so it comes from a paused game's dump. The chain, all live pointers: igVertexArray1_1
 * vtable 0x00525190 _vdata +0x08 (-> {positions,normals}), _numVerts +0x0c, _blendWeights +0x20
 * (f32/vert), _blendIndices +0x24 (u8/vert) igGeometryAttr1_5 vtable 0x005238c0 _vertexArray
 * +0x0c, _primType +0x14, _numPrims +0x18, _stripLengths +0x30 igBlendMatrixSelect vtable
 * 0x0052a400 _blendMatrixIndices +0x28 -> igIntList (+0x08 count, +0x10 array): bone -> slot
 * igBlendMatricesAttr vtable 0x00524190 _matrixCache +0x0c, count +0x10: the palette, 64-byte
 * igMatrix44f, row-major with the translation in elements 12..14 Skinning is `v' = M[slot[bone]] *
 * v`, one bone per vertex for the shipped mesh. Measured open item: nothing links the mesh/select
 * to *its* palette, so the palette is chosen by index into the non-empty pool in address order,
 * not resolved. */
#ifndef DW4_SKIN_H
#define DW4_SKIN_H

#include <stdint.h>

typedef struct dw4_skin dw4_skin;

/* Open a dump and find the skinned mesh.  Returns NULL on failure. */
dw4_skin *dw4_skin_open(const char *path);
void dw4_skin_close(dw4_skin *sk);

/* The palette pool, in address order. */
int dw4_skin_palette_count(const dw4_skin *sk);
uint32_t dw4_skin_palette_addr(const dw4_skin *sk, int i);
int dw4_skin_palette_size(const dw4_skin *sk, int i);

/* The palette to use for this mesh: the first whose slot count covers every bone and is a
 * multiple of the bone range (the pool holds both 24- and 40-matrix skeletons). */
int dw4_skin_default_palette(const dw4_skin *sk);

/* Write the mesh as OBJ.  `posed` applies the palette through the bone map; otherwise the bind
 * pose is written.  Returns 0, or -1 on an unwritable path. */
int dw4_skin_write_obj(dw4_skin *sk, int palette, const char *path, int posed);

/* A one-line summary (vertex/primitive/bone/palette counts). */
void dw4_skin_print(const dw4_skin *sk);

#endif /* DW4_SKIN_H */
