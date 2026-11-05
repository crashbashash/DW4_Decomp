/* dw4/fieldhud.h — the HP/MP meters of a field world's HUD panels.
 *
 * A field stage's i_stpnl panels carry one beMeterCtrlOneData per player and gauge (hpmt1..4, mpmt1..4). The meter-mode state is the recovered
 * dw4_hudmeter (display value stepping toward the SETPERCENT target); the panel's gauge nodes are posed at the meter's time, as the hub HUD does
 * (lobbyui.c). The stage's scripts set the percentages through METERCTRL <hpmt|mpmt> <player slot> SETPERCENT.
 */
#ifndef DW4_FIELDHUD_H
#define DW4_FIELDHUD_H
#include <stdint.h>
#include "dw4/mount.h"
typedef struct dw4_fieldhud dw4_fieldhud;
/* NULL when the stage pack has no complete meter set. */
dw4_fieldhud *dw4_fieldhud_open(dw4_mount *,const char *stage);
void dw4_fieldhud_close(dw4_fieldhud *);
/* gauge 0 = HP, 1 = MP; slot 0..3. */
void dw4_fieldhud_percent(dw4_fieldhud *,unsigned gauge,unsigned slot,float percent);
void dw4_fieldhud_tick(dw4_fieldhud *);
/* The boss gauge (bshp10) of a stage that has one; the hub runtime feeds it the boss model's HP percent. */
void dw4_fieldhud_boss_percent(dw4_fieldhud *,float percent);
/* The pose time of a gauge's node (a scene node id of the panel graph of the instance in RAM slot `slot`): 1 and *time set when `node_id` is a meter node of that slot. */
int dw4_fieldhud_time(const dw4_fieldhud *,uint32_t node_id,int32_t slot,int64_t *time);
/* The number plates (lvnm1..4, hpnm1..4, mpnm1..4): kind 0 level, 1 HP, 2 MP. */
void dw4_fieldhud_number(dw4_fieldhud *,unsigned kind,unsigned slot,int32_t value);
/* A vertex of a number geometry takes the digit's UV; 1 when it did. */
int dw4_fieldhud_uv(const dw4_fieldhud *,uint32_t node_id,uint32_t geometry_id,uint32_t vertex,float uv[2]);
/* The floating numbers (damage 0, exp 1, player damage 2, bit 3): the value of RAM slot `slot`'s digit plate (NUMBERCTRL dmgnm0 ... SETVALUE), and the UV a vertex
 * of a plate's geometry takes (1 when it did). The plates are keyed by their geometry (the mesh node's id, like the HUD plates), one per RAM slot. */
void dw4_fieldhud_popup_value(dw4_fieldhud *,unsigned kind,unsigned slot,int32_t value);
unsigned dw4_fieldhud_popup_hits(const dw4_fieldhud *);   /* vertices rewritten so far (tests) */
int dw4_fieldhud_popup_uv(dw4_fieldhud *,uint32_t node_id,uint32_t geometry_id,uint32_t vertex,float uv[2]);
#endif
