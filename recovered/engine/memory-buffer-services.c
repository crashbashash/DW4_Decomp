/* Contiguous owner-directed free/size/duplicate/allocator-dispatch services. */
#include "memory-buffer-services.h"
#define P(p) ((uint32_t)a->read(a->user, (p), 4))
#define CALL(e,...) a->call(a->user, (e), (const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_memory_buffer_service(a, (e), (const uint64_t[8]){__VA_ARGS__})
static uint32_t method(const Dw4MessengerResultsApi *a, uint32_t object, unsigned slot) {
    return P(P(object) + slot);
}
uint64_t dw4_memory_buffer_service(const Dw4MessengerResultsApi *a, uint32_t entry,
                                  const uint64_t v[8]) {
    uint32_t buffer = (uint32_t)v[0], owner;
    switch (entry) {
    case 0x2ed460: case 0x2ed4b0: case 0x2ed5c0:
        if (buffer) {
            owner = (uint32_t)CALL(0x2f04f0, v[0]);
            if (owner) CALL(method(a, owner, 264), owner, v[0]);
        }
        return 0;
    case 0x2ed4c0:
        CALL(method(a, (uint32_t)v[1], 264), v[1], v[0]);
        return 0;
    case 0x2ed4e0:
        owner = (uint32_t)CALL(0x2f04f0, v[0]);
        return CALL(method(a, owner, 336), owner, v[0]);
    case 0x2ed520:
        return CALL(0x2f04f0, v[0]);
    case 0x2ed530: {
        uint64_t size = CORE(0x2ed4e0, v[0]);
        uint64_t allocator = CORE(0x2ed520, v[0]);
        uint64_t copy = CALL(0x2ed1c0, size, allocator);
        /* Retail re-queries size after allocation; it does not check failure. */
        size = CORE(0x2ed4e0, v[0]);
        CALL(0x127098, copy, v[0], size);
        return copy;
    }
    case 0x2ed5a0:
        return CALL(method(a, (uint32_t)v[1], 240), v[1], v[0]);
    case 0x2ed5d0:
        owner = (uint32_t)CORE(0x2ed520, v[0]);
        CALL(method(a, owner, 264), owner, v[0]);
        return 0;
    default:
        return UINT64_MAX;
    }
}
