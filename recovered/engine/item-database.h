#ifndef DW4_RECOVERED_ITEM_DATABASE_H
#define DW4_RECOVERED_ITEM_DATABASE_H
#include "messenger-results.h"
/* Complete item lookup run447bc0..447cf8, chip database selector448640,
 * and database index/value/count block3a93a0..3a9708. Guest addresses.
 * All entries return v0; boolean lookup returns its raw byte, not normalized1.
 * scratch maps the index finder's80-byte frame (temporary pointer at76).
 * Messaging, virtual selection and property-name search may be composed by call.
 */
uint64_t dw4_item_database(const Dw4MessengerResultsApi *, uint32_t entry, const uint64_t args[8],
                           uint32_t scratch);
#endif
