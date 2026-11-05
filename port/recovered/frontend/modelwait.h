/* Behavioral reference for the contiguous 0x00394ae0..0x00394f98 group.
 * String pool, motion query, messenger, virtual slots and dispatcher are leaves. */
#ifndef DW4_MODELWAIT_H
#define DW4_MODELWAIT_H
#include "loadintf2.h"
enum { MW_EMPTY=0x4e0858, MW_TURNY=0x50f138, MW_LANDING=0x50f140,
       MW_ACTION=0x50f148, MW_MOVING=0x50f160, MW_ROTATION=0x50f168,
       MW_ACTION2=0x50eff8, MW_ISCOMEND=0x50f150 };
int32_t mw_jump(const Dw4LoadIntf2Api *,int32_t owner,int32_t work,int32_t command);
int32_t mw_start(const Dw4LoadIntf2Api *,int32_t owner,int32_t work,int32_t command);
void mw_update(const Dw4LoadIntf2Api *,int32_t owner,int32_t info,int32_t node,int32_t work);
void mw_noop(const Dw4LoadIntf2Api *);
#endif
