/* dw4/frontlayer.h — the front-end title's generated light-trail layer (findings #610/#614/#619).
 *
 * The title screen's animated additive backdrop is the scene model **`j_startback`** carried in
 * `AREA.AFS` entry 620.  It is not replayable from a pack alone: its motion is a small scripted
 * **model controller** in the same pack — `beModelCtrlData` sequences (`SQ_OPEN`, `SQ_WAIT`) whose
 * `beAction2JOINTSET` components are *time ranges* driving the scene's animated `igTransform`
 * nodes.  This module generates that layer from the pack's own data at the host's 60 fps tick.
 *
 *   * the controller schedule is `SQ_OPEN` `0…209` frames one-shot (hold at the end), then
 *     `SQ_WAIT` `240…360` frames looping (findings #618/#621);
 *   * each animated node's `_time` is recomputed from the engine clock as
 *     `((int64)(_timeScale * (engineTime>>18)))<<18 + _timeBias` (finding #619), which is what makes
 *     the layer move *every frame* rather than at a capture rate;
 *   * the pack's 16 `igGeometry` meshes (3184 triangles) are drawn once each, additively, in a
 *     perspective screen space (the `sback00.png` texture comes from the pack's own `igImage`).
 *
 * Nothing here reads an analysis artefact: the asset root's `AREA.AFS` supplies the graph, the
 * controller data and the texture.
 */
#ifndef DW4_FRONTLAYER_H
#define DW4_FRONTLAYER_H

#include <stddef.h>
#include <stdint.h>

#include "dw4/mount.h"
#include "dw4/render.h"
#include "dw4/script.h"

typedef struct dw4_frontlayer dw4_frontlayer;

/* Load `AREA.AFS` entry 620 through the mount, resolve its `j_startback` graph and its `sback00`
 * texture, and prepare the controller.  Returns NULL when the archive or the graph is missing. */
dw4_frontlayer *dw4_frontlayer_open(const dw4_mount *mnt);
void dw4_frontlayer_close(dw4_frontlayer *fl);

/* The number of meshes the layer will draw (16 in the recovered pack; 0 when not ready). */
int dw4_frontlayer_meshes(const dw4_frontlayer *fl);

/* Advance the controller to `engine_ns` (nanoseconds; the host feeds one 60 fps tick per frame) and
 * rebase every animated node's `_time` for the current JOINTSET window. */
void dw4_frontlayer_set_engine(dw4_frontlayer *fl, long long engine_ns);

/* Draw the layer additively over `fb`, composing at its own w x h. */
void dw4_frontlayer_draw(dw4_frontlayer *fl, dw4_fb *fb);

/* Use GLES for the ordered material draws; NULL means the CPU path remains active.
 * The returned renderer name is owned by fl. Animation/projection remain unchanged. */
const char *dw4_frontlayer_enable_gpu(dw4_frontlayer *fl, int w, int h);
struct dw4_gl_layer;
const char *dw4_frontlayer_use_gpu(dw4_frontlayer *fl, struct dw4_gl_layer *layer);
/* NULL after a GPU failure reverts this instance to CPU rendering. */
const char *dw4_frontlayer_gpu_info(const dw4_frontlayer *fl);

/* The recovered title camera the layer composes through (finding #628): its world -> view matrix
 * (row-vector convention, as `dw4_render_set_view` takes it) and its focal length per reference
 * pixel (`FL_FOCAL/448`).  A caller can render co-located geometry — the stagML11 backdrop — through
 * the same projection so it composes with the tunnel.  Returns 0, or -1 when not recovered. */
int dw4_frontlayer_view(const dw4_frontlayer *fl, float view[16], float *focal_per_ref);

/* How long `SQ_OPEN` runs, in nanoseconds (209 frames at 60 fps, finding #618/#640).  The layer's
 * opening plays alone: the game shows no title UI until it has finished, so a caller times the UI's
 * own `OPEN` from here rather than from the boot. */
long long dw4_frontlayer_open_ns(void);
/* Static title entry camera: actual pack duration and retail capped clock.
 * Tick only on simulation updates. Drawing does not change completion. */
void dw4_frontlayer_camera_tick(dw4_frontlayer *, uint64_t world_ns);
int dw4_frontlayer_camera_service(void *,const char *,const dw4_script_value *,
    size_t,dw4_script_value *,char *,size_t);

#endif /* DW4_FRONTLAYER_H */
