#ifndef DW4_RECOVERED_CHIP_LIST_VIEW_H
#define DW4_RECOVERED_CHIP_LIST_VIEW_H
#include "messenger-results.h"
/* Complete contiguous chip count/text helper block43c720..43cc20.
 * Count returns visible rows and updates maximum pages. Text args are self,
 * refresh rows/page labels, refresh selected description (full-width flags).
 * Text scratch maps its160-byte original frame. Transactions are separate. */
uint64_t dw4_chip_list_view(const Dw4MessengerResultsApi *,uint32_t entry,
                            const uint64_t args[8],uint32_t scratch);
#endif
