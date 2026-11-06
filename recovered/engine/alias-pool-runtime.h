#ifndef DW4_RECOVERED_ALIAS_POOL_RUNTIME_H
#define DW4_RECOVERED_ALIAS_POOL_RUNTIME_H
#include "alias-pool-binding.h"
/* Guest-reference behavioral recovery of the complete alias-pool method run
 * 2d0560..2d163c, plus factory2cd170. Nested calls need distinct scratch frames
 * of at least128 bytes. Diagnostic304430 receives12 argument words; other
 * callbacks use the existing eight-word convention. */
uint64_t dw4_alias_pool_runtime(const Dw4MessengerResultsApi *,uint32_t entry,
                               const uint64_t args[8],uint32_t scratch);
#endif
