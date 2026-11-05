#ifndef DW4_RECOVERED_OBJECT_LISTS_H
#define DW4_RECOVERED_OBJECT_LISTS_H
#include "messenger-results.h"
/* Guest references, including output-first RemoveOne. Defined return entries:
 * RemoveAll, AppendUnique, four property lookups. Other entries are void. */
uint64_t dw4_object_list(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8]);
#endif
