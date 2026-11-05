/* Native storage/allocator/list boundary for the recovered common-model code.
 * Model execution and messenger queries are supplied by the owning screen. */
#ifndef DW4_COMMDLHOST_H
#define DW4_COMMDLHOST_H
#include "commdl.h"
enum { DW4_CM_BASE=0x01000000, DW4_CM_BYTES=0x3000, DW4_CM_CAPACITY=128 };
typedef struct {
    Dw4LoadIntf2Api api;
    unsigned char memory[DW4_CM_BYTES], used[DW4_CM_CAPACITY];
    void *user;
    int32_t (*message)(void *, int32_t, const int32_t[8]);
    int error;
} dw4_commdl_host;
void dw4_commdl_host_init(dw4_commdl_host *, void *, int32_t (*)(void *,int32_t,const int32_t[8]));
#endif
