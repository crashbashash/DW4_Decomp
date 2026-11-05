/* dw4/scene.h — a stage pack loaded into the port's guest arena (porting tasks P2.3 / P3.5).
 *
 * This is the loader's *output*, not a reader over the file.  The engine's loader converts a
 * pack's ids into resolved pointers in a later pass (finding #423), so the port gives itself the
 * same shape: one arena holds every id's payload, and a **32-bit handle** addresses it.
 *
 *   handle = arena offset (0 is NULL)          -- pointer-model option (b), P1.5
 *   id     = the pack's own id (igb.h, #460)   -- what the file says
 *
 * `dw4_scene_load` walks the pack's id table, allocates each id's payload in the arena in id
 * order and records the handle, so a reader afterwards asks for *handles*, exactly as engine code
 * would.  Nothing is searched and nothing is replayed: the geometry a scene hands out is the same
 * geometry `dw4asset models` extracts, reached the way the game reaches it.
 *
 * Two consequences worth stating, because they are the reason this exists:
 *
 *  * **the pool's padding disappears.** In the file a block starts at a 4-byte boundary, so a
 *    `_memSize` that is not a multiple of 4 is followed by 1-3 pad bytes (finding #478).  The
 *    loader *allocates*, so it decides its own layout: the arena packs ids densely at a chosen
 *    alignment and no arithmetic depends on the file's offsets.
 *  * **the meshes are renderer-ready.** A mesh points straight at the arena's float streams
 *    (positions, UVs) and carries its triangle list, so the renderer never touches a pack.
 *
The **id -> pointer pass** (finding #423) happens here too: once every payload is placed, each
object record's `igObjectRef` and `igMemoryRef` values are rewritten from the pack's ids into
handles.  Which values those are comes from the value's own descriptor -- its type id is the kind
(finding #482, measured: type 0 is always an object id or NULL and type 7 always a pool-block id or
NULL, with no value of either kind ever outside the id space) -- so there is no (class, offset) table
and no reflection involved.  A NULL (0xFFFFFFFF) stays NULL.

Deliberately *not* done: rewriting the contents of a memory block (a `_vdata` block holds the ids of
the streams it lists, and the live engine sees pointers there).  A block can be shared, and its item
kind is a property of the *field* that points at it, not of the block -- so that pass needs its own
rule and is left until something reads those items as pointers.  Readers resolve them through
`dw4_scene_handle()` today.
 */
#ifndef DW4_SCENE_H
#define DW4_SCENE_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "dw4/igfile.h"

#define DW4_SCENE_ALIGN 16u      /* every payload's arena alignment, so floats/vectors are aligned */
#define DW4_SCENE_BASE  0x1000u  /* handle 0 is NULL, so the first payload starts here */

/* A 32-bit handle into the arena (pointer-model option (b)). */
typedef struct {
    uint32_t off;
} dw4_handle;

typedef struct {
    uint32_t id;
    dw4_handle h;      /* where this id's payload sits in the arena */
    uint32_t size;     /* the payload's byte size (`_memSize` or the record's size) */
    uint8_t kind;      /* 1 = pool block, 2 = object record */
} dw4_scene_ent;

typedef struct {
    const char *name;        /* the DCC shape name, or NULL (borrowed from the arena) */
    uint32_t attr_id;        /* the geometry attribute's id */
    uint32_t vertex_array_id;/* `_vertexArray`'s id -- a mesh's identity in the pack, and what the
                              * file reader names an unnamed mesh by, so both front ends agree */
    dw4_handle attr;         /* the attribute record */
    dw4_handle positions;    /* `num_verts` x 3 floats */
    dw4_handle normals;      /* `num_verts` x 3 floats (0 = the mesh ships none; finding #458) */
    dw4_handle uvs;          /* `num_verts` x 2 floats (0 = the mesh has none) */
    dw4_handle lengths;      /* the primitive lengths, u32 (0 for a list) */
    uint32_t num_verts;
    uint32_t prim_type;      /* 3 list, 4 strip */
    uint32_t num_prims;
    uint32_t num_lengths;
} dw4_scene_mesh;

/* One `igTransformSequence1_5`: parallel keyframe lists, borrowed from the pack.  `times` are
 * nanoseconds (the pack's unit -- e.g. a 24-key menu sequence spans 0..3.083 s in 1/12 s steps). */
typedef struct {
    const void *times;       /* int64 nanoseconds, `ntimes` keys */
    const void *trans;       /* float[3] per key, `ntrans` keys (the first vec3f list) */
    const void *scale;       /* float[3] per key, `nscale` keys (the second vec3f list) */
    const void *rot;         /* float[4] quaternion per key, `nrot` keys */
    uint32_t ntimes, ntrans, nscale, nrot;
    void *owned;            /* decoded compressed QS lists, otherwise NULL */
    /* the pack's descriptor slots the two `igVec3fList`s came from: the reflection's field order is
     * `_interpolationDataTranslation` then `_interpolationDataScale`, but a node may carry only one
     * of them -- so which list is which is decided by the slot, never by the order seen. */
    uint32_t trans_ord, scale_ord;
    uint32_t interpolation_method; /* packed translation/rotation/scale method bytes */
    int rotation_euler;      /* explicit degree-XYZ evaluation, verified for the arrival camera */
    int64_t duration_ns;     /* authored compressed-sequence cycle, independent of quantized last key */
    uint32_t play_mode;
} dw4_scene_seq;

/* One node of a loaded stage's **scene graph** (porting P4.2, reached offline): the pack's
 * `igSceneInfo` records each name a scene and carry an `igGraphPathList`; a graph path carries an
 * `igNodeList`; and a node carries a name, optionally a transform matrix, an `igNodeList` of
 * children and an `igGeometry` it draws.  A node's values are found by their *type*, so no class
 * has to be special-cased: the matrix is the `igMatrix44f` value, the children the `igNodeList`
 * reference, the geometry a reference to an `igGeometry`. */
typedef struct {
    uint32_t id;             /* the node's id in the pack */
    const char *class_name;
    const char *name;        /* the node's own name (its string value), or NULL */
    uint32_t parent;         /* index into the node array, or 0xFFFFFFFF for a root */
    uint32_t scene;          /* index of the igSceneInfo it belongs to, or 0xFFFFFFFF */
    uint32_t depth;
    int has_matrix;
    float m[16];             /* the node's igMatrix44f, when it has one (row-major, as stored) */
    dw4_handle geometry;     /* an igGeometry it references, or a NULL handle */
    /* An `igTransform` may name an `igTransformSequence1_5` instead of holding a usable `_m`: the
     * pack writes a *placeholder* matrix (zero rows) for an animated node and keeps the real
     * transform in the sequence's keyframe lists (finding #611).  When present the sequence, not
     * `m`, is the node's local transform -- evaluated at the scene's current time. */
    int has_seq;
    dw4_scene_seq seq;
    /* Per-node animation clock (beModelCtrlNode2, finding #619): a node's `_time` is recomputed
     * every frame as `((int64)(_timeScale * (engineTime>>18)))<<18 + _timeBias`, not advanced by a
     * cursor.  `time_scale` (`_timeScale`, +0x78) is normally 1.0; `time_bias` (`_timeBias`, +0x80)
     * is what a JOINTSET range writes to select the animation window.  A node the front-end drive
     * has touched is `driven`, and then ignores the scene-wide `time_ns`. */
    int driven;
    double tnode;            /* the node's own time (ns), when driven */
    float time_scale;        /* beModelCtrlNode2._timeScale (+0x78) */
    long long time_bias;     /* beModelCtrlNode2._timeBias (+0x80), ns */
    uint32_t mesh;           /* index into `mesh[]` this geometry node draws (0xFFFFFFFF none) */
    dw4_handle switch_mask, lod_ranges;
    uint32_t switch_bits, lod_count;
    uint32_t *switch_values; /* per-instance mutable copy, allocated on first change */
    uint32_t tex_image;      /* the `igImage` id the node's nearest `igAttrSet` ancestor binds
                              * through igTextureBindAttr -> igTextureAttr (0 when none) */
    const char *tex_name;    /* beTextureCtrlAttr's runtime binding, borrowed from the arena */
    int has_view, has_projection, has_viewport;
    float view[16], projection[16];
    uint32_t viewport[4];     /* x, y (bottom-origin), width, height */
    float viewport_z[2];      /* igViewportAttr nearZ/farZ */
    int has_color;           /* the nearest `igAttrSet` ancestor also names an `igColorAttr` */
    float color[4];          /* that record's `_color` (RGBA 0..1), valid when `has_color` */
    uint32_t xform_target;   /* igTransform._target (ordinal 9): 0 = a model transform; 9 on the 8 trace
                              * transforms of j_startback, whose translation is a texture-coordinate
                              * offset, not a position (finding #716) */
    int has_fog;             /* the node's own attribute list names an `igFogStateAttr` */
    uint32_t fog_enabled;    /* its `_enabled` (finding #722) */
    int has_alpha;           /* the node's own attribute list names an `igAlphaFunctionAttr` */
    float alpha_ref;         /* its `_refValue` (0..1; the GS AREF is floor(ref * 128), finding #721) */
    int has_blend;           /* the node's own attribute list names an `igBlendFunctionAttr` */
    uint32_t blend_src;      /* its `_src` / `_dst` (4 = src alpha, 1 = dst colour, 5 = 1 - src alpha) */
    uint32_t blend_dst;
    int has_material;
    float material_diffuse[4], material_ambient[4], material_emission[4];
    int has_lighting, lighting_enabled;
    int has_blend_state, blend_enabled;
    int has_depth_write, depth_write;
    int has_depth_state, depth_enabled;
    int has_color_mask;
    uint8_t color_mask;      /* disabled RGBA channels, bits 0..3; default 0 */
    uint8_t texmat_state;    /* the node's own attribute list names an `igTextureMatrixStateAttr` (a texture-matrix scope) */
    uint8_t light_state;     /* ... or a light / light-state / lighting-state attribute (a lighting change the walk cannot model) */
    uint8_t light_rot;       /* VU1 in-place light rotation count k of the mesh this node draws (`dw4_scene_node_light_rot`) */
} dw4_scene_node;

/* An inline `igImage` a material set binds (the front-end title's own UI textures live in
 * `AREA.AFS` entry 620, not in a texture pack): its 8bpp index grid and 256-entry palette are pool
 * blocks in the same arena, so a caller reads both through `dw4_scene_host`. */
typedef struct {
    uint32_t id;             /* the igImage's id */
    const char *name;        /* `_pNameString` (borrowed from the arena) */
    uint32_t w, h;           /* `_px`, `_py` */
    uint32_t size;           /* `_imageSize` (w*h unless the pack pads it) */
    uint32_t bpr;            /* `_bytesPerRow` (w unless padded) */
    dw4_handle grid;         /* `_pImage` block */
    dw4_handle pal;          /* `_pClut`'s `_pData` block */
} dw4_scene_image;

typedef struct {
    const char *name;        /* the igSceneInfo's name */
    uint32_t node;           /* the index of its first root node, or 0xFFFFFFFF */
    uint32_t nnodes;
} dw4_scene_graph;

/* Static collision switchgraphs referenced by beHitLandModelInfo. The node
 * root is retained outside visible scene graphs; kind1=floor, kind2=wall. */
typedef struct {uint32_t info_id,kind,node;} dw4_scene_collision;
#define DW4_HITLAND_DYNAMIC_WALL 0x402u   /* beHitLandModelInfo _kind of a prop whose walls follow its model instances */
/* A dynamic wall info (beHitLandModelInfo kind 0x402): `node` is the root of its ordinal-8 _checkSwitch, whose children (the slots) are
 * beCopyTransform proxies of the ram slots of the model of the same `name`; slot i's first child is the proxy geometry, `bound[6*i..]` its igAABox
 * (xmin,ymin,zmin,xmax,ymax,zmax in the slot's own frame; infinite when the pack names none). `name` is borrowed from the arena, `bound` owned. */
typedef struct {uint32_t info_id,node,nslot;const char *name;float *bound;} dw4_scene_dynamic;

typedef struct {
    uint8_t *arena;
    size_t arena_len;
    dw4_scene_ent *ent;      /* [arena_len entries] the handle table, indexed by id */
    uint32_t nent;
    uint32_t nblock, nobject;
    dw4_scene_mesh *mesh;
    uint32_t nmesh;
    /* The scene graph, walked from the igSceneInfo records (porting P4.2). */
    dw4_scene_node *node;
    dw4_scene_graph *graph;
    uint32_t nnode, ngraph;
    dw4_scene_collision *collision;
    uint32_t ncollision;
    dw4_scene_dynamic *dynamic;   /* the kind-0x402 prop infos, appended after the static rows (actor-aware world load only) */
    uint32_t ndynamic;
    /* The timeline for the animated nodes: `igTransformSequence1_5` keys are evaluated at this
     * instant (nanoseconds, the pack's unit).  Set with `dw4_scene_set_time`. */
    double time_ns;
    /* The shared engine clock (int64 ns) the last `dw4_scene_set_engine_time` was fed. */
    long long engine_time;
    /* The id -> pointer pass, measured on the pack that was loaded: `nref` values were rewritten
     * from an id into a handle, `nnull` were NULL, and `nref_bad` were neither -- which must be 0,
     * because a reference-typed value is always an id or NULL (finding #482). */
    uint32_t nref, nnull, nref_bad;
    /* The inline textures the scene's material sets bind (the front-end title's own UI images). */
    dw4_scene_image *img;
    uint32_t nimg;
} dw4_scene;

/* Switch changes address the authored child order. child=-1 sets all children.
 * Visibility also selects igLod's half-open distance interval. */
int dw4_scene_switch_set(dw4_scene *, uint32_t node, int child, int visible);
int dw4_scene_node_visible(const dw4_scene *, uint32_t node, float distance);

/* Load a pack (`dw4_igb` container with an id table) into the arena.  Returns 0, or -1 when the
 * blob is not a pack or its ids do not tile the pool. */
int  dw4_scene_load(dw4_scene *s, const uint8_t *blob, size_t len);
/* Include actor appearance skin graphs for bind-pose previews (no animation evaluation). */
int dw4_scene_load_actor_preview(dw4_scene *s, const uint8_t *blob, size_t len);
/* Actor-aware world load also retains authored static collision switchgraphs. */
int dw4_scene_load_world(dw4_scene *,const uint8_t *blob,size_t len);
/* The same, through the file seam. */
int  dw4_scene_load_file(dw4_scene *s, const dw4_igfile *f);
void dw4_scene_close(dw4_scene *s);

/* The table entry for an id, or NULL. */
const dw4_scene_ent *dw4_scene_lookup(const dw4_scene *s, uint32_t id);
/* A handle's payload, or NULL when it does not name one. */
const void *dw4_scene_host(const dw4_scene *s, dw4_handle h);
/* The handle an id resolves to (a NULL handle when it does not). */
dw4_handle dw4_scene_handle(const dw4_scene *s, uint32_t id);
/* The id a handle came from (0 when it is not one).  Handles are placed in id order, so this is a
 * binary search -- and it is what lets a reader report a *name or id* after materialisation. */
uint32_t dw4_scene_id_of(const dw4_scene *s, dw4_handle h);

/* A mesh's triangles (3*ntris u32 vertex indices), malloc'd for the caller to free.  Fails, with
 * `*why` set, when the counts do not add up. */
int dw4_scene_tris(const dw4_scene *s, const dw4_scene_mesh *g, uint32_t **out, uint32_t *ntris,
                   const char **why);

/* One mesh as a Wavefront OBJ — the text `dw4asset models` writes, so the two can be diffed. */
int dw4_scene_write_obj(const dw4_scene *s, const dw4_scene_mesh *g, FILE *f);

/* The stage pack's own camera (porting P4.2/P4.3, findings #495/#496).  A camera node's world
 * matrix is its ancestor chain composed **child x parent** (row-major, translation at words
 * 12..14), and the renderer's view is its affine inverse.  `name` selects an `igCamera` node by
 * its own name; NULL selects the **stage camera**, which is the first `igCamera` in node order
 * whose composed world is not the identity (on `stag0102` that is node 4 `cameraShape00`, the one
 * finding #495 measured at (0, 102.490, 74.565)).  `world`/`view` are each 16 floats and may be
 * NULL.  Returns the selected node index, or -1 when the pack has no such camera. */
int dw4_scene_camera(const dw4_scene *s, const char *name, float world[16], float view[16]);

/* The same composition for one chosen camera node (no identity check).  Returns 0, or -1 when the
 * node does not exist or is not an `igCamera`. */
int dw4_scene_node_camera(const dw4_scene *s, uint32_t node, float world[16], float view[16]);

/* The mesh a geometry node draws (its `igGeometry`'s `igAttrList` matched to the loaded `mesh[]` by
 * attribute id), or 0xFFFFFFFF when the node is not a drawable geometry.  Resolves node -> mesh
 * exactly: the pack holds several shapes of the same DCC name, so a name match is ambiguous. */
uint32_t dw4_scene_node_mesh(const dw4_scene *s, uint32_t node);

/* The `igImage` id the node's material binds: the node's nearest `igAttrSet` ancestor's
 * `_attributes` chain (igTextureBindAttr -> igTextureAttr -> igImage), or 0 when it binds none.
 * This is the pack's own binding, not a name convention. */
/* The texture-coordinate offset a node inherits from an `igTransform` whose `_target` is 9 (finding
 * #716): the translation of that transform's local matrix at the scene's current time.  Returns 1 and
 * fills `*du`/`*dv` when the node has such an ancestor, else 0 (and 0, 0). */
int dw4_scene_node_uv_offset(const dw4_scene *s, uint32_t node, float *du, float *dv);

/* Whether the GS fog stage applies to a node: its own or nearest ancestor's `igFogStateAttr._enabled`.
 * Returns 1 and fills `*enabled` when one is found, else 0 (fog off). */
int dw4_scene_node_fog(const dw4_scene *s, uint32_t node, uint32_t *enabled);

/* The `igAlphaFunctionAttr._refValue` a node inherits (its own, else its nearest ancestor's).
 * Returns 1 and fills `*ref` when one is found, else 0 (the engine default applies). */
int dw4_scene_node_alpha_ref(const dw4_scene *s, uint32_t node, float *ref);

/* The `igBlendFunctionAttr` a node inherits: its own, else its nearest ancestor's (the pack's
 * attribute-stack order).  Returns 1 and fills `*src`/`*dst` when one is found, else 0. */
int dw4_scene_node_blend(const dw4_scene *s, uint32_t node, uint32_t *src, uint32_t *dst);

uint32_t dw4_scene_node_texture(const dw4_scene *s, uint32_t node);
const char *dw4_scene_node_texture_name(const dw4_scene *s, uint32_t node);

/* The inline image record for `image_id` (from `dw4_scene_node_texture`), or NULL.  Its `grid` and
 * `pal` are read with `dw4_scene_host`; a palette entry is RGBA in its four bytes. */
const dw4_scene_image *dw4_scene_image_of(const dw4_scene *s, uint32_t image_id);

/* The local transform of any node: its evaluated `igTransformSequence1_5` when it has one, else its
 * stored `igMatrix44f`, else identity.  Returns 1 when a transform was available, 0 otherwise. */
int dw4_scene_node_local(const dw4_scene *s, uint32_t node, float out[16]);

/* The world matrix of any node: its local matrix composed down its parent chain (root first),
 * or the identity when no ancestor carries one.  Returns 0, or -1 when the node does not exist. */
int dw4_scene_node_world(const dw4_scene *s, uint32_t node, float world[16]);
/* How many extra times retail's VU1 program CALC_INFINITE_4 has rotated the packed light block in place when it lights this geometry
 * node's mesh (0 when the node draws nothing, lies outside an `igSwitch` named "BG02" root, or the walk cannot vouch for it).
 * The block is re-sent in eye space only after a model-view upload; every draw that follows any other hardware matrix upload (a
 * texture-matrix transform, leaving a texture-matrix scope) rotates it once more, so the k-th such draw lights with
 * n_eff = n_world . (V3 . R)^k.  Computed once at load from the depth-first draw order.  Safe scope (retail evidence: stag0001's
 * floor-grid overlays only): a root start is a fresh block; a target-0 `igTransform` enter/leave is a fresh block; a target-9
 * (texture) transform and a texture-matrix scope are pending uploads, the flag being boolean, so two before one draw count once; k
 * is kept only where the transform-event model and the scope-event model agree; any other node class, switch, light or lighting
 * attribute in the root makes every later mesh k = 0. */
uint32_t dw4_scene_node_light_rot(const dw4_scene *s, uint32_t node);

/* Set the instant (nanoseconds -- the pack's keyframe unit) that the animated nodes evaluate at. */
void dw4_scene_set_time(dw4_scene *s, double ns);

/* The controller clock (finding #619).  `engine_ns` is the engine's shared int64 clock in
 * nanoseconds, advanced one frame per 60 fps tick by the caller.  For every animated node this
 * recomputes `_time = ((int64)(_timeScale * (engineTime>>18)))<<18 + _timeBias` and marks the node
 * driven, so it ignores the scene-wide `dw4_scene_set_time` timeline.  A JOINTSET range selects its
 * window by calling `dw4_scene_node_drive` with a `timeBias` that rebases the node's `_time`. */
void dw4_scene_set_engine_time(dw4_scene *s, long long engine_ns);

/* Set one node's `_timeScale` / `_timeBias` (the JOINTSET write), then feed the clock:
 * `node_time == time_bias + (int64)(time_scale*(engine_ns>>18))<<18`. */
void dw4_scene_node_drive(dw4_scene *s, uint32_t node, float time_scale, long long time_bias);
/* Ambient compressed spatial/UV sequences own their authored loop, rather than an
 * Action2 JOINTSET window. Caller supplies a simulation-owned clock. */
int64_t dw4_scene_node_loop_time(const dw4_scene *,uint32_t,int64_t);

/* The projection the game actually uses (finding #496): a 39.60 degree vertical field of view at
 * a 640x448 framebuffer.  `dw4_scene_camera_fov()` is that angle in radians; the renderer wants
 * the horizontal scale as `0.7 * width / height` so its square-pixel projection matches the
 * game's. */
#define DW4_SCENE_CAMERA_FOV 0.6912f
float dw4_scene_camera_aspect(int width, int height);

#endif /* DW4_SCENE_H */
