#ifndef DW4_RECOVERED_OBJECT_BASE_H
#define DW4_RECOVERED_OBJECT_BASE_H
#include "messenger-results.h"
/* scratch reserves 320 bytes for header and retained-name temporaries. */
uint64_t dw4_object_base(const Dw4MessengerResultsApi *,uint32_t,const uint64_t[8],uint32_t scratch);
#endif
