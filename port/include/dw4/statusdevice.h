/* Retail 418090 DEVICE selector lifetime and 4191f0 row decisions. */
#ifndef DW4_STATUSDEVICE_H
#define DW4_STATUSDEVICE_H
#include "dw4/statuscontent.h"
#include "dw4/statuspage.h"
#include "dw4/statusequip.h"
typedef struct {
    int32_t kinds[4],nkinds,ab_type;
    uint8_t equip_disable,unknown_enable,unknown_disable;
} dw4_statusdevice_filter;
typedef struct {int32_t pages,rows,count;uint8_t enabled[12];} dw4_statusdevice_rows;
typedef int (*dw4_statusdevice_attribute)(void *,const dw4_item_record *,const char *,int32_t *);
/* Keep every inventory row in order. Restrictions disable rows; they never
 * compact the list or substitute value equality for DEVICEFOLDER identity. */
int dw4_statusdevice_decide(const dw4_item_record *,size_t,int page,
    const dw4_statusdevice_filter *,dw4_statusdevice_attribute,void *,dw4_statusdevice_rows *);
typedef struct {dw4_statusctrl window;int32_t page,pages,row,auto_close;} dw4_statusdevice;
enum dw4_device_op {DW4_DEVICE_INIT,DW4_DEVICE_COUNT,DW4_DEVICE_REFRESH,
    DW4_DEVICE_TOP,DW4_DEVICE_PREVIOUS,DW4_DEVICE_NEXT,DW4_DEVICE_REPAGE,
    DW4_DEVICE_INVENTORY_COUNT,DW4_DEVICE_RESELECT,DW4_DEVICE_PUBLISH,
    DW4_DEVICE_CLOSE_MODELS,DW4_DEVICE_CLEAR_TEXT,DW4_DEVICE_CLOSE_CHILDREN,
    DW4_DEVICE_COLORS,DW4_DEVICE_FINISHED};
/* INIT/RESELECT append real selectors. REFRESH's bits are rows=1, description=2.
 * PUBLISH writes an absolute inventory index or -1 to the caller's selection.
 * A non-auto-close owner holds at state 1/sub 2 until explicit restart/close. */
typedef int (*dw4_statusdevice_io)(void *,dw4_statusdevice *,int,int32_t);
int dw4_statusdevice_tick(dw4_statusdevice *,dw4_statusdevice_io,void *);
/* 412600 hover gate: 0 enabled new row, 2 disabled new row, 1 unchanged/not
 * selecting. Publishes the absolute index/latch only for a new valid hover. */
int dw4_statusdevice_hover(const dw4_statusdevice *,int32_t *latch,const uint8_t [12],int32_t *index);
typedef struct {
    dw4_statusview_context view;
    const dw4_databases *databases;
    dw4_statusdevice_filter filter;
    int bank,auto_close;
    int (*input)(void *,int32_t,dw4_statuspage_input *);
    void *user;
    int prompt; /* equipment caller's original txt_status event before call 70 */
} dw4_statusdevice_context;
/* Borrowed dependencies/parent outlive the tree. Bank mode requires actual
 * BANKDEVICE records within the 96-record bank bound (inventory 36). Save integration is separate; no empty-bank fallback or boot factory is installed.
 * No initialization at open, and no ticks in queries. Failures hold until reset. */
dw4_menu_window *dw4_statusdevice_window_open(const dw4_statusdevice_context *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusdevice dw4_statusdevice_window_state(const dw4_menu_window *);
int dw4_statusdevice_window_is(const dw4_menu_window *);
int dw4_statusdevice_window_ready(const dw4_menu_window *);
int dw4_statusdevice_window_restart(dw4_menu_window *);
/* Owner-driven refresh (418ac0; bits rows=1, description=2) and close (state 1 -> 2). */
int dw4_statusdevice_window_refresh(dw4_menu_window *,int bits);
int dw4_statusdevice_window_close(dw4_menu_window *);
/* 0 actual DEVICE/BANKDEVICE identity, 1 no hover/cancel/uninitialized,
 * negative invalid/stale record. Safe while accepted selection is held. */
int dw4_statusdevice_window_candidate(const dw4_menu_window *,int32_t *);
/* 412600's inventory-preview gate: a held result resolves every call; active
 * hover resolves only a new absolute index and updates equipment's latch.
 * Return 2 for a disabled new row so transaction IO restores baseline preview. */
int dw4_statusdevice_equipment_candidate(void *,dw4_statusequip *,int chip,int32_t *);
#endif
