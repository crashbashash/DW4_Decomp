/* Owned STATUS skill menu, original content and selector routing. */
#ifndef DW4_STATUSSKILL_H
#define DW4_STATUSSKILL_H
#include "dw4/statuscontent.h"
#include "dw4/statussubmenu.h"
#include "dw4/statuspage.h"
typedef struct {
    dw4_statusview_context view;
    const dw4_databases *databases;
    int (*input)(void *,int32_t player,dw4_statuspage_input *);
    void *user;
} dw4_statusskill_context;
/* Copies context; dependencies outlive the tree. No initialization or input at
 * open. Resource close is awaited before reusing shared models/fonts. Errors
 * latch completion until scene reset. Does not install the normal-boot factory. */
dw4_menu_window *dw4_statusskill_window_open(const dw4_statusskill_context *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statussubmenu dw4_statusskill_window_state(const dw4_menu_window *);
int dw4_statusskill_window_is(const dw4_menu_window *);
#endif
