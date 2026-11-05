#ifndef DW4_RECOVERED_STRING_FIELDS_H
#define DW4_RECOVERED_STRING_FIELDS_H
#include "messenger-results.h"
/* scratch is a four-byte temporary token/length cell. Nested callers need
 * distinct frames. All references are guest words, not native host pointers. */
uint64_t dw4_string_field(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8],uint32_t scratch);
#endif
