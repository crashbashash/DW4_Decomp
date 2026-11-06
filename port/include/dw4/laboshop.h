/* Native Digi-Lab service: retail beNDMWShopCtrlDigilabo update 431760..432950 (SUBWND mode 2,
 * "LABO") with its beNDMWShopCtrlEvolve child (42f710..430d20). */
#ifndef DW4_LABOSHOP_H
#define DW4_LABOSHOP_H
#include "dw4/statusgear.h"
/* The STATUS gear context: view (sd, engine, players, scope, player), databases (shinka, weapon, armor, abChip),
 * stats and appearance for the embedded equipment menu, and the pad input used for the list's page turns.
 * Borrowed dependencies outlive the window. Only a single joined player is supported (co-op is out of scope). */
dw4_menu_window *dw4_laboshop_window_open(const dw4_statusgear_context *);
/* Diagnostic snapshot of the controller's phase counters. */
typedef struct {int32_t state,main,sub,evolved,checked,result;} dw4_laboshop_state;
int dw4_laboshop_window_state(const dw4_menu_window *,dw4_laboshop_state *);
#endif
