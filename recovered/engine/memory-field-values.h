#ifndef DW4_RECOVERED_MEMORY_FIELD_VALUES_H
#define DW4_RECOVERED_MEMORY_FIELD_VALUES_H
#include "messenger-results.h"
/* scratch reserves 16 bytes for word/default and array-output temporaries. */
uint64_t dw4_memory_field_value(const Dw4MessengerResultsApi *,uint32_t,const uint64_t[8],uint32_t scratch);
#endif
