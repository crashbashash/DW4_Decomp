#ifndef DW4_RECOVERED_PAD_MANAGER_SELECTION_H
#define DW4_RECOVERED_PAD_MANAGER_SELECTION_H
#include "messenger-results.h"
/* Original 39b810 body, no controlled callees. References are guest addresses.
 * player preserves the incoming EE register for the signed comparison; the
 * actual callers publish a sign-extended 32-bit player number. */
uint64_t dw4_pad_manager_selection(const Dw4MessengerResultsApi *,uint64_t self,
                                    uint64_t player);
#endif
