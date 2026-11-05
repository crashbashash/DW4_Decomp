/* Native inventory identity is a DEVICEFOLDER index, never a guest pointer. */
#ifndef DW4_PLAYERTRANSACTIONS_H
#define DW4_PLAYERTRANSACTIONS_H
#include "dw4/playerrecords.h"
typedef int (*dw4_item_attribute)(void *,const dw4_item_record *,const char *,int32_t *);
/* Retail 411950: -1 is an empty candidate; repeated identity toggles off.
 * All lookups complete before mutation. References are indices, -1 for NULL.
 * Chip exclusion uses the first positive family in retail table order. */
int dw4_equipment_assign(dw4_item_record *,size_t,int32_t *,size_t,size_t,int32_t,
    dw4_item_attribute,void *);
/* Retail 4144a0/3f93c0: EE masked species shift and signed skill threshold. */
int dw4_weapon_eligible(int32_t species,const int32_t skills[9],uint32_t mask,
    int32_t skill,int32_t threshold);
/* CTRLITEM DEVICE: native safe bounds; query results do not advance state. */
typedef enum {DW4_DEVICE_SET,DW4_DEVICE_CLR,DW4_DEVICE_IS,DW4_DEVICE_ISMAX,
    DW4_DEVICE_ISEQUIP} dw4_device_operation;
int dw4_playertransactions_device(dw4_playerrecords *,int32_t,dw4_device_operation,
    int32_t kind,int32_t record,int32_t revision,int32_t pocket,int *result);
/* Detail actions consume the selected identity, not the first equal value.
 * Policy (ISHAKAI/ISJYOUDO, confirmation and joined-recipient selection) stays
 * in its controller; equipped or referenced identities cannot be removed. */
int dw4_playertransactions_remove_item(dw4_playerrecords *,int32_t,size_t index,int *result);
int dw4_playertransactions_give_item(dw4_playerrecords *,int32_t from,int32_t to,size_t index,int *result);
int dw4_playertransactions_give_bit(dw4_playerrecords *,int32_t from,int32_t to,int32_t amount,int *result);
/* NPC bank (beNDMWShopCtrl30 428790). Deposit moves DEVICEFOLDER[index] to the end of BANKDEVICE
 * (capacity 96); withdraw moves BANKDEVICE[index] to the end of DEVICEFOLDER (capacity 36).
 * A full destination, or an equipped/referenced deposit, leaves everything unchanged and sets
 * *result to 0; an invalid index or record is -1. Atomic, including the equipment references.
 * The bit variant moves amount between BIT and BANKBIT (each 0..9,999,999). */
int dw4_playertransactions_bank_item(dw4_playerrecords *,int32_t player,int withdraw,size_t index,int *result);
int dw4_playertransactions_bank_bit(dw4_playerrecords *,int32_t player,int withdraw,int32_t amount,int *result);
/* DISK shop (beNDMWShopCtrl50 42a2e0) and its sell branch (434790/4353e0/436ac0). disk_buy debits
 * quantity*price from BIT and raises the DISKFOLDER entry whose record is `record` (quantity 1..9, at most
 * nine held in total, enough BIT; otherwise *result is 0 and nothing changes). disk_sell lowers
 * DISKFOLDER[index] and credits quantity*price. sell_item removes an unequipped, unreferenced
 * DEVICEFOLDER[index] (references re-projected) and credits price. BIT is capped at 9,999,999 when
 * credited. All are atomic; an invalid index or record is -1. */
int dw4_playertransactions_disk_buy(dw4_playerrecords *,int32_t player,int32_t record,int32_t quantity,int32_t price,int *result);
int dw4_playertransactions_disk_sell(dw4_playerrecords *,int32_t player,size_t index,int32_t quantity,int32_t price,int *result);
/* ShopCtrlA2 Booster Pack opening: consumes one pack (disk record 10), draws three cards from per-mille KAKURITSU odds with
 * the given engine rolls, marks them owned in CARDLIST and reports the picks and the highest RARE. Atomic; -1 on bad input. */
int dw4_playertransactions_booster_open(dw4_playerrecords *,int32_t player,const int32_t *kakuritsu,const int32_t *rare,
    size_t count,const uint32_t rolls[3],int32_t picks[3],int32_t *max_rare);
/* CTRLITEM DISK as sent by SYSctlDiskFolder(op, player, record, amount). A missing record is -1
 * (retail indexes the list with -1); a negative amount is refused. Atomic. */
typedef enum {DW4_DISK_SET,DW4_DISK_CLR,DW4_DISK_IS,DW4_DISK_ISMAX} dw4_disk_operation;
int dw4_playertransactions_disk_folder(dw4_playerrecords *,int32_t player,dw4_disk_operation op,int32_t record,int32_t amount,int *result);
/* Engine calls SYSctlDiskFolder / SYSctlDeviceFolder over those transactions; returns 1 for other methods
 * (chain after dw4_playerrecords_call), 0 on success, -1 with a message otherwise. */
int dw4_playertransactions_folder_call(void *players,const char *method,const dw4_script_value *,size_t,dw4_script_value *,char *error,size_t cap);
int dw4_playertransactions_sell_item(dw4_playerrecords *,int32_t player,size_t index,int32_t price,int *result);
/* CNOS item converter (beNDMWShopCtrl40 429630). LEVEL selects a tier 1..6 (signed compares at
 * 41/101/201/301/401); a table row tier*100 holds the entry count in its ID column and rows
 * tier*100+1.. hold a result record ID and a RATE weight. The draw is the shared MT stream
 * modulo 10000; the first entry whose running RATE sum reaches it wins and a miss leaves the
 * record alone. The 300 BIT charge applies either way. table(user,row,&id,&rate) returns 0 when
 * the row exists. */
#define DW4_CNOS_PRICE 300
typedef int (*dw4_cnos_table)(void *,int32_t row,int32_t *id,int32_t *rate);
int32_t dw4_cnos_tier(int32_t level);
/* 1 chosen (*record set), 0 no entry reached the draw, -1 invalid table or tier. */
int dw4_cnos_roll(dw4_cnos_table,void *,int32_t tier,uint32_t draw,int32_t *record);
/* Converts DEVICEFOLDER[index] (kind 0 weapon, 1 armor1, 2 armor2: tables[kind]/users[kind]).
 * *result: 0 refused (BIT below the price, nothing changed), 1 charged and unchanged, 2 charged and
 * re-rolled. Debit, record and equipment projections publish atomically; stats are not recalculated
 * (retail only sends SUBWND UPDATE). An invalid index/kind or table is -1. */
int dw4_playertransactions_cnos_convert(dw4_playerrecords *,int32_t player,size_t index,
    dw4_cnos_table tables[3],void *users[3],uint32_t draw,int *result);
int dw4_playertransactions_swap_disk(dw4_playerrecords *,int32_t,size_t,size_t);
int dw4_playertransactions_give_disk(dw4_playerrecords *,int32_t from,int32_t to,size_t index,int32_t amount,int *result);
/* Source sort helpers: normal equipment is stable descending revision, special
 * records 276/31/44 move to the tail in reverse traversal order, chips stable
 * ascending recNo. Inventory sort prepends actual equipped identities. */
int dw4_inventory_sort_part(const dw4_item_record *,size_t,int chips,int32_t *order);
int dw4_playertransactions_sort_device(dw4_playerrecords *,int32_t);
/* Staged callback supplies general stat/technique/name projection. Required:
 * failure publishes nothing. It must not mutate the session or retain staging.
 * Equipment commit is for accepted controller selections, after eligibility.
 * keys: POWERSOCKET, POWERPOCKET, MAINSLOT, MAINPOCKET, SUBSLOT.
 * <key>REF holds host-only identity metadata. */
typedef int (*dw4_player_recalculate)(void *,dw4_property_folder *);
int dw4_playertransactions_equip(dw4_playerrecords *,int32_t,const char *,size_t,int32_t,
    dw4_item_attribute,void *,dw4_player_recalculate,void *);
/* Same private candidate state, released after callback; session stays intact.
 * Callback can copy comparison values, but must not retain staged buffers. */
int dw4_playertransactions_preview(dw4_playerrecords *,int32_t,const char *,size_t,int32_t,
    dw4_item_attribute,void *,dw4_player_recalculate,void *);
/* GAMERAM RECALCPLAYER: recalculate on a private copy and publish together.
 * Failure leaves the live record untouched. */
int dw4_playertransactions_recalculate(dw4_playerrecords *,int32_t,dw4_player_recalculate,void *);
/* Retail XDATA stat price (4270a0 / 43fb70): signed wrap of stat-45, divide by five
 * rounding away from zero for non-multiples, negative replaced by 1, capped at 400.
 * Zero remains zero. */
int32_t dw4_xdata_price(int32_t stat);
/* XDATA stat selections 0..6 are TSUYOSA, MAMORI, KASHIKOSA, SEISHIN, SUBAYASA, MHP, MMP. */
int dw4_xdata_stat(int32_t parameter,const char **key,int32_t *limit,int *upcnt_index);
/* ShopCtrl10 confirmation (substate 3): re-read the CURRENT stat, charge its price with
 * 32-bit wrap, add one to the stat's UPCNT slot when present, recalculate with equipment,
 * then copy MHP/MMP into HP/MP. Atomic; quoting and balance checks belong to the
 * controller, as in retail. */
int dw4_playertransactions_xdata_upgrade(dw4_playerrecords *,int32_t,int32_t parameter,
    dw4_player_recalculate,void *);
/* XDATA chip upgrade (beNDMWShopCtrlXdataChip 43aae0). Identity is the DEVICEFOLDER index of a
 * chip (kind 3). Preview raises that chip's catalogue record by one on a private copy,
 * re-projects every equipment list from its references, recalculates and hands the staged
 * folder to the visitor; nothing is published. Upgrade debits the chip's NEXTX (32-bit wrap),
 * raises the record, re-projects, recalculates and publishes all together. Eligibility
 * (NEXTX -1, balance) is the controller's quote step and is not repeated here, as in retail. */
typedef int (*dw4_player_preview_visit)(void *,dw4_property_folder *);
int dw4_playertransactions_chip_preview(dw4_playerrecords *,int32_t,size_t index,
    dw4_player_recalculate,void *,dw4_player_preview_visit,void *);
/* ShopCtrlSales purchase: debit BIT and append the item to DEVICEFOLDER atomically. *result 0 when the
 * balance is short or DEVICEFOLDER already holds 36 items; -1 for invalid input. */
int dw4_playertransactions_shop_buy(dw4_playerrecords *,int32_t player,const dw4_item_record *item,int32_t price,int *result);
/* Junk-shop donation: debit BIT by amount and raise the common COUNTER[1] investment together. *result 0
 * for a non-positive amount or one above BIT; -1 for invalid records. */
int dw4_playertransactions_junk_donate(dw4_playerrecords *,int32_t player,int32_t amount,int *result);
/* Equip-candidate stat preview (439f30): see port/docs/equipment-shops.md. */
int dw4_playertransactions_equip_preview(dw4_playerrecords *,int32_t player,const dw4_item_record *candidate,
    dw4_player_recalculate recalc,void *recalcuser,dw4_player_preview_visit visit,void *visituser);
int dw4_playertransactions_chip_upgrade(dw4_playerrecords *,int32_t,size_t index,
    dw4_item_attribute,void *,dw4_player_recalculate,void *);
/* CURRENT2BASE 3f8760: all species arrays committed together. No save I/O. */
int dw4_playertransactions_current_to_base(dw4_playerrecords *,int32_t);
/* DIGILAB evolution (beNDMWShopCtrlEvolve 42f710; commit sequence 4313b0 over GAMERAM 3f93c0, 3f8760, 3f82a0,
 * 3f8c90 and 431670). Species are shinka rows 0..15. weapon_check is WEAPONEQUIPCHECK: whether any owned weapon
 * (DEVICEFOLDER kind 0) allows the species (SOUBI mask) with enough of the matching skill, read from SKILL for
 * the current species and from BASE_SKILL otherwise. evolve runs, on one private copy and published together:
 * CURRENT2BASE, BASE2CURRENT (the species is resolved from its MODEL_NAME exactly as 3f80e0 does: the first
 * of rows 0..15 with that model, else row 0), RECALCPLAYER, WEAPONEQUIPSTRONG (the highest-TSUYOSA eligible
 * weapon becomes the only equipped one and POWERSOCKETNAME holds its MODEL; none leaves no weapon), the
 * MAINSLOT/SUBSLOT/POWERPOCKET/MAINPOCKET lists emptied and un-equipped, then RECALCPLAYER again.
 * Eligibility checks (same form, no usable weapon) belong to the controller. */
typedef const char *(*dw4_species_model)(void *,int32_t species);
typedef const char *(*dw4_item_string)(void *,const dw4_item_record *,const char *);
int dw4_playertransactions_weapon_check(dw4_playerrecords *,int32_t player,int32_t species,
    dw4_item_attribute,void *,int *eligible);
int dw4_playertransactions_base_to_current(dw4_playerrecords *,int32_t player,dw4_species_model,void *,
    dw4_player_recalculate,void *);
int dw4_playertransactions_evolve(dw4_playerrecords *,int32_t player,int32_t species,dw4_species_model,void *,
    dw4_item_attribute,dw4_item_string,void *,dw4_player_recalculate,void *);
#endif
