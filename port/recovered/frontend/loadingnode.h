/* Complete contiguous beNodeAnim/loading-node runtime, 0x0039a930..0x0039ae44.
 * Behavioral reference; traversal allocation/callbacks remain external leaves. */
#ifndef DW4_LOADINGNODE_H
#define DW4_LOADINGNODE_H
#include "systemclock.h"
uint64_t dw4_loadingnode_call(const Dw4SystemClockApi *, uint32_t entry,
                             uint64_t a, uint64_t b, uint64_t c);
#endif
