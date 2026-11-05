#ifndef DW4_RECOVERED_SHOP_ROOT_UPDATE_H
#define DW4_RECOVERED_SHOP_ROOT_UPDATE_H
#include "messenger-results.h"
/* Full ShopCtrl00 update4267b0..426f94. An80-byte private guest frame
 * retains its six scoped factory-reference cells. Factories and UI remain calls. */
uint64_t dw4_shop_root_update(const Dw4MessengerResultsApi *,const uint64_t args[8],uint32_t scratch);
/* Adjacent scoped-reference cleanups426fa0/427020 share this exact behavior. */
uint64_t dw4_shop_root_reference_cleanup(const Dw4MessengerResultsApi *,const uint64_t args[8]);
#endif
