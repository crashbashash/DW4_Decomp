#ifndef DW4_STATUSEQUIPMENTMENU_H
#define DW4_STATUSEQUIPMENTMENU_H
#include "dw4/statusgear.h"
#include "dw4/statussubmenu.h"
/* Normal STATUS equipment menu (40ee60, mode zero). */
dw4_menu_window *dw4_statusequipmentmenu_window_open(const dw4_statusgear_context *);
/* Entry code 1 (the Digi-Lab's "Check", 431e5c): the bottom band (StatusTitle02) replaces the Title04 header. */
dw4_menu_window *dw4_statusequipmentmenu_window_open_entry(const dw4_statusgear_context *,int entry);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statussubmenu dw4_statusequipmentmenu_window_state(const dw4_menu_window *);
int dw4_statusequipmentmenu_window_is(const dw4_menu_window *);
#endif
