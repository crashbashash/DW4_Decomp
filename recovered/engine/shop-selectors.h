#ifndef DW4_RECOVERED_SHOP_SELECTORS_H
#define DW4_RECOVERED_SHOP_SELECTORS_H
#include "messenger-results.h"
/* Full Select00/01/11 initializers plus Select11 stat display. Private frames
 *64/96/128/288 bytes respectively; dispatcher may execute shared services. */
uint64_t dw4_shop_selectors(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8],uint32_t scratch);
#endif
