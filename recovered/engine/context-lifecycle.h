#ifndef DW4_RECOVERED_CONTEXT_LIFECYCLE_H
#define DW4_RECOVERED_CONTEXT_LIFECYCLE_H
#include "messenger-results.h"
/* scratch reserves 16 bytes for builder and detach/status temporaries.
 * Slot204 allocator construction and tracker/allocator virtuals remain callbacks. */
uint64_t dw4_context_lifecycle(const Dw4MessengerResultsApi *,uint32_t entry,
                              const uint64_t arguments[8],uint32_t scratch);
#endif
