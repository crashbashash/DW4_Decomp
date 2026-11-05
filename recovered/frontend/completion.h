/* The slot screen's completion and selection decisions.
 *
 * Recovered from the retail binary (see docs/engine/load-intf2.md §Recovered
 * completion/selection helpers).  Three small functions the master update, the
 * SelSlot helpers and the message path consult to decide whether the model
 * work is finished and which row a confirm selects:
 *
 *   0x003e4280  cm_open_empty   the CommMdlCtrl's open-data list is empty
 *   0x003e44d0  cm_close_empty  the CommMdlCtrl's close-data list is empty
 *   0x003ee190  ds_select       arm the four per-player records, select one
 *
 * They own no state: every field read/written is reached through the record
 * passed in (a0).  The engine/messenger callees of the callers stay opaque
 * (api->call) as in the rest of recovered/frontend/.
 */
#ifndef DW4_COMPLETION_H
#define DW4_COMPLETION_H

#include <stdint.h>

#include "loadintf2.h"

/* 0x003e4280 — CommMdlCtrl(a0)._openDataList(+0x14).count(+8) <= 0.
 * owner +0x14 is an igObjectList: +8 count, +0x10 data pointer. */
int cm_open_empty(const Dw4LoadIntf2Api *api, int32_t cm);

/* 0x003e44d0 — the same predicate on _closeDataList(+0x18). */
int cm_close_empty(const Dw4LoadIntf2Api *api, int32_t cm);

/* 0x003ee190 — the per-player records live at
 * common(+0).+0x28 -> list -> +0x10 data -> [i*4]; for i in 0..3 set
 * _closeKind(+0x24)=1, _st2(+0x28)/_st3(+0x2c)/_isUseData(+0x30)=0, the
 * run byte(+0xf)=0 and the timer(+8)=0x3c, then for row `sel` clear
 * _closeKind and set the run byte(+0xf)=1 and the timer(+8)=0. */
void ds_select(const Dw4LoadIntf2Api *api, int32_t common, int32_t sel);

#endif /* DW4_COMPLETION_H */
