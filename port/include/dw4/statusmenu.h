#ifndef DW4_STATUSMENU_H
#define DW4_STATUSMENU_H
#include "dw4/statusgear.h"
typedef struct {dw4_statusgear_context gear;dw4_dialogue *dialogue;} dw4_statusmenu_context;
/* Complete original STATUS tree with independent Title00 resource ownership.
 * Scene lifecycle belongs to SUBWND's factory, not this window. */
dw4_menu_window *dw4_statusmenu_window_open(const dw4_statusmenu_context *);
const beNDMWStatusCtrl00 *dw4_statusmenu_window_state(const dw4_menu_window *);
#endif
