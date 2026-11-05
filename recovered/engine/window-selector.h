#ifndef DW4_RECOVERED_WINDOW_SELECTOR_H
#define DW4_RECOVERED_WINDOW_SELECTOR_H
#include "messenger-results.h"
/* Complete shared selector4233f0 and FO2TOP predicate423700. scratch64 bytes
 * carries the copied offset vector. Receiver callbacks/virtual init can reenter. */
uint64_t dw4_window_selector(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8],uint32_t scratch);
#endif
