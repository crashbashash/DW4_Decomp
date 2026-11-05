#ifndef DW4_RECOVERED_OBJECT_FIELDS_H
#define DW4_RECOVERED_OBJECT_FIELDS_H
#include "messenger-results.h"
/* Guest references and canonical EE word arguments. Defined returns: metadata
 * count/index getters, serialized size/write, reference size and construct flag. */
uint64_t dw4_object_field(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8]);
#endif
