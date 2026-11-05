#ifndef DW4_RECOVERED_MEMORY_FIELD_COPY_H
#define DW4_RECOVERED_MEMORY_FIELD_COPY_H
#include "messenger-results.h"
/* Four original void entries: deep/shallow copy, print and element visitor. */
uint64_t dw4_memory_field_copy(const Dw4MessengerResultsApi *, uint32_t entry,
                              const uint64_t arguments[8]);
#endif
