/* dw4/pose.h — pose the player's skinned mesh from a live EE RAM dump (P4.1).
 *
 * The player (Susanoomon) is skinned by the engine's VU1 blend programs from three runtime
 * pieces, all recovered offline from the Goblin Pass capture (finding #596):
 *
 *   per-vertex bone index   in the MODEL PACK, a u8 pool block of exactly `num_verts` bytes
 *                           (pack 861: 5483/5595/5566 for Skin0Shape0/2/1) — one bone per
 *                           vertex, weight 1.0, values 1..23
 *   bone -> matrix slot     igBlendMatrixSelect._blendMatrixIndices (+0x28), an igIntList
 *                           (+0x08 count, +0x10 array)
 *   matrix palette          a 21-matrix array at igAnimationCombiner+0x58 — the pairing the
 *                           object graph DOES carry (0x16df680 behind 0x16de250+0x58); each
 *                           matrix is a 64-byte igMatrix44f, translation in elements 12..14
 *
 * Skinning is `v' = M[slot[bone]] * v` with the matrix read column-wise
 * (`v'x = m0*vx + m4*vy + m8*vz + m12`, the convention `tools/verify_skin.py` pinned on the
 * Ogremon, #540) — the mesh is then placed by its node matrix (`beModelCtrlNode2._m` +0x20,
 * row-vector convention) exactly as the scene path already places a row.
 *
 * The palette is a *capture* — an instant of the animation — so a posed render is exact for the
 * frame the dump was taken at.  The addresses are passed explicitly; discovery of the combiner
 * from the node is the next step.
 */
#ifndef DW4_POSE_H
#define DW4_POSE_H

#include <stddef.h>
#include <stdint.h>

typedef struct dw4_pose dw4_pose;

/* Open a dump (31 MB from 0x00100000 or 32 MB from 0).  Returns NULL on failure. */
dw4_pose *dw4_pose_open(const char *path);
void dw4_pose_close(dw4_pose *p);

/* Configure the chain: the skinned graph's igBlendMatrixSelect, the palette array, its matrix
 * count, and the node whose +0x20 matrix places the mesh.  All EE addresses.  Returns 0, or -1
 * with a message on stderr when a field does not resolve. */
int dw4_pose_config(dw4_pose *p, uint32_t select, uint32_t palette, int count, uint32_t node);

/* The palette's matrix count as configured. */
int dw4_pose_count(const dw4_pose *p);

/* Pose one mesh.  `pos` is 3*nv floats, `bones` nv u8 indices; `out_pos` (3*nv) receives the
 * skinned vertices in the mesh's model space — apply the node/row matrix afterwards, as the
 * scene path does.  `out_nrm` (may be NULL) receives the rotated normals when `nrm` is given
 * (rotation only, no translation).  Returns 0, or -1 when a bone has no slot. */
int dw4_pose_mesh(const dw4_pose *p, const float *pos, const float *nrm, const uint8_t *bones,
                  int nv, float *out_pos, float *out_nrm);

#endif /* DW4_POSE_H */
