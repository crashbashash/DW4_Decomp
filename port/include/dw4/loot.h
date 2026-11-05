/* Loot delivery: what a field drop is, how its item is rolled and what picking it up does to the player records.
 * Recovered from beNDMWMdlItem (vfunc_36 builds the item, vfunc_38 the walk-over delivery of unnamed models and the
 * label lock of named ones, vfunc_45 the button pickup of named ones), FUN_00384800 (the model a drop spawns),
 * beNDMWItemInstant::vfunc_22 (BIT / x-data / UPCNT) and FUN_004480a0 / FUN_00448190 (revision and pocket rolls).
 * See docs/dungeon-floors.md "Loot delivery". Item identity is the native dw4_item_record, not the packed id word
 * (recNo | equipped << 10 | kind << 12 | pocket << 16 | revision << 20, which only the save image needs). */
#ifndef DW4_LOOT_H
#define DW4_LOOT_H
#include "dw4/playerrecords.h"
#include "dw4/playertransactions.h"
#include "dw4/random.h"
#include <stddef.h>
#include <stdint.h>
/* Drop categories in the order of the generator drop lists' category strings (the dbId handed to GENERATE). */
enum {DW4_LOOT_CON,DW4_LOOT_INS,DW4_LOOT_IMP,DW4_LOOT_WEAPON,DW4_LOOT_ARMOR1,DW4_LOOT_ARMOR2,DW4_LOOT_CHIP,DW4_LOOT_CATEGORIES};
/* The ten item-model names beNDMWMdlItem knows (table 0x4cfc10): the position is the model "kind". Kinds 0-2 are unnamed
 * (walk-over delivery, no label); kinds 3-9 are named (a label, then Cross picks them up). */
enum {DW4_LOOT_BIT,DW4_LOOT_XDATA1,DW4_LOOT_XDATA2,DW4_LOOT_ACCESS,DW4_LOOT_ARMOR,DW4_LOOT_BOOST1,DW4_LOOT_ITEM,DW4_LOOT_KEY,
      DW4_LOOT_PENX,DW4_LOOT_WEAPONMODEL,DW4_LOOT_MODELS};
/* Squared distance to the nearest player below which an item reacts (vfunc_38 compares FUN_003a68d0, the squared
 * 3-D distance FUN_003a5cc0 stores, with 64.0). */
#define DW4_LOOT_RADIUS_SQ 64.0f
#define DW4_LOOT_DEVICE_CAPACITY 36
int dw4_loot_category(const char *name);              /* conItem insItem impItem weapon armor1 armor2 abChip -> 0..6, else -1 */
const char *dw4_loot_category_name(int category);
int dw4_loot_model_kind(const char *model);           /* g_000bit g_000xdata1 g_000xdata2 g_000access g_000armor g_000boost1 g_000item g_000key g_000penx g_000weapon -> 0..9, else -1 */
const char *dw4_loot_model_name(int kind);
int dw4_loot_named(int kind);                         /* 1 for kinds 3..9 */
/* Item database access, supplied by the caller (the hub reads the prepared databases; tests supply a table). `number`
 * and `string` answer 0 / non-NULL when the column exists for that record. */
typedef struct {
    void *user;
    int (*number)(void *,int category,int32_t record,const char *column,int32_t *out);
    const char *(*string)(void *,int category,int32_t record,const char *column);
} dw4_loot_db;
/* FUN_00384800: the model the drop spawns. impItem, weapon, armor1, armor2 and abChip have a fixed model; conItem and
 * insItem take the MODEL column of their record. NULL when unknown. */
const char *dw4_loot_model(const dw4_loot_db *,int category,int32_t record);
/* beNDMWMdlItem::vfunc_36: the item object built when the model is generated. `level` is the LEVEL record of player 1.
 * Weapon and BlueArmor draw the pocket (one draw) then the revision (two draws); YellowArmor draws the revision only;
 * the other categories draw nothing. Returns 0, or -1 for an unknown category or a level below one. */
int dw4_loot_roll(int category,int32_t record,int32_t level,dw4_random *,dw4_item_record *out);
/* beNDMWItemInstant::vfunc_22, BIT: the amount for one draw (the level band table, then the player's BITRITSU percent). */
int32_t dw4_loot_bit_amount(int32_t level,uint32_t draw,int32_t bitritsu);
void dw4_loot_bit_band(int32_t level,int32_t *low,int32_t *high);
/* beNDMWItemInstant::vfunc_22, records 4..25: the UPCNT slot the record raises, or -1. */
int dw4_loot_upcnt_index(int32_t record);
typedef struct {
    dw4_playerrecords *players;
    dw4_loot_db db;
    dw4_random *random;
    dw4_player_recalculate recalculate;void *recalculate_user;   /* GAMERAM RECALCPLAYER for the receiving player */
} dw4_loot_ctx;
/* Unnamed-model delivery (vfunc_38 calling the Instant item's virtual 24 = beNDMWItemInstant::vfunc_22) to the player
 * `slot`: record 0 adds a BIT amount to the player's BIT (one draw; the amount is stored in *amount), records 1..3 add
 * the record's UP to the player's XDATA, records 4..25 add UP to a UPCNT slot and recalculate the player. Returns 1
 * delivered, -1 on a missing record or database column. Nothing is refused: there is no cap. */
int dw4_loot_instant(const dw4_loot_ctx *,int32_t record,int slot,int32_t *amount);
/* A drop as the pickup rules see it: the generated model's kind, the item rolled when it was generated and where it lies. */
typedef struct {int category,model_kind;int32_t record;dw4_item_record item;float position[3];int collected;} dw4_loot_drop;
/* Fills category, model kind and record from a drop-list row and rolls the item (vfunc_36 runs when GENERATE creates the model).
 * Returns 0, or -1 for an unknown category / model / level. */
int dw4_loot_make(const dw4_loot_db *,const char *category,int32_t record,int32_t level,dw4_random *,dw4_loot_drop *out);
/* Named-model pickup (beNDMWMdlItem::vfunc_45, sent on Cross by a player whose label is displayed): access, armor and
 * weapon models append the rolled item to the player's DEVICEFOLDER (refused at 36); boost1, item and penx models raise
 * the Disk of that record in DISKFOLDER by one (refused at nine, or when the folder has no such record); the key model
 * sets FLAGFOLDER[record] (a record outside the folder still counts as picked up, as retail). Returns 1 picked up,
 * 0 refused (the swing goes ahead), -1 on a record error. */
int dw4_loot_press(const dw4_loot_ctx *,const dw4_loot_drop *,int slot);
/* The nearest of the joined players to `p` by squared 3-D distance (the first one on a tie, as FUN_003a5cc0); -1 when none
 * is joined. *distance_sq receives the squared distance. */
int dw4_loot_nearest(const float (*players)[3],const int joined[4],const float p[3],float *distance_sq);
/* One tick of the field pickup rules. Per uncollected drop: the nearest joined player within DW4_LOOT_RADIUS_SQ receives an
 * unnamed model's item at once (dw4_loot_instant); a named model takes the label of that player when the player has none
 * (`lock`, one drop index per player, kept by the caller between ticks and reset when the drop list is cleared), keeps it
 * while the player stays within the radius and delivers on that player's Cross press (`pressed[slot]`, the press edge) with
 * dw4_loot_press. `picked` (optional) is told about each delivery; bit is the BIT amount of a BIT drop, else 0.
 * Returns the number of drops collected, or -1 on a record error. */
typedef void (*dw4_loot_label)(void *,size_t index,int slot,int on);   /* a player's name label of drop `index` is shown (on) or dropped (vfunc_38 state 0 -> 1, vfunc_43) */
typedef struct {int lock[4];unsigned unnamed,named,refused;dw4_loot_label label;void *label_user;} dw4_loot_state;
typedef void (*dw4_loot_picked)(void *,size_t index,int slot,int32_t bit);
void dw4_loot_state_reset(dw4_loot_state *);                             /* clears the labels, the counters and the label hook */
void dw4_loot_state_label(dw4_loot_state *,dw4_loot_label,void *user);   /* installs the label hook (after a reset) */
/* FUN_004412c0's table (0x4cfb40, stride 8): the 'got item' effect of the unnamed insItem record 1..25 - the panel model and its
 * sequence sent as PLAYER SETEFFECT to the receiving player. 0 and fills the names, or -1 for a record outside 1..25 (record 0, BIT,
 * shows the amount through the floating number instead). */
int dw4_loot_effect(int32_t record,const char **panel,const char **sequence);
/* beNDMWMdlItem::vfunc_38: the player's label text font is the entry `slot` of the table at 0x4cfc40 ("font00".."font03" of the
 * ITNAMEFONT group); NULL for a slot outside 0..3. */
const char *dw4_loot_label_font(int slot);
/* FUN_00447d00: the label colour. White for chips, disks and the other non-revision items and for the three exceptions (weapon 276,
 * blue armour 31, yellow armour 44); else by revision (>=1000 magenta, >=501 orange, >=101 gold, >=31 green, >0 cyan, 0 white). */
void dw4_loot_label_color(const dw4_loot_drop *,float rgb[3]);
int dw4_loot_step(dw4_loot_state *,const dw4_loot_ctx *,size_t count,dw4_loot_drop *(*at)(void *,size_t),void *at_user,
    const float (*players)[3],const int joined[4],const int pressed[4],dw4_loot_picked picked,void *picked_user);
/* The Cross press of beNDMWMdlPlayer::vfunc_38 (its `ACTION1` message to the DROPITEM group), answered at once for player `slot`: the drop that player's label
 * names takes the press (beNDMWMdlItem::vfunc_45) and is delivered or refused as dw4_loot_press does. Returns 1 when a pickup was delivered (the player
 * then skips its swing: the branch swings only when no bool came back), 0 when no label or a refusal (the swing goes ahead), -1 on a record error. */
int dw4_loot_cross(dw4_loot_state *,const dw4_loot_ctx *,size_t count,dw4_loot_drop *(*at)(void *,size_t),void *at_user,int slot,dw4_loot_picked,void *picked_user);
#endif
