/* Native XDATA shop controller: retail beNDMWShopCtrl10 update 4270a0..42860c. */
#ifndef DW4_XDATASHOP_H
#define DW4_XDATASHOP_H
#include "dw4/statusview.h"
#include "dw4/database.h"
#include "dw4/statuspage.h"
typedef struct {
    /* sd, engine, players, scope and player are required; parent/callno/rows/selected
     * belong to the individual selector windows this controller creates. */
    dw4_statusview_context view;
    const dw4_databases *databases;
    /* Chip list paging samples the pad once per update (statuspage horizontal/digital words). */
    int (*input)(void *,int32_t player,dw4_statuspage_input *);
    /* ONPREVIEW: show the staged, recalculated folder's stats against the baseline. */
    int (*preview)(void *,dw4_property_folder *,char *,size_t);
    void *user;
} dw4_xdatashop_context;
/* Root window for SUBWND mode XDATA. It creates the main menu, the seven-stat list,
 * quote/notice dialogs and confirmations as owned children in retail order, and
 * charges a selected stat exactly once on confirmation. The chip branch is the recovered
 * beNDMWShopCtrlXdataChip (43aae0): a paged chip list, quote with equipped-chip stat preview,
 * confirmation and an atomic upgrade. input and preview are required for it. The context's
 * registry, engine and records outlive the window. */
dw4_menu_window *dw4_xdatashop_window_open(const dw4_xdatashop_context *);
/* Diagnostic snapshot of the controller's phase counters. */
typedef struct {int32_t state,main,sub,flag,parameter,menu;} dw4_xdatashop_state;
int dw4_xdatashop_window_state(const dw4_menu_window *,dw4_xdatashop_state *);
#endif
