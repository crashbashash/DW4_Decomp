#ifndef DW4_GPU_POLICY_H
#define DW4_GPU_POLICY_H
#include <stdint.h>

/* Main-thread render session policy. Reference tools default to diagnostic
 * mode; normal engines select hardware-required mode for their lifetime. */
int dw4_gpu_policy_begin(int hardware_required);
int dw4_gpu_policy_required(void);
int dw4_gpu_policy_hardware(const char *renderer);
int dw4_gpu_policy_accept(const char *renderer);
void dw4_gpu_policy_fail(const char *operation);
const char *dw4_gpu_policy_error(void);
/* A CPU call in hardware-required mode is counted and rejected before pixel
 * work. Explicit reference mode returns zero and keeps the original oracle. */
enum {DW4_CPU_UI,DW4_CPU_LAYER,DW4_CPU_MESH,DW4_CPU_FILL,DW4_CPU_COMPOSITE,DW4_CPU_KIND_COUNT};
int dw4_gpu_policy_cpu(unsigned kind);
uint64_t dw4_gpu_policy_cpu_count(unsigned kind);
#endif
