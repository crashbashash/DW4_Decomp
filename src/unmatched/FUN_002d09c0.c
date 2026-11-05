#include "dw4/reflected.h"
/* 0x002d09c0 — igAliasMemoryPool getter (vtable 0x5313a0): returns the unsigned 64-bit byte high-water at +160. */
long long FUN_002d09c0(igAliasMemoryPool *arg0) {
    return arg0->_allocedBytesHigh;
}
