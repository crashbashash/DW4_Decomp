#ifndef DW4_FILELIST_H
#define DW4_FILELIST_H
#include "dw4/mount.h"
#include "dw4/scriptengine.h"

typedef struct dw4_filelist dw4_filelist;
/* Borrowed mount must outlive the loader. Scene packs remain resident until
 * begin/close; the two first-use resources remain resident for its lifetime.
 * Call begin only at a quiescent scene boundary on an empty script engine.
 * No graphics/audio device work or native receiver publication occurs here. */
dw4_filelist *dw4_filelist_open(dw4_mount *);
void dw4_filelist_close(dw4_filelist *);
int dw4_filelist_begin(dw4_filelist *,dw4_scriptengine *,const char *stage,uint64_t scope);
/* Execute original func/boot, then load the CFL queue. An unsupported native
 * query or missing asset fails preparation; callers reset the scene before
 * retrying. Preserves the retail startup statuses in the script engine. */
int dw4_filelist_shared(dw4_filelist *);
/* Route the stage directory, then prepared packs into owning native systems, then run start.lua after
 * layer binding, and first.lua after system activation. The callback borrows
 * parsed packs and is responsible for validating/registering its own objects.
 * Returns -1 on failures; a failed preparation cannot advance to FIRST. */
typedef int (*dw4_filelist_route)(void *,const char *path,dw4_igb *,int onetime);
int dw4_filelist_route_assets(dw4_filelist *,dw4_filelist_route,void *);
/* Complete layer binding after every pack has routed. A failed bind latches
 * preparation failure; start/first cannot run without successful binding. */
typedef int (*dw4_filelist_bind)(void *);
int dw4_filelist_bind_layers(dw4_filelist *,dw4_filelist_bind,void *);
int dw4_filelist_start(dw4_filelist *);
int dw4_filelist_first(dw4_filelist *);
const char *dw4_filelist_error(const dw4_filelist *);
const char *dw4_filelist_stage(const dw4_filelist *);
size_t dw4_filelist_count(const dw4_filelist *);
const char *dw4_filelist_path(const dw4_filelist *,size_t);
size_t dw4_filelist_queue_count(const dw4_filelist *);
const char *dw4_filelist_queue_path(const dw4_filelist *,size_t);
/* Native-call boundary for CFL and USA constant queries. Other methods are
 * deliberately rejected; they must be supplied by their owning systems. */
int dw4_filelist_call(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
#endif
