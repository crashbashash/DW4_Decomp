/* Enemy generator registry and spawner of a field stage (GENERATER START/STOP/...). Authored
 * beGeneraterData records come from the stage's difficulty pack; the service tracks which
 * generators the stage scripts started and, each world tick, runs the recovered spawn rules: start
 * mode direct/radar/timer, first wave (one tick, up to the concurrent count) then fill mode
 * add/wipeout/timer, per-player-count wave sizes, position/facing cursor. A spawn is a MODELCTRL
 * GENERATE of the row's model (enemy database column MODEL). Retail timing is not measured. */
#ifndef DW4_FIELDGEN_H
#define DW4_FIELDGEN_H
#include <stdio.h>
#include "dw4/mount.h"
#include "dw4/igfile.h"
#include "dw4/igb.h"
#include "dw4/object.h"
#include "dw4/scriptservices.h"
#include "dw4/database.h"
#include "dw4/controllers.h"
#include "dw4/scriptengine.h"
#include "dw4/random.h"
#include "dw4/loot.h"
/* One row of a generator's drop list (beGeneraterItemDataOne): category string (conItem/insItem/impItem/weapon/armor1/armor2/abChip), item id, rank and the
 * chance in 1/10000 (FUN_00384800 draws RNG % 10000 and walks the rates; the sum is the chance that anything drops). */
typedef struct {char category[12];int32_t id,rank,rate;} dw4_drop_entry;
/* A drop that was rolled when a generated enemy was removed (position is the enemy's last known world position). */
typedef struct {char generator[16];dw4_drop_entry entry;float position[3];int collected;
    dw4_loot_drop loot;int loot_ready;   /* the item model's identity and rolled item (dw4_loot_make), set by the drop hook when one is installed */
    char model[16];int32_t model_slot;int model_live;   /* the MODELCTRL item model the hook generated (FUN_00384800): its name, pool slot, and 1 while it is still running; model_slot is -1 for a record-only drop */
} dw4_drop;
typedef enum {DW4_GENE_IDLE,DW4_GENE_STARTED,DW4_GENE_STOPPED} dw4_gene_state;
typedef struct {
    char name[16];
    int32_t enemy_row;      /* _geneEnemyId: row of the 649-row enemy table */
    char start_mode[12],fill_mode[12];
    float start_data,fill_data;
    float pos[3];int global;
    uint32_t npoints;float *points;float *rotations;   /* world xyz triples / facing in radians */
    int32_t count[4],max_count[4];                      /* _geneCount/_geneMaxCount by player count 1..4 */
    char sequence[24],call_lua[24];int finished;   /* _callLua: script run when the generator's last enemy is gone */
    dw4_drop_entry *drops[2];unsigned ndrops[2];       /* [0] _itemDataList, [1] _itemLastDataList of the first player-count row, for this difficulty */
    dw4_gene_state state;
    unsigned starts;
    /* runtime */
    int64_t boot_due_ns,refill_due_ns;int armed,wave1;   /* wave1: the first wave (state 1) has run */
    uint32_t cursor;unsigned remaining,spawned_total;
    int32_t live_id[16];float live_pos[16][3];unsigned nlive;   /* MODELCTRL slots this generator filled that were running at the last tick */
} dw4_gene;
typedef struct dw4_fieldgen dw4_fieldgen;
/* difficulty 0/1/2 selects generatorn/h/v.igb of the stage (Normal/Hard/Very Hard). */
dw4_fieldgen *dw4_fieldgen_open(dw4_mount *,const char *stage,int difficulty);
void dw4_fieldgen_close(dw4_fieldgen *);
size_t dw4_fieldgen_count(const dw4_fieldgen *);
const dw4_gene *dw4_fieldgen_at(const dw4_fieldgen *,size_t);
const dw4_gene *dw4_fieldgen_find(const dw4_fieldgen *,const char *);
/* GENERATER sd service; register under category GENERATER with the owner as user. */
int dw4_fieldgen_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
/* Attach the spawn target: the SD registry that receives MODELCTRL GENERATE and the enemy database. */
void dw4_fieldgen_attach(dw4_fieldgen *,dw4_scriptservices *,const dw4_databases *,dw4_controllers *models);
/* One world tick: player positions (n 1..4, joined players) for the radar test. Returns -1 and fills error on a failed spawn. */
int dw4_fieldgen_tick(dw4_fieldgen *,int64_t now_ns,const float (*players)[3],unsigned nplayers,char *error,size_t cap);
unsigned dw4_fieldgen_spawned(const dw4_fieldgen *);
/* The drop roll of FUN_00384800: one draw, first entry that brings it below zero. Returns 1 and fills *out on a drop, 0 for none. last!=0 selects the
 * _itemLastDataList (the generator's final enemy). */
int dw4_fieldgen_roll_drop(const dw4_gene *,int last,uint32_t draw,dw4_drop_entry *out);
/* Drops rolled since the last call (oldest first); the caller owns nothing, the array is valid until the next tick. */
const dw4_drop *dw4_fieldgen_drops(const dw4_fieldgen *,size_t *count);
void dw4_fieldgen_clear_drops(dw4_fieldgen *);
/* Called for each drop right after it is rolled (and for injected ones), with the world random stream: retail's GENERATE builds the item
 * object (its pocket and revision draws) in the same step as the drop roll, so the hook draws in that order. */
typedef void (*dw4_fieldgen_drop_hook)(void *user,dw4_drop *,dw4_random *);
void dw4_fieldgen_on_drop(dw4_fieldgen *,dw4_fieldgen_drop_hook,void *user);
/* Test/bring-up seam: add a drop at `position` as if `generator` had rolled `entry` (the hook runs). Returns the drop or NULL. */
dw4_drop *dw4_fieldgen_inject_drop(dw4_fieldgen *,const char *generator,const dw4_drop_entry *entry,const float position[3]);
/* Mutable view for the pickup step (marks drops collected). */
dw4_drop *dw4_fieldgen_drops_mut(dw4_fieldgen *,size_t *count);
/* The random stream the drop rolls draw from (the world's). */
void dw4_fieldgen_random(dw4_fieldgen *,dw4_random *);
/* The scene script engine that runs a generator's _callLua chunk. */
void dw4_fieldgen_scripts(dw4_fieldgen *,dw4_scriptengine *);
#endif
