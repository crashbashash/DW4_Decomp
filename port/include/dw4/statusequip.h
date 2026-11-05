/* Shared equipment controller 40f720. Native references stay outside guest data. */
#ifndef DW4_STATUSEQUIP_H
#define DW4_STATUSEQUIP_H
#include "dw4/statusctrl.h"
#include "dw4/playerstats.h"
typedef struct {
    dw4_statusctrl window;
    int32_t slot,slots,pocket,mode;
} dw4_statusequip;
enum dw4_equip_op {
    DW4_EQUIP_COUNT,DW4_EQUIP_PREPARE,DW4_EQUIP_SELECTOR,
    DW4_EQUIP_CURSOR,DW4_EQUIP_BLANK,DW4_EQUIP_PREVIEW_OFF,
    DW4_EQUIP_REFRESH,DW4_EQUIP_COLORS,DW4_EQUIP_HIDE,
    DW4_EQUIP_FIND,DW4_EQUIP_READY,DW4_EQUIP_SELECTOR_CLOSE,
    DW4_EQUIP_SELECTOR_RESTART,DW4_EQUIP_SWAP,DW4_EQUIP_SWAP_PREVIEW,
    DW4_EQUIP_ERROR,DW4_EQUIP_SCRIPT,DW4_EQUIP_CLOSE_MODELS,
    DW4_EQUIP_CLEAR_TEXT,DW4_EQUIP_CLOSE_CHILDREN,DW4_EQUIP_FINISHED,
    DW4_EQUIP_CLEAR_POCKETS,DW4_EQUIP_PLAYER_MODEL,
    /* 100 + recovered virtual slot, 22..39. v32 receives -1 for the remove
     * action, zero for inventory hover; the distinction is part of its ABI. */
    DW4_EQUIP_VIRTUAL=100
};
/* All operations required. Queries are COUNT/FIND/READY/FINISHED and virtual 30
 * (eligibility). SELECTOR/ERROR and virtual 27/29/33/35/36 append owned children.
 * PREPARE resolves the six player equipment/inventory lists. SWAP is an atomic
 * accepted socket swap; SWAP_PREVIEW must not publish session records. */
typedef int (*dw4_equip_io)(void *,dw4_statusequip *,int,int32_t);
int dw4_statusequip_tick(dw4_statusequip *,dw4_equip_io,void *);
dw4_menu_window *dw4_statusequip_window_open(int mode,int slots,dw4_equip_io,void *);
/* Read-only snapshot by value; use window_is to validate the owner. */
dw4_statusequip dw4_statusequip_window_state(const dw4_menu_window *);
int dw4_statusequip_window_is(const dw4_menu_window *);
/* Filtered inventory rows retain DEVICEFOLDER identity, including duplicates.
 * kind 0=PowerSocket, 1=MainSlot, 2=SubSlot, 3=pocket chip. */
int dw4_statusequip_candidates(dw4_playerrecords *,int32_t,int kind,int32_t *,size_t,size_t *);
typedef struct {int32_t callno,rows;uint8_t enabled[3];} dw4_statusequip_actions;
int dw4_statusequip_action_rows(dw4_playerrecords *,int32_t,int kind,
    int mode,int32_t slot,int32_t latch,dw4_statusequip_actions *);
int dw4_statusequip_eligible(dw4_playerrecords *,int32_t,int32_t,const dw4_databases *,int *);
/* Candidate is an actual inventory index, -1 clears. Power/Main slot zero
 * clears corresponding pockets; other slots preserve them. Recalculation and
 * publication happen in one staged transaction. preview callback sees only the
 * private recalculated folder and must not retain it. */
int dw4_statusequip_accept(dw4_playerrecords *,int32_t,int kind,size_t,int32_t,const dw4_databases *);
int dw4_statusequip_preview(dw4_playerrecords *,int32_t,int kind,size_t,int32_t,
    const dw4_databases *,dw4_player_recalculate,void *);
int dw4_statusequip_swap(dw4_playerrecords *,int32_t,size_t,size_t,const dw4_databases *,
    int preview,dw4_player_recalculate,void *);
/* Transaction IO adapter for the owned base window. view is mandatory for
 * model/text/selector operations. candidate resolves the actual inventory row
 * (scrolling owner) to DEVICEFOLDER identity, returns 1 if no new hover,
 * 2 for a disabled new row (restore baseline preview), 0 when enabled/present,
 * negative on failure. Accepted results cannot be disabled. preview consumes a private stat folder.
 * Dependencies and context outlive the window. */
typedef struct {
    dw4_playerrecords *players;const dw4_databases *databases;
    int32_t player;int kind;
    dw4_equip_io view;void *user;
    int (*candidate)(void *,dw4_statusequip *,int chip,int32_t *);
    dw4_player_recalculate preview;void *preview_user;
} dw4_statusequip_context;
int dw4_statusequip_transaction_io(void *,dw4_statusequip *,int,int32_t);
#endif
