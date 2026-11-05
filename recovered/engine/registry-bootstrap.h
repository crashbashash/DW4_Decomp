#ifndef DW4_RECOVERED_REGISTRY_BOOTSTRAP_H
#define DW4_RECOVERED_REGISTRY_BOOTSTRAP_H
#include "messenger-results.h"
/* Registry-list lifetime/publication and current-context virtual dispatch.
 * scratch reserves 4 bytes for selector realization status.
 * Allocator implementations, context realization and unknown slots remain callbacks. */
uint64_t dw4_registry_bootstrap(const Dw4MessengerResultsApi *, uint32_t entry,
                                const uint64_t arguments[8], uint32_t scratch);
#endif
