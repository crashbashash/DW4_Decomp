#ifndef DW4_RECOVERED_LIST_SERVICES_H
#define DW4_RECOVERED_LIST_SERVICES_H
#include "messenger-results.h"
/* Behavioral entry adapter for 12 shared list primitives and four reference
 * bridges. Typed count/index inputs use sign-extended EE words. scratch is a
 * caller-owned four-byte guest temporary, separate from live inputs/caller
 * temporaries. Allocation/metadata/copy are leaves. */
uint64_t dw4_list_service(const Dw4MessengerResultsApi *,uint32_t entry,
                          const uint64_t args[8],uint32_t scratch);
#endif
