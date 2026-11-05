/* Native SUBWND ownership and the recovered recursive window update boundary. */
#ifndef DW4_SUBWINDOW_H
#define DW4_SUBWINDOW_H
#include "dw4/stageobjects.h"
#include "dw4/arena.h"
#include "dw4/reflected.h"
typedef struct dw4_subwindows dw4_subwindows;
typedef struct dw4_menu_window dw4_menu_window;
typedef int (*dw4_menu_update)(dw4_menu_window *,char *,size_t);
/* Original window fields +24..+40 live in the arena. Callbacks implement the particular menu;
 * queries never call them. Each parent exclusively owns its children. Callbacks
 * may append children or request close, but must not free a ticking tree or
 * mutate its child array directly. Additions during descendant updates wait
 * until the parent's next update. Cancel the SD scope before owner teardown. */
struct dw4_menu_window {
    dw4_arena *arena;
    dw4_handle object;
    dw4_menu_update update;
    void *user;
    void (*release)(void *);
    dw4_menu_window **children;
};
dw4_menu_window *dw4_menu_window_open(dw4_menu_update,void *,void (*release)(void *));
/* The wrapper holds host callbacks/resources only. Game fields and the child
 * handle list live in the authoritative arena object. Borrow field views only
 * during a call; never store host pointers in reference fields. */
dw4_menu_window *dw4_menu_window_open_class(const char *,dw4_menu_update,void *,void (*release)(void *));
beNDMWWindow *dw4_menu_window_data(const dw4_menu_window *);
size_t dw4_menu_window_count(const dw4_menu_window *);
/* Transfers child ownership on success; rejects sharing and ancestor cycles. */
int dw4_menu_window_add(dw4_menu_window *,dw4_menu_window *);
int dw4_menu_window_is_root(const dw4_menu_window *);
void dw4_menu_window_remove(dw4_menu_window *);
int dw4_menu_window_tick(dw4_menu_window *,char *,size_t);
/* Explicit retained references keep the arena object and its complete resource
 * facade alive after parent pruning. Release each hold with close; a pruned
 * child is detached. Parent links remain borrowed, so this creates no cycle.
 * Borrowed services/parent contexts must still outlive any further updates;
 * after scene teardown a retained reference is for inspection/release only. */
dw4_menu_window *dw4_menu_window_retain(dw4_menu_window *);
void dw4_menu_window_close(dw4_menu_window *);
/* Exact scalar command boundary from beNDMWStatus 3d60e0. */
typedef struct {
    int active;
    int32_t state,sub,delay,latch,player,mode;
} dw4_subwindow_state;
void dw4_subwindow_generate(dw4_subwindow_state *,int32_t mode,int32_t player);
/* Returns 1 when retail requires a one-frame deferred REMOVE (no root yet). */
int dw4_subwindow_remove(dw4_subwindow_state *,dw4_menu_window *);
/* A concrete menu factory must preflight gameplay records/assets and return a
 * private tree. begin/end implement retail scene freeze, layer/audio and player
 * restoration. Missing factories fail before publishing active state. */
typedef struct {
    int (*prepare)(void *,int32_t mode,int32_t player,dw4_menu_window **,char *,size_t);
    int (*begin)(void *,int32_t mode,int32_t player,char *,size_t);
    int (*end)(void *,int32_t mode,int32_t player,char *,size_t);
    void *user;
    /* Optional accepted-GENERATE hook: retail freezes world/model/generator/
     * sound before the first manager update. Runs after private preparation
     * and active publication. Failure latches the scene with ISRUN retained. */
    int (*activate)(void *,int32_t mode,int32_t player,char *,size_t);
    /* Original UPDATE / ONPREVIEW / OFPREVIEW stat-owner commands. */
    int (*update)(void *,int32_t player,char *,size_t);
    int (*preview)(void *,int32_t player,int on,char *,size_t);
} dw4_subwindow_factory;
dw4_subwindows *dw4_subwindows_open(dw4_scriptservices *,uint64_t,const dw4_stageobjects *);
void dw4_subwindows_close(dw4_subwindows *);
int dw4_subwindows_factory(dw4_subwindows *,const dw4_subwindow_factory *);
int dw4_subwindows_tick(dw4_subwindows *);
const char *dw4_subwindows_error(const dw4_subwindows *);
/* Borrow a typed Work closure whose owner outlives this SUBWND slot. */
int dw4_subwindows_bind_work(dw4_subwindows *,size_t,dw4_handle);
size_t dw4_subwindows_count(const dw4_subwindows *);
/* Diagnostic snapshot; runtime state remains in Status/StatusInfoRam. Invalid
 * slots return a zero snapshot. No pointer into a mutable host mirror escapes. */
dw4_subwindow_state dw4_subwindows_at(const dw4_subwindows *,size_t);
/* The running root window of a slot (NULL when none), for diagnostics. */
const dw4_menu_window *dw4_subwindows_root(const dw4_subwindows *,size_t);
/* Compatibility for externally owned services; replace only while inactive. */
int dw4_subwindows_override(dw4_subwindows *,dw4_script_binding,void *);
#endif
