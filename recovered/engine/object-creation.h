#ifndef DW4_RECOVERED_OBJECT_CREATION_H
#define DW4_RECOVERED_OBJECT_CREATION_H
#include "messenger-results.h"
/* Guest-reference adapter; defined returns are the three create operations and
 * the four messenger factories. Other bodies return no defined integer value. */
uint64_t dw4_object_creation(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8]);
#endif
