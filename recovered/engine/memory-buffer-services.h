#ifndef DW4_RECOVERED_MEMORY_BUFFER_SERVICES_H
#define DW4_RECOVERED_MEMORY_BUFFER_SERVICES_H
#include "messenger-results.h"
/* Owner lookup, virtual allocator methods and byte copying remain API callbacks. */
uint64_t dw4_memory_buffer_service(const Dw4MessengerResultsApi *, uint32_t entry,
                                  const uint64_t arguments[8]);
#endif
