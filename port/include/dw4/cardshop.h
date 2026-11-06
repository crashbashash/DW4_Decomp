/* Native card album: retail SUBWND mode 10 (CARD), the stagIS11 scene's window tree:
 * beNDMWShopCtrlA0 update 42c810 (the root: titles, the two-row menu and the player chooser),
 * ShopCtrlA1 42d450 (a player's menu and the album viewer) and ShopCtrlA2 42eb80 (the Booster Pack
 * opening). */
#ifndef DW4_CARDSHOP_H
#define DW4_CARDSHOP_H
#include "dw4/statusview.h"
#include "dw4/database.h"
#include "dw4/random.h"
typedef struct {
    /* sd, engine, players, scope and player are required. */
    dw4_statusview_context view;
    /* Must provide the card database (NAME/CARDINFO/SQALBUM/KAKURITSU/RARE) and the shinka species names. */
    const dw4_databases *databases;
    /* The engine's random stream: every card of a Booster Pack takes one draw (the retail vfunc 0x60 of the pad/random manager). */
    dw4_random *random;
    /* STATUS stat owner for the player panel (StatusTitle01): refresh(user, player, error, cap). */
    int (*refresh)(void *,int32_t,char *,size_t);
    void *user;
} dw4_cardshop_context;
/* Root window (SUBWND mode 10). Borrowed dependencies outlive it. */
dw4_menu_window *dw4_cardshop_window_open(const dw4_cardshop_context *);
/* Diagnostic snapshot: the root's primary/main/sub, the player the album shows, and the last opened pack's cards. */
typedef struct {int32_t state,main,sub,player;} dw4_cardshop_state;
int dw4_cardshop_window_state(const dw4_menu_window *,dw4_cardshop_state *);
#endif
