/* The generic shop root (SUBWND modes 1 and 3..9): retail beNDMWShopCtrl00 update 4267b0..426f94.
 * State 0 creates the five common widgets in order (ShopTitle00 the j_shback backdrop,
 * StatusTitle01 the player panel, StatusTitle02 the message window, StatusTitle03 the
 * Select/Confirm/Cancel legend, ShopTitle01 the i_sttitle header); state 1 waits for the message
 * window's opening sequence, creates the service selected by the entry code and then waits for its
 * completion (a change of the child count); state 2 closes every widget. */
#ifndef DW4_SHOPROOT_H
#define DW4_SHOPROOT_H
#include "dw4/statusview.h"
#include "dw4/statusstats.h"
typedef struct {
    /* sd, engine, players, scope and player are required (they outlive the window). */
    dw4_statusview_context view;
    /* The stat owner Title01's refresh reads (the same owner the STATUS menu uses). */
    dw4_statusstats *stats;
    /* _entCode: 1 XDATA, 3 BANK, 4 CNOS, 5 DISK, 6/7/8 WPU/APU/CHIP, 9 JUNK. It picks the header text (txt_shop call
     * 1000 + 100 * entry). Entry 2 hosts the Digi-Lab with the widget set of its own root (Digilabo 431760 state 0:
     * ShopTitle00, StatusTitle03, ShopTitle01, no message-window gate). */
    int32_t entry;
    /* Creates the selected service window (the original factory call); it becomes the root's last child. */
    dw4_menu_window *(*service)(void *);void *user;
} dw4_shoproot_context;
dw4_menu_window *dw4_shoproot_window_open(const dw4_shoproot_context *);
/* Diagnostic: primary state, substate and the service-wait child count. */
typedef struct {int32_t state,sub;size_t children;} dw4_shoproot_state;
int dw4_shoproot_window_state(const dw4_menu_window *,dw4_shoproot_state *);
#endif
