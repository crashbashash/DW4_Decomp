/* Authored item and skill projection; no session mutation or query-time ticks. */
#ifndef DW4_STATUSCONTENT_H
#define DW4_STATUSCONTENT_H
#include "dw4/statusview.h"
#include "dw4/database.h"
const char *dw4_statuscontent_item_string(const dw4_databases *,const dw4_item_record *,const char *);
void dw4_statuscontent_item_color(const dw4_item_record *,float [3]);
/* Equipment virtual 24/26/22. Callers retain resource ownership through the
 * CONTENT tracker. Missing records/strings fail before publication. */
int dw4_statuscontent_equipment(dw4_playerrecords *,const dw4_databases *,int32_t player,
    int kind,int32_t selected,int description,dw4_statusview_io,void *);
int dw4_statuscontent_pockets(dw4_playerrecords *,const dw4_databases *,int32_t player,
    int kind,dw4_statusview_io,void *);
/* 418ac0: twelve inventory rows, actual DEVICEFOLDER identity, eligibility and
 * equipped markers. A NULL enabled list means every row enabled. */
int dw4_statuscontent_device(const dw4_databases *,const dw4_item_record *,size_t count,
    const uint8_t enabled[12],int page,int pages,int selected,int bank,
    int rows,int description,dw4_statusview_io,void *);
/* 43c7f0: XDATA chip rows (NAME in STWINFONT14, NEXTX in STWINFONT17, "----" below one),
 * page labels in STWINFONT30 and the selected row's TXT in STWINFONT29. items are the retained
 * chips in DEVICEFOLDER order; description uses page*12 + the selector result. */
int dw4_statuscontent_xdata_chip(const dw4_databases *,const dw4_item_record *items,size_t count,
    int page,int pages,int selected,int rows,int description,dw4_statusview_io,void *);
/* KAITORI buy-back price of a DEVICEFOLDER item or DISKFOLDER disk. */
int dw4_statuscontent_kaitori(const dw4_databases *,const dw4_item_record *,int32_t *out);
/* 436060 DeviceSell list (36 items, 12 per page) and 437ae0 DiskSell list (12 disks). enabled flags the
 * 12 rows of the page. */
int dw4_statuscontent_sell_device(const dw4_databases *,const dw4_item_record *,size_t count,
    const uint8_t enabled[12],int page,int pages,int selected,int rows,int description,dw4_statusview_io,void *);
int dw4_statuscontent_sell_disk(const dw4_databases *,const dw4_item_record *,size_t count,
    int selected,int rows,int description,int32_t *unit,dw4_statusview_io,void *);
/* 4393e0 ShopCtrlSales list: stock slots (36, kind -1 = null) with prices, page labels and the highlighted
 * slot's description. rows/description correspond to the retail helper's two flags. */
int dw4_statuscontent_sales(const dw4_databases *,const dw4_item_record *items,size_t count,int page,int pages,
    int selected,int rows,int description,dw4_statusview_io,void *);
typedef struct {int32_t species,level;const char *name;} dw4_status_skillrow;
/* 4432a0: species 3 is inserted first; others retain ascending species order. */
int dw4_statuscontent_skill_list(dw4_playerrecords *,const dw4_databases *,int32_t,
    dw4_status_skillrow [16],size_t *);
/* 420230: eight species rows/page or SKILL/WAZALIST selection descriptions.
 * rows/description correspond to the retail helper's two flags. */
int dw4_statuscontent_skill(dw4_playerrecords *,const dw4_databases *,int32_t player,
    int mode,int page,int pages,int selected,int rows,int description,
    dw4_statusview_io,void *);
/* Initialize a complete authored skill page resource owner (41f190 setup).
 * selector row count is returned; selector stays a separate owned child. */
int dw4_statuscontent_skill_setup(dw4_playerrecords *,const dw4_databases *,int32_t,
    int mode,int pages,int *selector_rows,dw4_statusview_io,void *);
int dw4_statuscontent_skill_clear_colors(dw4_statusview_io,void *);
/* 41aaa0: collected nonzero FLAGFOLDER indices retain ascending order. */
int dw4_statuscontent_flag(const dw4_databases *,const int32_t *,size_t,int selected,
    int rows,int description,dw4_statusview_io,void *);
/* 4402e0: seven right-to-left digits, minimum display width (zero hides all).
 * Borrowed font prefix is fixed to font%03d in STATUS currency callers. */
int dw4_statuscontent_digits(int family,int32_t value,int width,dw4_statusview_io,void *);
int dw4_statuscontent_number(int variant,int32_t value,int width,dw4_statusview_io,void *);
/* DIGILAB evolve window texts (beNDMWShopCtrlEvolve 430d20): up to eight forms per page (the species list of
 * dw4_statuscontent_skill_list) in STWINFONT20/43/21 with page labels in STWINFONT31; with detail, the selected
 * row's sixteen values (dw4_playerstats_form) in STWINFONT22 and its shinka EXPLANATION in STWINFONT29 font000.
 * rows/detail are independent refresh flags; selected is the row on the page. */
int dw4_statuscontent_labo(dw4_playerrecords *,const dw4_databases *,int32_t player,int page,int pages,int selected,
    int rows,int detail,dw4_statusview_io,void *);
#endif
