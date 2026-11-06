/* dw4/mesh.h — the two things every model path shares: the triangle rule and the OBJ text.
 *
 * Both front ends need them — `dw4asset models` (walking a pack *file*, src/models.c) and
 * `dw4_scene` (walking a loaded *arena*, src/scene.c) — and they must agree byte for byte, so
 * they are written once here rather than twice.  The rule:
 *
 *   primType 4 (strip)  a `_stripLengths` array of u32s; `sum(lengths) == _numVerts`; primitive
 *                       k uses vertices [off, off+L), off += L, and contributes L-2 triangles
 *   primType 3 (list)   3*_numPrims <= _numVerts, and primitive i is (3i, 3i+1, 3i+2)
 *
 * There is **no index array** in the shipped models: the vertex buffer is consumed in order.
 */
#ifndef DW4_MESH_H
#define DW4_MESH_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Triangles for one attribute: `*out` is malloc'd (3 * *ntris u32 vertex indices) for the caller
 * to free, or NULL with `*why` set when the counts do not add up.  `lengths` is a raw byte
 * pointer (little-endian u32s), so an unaligned source is fine.  Returns 0 or -1. */
int dw4_mesh_tris(uint32_t prim_type, uint32_t num_prims, uint32_t num_verts,
                  const uint8_t *lengths, uint32_t num_lengths,
                  uint32_t **out, uint32_t *ntris, const char **why);

/* One mesh as Wavefront OBJ.  `pos` is `num_verts` x 3 floats and `uv` (may be NULL) is
 * `num_verts` x 2 floats, both little-endian f32.  Writes exactly what `dw4asset models` writes,
 * including the byte order of the text, so two front ends can be diffed. */
/* `model_<name>.obj` when there is a name, else `model_<id>.obj`; anything outside
 * `A-Za-z0-9._-` becomes `_`.  Shared so both front ends write the same filenames. */
void dw4_mesh_obj_basename(const char *name, uint32_t id, char *out, size_t cap);

int dw4_mesh_write_obj(FILE *f, const uint8_t *pos, const uint8_t *uv, uint32_t num_verts,
                       const uint32_t *tris, uint32_t ntris);

#endif /* DW4_MESH_H */
