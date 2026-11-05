#ifndef DW4_PLAYERHEALTH_H
#define DW4_PLAYERHEALTH_H
#include "dw4/playerrecords.h"
typedef struct {int32_t level,hp,mp,max_hp,max_mp;int hp_publish;float hp_percent,mp_percent;} dw4_playerhealth;
/* Retail ADDHP 0 / ADDMP 0, with safe maxima preflight. Dead HP skips ADDHP
 * publication; MP still clamps and publishes. No tick or stat recalculation. */
int dw4_playerhealth_restore(dw4_playerrecords *,int32_t,dw4_playerhealth *,char *,size_t);
/* Scalar ADDHP/ADDMP contract; absolute HP -1 selects additive/dead guard. */
int dw4_playerhealth_add(dw4_playerrecords *,int32_t,int mp,int32_t amount,int32_t absolute_hp,char *,size_t);
#endif
