#ifndef DW4_RECOVERED_CHIP_CONTROLLER_H
#define DW4_RECOVERED_CHIP_CONTROLLER_H
#include "messenger-results.h"
/* Full43aae0 update. Guest references; scratch maps the original288-byte frame.
 * Factories, property/pricing/stat services, text/scripts and engine interfaces
 * remain explicit calls. This does not imply a matching PS2 or native build. */
uint64_t dw4_chip_controller(const Dw4MessengerResultsApi *, const uint64_t args[8],
                             uint32_t scratch);
#endif
