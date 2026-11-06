/* Native weapon / armor / chip / junk shops: SUBWND modes 6 WPU, 7 APU, 8 CHIP (retail
 * beNDMWShopDevice 43cc20) and 9 JUNK (beNDMWShopJunk 42bc70), with their shared goods list
 * beNDMWShopCtrlSales (438160). The sell branch is ShopCtrlSell and the donation editor
 * ShopCtrlEditBit mode 2, both shared with DISK and BANK. */
#ifndef DW4_EQUIPSHOP_H
#define DW4_EQUIPSHOP_H
#include "dw4/statusview.h"
#include "dw4/database.h"
#include "dw4/statuspage.h"
#include "dw4/shopstock.h"
typedef struct {
    /* sd, engine, players, scope and player are required; parent/callno/rows/selected belong to the individual
     * selector windows the controllers create. */
    dw4_statusview_context view;
    /* Must provide the weapon/armor1/armor2/abChip item databases, conItem and the shop tables' items. */
    const dw4_databases *databases;
    /* The prepared stock for the mode (dw4_shopstock_prepare); it persists across visits and is shared with the owner. */
    dw4_shopstock *stock;
    /* 6 WPU, 7 APU, 8 CHIP or 9 JUNK. */
    int32_t mode;
    /* The lists sample the pad once per update for their page turns. */
    int (*input)(void *,int32_t player,dw4_statuspage_input *);
    /* ONPREVIEW: show the staged, recalculated folder's stats against the baseline (OFPREVIEW is sent as an SD
     * command). Called when the highlighted goods item would replace the equipped weapon/armor. */
    int (*preview)(void *,dw4_property_folder *,char *,size_t);
    void *user;
} dw4_equipshop_context;
/* Root window for the mode: the buy/sell/leave menu (6..8) or the donate/buy/leave menu (9), the goods list with
 * its page turns, equip preview, eligibility warning, confirmation and atomic purchase, the sell branch and (9)
 * the donation editor with the stock-tier threshold. Borrowed dependencies outlive it. */
dw4_menu_window *dw4_equipshop_window_open(const dw4_equipshop_context *);
/* Diagnostic snapshot of the root's phase counters (page/cursor are the goods list's, valid while it is open). */
typedef struct {int32_t state,main,sub,page,cursor,notice;} dw4_equipshop_state;
int dw4_equipshop_window_state(const dw4_menu_window *,dw4_equipshop_state *);
#endif
