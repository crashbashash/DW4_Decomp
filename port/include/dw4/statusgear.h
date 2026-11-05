/* Complete owned Power/Main/Sub equipment view and transaction routing. */
#ifndef DW4_STATUSGEAR_H
#define DW4_STATUSGEAR_H
#include "dw4/statusdevice.h"
#include "dw4/statusstats.h"
typedef struct {
    dw4_statusview_context view;const dw4_databases *databases;
    dw4_statusstats *stats;
    int (*input)(void *,int32_t,dw4_statuspage_input *);
    /* Required for first-weapon swap publication, including empty weapons. */
    int (*appearance)(void *,int32_t player,char *,size_t);
    void *user;
} dw4_statusgear_context;
dw4_menu_window *dw4_statusgear_window_open(const dw4_statusgear_context *,int kind,int mode);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusequip dw4_statusgear_window_state(const dw4_menu_window *);
int dw4_statusgear_window_is(const dw4_menu_window *);
#endif
