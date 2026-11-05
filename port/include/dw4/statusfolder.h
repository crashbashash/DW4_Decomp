/* Owned original FOLDER orchestration and every concrete child. */
#ifndef DW4_STATUSFOLDER_H
#define DW4_STATUSFOLDER_H
#include "dw4/statussubmenu.h"
#include "dw4/statusdevice.h"
#include "dw4/dialogue.h"
typedef struct {
    dw4_statusview_context view;const dw4_databases *databases;dw4_dialogue *dialogue;
    int (*input)(void *,int32_t,dw4_statuspage_input *);void *user;
} dw4_statusfolder_context;
dw4_menu_window *dw4_statusfolder_window_open(const dw4_statusfolder_context *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statussubmenu dw4_statusfolder_window_state(const dw4_menu_window *);
int dw4_statusfolder_window_is(const dw4_menu_window *);
#endif
