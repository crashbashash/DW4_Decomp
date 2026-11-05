#ifndef DW4_RECOVERED_ALLOCATOR_REGISTRY_H
#define DW4_RECOVERED_ALLOCATOR_REGISTRY_H
#include "messenger-results.h"
/* Original owner lookup, index encoding/resolution and allocation dispatch.
 * Allocator virtual methods and default allocator service remain callbacks. */
uint64_t dw4_allocator_registry(const Dw4MessengerResultsApi *, uint32_t entry,
                                const uint64_t arguments[8]);
#endif
