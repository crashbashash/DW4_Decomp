/* Original aligned storage allocation and named alignment selection.
 * Allocation initializes reference cells only; it invokes no element constructors. */
#include "array-storage.h"
#define P(p) ((uint32_t)a->read(a->user, (p), 4))
#define W(p,v) a->write(a->user, (p), 4, (uint32_t)(v))
#define CALL(e,...) a->call(a->user, (e), (const uint64_t[8]){__VA_ARGS__})

static uint32_t method(const Dw4MessengerResultsApi *a, uint32_t object, unsigned slot) {
    return P(P(object) + slot);
}

static void release(const Dw4MessengerResultsApi *a, uint32_t object) {
    if (object) {
        W(object + 4, P(object + 4) - 1);
        if (!(P(object + 4) & 0x7fffff)) CALL(0x2ff820, object);
    }
}

uint64_t dw4_array_storage(const Dw4MessengerResultsApi *a, uint32_t entry,
                          const uint64_t v[8], uint32_t scratch) {
    if (entry == 0x2fb190) {
        uint32_t out = (uint32_t)v[0], field = (uint32_t)v[1];
        uint32_t object = (uint32_t)v[2], count = (uint32_t)v[3];
        uint32_t allocator = (uint32_t)v[4];
        uint32_t size = (uint32_t)CALL(method(a, P(field + 60), 100), P(field + 60)) & 65535;
        uint32_t bytes = count * size;
        /* Each query reloads the element descriptor after preceding callbacks. */
        uint32_t alignment = (uint32_t)CALL(method(a, P(field + 60), 108), P(field + 60)) & 65535;
        uint32_t buffer = (uint32_t)CALL(method(a, allocator, 220), allocator,
                                        (uint64_t)(int64_t)(int32_t)bytes, alignment);
        if (!buffer) {
            W(out, P(0x4fb418));
            return 0;
        }
        if (CALL(0x300cd0, P(field + 60), P(0x585a60)))
            CALL(0x12724c, buffer, 0, (uint64_t)(int64_t)(int32_t)bytes);
        W(object + P(field + 8), buffer);
        W(out, P(0x4fb410));
        return 0;
    }
    if (entry == 0x2fb280) {
        uint32_t field = (uint32_t)v[0], name = (uint32_t)v[1];
        if (!name) {
            W(field + 68, 0xffffffff);
            return 0;
        }
        W(scratch, P(P(0x586dd0) + 44));
        uint32_t list = P(scratch);
        if (list) W(list + 4, P(list + 4) + 1);
        int32_t count = list ? (int32_t)P(list + 8) : 0;
        for (int32_t i = 0; i < count; i++) {
            uint32_t current = P(P(P(scratch) + 16) + (uint32_t)i * 4);
            uint32_t candidate = P(current + 8);
            if (!candidate) candidate = P(0x4c22f0);
            if (!CALL(0x12a4a4, candidate, v[1])) {
                W(field + 68, (uint32_t)i);
                release(a, P(scratch));
                return 0;
            }
        }
        release(a, P(scratch));
        return 0;
    }
    return UINT64_MAX;
}
