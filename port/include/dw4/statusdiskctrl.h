/* Retail 41acf0 DISK update boundary. Host resources remain with its IO owner. */
#ifndef DW4_STATUSDISKCTRL_H
#define DW4_STATUSDISKCTRL_H
#include "dw4/statusctrl.h"
typedef struct {
    dw4_statusctrl window;
    int32_t selected,recipient,limit;
} dw4_statusdisk_ctrl;
enum dw4_statusdisk_op {
    DW4_DISK_INIT, DW4_DISK_MAIN_SELECTOR, DW4_DISK_REFRESH,
    DW4_DISK_ACTION_SELECTOR, DW4_DISK_ACTION_TEXT, DW4_DISK_REORDER_SELECTOR,
    DW4_DISK_SWAP, DW4_DISK_CURSOR_CLOSE, DW4_DISK_GIVE_CHECK,
    DW4_DISK_POPUP, DW4_DISK_RETIRE_MAIN, DW4_DISK_GIVE_SETUP,
    DW4_DISK_RECIPIENT_SELECTOR, DW4_DISK_RECIPIENT_QUANTITY,
    DW4_DISK_CURSOR_OPEN, DW4_DISK_QUANTITY_SELECTOR, DW4_DISK_QUANTITY_TEXT,
    DW4_DISK_TRANSFER, DW4_DISK_ACK_CLEAR, DW4_DISK_RETIRE_GIVE,
    DW4_DISK_CLOSE, DW4_DISK_FINISHED, DW4_DISK_COUNT
};
/* Zero commands, numeric queries, negative errors. GIVE_CHECK returns zero
 * when recipients exist, otherwise original popup call 141/142. COUNT reads
 * actual children after selector construction. RETIRE_* sends close/clear and
 * releases tracking immediately, preserving retail's per-update delays rather
 * than waiting for those models to stop before opening the next resource set.
 * FINISHED, used only for final closure, waits for models and child pruning. */
typedef int (*dw4_statusdisk_io)(void *,dw4_statusdisk_ctrl *,int op,int32_t value);
int dw4_statusdiskctrl_tick(dw4_statusdisk_ctrl *,dw4_statusdisk_io,void *);
#endif
