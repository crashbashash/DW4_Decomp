/* Retail 41d810 CtrlBit and 41de40 SendBit outer updates. */
#ifndef DW4_STATUSBITCTRL_H
#define DW4_STATUSBITCTRL_H
#include "dw4/statusctrl.h"
typedef struct {dw4_statusctrl window;int32_t recipients;} dw4_statusbit_ctrl;
typedef struct {dw4_statusctrl window;int32_t amount,limit,recipient;} dw4_statussendbit_ctrl;
enum dw4_statusbit_op {DW4_BIT_COLLECT,DW4_BIT_SEND_CHILD,DW4_BIT_POPUP,
    DW4_BIT_COUNT,DW4_BIT_CLOSE,DW4_BIT_FINISHED};
enum dw4_statussendbit_op {DW4_SEND_INIT,DW4_SEND_HIDE_DIGITS,DW4_SEND_RESET,
    DW4_SEND_COUNT,DW4_SEND_CURSOR_OPEN,DW4_SEND_NUMBER_SELECTOR,
    DW4_SEND_NUMBER,DW4_SEND_LIMIT,DW4_SEND_EDIT,DW4_SEND_CURSOR_CLOSE,
    DW4_SEND_HIDE_PROMPT,DW4_SEND_TRANSFER,DW4_SEND_POPUP,
    DW4_SEND_ACK_HIDE,DW4_SEND_REFRESH,DW4_SEND_CLOSE,DW4_SEND_FINISHED};
/* Commands return zero; numeric queries return values; negative means failure.
 * COLLECT returns ordered other joined players, SEND_CHILD creates an actual
 * SendBit tree and POPUP creates an actual ShopSelect00. COUNT is the owned tree.
 * EDIT implements the separately verified amount/readiness/number/sound phase
 * without ticking any model, selector or input owner. */
typedef int (*dw4_statusbit_io)(void *,dw4_statusbit_ctrl *,int,int32_t);
typedef int (*dw4_statussendbit_io)(void *,dw4_statussendbit_ctrl *,int,int32_t);
int dw4_statusbitctrl_tick(dw4_statusbit_ctrl *,dw4_statusbit_io,void *);
int dw4_statussendbitctrl_tick(dw4_statussendbit_ctrl *,dw4_statussendbit_io,void *);
#endif
