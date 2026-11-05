#ifndef DW4_RECOVERED_REFLECTION_REGISTRATION_H
#define DW4_RECOVERED_REFLECTION_REGISTRATION_H
#include "messenger-results.h"
/* RegisterClass consumes eleven arguments; other entries consume at most five.
 * scratch reserves 320 bytes for debug name, token and out temporaries. */
uint64_t dw4_reflection_registration(const Dw4MessengerResultsApi *,uint32_t entry,
                                     const uint64_t args[12],uint32_t scratch);
#endif
