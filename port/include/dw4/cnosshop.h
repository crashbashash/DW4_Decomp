/* Native NPC item converter: retail beNDMWShopCtrl40 update 429630..42a2d8 (SUBWND mode 4, "CNOS")
 * over the shared beNDMWStatusCtrlD0 item list. */
#ifndef DW4_CNOSSHOP_H
#define DW4_CNOSSHOP_H
#include "dw4/statusview.h"
#include "dw4/database.h"
#include "dw4/statuspage.h"
#include "dw4/random.h"
typedef struct {
    /* sd, engine, players, scope and player are required; parent/callno/rows/selected belong
     * to the individual selector windows this controller creates. */
    dw4_statusview_context view;
    /* Must provide the coweapon/coarmor1/coarmor2 reroll tables. */
    const dw4_databases *databases;
    /* The item list samples the pad once per update. */
    int (*input)(void *,int32_t player,dw4_statuspage_input *);
    /* The engine's one shared MT19937 stream (retail genrand, vtable slot 24). */
    dw4_random *random;
    void *user;
} dw4_cnosshop_context;
/* Root window: the item list (only the placeholder "unknown" equipment is selectable), the
 * unaffordable notice, the confirmation and yes/no menu, and the 300 BIT conversion. Borrowed
 * dependencies outlive it. */
dw4_menu_window *dw4_cnosshop_window_open(const dw4_cnosshop_context *);
/* Diagnostic snapshot of the controller's phase counters (selected is the converted DEVICEFOLDER index). */
typedef struct {int32_t state,main,sub,selected;} dw4_cnosshop_state;
int dw4_cnosshop_window_state(const dw4_menu_window *,dw4_cnosshop_state *);
#endif
