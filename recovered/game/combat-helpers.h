#ifndef DW4_RECOVERED_COMBAT_HELPERS_H
#define DW4_RECOVERED_COMBAT_HELPERS_H
#include "../engine/messenger-results.h"
/* Behavioral projections of the two complete bodies immediately before the
 * GAMERAM command callback. References and scratch addresses are guest words.
 * The row search leaves output unchanged on a miss. The nearby query stores
 * a retained list reference and exposes the original zero result in v0.
 */
void dw4_combat_find_technique_row(const Dw4MessengerResultsApi *,uint32_t player,
                                  int32_t base_no,uint32_t output);
uint32_t dw4_combat_collect_nearby(const Dw4MessengerResultsApi *,uint32_t output,
                                  uint32_t self,uint32_t group,int32_t excluded,
                                  uint32_t center,uint32_t frame);
#endif
