/* Concrete authored STATUS title/selection setup and native resource lifetime. */
#ifndef DW4_STATUSVIEW_H
#define DW4_STATUSVIEW_H
#include "dw4/statusctrl.h"
#include "dw4/playerrecords.h"
#include "dw4/scriptengine.h"
enum dw4_statusview_kind { DW4_STATUS_SELECT01=9, DW4_STATUS_SELECTE0, DW4_STATUS_SELECTE1,
    DW4_STATUS_CONTENT, DW4_STATUS_SHOPSELECT00, DW4_STATUS_SHOPSELECT34, DW4_STATUS_SHOPSELECT52,
    /* XDATA ShopSelect01 (entry code in callno, start in selected) and ShopSelect11
     * (stat list; selected is the cached parameter). Player records and RECALCPLAYER
     * come from the context. */
    DW4_STATUS_XDATAMENU, DW4_STATUS_XDATASTAT,
    /* ShopSelectB0 (440a20): the two-row DISK sell menu. rows must be 2; enabled flags colour the rows
     * and become the selector's decide list. */
    DW4_STATUS_SHOPSELECTB0,
    /* Talk-window selectors of the Digilabo controller. ShopSelect03 (43eab0) is the one-choice TALKFONT01 font00 message
     * (cursor i_messky, callno is its txt_shop call); ShopSelect02 (43dc10) is the TALKFONT01 font01.. menu on i_messcr:
     * callno 1 has three rows (script 0x7F2), 2..4 four rows (0x7EE) and 1262/1268/2003/2005/2008 two rows (script =
     * callno). rows must match; the player-chooser form (callno -1, ShopSelect02's first case) lists one to four joined
     * players: TALKFONT01 font01..N and TALKFONT04 font01..N are tracked and the caller fills the names through its
     * selection_initialize. CARDPAGE is ShopSelectA0 (440670), the card album's nine-page selector over
     * j_shcardwin with the j_shcardcursor cursor; rows must be 9. */
    DW4_STATUS_TALKSELECT03, DW4_STATUS_TALKSELECT02, DW4_STATUS_CARDPAGE };
enum dw4_statusview_op {DW4_VIEW_MODEL,DW4_VIEW_TRACK_TEXT,DW4_VIEW_TEXT,
    DW4_VIEW_SCRIPT,DW4_VIEW_SWITCH,DW4_VIEW_REFRESH,DW4_VIEW_COLOR,DW4_VIEW_SET_TEXT,DW4_VIEW_ALIGN};
typedef struct {
    int op;const char *group,*name,*key,*value;int32_t slot;
} dw4_statusview_command;
/* Synchronous sink returns zero on success, nonzero on failure. Strings are borrowed only during the call. MODEL carries
 * open (including optional V<...>) and close sequences in key/value. TEXT
 * carries alignment/text. SCRIPT carries the original chunk and call number. */
typedef int (*dw4_statusview_io)(void *,const dw4_statusview_command *);
int dw4_statusview_setup(int kind,int variant,int32_t player,int32_t digimon,
    int32_t callno,dw4_statusview_io,void *);
/* Title01's refresh requires an actual stat/inventory owner, and is mandatory
 * for that kind. The other titles and Select00 need no stat projection.
 * Registry/engine/records and parent state outlive the returned window; cancel
 * the scope before destroying them. Opening/closing only advance during tick. */
typedef struct {
    dw4_scriptservices *sd;dw4_scriptengine *engine;dw4_playerrecords *players;
    uint64_t scope;int32_t player,callno;int variant;
    dw4_statusctrl *parent;
    /* Select01 caller supplies selected row; E0/E1 also need rows/position. Flags copy
     * into the view; NULL means every row enabled. */
    int32_t rows,selected;float position[3];const uint8_t *enabled;
    int (*refresh)(void *,int32_t,char *,size_t);void *user;
    /* CONTENT initializes an authored resource set through the same tracker.
     * The callback and user outlive the window. No initialization during open. */
    int (*initialize)(void *,dw4_statusview_io,void *);
    /* Optional caller-owned selector resources (e.g. skill menu's blank
     * description); tracked and closed with that selector. */
    int (*selection_initialize)(void *,dw4_statusview_io,void *);
    /* Production selection sink: the recovered parent's _retCode. The scalar
     * parent above remains available to isolated rule fixtures/adapters. */
    dw4_menu_window *parent_window;
} dw4_statusview_context;
dw4_menu_window *dw4_statusview_window_open(int kind,const dw4_statusview_context *);
/* Refresh a CONTENT resource without duplicating ownership. Failure retains
 * completion and blocks further updates until the containing scene is reset. */
int dw4_statusview_window_emit(void *,const dw4_statusview_command *);
/* Title01 only: refresh and present the full panel (variant 0, 425e60) or the compact shop base (variant 1, 425fb0) on
 * an open window (the Digi-Lab switches before and after its equipment check). Both bases stay tracked for the close. */
int dw4_statusview_window_title_variant(dw4_menu_window *,int variant);
/* Parent-issued 3f5f00/3f5410-style construction resources belong to the
 * selector before its first recursive update. This sends authored commands
 * and records ownership without advancing selector/model clocks. */
int dw4_statusview_window_prepare(dw4_menu_window *,
    int (*initialize)(void *,dw4_statusview_io,void *),void *);
/* 3f5a40 hides a CONTENT owner's tracked text without closing its models. */
int dw4_statusview_window_clear_text(dw4_menu_window *);
/* Selector-only queries/repage. Ready means SELECTCTRL is at its input top;
 * neither operation advances clocks. Repage uses the original state-four
 * FO2TOP route, updates the row count and resets selection to zero. */
int dw4_statusview_selector_ready(dw4_menu_window *);
int dw4_statusview_selector_repage(dw4_menu_window *,int rows);
/* DEVICE pages replace their copied decision flags through the same FO2TOP
 * route. NULL means all rows enabled (including the retail empty-list cursor). */
int dw4_statusview_selector_restart(dw4_menu_window *,int rows,const uint8_t *enabled);
#endif
