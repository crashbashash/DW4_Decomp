/* Native Digi-Disk shop: retail beNDMWShopCtrl50 update 42a2e0..42b7f8 (SUBWND mode 5, "DISK")
 * with its sell branch (ShopCtrlSell 434790, ShopCtrlDeviceSell 4353e0, ShopCtrlDiskSell 436ac0). */
#ifndef DW4_DISKSHOP_H
#define DW4_DISKSHOP_H
#include "dw4/statusview.h"
#include "dw4/database.h"
#include "dw4/statuspage.h"
typedef struct {
    /* sd, engine, players, scope and player are required; parent/callno/rows/selected belong to the
     * individual selector windows the controllers create. */
    dw4_statusview_context view;
    /* Must provide conItem (NAME/TXT/HANBAI/KAITORI) and the weapon/armor/chip databases. */
    const dw4_databases *databases;
    /* The device sell list samples the pad once per update for its page turns. */
    int (*input)(void *,int32_t player,dw4_statuspage_input *);
    void *user;
} dw4_diskshop_context;
/* Root window: the buy/sell/leave menu, the ten-disk price list, the quantity selector, the buy
 * confirmation and the sell branch with its device and disk lists. Borrowed dependencies outlive it. */
dw4_menu_window *dw4_diskshop_window_open(const dw4_diskshop_context *);
/* The sell branch on its own (ShopCtrlSell 434790): the device/disk menu with its two lists. The WPU/APU/CHIP
 * shops open it as their sell entry. Borrowed dependencies outlive it. */
dw4_menu_window *dw4_diskshop_sell_window_open(const dw4_diskshop_context *);
/* Diagnostic snapshot of the controller's phase counters (item is the listed disk, owned the held count). */
typedef struct {int32_t state,main,sub,item,owned,quantity;} dw4_diskshop_state;
int dw4_diskshop_window_state(const dw4_menu_window *,dw4_diskshop_state *);
#endif
