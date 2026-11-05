#ifndef DW4_RECOVERED_STRING_POOL_H
#define DW4_RECOVERED_STRING_POOL_H
#include "messenger-results.h"
/* Four public pool bodies, ten ordered-table bodies and chunk release bridge.
 * scratch supplies 24 guest bytes, separate from caller inputs/temporaries.
 * Byte, allocation, chunk and synchronization primitives remain service leaves. */
uint64_t dw4_string_pool(const Dw4MessengerResultsApi *,uint32_t entry,
                         const uint64_t args[8],uint32_t scratch);
#endif
