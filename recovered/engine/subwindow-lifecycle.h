#ifndef DW4_RECOVERED_SUBWINDOW_LIFECYCLE_H
#define DW4_RECOVERED_SUBWINDOW_LIFECYCLE_H
#include "messenger-results.h"
/* Complete lifecycle prefix3d58f0..3d60d8, four scoped-ref destructors and
 * final metadata getter. Guest-reference behavior.
 * Menu setup/constructors/update, message services and record lookups remain
 * explicit callbacks; no host pointers enter the recovered fields. scratch is
 * an80-byte private frame; +76 is the original temporary root reference. Nested
 * invocations require distinct frames. */
uint64_t dw4_subwindow_lifecycle(const Dw4MessengerResultsApi *,uint32_t entry,
                                const uint64_t args[8],uint32_t scratch);
#endif
