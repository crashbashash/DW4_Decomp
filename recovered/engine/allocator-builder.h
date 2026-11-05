#ifndef DW4_RECOVERED_ALLOCATOR_BUILDER_H
#define DW4_RECOVERED_ALLOCATOR_BUILDER_H
#include "messenger-results.h"
/* scratch reserves 4 temporary output bytes; nested builders need distinct scratch. */
uint64_t dw4_allocator_builder(const Dw4MessengerResultsApi *,uint32_t entry,
                               const uint64_t arguments[8],uint32_t scratch);
#endif
