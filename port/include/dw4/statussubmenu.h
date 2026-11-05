/* Retail equipment/folder/skill orchestration; host-owned trees and services. */
#ifndef DW4_STATUSSUBMENU_H
#define DW4_STATUSSUBMENU_H
#include "dw4/statusctrl.h"
typedef struct {
    dw4_statusctrl window;
    int32_t mode,page,pages,offset;
} dw4_statussubmenu;
enum dw4_submenu_op {
    DW4_SUBMENU_CREATE, DW4_SUBMENU_COUNT, DW4_SUBMENU_MODEL,
    DW4_SUBMENU_SCRIPT, DW4_SUBMENU_CLEAR_MESSAGE, DW4_SUBMENU_CLOSE_MODELS,
    DW4_SUBMENU_CLEAR_TEXT, DW4_SUBMENU_CLOSE_CHILDREN, DW4_SUBMENU_FINISHED,
    DW4_SUBMENU_FIND_SELECTOR, DW4_SUBMENU_SELECTOR_READY,
    DW4_SUBMENU_SELECTOR_CLOSE, DW4_SUBMENU_SELECTOR_RESTART,
    DW4_SUBMENU_RESET_RESOURCES, DW4_SUBMENU_SKILL_LIST,
    DW4_SUBMENU_SKILL_SETUP, DW4_SUBMENU_SKILL_REFRESH,
    DW4_SUBMENU_SKILL_TOP, DW4_SUBMENU_SKILL_NEXT, DW4_SUBMENU_SKILL_PREVIOUS,
    DW4_SUBMENU_SKILL_REPAGE, DW4_SUBMENU_SKILL_CLEAR_COLORS
};
/* CREATE is synchronous and appends an exclusively owned child. value is the
 * original text call/selection; key identifies the concrete child (NULL means
 * the three/four-row menu). Child selectors write window.selection.
 * SKILL_SETUP initializes the original page view/list and appends its selector;
 * SKILL_REFRESH receives 1 on initial page, 0 on selection refresh.
 * SKILL_NEXT/PREVIOUS mutate page/offset only when an actual page exists.
 * Negative queries fail (selection cancellation is a field, not an IO error).
 * All model/text/list leaves are mandatory; no empty-success default is supplied. */
typedef int (*dw4_submenu_io)(void *,dw4_statussubmenu *,int,const char *,const char *,int32_t);
int dw4_statussubmenu_tick(dw4_statussubmenu *,int kind,dw4_submenu_io,void *);
/* IO and its resource owner outlive the returned tree. COUNT, child close and
 * FINISHED's pruning hold are supplied by the window owner. */
dw4_menu_window *dw4_statussubmenu_window_open(int kind,int mode,dw4_submenu_io,void *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statussubmenu dw4_statussubmenu_window_state(const dw4_menu_window *);
int dw4_statussubmenu_window_is(const dw4_menu_window *);
#endif
