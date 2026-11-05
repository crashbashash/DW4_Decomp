/* Recovered record access shared by the FIGHTCALC ports. Private to the fight
 * modules; borrowed fields never survive a setter or recalculation. */
#ifndef DW4_FIGHTRECORD_H
#define DW4_FIGHTRECORD_H
#include "dw4/playerrecords.h"
int dw4_fight_record_number(const dw4_property_folder *,const char *,int32_t *);
const int32_t *dw4_fight_record_array(const dw4_property_folder *,const char *,size_t *);
int dw4_fight_record_technique(const dw4_property_folder *,int32_t,int32_t *);
#endif
