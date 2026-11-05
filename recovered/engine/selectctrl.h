#ifndef DW4_RECOVERED_SELECTCTRL_H
#define DW4_RECOVERED_SELECTCTRL_H
#include "messenger-results.h"
/* Full guest-address behavioral recovery of beSelectCtrl update39cbf0 and
 * general receiver39d720. Callbacks preserve engine services and ownership.
 * scratch maps the body's original private frame (240/160 bytes respectively).
 * This is neither matching PS2 source nor native SELECTCTRL integration. */
uint64_t dw4_selectctrl_manager(const Dw4MessengerResultsApi *,uint32_t entry,
                       const uint64_t args[8],uint32_t scratch);
#endif
