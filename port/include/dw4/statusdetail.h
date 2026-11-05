/* Original STATUS DEVICE action menu: discard, arrange and give. */
#ifndef DW4_STATUSDETAIL_H
#define DW4_STATUSDETAIL_H
#include "dw4/statusdevice.h"
#include "dw4/dialogue.h"
enum {DW4_DETAIL_RETAINED_CLOSE,DW4_DETAIL_RETAINED_FINISHED};
typedef struct {
    dw4_statusview_context view;const dw4_databases *databases;dw4_dialogue *dialogue;
    int32_t selected;
    /* Original detail +88 retains the parent's DEVICE. Its owner handles
     * close/completion without sharing a host tree pointer after child pruning.
     * FINISHED is read-only; NULL preserves retail's absent-DEVICE give exit. */
    int (*device)(void *,int);void *device_user;
    dw4_menu_window *device_window; /* production retained DEVICE closure */
} dw4_statusdetail_context;
dw4_menu_window *dw4_statusdetail_window_open(const dw4_statusdetail_context *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusctrl dw4_statusdetail_window_state(const dw4_menu_window *);
int dw4_statusdetail_window_is(const dw4_menu_window *);
#endif
