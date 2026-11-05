#ifndef DW4_RECOVERED_SHOP_ROOT_METADATA_H
#define DW4_RECOVERED_SHOP_ROOT_METADATA_H
#include "messenger-results.h"
/* Complete six-body ShopCtrl00 metadata block plus its published parent
 * callback. RegisterClass call arguments0..10 include the three stack words.
 * A private128-byte guest frame is required for the temporary vtable object. */
uint64_t dw4_shop_root_metadata(const Dw4MessengerResultsApi *,uint32_t entry,const uint64_t args[8],uint32_t scratch);
#endif
