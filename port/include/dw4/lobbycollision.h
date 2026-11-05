#ifndef DW4_LOBBYCOLLISION_H
#define DW4_LOBBYCOLLISION_H
#include "dw4/scene.h"
/* bounds: per triangle {xmin,xmax,zmin,zmax,ymin,ymax}; the x/z box is padded by the floor test's barycentric tolerance, and a sliver
 * triangle whose floor test is numerically unstable is given infinite x/z bounds so no prefilter ever changes a result. */
typedef struct { const float *positions; uint32_t *indices, count; float *owned_positions; uint32_t vertices; float *bounds; } dw4_collision_mesh;
/* One slot of a dynamic wall info (beHitLandModelInfo kind 0x402): the small proxy geometry of a beCopyTransform, in the frame of the ram slot's model
 * instance (`local` owns its triangles). `bound` is the proxy's igAABox (xmin,ymin,zmin,xmax,ymax,zmax). `name` is the info's (the prop model's) name. */
typedef struct { dw4_collision_mesh local; float bound[6]; const char *name; unsigned slot; } dw4_dynamic_wall;
/* The live world matrix of dynamic node `index`; 0 (and no matrix) while its model instance is not generated, hidden, erased or broken, so it is no wall. */
typedef int (*dw4_dynamic_pose)(void *user,unsigned index,float world[16]);
/* wall: the merged kind-2 graphs, every model collides with them. special[k]: the static wall graphs of the other kinds, dw4_collision_special_kind[k] = 4
 * (limit_Circle), 8 and 0x802 (walls the check flag selects: enemies take 8 and 0x802, players 0x802 and 4, bullets neither 8 nor 0x802); a query by a model with check flag F uses special[k] when dw4_hitland_info_applies(kind, F). Retail picks the models per check flag (players 7, hub actors 3, enemies 11, bullets 2051), so the walls of kind 8 and 0x802 apply to enemies and players alike where the flag selects them. */
typedef struct { dw4_collision_mesh wall, floor; dw4_collision_mesh special[3];
    /* dynamic[i]: the kind-0x402 prop walls. A query by a model whose check flag selects kind 0x402 (players 7, hub actors 3, not the zero flag of the short
     * forms) tests every node that `pose` reports active: the node's xz prefilter box is retail's (the proxy bound plus the matrix translation only, unrotated,
     * inclusive), its triangles are tested transformed by the whole matrix, nearest hit wins together with the static walls. No `pose` means no node is solid. */
    dw4_dynamic_wall *dynamic; unsigned ndynamic; dw4_dynamic_pose pose; void *pose_user;
} dw4_lobby_collision;
extern const unsigned dw4_collision_special_kind[3];
int dw4_lobby_collision_open(dw4_lobby_collision *, const dw4_scene *);
/* The same without the info-owned graphs whose scene->collision index is set in off[] (HITLANDMODEL OFFHIT). */
int dw4_lobby_collision_open_except(dw4_lobby_collision *, const dw4_scene *,const uint8_t *off);
/* The same, and also without the meshes whose bit is set in parts[graph] (bit i = the i-th mesh node, in scene order, of that collision graph): a
 * wall graph that holds several doors as separate meshes (the Humid Cave's doorwall01..06) switches them one at a time. */
int dw4_lobby_collision_open_parts(dw4_lobby_collision *, const dw4_scene *,const uint8_t *off,const uint64_t *parts);
/* The number of mesh nodes of collision graph <graph> (its parts). */
unsigned dw4_lobby_collision_parts(const dw4_scene *,unsigned graph);
/* Build the per-triangle bounds for a collision set assembled by hand (the open calls do it themselves). Results never change. */
int dw4_lobby_collision_index(dw4_lobby_collision *);
void dw4_lobby_collision_close(dw4_lobby_collision *);
/* Install the pose reader of the dynamic nodes (it survives a rebuild only if the caller copies it: the open calls start from a zeroed struct). */
void dw4_lobby_collision_dynamic_pose(dw4_lobby_collision *,dw4_dynamic_pose,void *user);
/* Authored lobby wall/floor geometry; returns contacts, preserves a valid floor. */
unsigned dw4_lobby_collision_move(const dw4_lobby_collision *, const float old[3],
                                  float pos[3], float half_width, float up, float down);
unsigned dw4_lobby_collision_check(const dw4_lobby_collision *,const float old[3],
    float pos[3],float half_width,float up,float down,int wall,int floor);
/* Airborne motion preserves height until a descending floor crossing. Contact
 * bit 4 marks landing; unsupported space never invokes the walking edge hold. */
unsigned dw4_lobby_collision_air(const dw4_lobby_collision *,const float old[3],
    float pos[3],float half_width,int wall,int floor);
/* Player walking publishes loss of support (bit 2) without restoring X/Z;
 * the owning model then enters its authored Fall sequence. */
unsigned dw4_lobby_collision_walk(const dw4_lobby_collision *,const float old[3],
    float pos[3],float half_width,float up,float down,int wall,int floor);
/* The same entry points for a model whose beHitLandDelivInfoRam check flag is `flags` (players 7, hub actors and records without a flag 3, enemies 11). The
 * short forms above query only the kind-2 walls. */
unsigned dw4_lobby_collision_move_for(const dw4_lobby_collision *,unsigned flags,const float old[3],float pos[3],float half_width,float up,float down);
unsigned dw4_lobby_collision_check_for(const dw4_lobby_collision *,unsigned flags,const float old[3],
    float pos[3],float half_width,float up,float down,int wall,int floor);
unsigned dw4_lobby_collision_air_for(const dw4_lobby_collision *,unsigned flags,const float old[3],
    float pos[3],float half_width,int wall,int floor);
unsigned dw4_lobby_collision_walk_for(const dw4_lobby_collision *,unsigned flags,const float old[3],
    float pos[3],float half_width,float up,float down,int wall,int floor);
/* Retail's per-model selection of wall infos (FUN_00388640): does a beHitLandModelInfo of `info_kind` (the pack's _kind, ordinal 10) take part in a query
 * by a model whose beHitLandDelivInfoRam check flag is `check_flags` (ordinal 12; players 7, enemies 11, bullets 2051)? order.kind = flags & ~1:
 * (info & order & 0x1FF) != 0, an info with 0x800 is skipped by an order with 0x800, an order with 0x1000 sees only infos with 0x1000. */
int dw4_hitland_info_applies(unsigned info_kind,unsigned check_flags);
#endif
