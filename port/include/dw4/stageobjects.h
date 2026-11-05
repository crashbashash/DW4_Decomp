/* Prepared scene objects and the authored layer graph. */
#ifndef DW4_STAGEOBJECTS_H
#define DW4_STAGEOBJECTS_H
#include "dw4/arena.h"
#include "dw4/filelist.h"
#include "dw4/igb.h"
#include "dw4/scene.h"
#include "dw4/scriptservices.h"

typedef struct dw4_stageobjects dw4_stageobjects;
typedef struct {
    const char *path;
    uint32_t id;
    int onetime;
    dw4_handle object;      /* the info record as a typed instance in the session arena (references are NULL: the asset layer reads them) */
    const dw4_igb *igb;     /* the pack the info came from, for the asset-layer reads of its referents */
    dw4_scene *scene; /* command owners mutate instance transforms/switches; draw only samples */
    dw4_arena *arena;
} dw4_stageobject;
/* Typed reads of the info instance (igNamedObject._name, beModelCtrlInfo._kindString, beBkColorInfo._rgba); NULL / 0 when the class
 * has no such field. The class is the instance's recovered class name. */
const char *dw4_stageobject_class(const dw4_stageobject *);
const char *dw4_stageobject_name(const dw4_stageobject *);
const char *dw4_stageobject_kind_string(const dw4_stageobject *);
int dw4_stageobject_rgba(const dw4_stageobject *,float rgba[4]);
/* Two infos are the same record (the same pack object, listed more than once). */
int dw4_stageobject_same(const dw4_stageobject *,const dw4_stageobject *);
/* The pack id a reference field of the info names (the asset layer follows it in `igb`); UINT32_MAX when absent. */
uint32_t dw4_stageobject_ref_id(const dw4_stageobject *,const char *field);
typedef struct {
    const dw4_stageobject *info;
    uint32_t root_id;
    size_t layer;
} dw4_layer_attachment;
/* The mount supplying prepared bytes must outlive this owner. Typed infos and
 * renderer arenas are owned here; callback pack descriptors are never retained.
 * Build privately, bind, then publish. Close only after SD/Lua/DM teardown. */
dw4_stageobjects *dw4_stageobjects_open(void);
/* Before routing: also expand each igActor's appearance skin graph into the pack scenes (dw4_scene_load_actor_preview),
 * so model renderers can pose skinned character packs (the digivolution demo's s_<species> models). */
void dw4_stageobjects_actor_skins(dw4_stageobjects *,int on);
void dw4_stageobjects_close(dw4_stageobjects *);
int dw4_stageobjects_route(void *,const char *,dw4_igb *,int onetime);
int dw4_stageobjects_bind(dw4_stageobjects *);
int dw4_stageobjects_bind_layers(void *); /* file-list completion callback */
const char *dw4_stageobjects_error(const dw4_stageobjects *);
size_t dw4_stageobjects_count(const dw4_stageobjects *);
const dw4_stageobject *dw4_stageobjects_at(const dw4_stageobjects *,size_t);
/* Exact class/name lookup in collection order; occurrence retains duplicates. */
const dw4_stageobject *dw4_stageobjects_find(const dw4_stageobjects *,const char *class_name,
    const char *name,size_t occurrence);
/* Authored ROOTATTR scene and its LAYERPARENT node; synthetic layer switch
 * attaches here, while cross-pack roots retain their own arena handles. */
const dw4_stageobject *dw4_stageobjects_root(const dw4_stageobjects *,uint32_t *parent_id);
size_t dw4_stageobjects_layers(const dw4_stageobjects *);
const char *dw4_stageobjects_layer(const dw4_stageobjects *,size_t);
int dw4_stageobjects_layer_visible(const dw4_stageobjects *,size_t);
size_t dw4_stageobjects_attachments(const dw4_stageobjects *);
const dw4_layer_attachment *dw4_stageobjects_attachment(const dw4_stageobjects *,size_t);
/* LAYERCTL SWITCH name/action. Other services fail.
 * Receiver registration is a separate publication step after complete binding. */
int dw4_stageobjects_publish(dw4_stageobjects *,dw4_scriptservices *,uint64_t scope);
int dw4_stageobjects_layer_service(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
int dw4_stageobjects_switch_service(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
#endif
