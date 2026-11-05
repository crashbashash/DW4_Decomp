#ifndef DW4_RECOVERED_WINDOW_PRESENTATION_H
#define DW4_RECOVERED_WINDOW_PRESENTATION_H
#include "messenger-results.h"
/* Complete contiguous message/presentation/close run3f5920..3f6348, plus shared title
 * update424160..424230. Private frames:144 bytes for list/model methods,
 *32 for default model origin; dispatcher can reenter for composed routines. */
uint64_t dw4_window_presentation(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8],uint32_t scratch);
#endif
