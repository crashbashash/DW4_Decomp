#ifndef DW4_RECOVERED_XDATA_CONTROLLER_H
#define DW4_RECOVERED_XDATA_CONTROLLER_H
#include "messenger-results.h"
/* Complete Ctrl10 update4270a0..42860c with368-byte private guest frame.
 * incoming_s0 preserves the original undefined-selector fallback's saved input
 * register; valid ordinary paths select parameter0..6. Other services are calls. */
uint64_t dw4_xdata_controller(const Dw4MessengerResultsApi *,const uint64_t args[8],uint32_t scratch,uint64_t incoming_s0);
uint64_t dw4_xdata_reference_cleanup(const Dw4MessengerResultsApi *,const uint64_t args[8]);
#endif
