#ifndef DW4_RECOVERED_MESSENGER_LIFECYCLE_H
#define DW4_RECOVERED_MESSENGER_LIFECYCLE_H
#include "messenger-results.h"
/* Guest-reference recovery. scratch has 24 bytes; nested adapters need their
 * own scratch frame. Callbacks may route into messenger-dispatch.c. */
uint64_t dw4_messenger_lifecycle(const Dw4MessengerResultsApi *,uint32_t entry,
                                const uint64_t args[8],uint32_t scratch);
#endif
