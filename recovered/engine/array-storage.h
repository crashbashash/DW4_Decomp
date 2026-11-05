#ifndef DW4_RECOVERED_ARRAY_STORAGE_H
#define DW4_RECOVERED_ARRAY_STORAGE_H
#include "messenger-results.h"
/* scratch reserves 4 bytes for the retained alignment-list pointer.
 * Both retail entries return void; a recognized entry returns zero here. */
uint64_t dw4_array_storage(const Dw4MessengerResultsApi *, uint32_t entry,
                          const uint64_t arguments[8], uint32_t scratch);
#endif
