#ifndef DW4_RECOVERED_ALIAS_POOL_BINDING_H
#define DW4_RECOVERED_ALIAS_POOL_BINDING_H
#include "messenger-results.h"
/* Factory2cd170 and contiguous binding/accounting block 2d0560..2d06b8.
 * This is a guest-reference behavioral oracle. */
uint64_t dw4_alias_pool_binding(const Dw4MessengerResultsApi *, uint32_t entry,
                               const uint64_t args[8]);
#endif
