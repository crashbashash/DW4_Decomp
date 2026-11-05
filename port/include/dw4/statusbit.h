/* Original STATUS BANK child is the currency-transfer controller. */
#ifndef DW4_STATUSBIT_H
#define DW4_STATUSBIT_H
#include "dw4/statusdevice.h"
#include "dw4/dialogue.h"
typedef struct {
    dw4_statusview_context view;dw4_dialogue *dialogue;
    int (*input)(void *,int32_t,dw4_statuspage_input *);void *user;
} dw4_statusbit_context;
/* 41de40 digit edit: up wins simultaneous up/down; clamp to 0..limit. */
int dw4_statusbit_adjust(int32_t *amount,int32_t limit,int selected,const dw4_statuspage_input *);
enum {DW4_STATUSBIT_REDRAW=1,DW4_STATUSBIT_SOUND=2};
/* Exact edit effects: changed place redraws only; a ready value change also sounds. */
int dw4_statusbit_edit(int32_t *,int32_t,int,int32_t *,int,const dw4_statuspage_input *);
/* Metadata transition after successful close IO; completion is a read-only query. */
int dw4_statusbit_close_step(dw4_statusctrl *,int finished);
dw4_menu_window *dw4_statusbit_window_open(const dw4_statusbit_context *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusctrl dw4_statusbit_window_state(const dw4_menu_window *);
/* Read the actual SendBit child state separately from its CtrlBit parent. */
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusctrl dw4_statussendbit_window_state(const dw4_menu_window *);
int dw4_statusbit_window_is(const dw4_menu_window *);
int dw4_statussendbit_window_is(const dw4_menu_window *);
#endif
