#ifndef DW4_RECOVERED_MESSENGER_DISPATCH_H
#define DW4_RECOVERED_MESSENGER_DISPATCH_H
#include "messenger-results.h"
/* Original guest-reference semantics. scratch reserves 24 bytes for temporary
 * reference owners; nested calls must provide separate scratch frames. */
uint64_t dw4_messenger_dispatch(const Dw4MessengerResultsApi *, uint32_t entry,
                               const uint64_t args[8], uint32_t scratch);
#endif
