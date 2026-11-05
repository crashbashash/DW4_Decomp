/* Retail 4207a0 DEVICE action update. IO owns views, records and retained DEVICE. */
#ifndef DW4_STATUSDETAILCTRL_H
#define DW4_STATUSDETAILCTRL_H
#include "dw4/statusctrl.h"
typedef struct {dw4_statusctrl window;int32_t recipient,retained;} dw4_statusdetail_ctrl;
enum dw4_statusdetail_op {
    DW4_DETAIL_INIT, DW4_DETAIL_COUNT, DW4_DETAIL_CLOSE, DW4_DETAIL_FINISHED,
    DW4_DETAIL_DEFAULT_COLOR, DW4_DETAIL_DISCARD_CHECK, DW4_DETAIL_POPUP,
    DW4_DETAIL_CONFIRM, DW4_DETAIL_REMOVE, DW4_DETAIL_SORT,
    DW4_DETAIL_GIVE_CHECK, DW4_DETAIL_DEVICE_CLOSE, DW4_DETAIL_DEVICE_FINISHED,
    DW4_DETAIL_DEVICE_RELEASE, DW4_DETAIL_CURSOR_CLOSE, DW4_DETAIL_CLEAR_TEXT,
    DW4_DETAIL_GIVE_SETUP, DW4_DETAIL_RECIPIENT_SELECTOR,
    DW4_DETAIL_RECIPIENT_COUNT, DW4_DETAIL_TRANSFER, DW4_DETAIL_CURSOR_OPEN
};
/* Commands return zero, queries return numbers, failures return negative.
 * DISCARD_CHECK returns the original 78/144/145 text call; GIVE_CHECK returns
 * zero for admission or 146/147/148 for rejection. retained reflects the actual
 * DEVICE dependency supplied by the parent. Completion queries never tick it.
 * Count snapshots observe actual selector children after construction. */
typedef int (*dw4_statusdetail_io)(void *,dw4_statusdetail_ctrl *,int,int32_t);
int dw4_statusdetailctrl_tick(dw4_statusdetail_ctrl *,dw4_statusdetail_io,void *);
#endif
