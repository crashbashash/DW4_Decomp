#ifndef DW4_RECOVERED_MESSENGER_RESULTS_H
#define DW4_RECOVERED_MESSENGER_RESULTS_H
#include <stdint.h>
typedef struct {
    void *user;
    uint64_t (*read)(void *,uint32_t,unsigned);
    void (*write)(void *,uint32_t,unsigned,uint64_t);
    uint64_t (*call)(void *,uint32_t,const uint64_t[8]);
} Dw4MessengerResultsApi;
/* Behavioral entry adapter for every body at 38f0e0..38f94c. Addresses are
 * guest references; f12 carries the float-append bit pattern. Float-get returns
 * f0's bits, not the incidental integer return register. scratch is four bytes. */
uint64_t dw4_messenger_result(const Dw4MessengerResultsApi *,uint32_t entry,
                              uint64_t a0,uint64_t a1,uint64_t a2,
                              uint32_t f12,uint32_t scratch);
#endif
