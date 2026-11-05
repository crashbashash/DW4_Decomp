/* Native shop stock for SUBWND modes 6 WPU, 7 APU, 8 CHIP and 9 JUNK: the recovered stock selection
 * of 3d8740..3d9bd0 (docs/engine/subwindow-preparation.md) with the item initializers 4482e0 /
 * 448430 / 448580 / 448660. Evidence and open boundaries: port/docs/equipment-shops.md. */
#ifndef DW4_SHOPSTOCK_H
#define DW4_SHOPSTOCK_H
#include "dw4/database.h"
#include "dw4/playerrecords.h"
#include "dw4/random.h"
#define DW4_SHOPSTOCK_SLOTS 36
#define DW4_SHOPSTOCK_SOLD_OUT 0xB9 /* the chip record that replaces a purchased slot */
/* The SUBWND work's four lists (_weaponSalesList, _armorSalesList, _chipSalesList, _junkSalesList) and
 * _junkGift. A null slot has kind -1. WPU/APU/CHIP always hold 36 slots once built; JUNK holds only the
 * present entries. An empty list is rebuilt on the next prepare, a populated one persists. */
typedef struct {
    dw4_arena *arena;dw4_handle work; /* beNDMWStatusInfoWork */
} dw4_shopstock;
/* First initialization only; close an existing owner before reinitializing. */
void dw4_shopstock_init(dw4_shopstock *);
void dw4_shopstock_close(dw4_shopstock *);
size_t dw4_shopstock_count(const dw4_shopstock *,int32_t mode);
int32_t dw4_shopstock_gift(const dw4_shopstock *);
/* Retained actual beNDMWItemBaseList; release with property_list_release. */
dw4_handle dw4_shopstock_acquire(const dw4_shopstock *,int32_t mode);
/* Retail preparation for one mode: caps the joined players' BIT (9,999,999) and XDATA (9,999), then
 * builds the mode's list from player zero's LEVEL (and DIGIMONNO / the joined count for WPU, the common
 * COUNTER investment for JUNK). Items roll their grade and enhancement from the shared random stream.
 * Returns 0, or -1 with a message when a record or table the retail code reads is unavailable. */
int dw4_shopstock_prepare(dw4_shopstock *,int32_t mode,const dw4_databases *,dw4_playerrecords *,
    dw4_random *,char *error,size_t cap);
/* Borrowed projection until stock mutation/close; NULL for empty or invalid modes. */
const dw4_item_record *dw4_shopstock_list(const dw4_shopstock *,int32_t mode,size_t *count);
/* Replaces a purchased slot with the sold-out chip. 0 on success, -1 for an invalid mode or slot. */
int dw4_shopstock_sell_out(dw4_shopstock *,int32_t mode,size_t slot);
/* Pure helpers exposed for tests: stock rows and the item rolls. */
unsigned dw4_shopstock_level_row(int32_t level,unsigned maximum);
int dw4_shopstock_investment_row(int32_t investment);
int32_t dw4_shopstock_pocket_roll(uint32_t draw,uint32_t level);
int32_t dw4_shopstock_revision_roll(uint32_t first,uint32_t second,uint32_t level);
#endif
