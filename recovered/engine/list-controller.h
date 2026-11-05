#ifndef DW4_RECOVERED_LIST_CONTROLLER_H
#define DW4_RECOVERED_LIST_CONTROLLER_H
#include "messenger-results.h"
/* Original ListCtrl arrow initialization/previous/next block40dae0..40de80.
 * Initialization args: self, left vector, right vector. Other entries take self.
 * Scratch maps the96-byte initializer frame; page methods need no scratch. */
uint64_t dw4_list_controller(const Dw4MessengerResultsApi *,uint32_t entry,
                             const uint64_t args[8],uint32_t scratch);
#endif
