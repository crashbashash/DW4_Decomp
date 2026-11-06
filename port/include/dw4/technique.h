/* Player technique panel and cast (R1): the part of the retail beNDMWPanelWaza manager (group
 * NDMWPANEL, one state machine per player) and of the player's control hook
 * (beNDMWMdlPlayer::vfunc_38) that opens the list, moves its cursor, fires a technique, charges
 * its MP and starts SQ_WAZA with the pcTech LABEL, plus the port's stand-in for the cast's bullet
 * (a timed volume, see technique.c). Page 0 (techniques) only; the item and status pages (L1, R2)
 * are not ported. One panel per player slot (0..3), each with its own cursor, FIRE lock and MP. */
#ifndef DW4_TECHNIQUE_H
#define DW4_TECHNIQUE_H
#include "dw4/database.h"
#include "dw4/playerrecords.h"
#define DW4_TECHNIQUE_LIST 6   /* the WAZALIST holds at most six techniques (TECH1..6 of the shinka row) */
#define DW4_TECHNIQUE_ROWS 4   /* rows the panel shows at once */
typedef struct dw4_technique dw4_technique;
dw4_technique *dw4_technique_open(dw4_playerrecords *,const dw4_databases *);
void dw4_technique_close(dw4_technique *);
/* Read-only view of one slot's panel. `open` mirrors the player's InfoWork+0x124 byte. `color` per list row: 0 usable, 1 MP short
 * (2, disabled by a stage flag, is not ported). */
typedef struct {
    int open,cursor,offset,count;
    int32_t row[DW4_TECHNIQUE_LIST],base[DW4_TECHNIQUE_LIST];   /* pcTech row and family base (the WAZALIST record / revision) */
    int color[DW4_TECHNIQUE_LIST];
} dw4_technique_panel;
int dw4_technique_panel_get(const dw4_technique *,int slot,dw4_technique_panel *);
/* One frame of pad input for a slot, before the world tick. pressed: edge word (R1 0x800, Cross 0x4000); up/down: a cursor step this frame
 * (D-pad or stick, edge or repeat); can_open: the player has control and is not in SQ_JUMP/SQ_FALL. */
typedef struct {uint32_t pressed;int up,down,can_open;} dw4_technique_pad;
/* Returns 1 while the panel owns the frame (open at the start of it, or opened by it): the caller must not start a weapon swing or the talk
 * probe from Cross. `now_ns` is the world clock of the last tick (it times the FIRE lock). */
int dw4_technique_input(dw4_technique *,int slot,uint64_t now_ns,const dw4_technique_pad *);
/* Once per world tick: the 2-frame debounce counter, the list refresh, and the close when the player lost control (OFCTRL clears the byte). */
void dw4_technique_tick(dw4_technique *,int slot,int on_ctrl);
/* A fired technique, as the panel publishes it (_retIsFire / _retWazaLabel). */
typedef struct {int32_t row,base,mp,delay,attack;int support;char label[16];} dw4_technique_cast;
/* ISCHECK: while the panel is open and the player is not airborne (SQ_JUMP/SQ_FALL), consume a pending fire. Returns 1 and fills *out. The MP was
 * charged when Cross was accepted, so a cast fired in the air waits for the landing with its MP and FIRE lock already spent (retail order). */
int dw4_technique_poll(dw4_technique *,int slot,int airborne,dw4_technique_cast *out);
/* Start the cast's bullet from the caster's world matrix at this moment. */
void dw4_technique_launch(dw4_technique *,int slot,const dw4_technique_cast *,const float world[16]);
/* Deliver a flying volume (offset/size in the launch matrix's frame) to the combat path; returns the contact count, or -1 on error. */
typedef int (*dw4_technique_deliver)(void *user,int32_t slot,int32_t attack,const float world[16],const float offset[3],const float size[3]);
/* Once per world tick, after the combat tick: move every live bullet of the slot one frame and deliver it. A bullet ends on its first contact
 * or when its lifetime runs out. Returns the total contacts, or -1. */
int dw4_technique_step(dw4_technique *,int slot,dw4_technique_deliver,void *user);
/* Bullets alive for a slot (tests). */
int dw4_technique_flying(const dw4_technique *,int slot);
#endif
