/* Original STATUS disk ordering and quantity-transfer menu. */
#ifndef DW4_STATUSDISK_H
#define DW4_STATUSDISK_H
#include "dw4/statuscontent.h"
#include "dw4/dialogue.h"
typedef struct {dw4_statusview_context view;const dw4_databases *databases;dw4_dialogue *dialogue;} dw4_statusdisk_context;
dw4_menu_window *dw4_statusdisk_window_open(const dw4_statusdisk_context *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusctrl dw4_statusdisk_window_state(const dw4_menu_window *);
int dw4_statusdisk_window_is(const dw4_menu_window *);
#endif
