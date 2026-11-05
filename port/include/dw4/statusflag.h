/* Original STATUS important-item page (41a400/41aaa0). */
#ifndef DW4_STATUSFLAG_H
#define DW4_STATUSFLAG_H
#include "dw4/statuscontent.h"
typedef struct {dw4_statusview_context view;const dw4_databases *databases;} dw4_statusflag_context;
dw4_menu_window *dw4_statusflag_window_open(const dw4_statusflag_context *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusctrl dw4_statusflag_window_state(const dw4_menu_window *);
int dw4_statusflag_window_is(const dw4_menu_window *);
#endif
