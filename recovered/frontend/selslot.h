/* recovered/frontend/selslot.h — behavioral interface for the slot-selection
 * screen helpers of Gap::Bec::beNDMWLoadIntf2SelSlot.
 *
 * These are the per-screen helper functions the master update
 * (0x003e4750, vfunc_31) calls with the SELSLOT record as their first
 * argument.  They own the slot grid: the slot base, the cursor, the two
 * slot marks and the per-slot model "made" checks.
 *
 *   0x003e0b80  clear the SELSLOT run state                          (40 B)
 *   0x003e0bb0  initialise the SELSLOT state from the manager mode  (136 B)
 *   0x003e2a80  reset the cursor state and publish one slot line    (140 B)
 *   0x003e1760  per-frame slot update: pad, movement, confirm/cancel (4,764 B)
 *   0x003e2b10  publish/finish the slot marks                        (1,336 B)
 *   0x003e0c40  open/refresh the slot base and marks                (2,808 B)
 *   0x003e3070  highlight the selected slot's mark                  (2,776 B)
 *
 * Field offsets and the animation/text tokens are taken from the retail
 * instructions (see docs/engine/load-intf2.md) and the ELF string table.
 */
#ifndef DW4_RECOVERED_SELSLOT_H
#define DW4_RECOVERED_SELSLOT_H
#include "loadintf2.h"

/* Front-end object/animation tokens (ELF string table). */
#define SS_T_SLOTBASE     0x517118   /* "j_slotbase"        */
#define SS_T_OPENPS01     0x517128   /* "SQ_OPENPS01"       */
#define SS_T_OPENPS02     0x517138   /* "SQ_OPENPS02"       */
#define SS_T_MEMICONWIN   0x517150   /* "j_memoryiconwin"   */
#define SS_T_SLOTCURSOR   0x517160   /* "j_slotcursor"      */
#define SS_T_SLOTMARK02   0x517170   /* "j_slotmark02"      */
#define SS_T_SLOTMARK01   0x5171a0   /* "j_slotmark01"      */
#define SS_T_OPEN01       0x517180   /* "SQ_OPEN01"         */
#define SS_T_OPEN02       0x517190   /* "SQ_OPEN02"         */
#define SS_T_OPEN1A       0x5171b0   /* "SQ_OPEN1A"         */
#define SS_T_OPEN1B       0x5171c0   /* "SQ_OPEN1B"         */
#define SS_T_OPEN1C       0x5171d0   /* "SQ_OPEN1C"         */
#define SS_T_OPEN1D       0x5171e0   /* "SQ_OPEN1D"         */
#define SS_T_ON           0x5171f0   /* "SQ_ON"             */
#define SS_T_OPEN         0x516cd0   /* "SQ_OPEN"           */
#define SS_T_CLOSE        0x516d30   /* "SQ_CLOSE"          */
#define SS_T_CANCEL       0x516d50   /* "SQ_CANCEL"         */
#define SS_T_MOVE         0x516e48   /* "SQ_MOVE"           */
#define SS_T_SELECT01     0x517108   /* "SQ_SELECT01"       */

/* The two mark tables: {u32 name; u32 modelIndex} rows, 8 bytes each. */
#define SS_TBL_SQSELECT01 0x004cd090
#define SS_TBL_SQSELECT1A 0x004cd060

/* SELSLOT impl: record +0x24..+0x30 (inherited per-player state),
 * +0x34 isOpen, +0x35 isSelect, +0x36 isCansel, +0x37 isEnd,
 * +0x38 mode, +0x3c markCur, +0x40 selPoint, +0x44 kind,
 * +0x48 isMarksOn, +0x4c..+0x58 st0..st3. */
void    ss_clear(const Dw4LoadIntf2Api *api, int32_t self);
void    ss_init(const Dw4LoadIntf2Api *api, int32_t self);
void    ss_pub_cursor(const Dw4LoadIntf2Api *api, int32_t self, int32_t p4);
int32_t ss_update(const Dw4LoadIntf2Api *api, int32_t self, int32_t ctrl, int32_t chk);
int32_t ss_marks(const Dw4LoadIntf2Api *api, int32_t self);
int32_t ss_open(const Dw4LoadIntf2Api *api, int32_t self, int32_t mark);
void    ss_select(const Dw4LoadIntf2Api *api, int32_t self, int32_t sel);

#endif /* DW4_RECOVERED_SELSLOT_H */
