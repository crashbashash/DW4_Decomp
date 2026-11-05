#ifndef DW4_RECOVERED_LIST_REGISTRATION_H
#define DW4_RECOVERED_LIST_REGISTRATION_H
#include "messenger-results.h"
/* scratch reserves 320 bytes for temporary object headers/shared registration. */
uint64_t dw4_list_registration(const Dw4MessengerResultsApi *,uint32_t,const uint64_t[8],uint32_t scratch);
#endif
