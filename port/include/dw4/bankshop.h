/* Native NPC bank: retail beNDMWShopCtrl30 update 428790..429628 (SUBWND mode 3, "BANK"), its
 * beNDMWShopCtrlEditBit amount editor (4332d0) and the shared beNDMWStatusCtrlD0 item list. */
#ifndef DW4_BANKSHOP_H
#define DW4_BANKSHOP_H
#include "dw4/statusview.h"
#include "dw4/database.h"
#include "dw4/statuspage.h"
typedef struct {
    /* sd, engine, players, scope and player are required; parent/callno/rows/selected belong
     * to the individual selector windows this controller creates. */
    dw4_statusview_context view;
    const dw4_databases *databases;
    /* The item list and the amount editor sample the pad once per update. */
    int (*input)(void *,int32_t player,dw4_statuspage_input *);
    void *user;
} dw4_bankshop_context;
/* Root window: first menu (deposit / withdraw / leave), second menu (items / money), the item
 * list with capacity and equipped-item rules, and the seven-digit money editor. Transactions
 * are the atomic dw4_playertransactions_bank_item / bank_bit. Borrowed dependencies outlive it. */
dw4_menu_window *dw4_bankshop_window_open(const dw4_bankshop_context *);
/* The beNDMWShopCtrlEditBit amount editor on its own (modes 0 deposit, 1 withdraw, 2 junk-shop donation).
 * The outer window's arena _retCode receives the amount, or -1 when cancelled or (mode 2) declined. The caller adds the
 * returned window to its tree and treats a child-count change as completion. Borrowed dependencies outlive it. */
dw4_menu_window *dw4_bankshop_editor_open(const dw4_bankshop_context *,dw4_menu_window *outer,int32_t mode);
/* Diagnostic snapshot of the controller's phase counters (flag is the pending notice code). */
typedef struct {int32_t state,main,sub,flag,menu;} dw4_bankshop_state;
int dw4_bankshop_window_state(const dw4_menu_window *,dw4_bankshop_state *);
#endif
