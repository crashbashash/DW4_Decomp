#ifndef DW4_MODELVIEW_H
#define DW4_MODELVIEW_H
#include "dw4/controllers.h"
#include "dw4/gl_layer.h"
#include "dw4/fontlayout.h"
typedef struct dw4_modelview dw4_modelview;
/* Authored WN-layer model geometry; dependencies outlive this renderer.
 * Pixel-space replay includes native instance position, indexed images,
 * sampled Action2 poses, UV translation and authored color/blend state.
 * Draw copies node state and never ticks or changes the prepared graph.
 * Missing textures produce a diagnostic and the agreed debug pattern.
 * Per-model FADESET alpha interpolation and full material/depth parity are
 * separate presentation work; HIDE eligibility is observed. */
dw4_modelview *dw4_modelview_open(const dw4_stageobjects *,const dw4_controllers *,char *,size_t);
/* As dw4_modelview_open, for interface scenes: every attached layer is drawn, not only the WN window layers. */
/* As dw4_modelview_open, for a field world or a hub party: no lobby HUD owns the player panels, so i_stpnl00..04 draw here (the gauges pose at their meters' times). */
dw4_modelview *dw4_modelview_open_field(const dw4_stageobjects *,const dw4_controllers *,char *,size_t);
dw4_modelview *dw4_modelview_open_scene(const dw4_stageobjects *,const dw4_controllers *,char *,size_t);
/* As dw4_modelview_open_scene, for scripted demo stages (stagML14): models draw in layer order, skinned meshes are posed
 * from their bank's motion database at the controller's motion time, model packs outside every layer path join the layer
 * their top igAttrSet names, and models without an authored camera use dw4_modelview_camera's view/projection
 * (row vectors, view space +Z forward, clip Z in [-W, W]). Unlit: scene lights are not applied. */
dw4_modelview *dw4_modelview_open_world(const dw4_stageobjects *,const dw4_controllers *,char *,size_t);
/* Hide the point-message arrow (i_pointcur) while an NPC message window is open (i_stpnl06 stays: it is the message panel too). */
void dw4_modelview_hide_labels(dw4_modelview *,int hide);
/* Hide the player panels i_stpnl00..04 (a hub party's HUD, drawn here, follows the lobby HUD's closed/talk state). */
void dw4_modelview_hide_hud(dw4_modelview *,int hide);
/* Gauge panels: nodes under a meter node pose at that meter's time rather than the controller's clock (the hub HUD's rule). `fn` answers 1 and the
 * time for a scene node id that is a meter node. */
typedef int (*dw4_modelview_node_time)(void *,uint32_t node_id,int32_t slot,int64_t *time);
/* Digit plates: called for every vertex of every mesh; `uv` holds the authored coordinates and may be rewritten (the hub HUD's number rule). */
typedef void (*dw4_modelview_vertex_uv)(void *,uint32_t node_id,uint32_t geometry_id,uint32_t vertex,float uv[2]);
void dw4_modelview_vertex_uvs(dw4_modelview *,dw4_modelview_vertex_uv,void *);
void dw4_modelview_node_times(dw4_modelview *,dw4_modelview_node_time,void *);
/* Restrict the following draws to part of the layer stack: part 1 draws the models on layers before `layer` (in the stage's
 * layer order, BG..WN00..WN04..FONT), part 2 the models on `layer` and after it, 0 every model again. Without that layer part 1
 * draws every model and part 2 none. */
void dw4_modelview_layer_split(dw4_modelview *,const char *layer,int part);
void dw4_modelview_camera(dw4_modelview *,const float view[16],const float projection[16]);
void dw4_modelview_close(dw4_modelview *);
/* Drop the decoded images from a GPU layer's texture cache; call before dw4_modelview_close frees their pixels (the cache is keyed by pixel pointer). */
void dw4_modelview_forget_gpu(const dw4_modelview *,dw4_gl_layer *);
int dw4_modelview_draw(dw4_modelview *,unsigned width,unsigned height,const dw4_ui_draw **,size_t *,char *,size_t);
/* Diagnostic snapshot sampling at observed reference node clocks. The callback
 * returns a pose time; actor position, eligibility and fade remain native.
 * No owner clock or prepared node is mutated. NULL uses the live node clock. */
typedef int64_t (*dw4_modelview_clock)(void *,const dw4_stageobject *,int32_t slot,int64_t native_ns);
int dw4_modelview_draw_clocks(dw4_modelview *,unsigned,unsigned,const dw4_ui_draw **,size_t *,char *,size_t,
    dw4_modelview_clock,void *);
#endif
