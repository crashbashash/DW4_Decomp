/* Concrete retail STATUS root and title/selection controller state machines. */
#ifndef DW4_STATUSCTRL_H
#define DW4_STATUSCTRL_H
#include <stdint.h>
#include "dw4/subwindow.h"
typedef struct {
    int32_t active,state,sub,delay,latch,selection,previous_count,last_selection;
} dw4_statusctrl;
/* Transient scalar adapters for the pure rule/oracle entry points. Production
 * owners keep these fields in the recovered arena object, not in a host copy. */
void dw4_statusctrl_load(const dw4_menu_window *,dw4_statusctrl *);
void dw4_statusctrl_store(dw4_menu_window *,const dw4_statusctrl *);
enum dw4_status_op { DW4_STATUS_CREATE, DW4_STATUS_MODEL, DW4_STATUS_LAYER,
    DW4_STATUS_COUNT, DW4_STATUS_CLOSE_CHILDREN, DW4_STATUS_CLOSE_MODELS,
    DW4_STATUS_CLEAR_TEXT, DW4_STATUS_FINISHED, DW4_STATUS_TEXT,
    DW4_STATUS_SELECT_INIT, DW4_STATUS_SELECT_GET, DW4_STATUS_SELECT_END,
    DW4_STATUS_SELECT_TOP, DW4_STATUS_SELECT_IS_TOP };
enum dw4_status_child { DW4_STATUS_TITLE00, DW4_STATUS_TITLE01,
    DW4_STATUS_TITLE02, DW4_STATUS_TITLE03, DW4_STATUS_TITLE04,
    DW4_STATUS_SELECT00, DW4_STATUS_EQUIP, DW4_STATUS_FOLDER, DW4_STATUS_SKILL };
/* IO owns host window/model/text references and player records. Return numeric
 * queries, zero for commands, negative for failure (SELECT_GET accepts -1
 * for cancel and requires values below -1 for errors). CREATE must publish an owned
 * child before returning; COUNT reads the actual tree, including that child.
 * FINISHED waits on tracked model ISRUN and child pruning, never elapsed ticks.
 * SELECT_IS_TOP returns helper 423700's !ISFO2TOP (one means input-ready),
 * rather than the raw SELECTCTRL query's busy flag.
 * Root selection is visible immediately after SELECT_GET, before SELECT_END;
 * later callback writes must not be overwritten by a delayed publication. */
typedef int (*dw4_status_io)(void *,int op,const char *name,const char *key,int32_t value);
int dw4_statusctrl_tick(dw4_statusctrl *,dw4_status_io,void *);
/* WindowTitle 424160 with concrete StatusTitle00 424230. */
int dw4_statustitle_tick(dw4_statusctrl *,dw4_status_io,void *);
/* WindowSelect 4233f0 with concrete StatusSelect00 423760 setup supplied through
 * SELECT_INIT: 3 rows, (-83,209,0), i_stcursor02, original txt_status.lua. */
int dw4_statusselect_tick(dw4_statusctrl *,dw4_statusctrl *parent,dw4_status_io,void *);
/* Owned window callbacks for the actual recursive SUBWND tree. Root creates
 * native Select00 children; title/data CREATE leaves must append their
 * concrete record/view controller to the root through menu_window_add.
 * FINISHED combines backend model completion with actual child pruning.
 * The borrowed IO owner outlives the tree. Queries never tick it. */
dw4_menu_window *dw4_statustitle_window_open(dw4_status_io,void *);
dw4_menu_window *dw4_statusctrl_window_open(dw4_status_io,void *);
beNDMWStatusCtrl00 *dw4_statusctrl_window_state(dw4_menu_window *);
#endif
