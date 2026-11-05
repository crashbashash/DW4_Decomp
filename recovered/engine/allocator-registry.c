#include "allocator-registry.h"
#define P(p) ((uint32_t)a->read(a->user, (p), 4))
#define B(p) ((uint32_t)a->read(a->user, (p), 1))
#define W(p,v) a->write(a->user, (p), 4, (uint32_t)(v))
#define CALL(e,...) a->call(a->user, (e), (const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_allocator_registry(a, (e), (const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t v) {return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t method(const Dw4MessengerResultsApi *a, uint32_t object, unsigned slot) {
    return P(P(object) + slot);
}
uint64_t dw4_allocator_registry(const Dw4MessengerResultsApi *a, uint32_t entry,
                                const uint64_t v[8]) {
    uint32_t self = (uint32_t)v[0];
    switch (entry) {
    case 0x2f04f0:
        /* Registry60 precedes registry58; both are scanned newest to oldest.
         * Counts are captured separately; publication/data reload on every row. */
        for (unsigned pass = 0; pass < 2; ++pass) {
            uint32_t global = pass ? 0x586f58 : 0x586f60;
            int32_t i = (int32_t)(P(P(global) + 4) - 1);
            while (i >= 0) {
                uint32_t candidate = P(P(P(global)) + (uint32_t)i * 4);
                if (candidate && CALL(method(a, candidate, 132), candidate) &&
                    CALL(method(a, candidate, 340), candidate, v[0])) return word(candidate);
                --i;
            }
        }
        return 0;
    case 0x2fa5c0: {
        int32_t count = (int32_t)P(self + 4);
        for (int32_t i = 0; i < count; ++i)
            if (P(P(self) + (uint32_t)i * 4) == (uint32_t)v[1]) return word((uint32_t)i);
        return UINT64_MAX;
    }
    case 0x2f0650: case 0x2f0670:
        if (B(P(0x586dc8)) && !CALL(method(a, self, 116), v[0]))
            return word((uint32_t)CORE(0x2fa5c0, P(0x586f58), v[0]) << 1);
        /* The first kind callback may change runtime mode. */
        if (!B(P(0x586dc8))) return 0;
        return word(((uint32_t)CORE(0x2fa5c0, P(0x586f60), v[0]) << 1) | 1);
    case 0x2f0700: {
        int32_t index = (int32_t)self >> 1;
        uint32_t global = (self & 1) ? 0x586f60 : 0x586f58;
        return word(P(P(P(global)) + (uint32_t)index * 4));
    }
    case 0x2f0620: W(self, P(0x4fb418)); return 0;
    case 0x2f0630: return 0;
    case 0x2f0640: return UINT64_MAX;
    case 0x2f0660: return 0;
    case 0x2f00d0: return CALL(0x2f88e0, 2);
    case 0x2ed1c0:
        return CALL(method(a, (uint32_t)v[1], 216), v[1], v[0]);
    case 0x2ed200: {
        uint64_t allocator = CORE(0x2f00d0);
        return CALL(method(a, (uint32_t)allocator, 216), allocator, v[0]);
    }
    case 0x2ed240:
        return CALL(method(a, (uint32_t)v[1], 216), v[1], v[0]);
    default:
        return UINT64_MAX;
    }
}
