/* Original memory-field copying, printing and callback-based element traversal. */
#include "memory-field-copy.h"
#define P(p) ((uint32_t)a->read(a->user, (p), 4))
#define B(p) ((uint32_t)a->read(a->user, (p), 1))
#define W(p,v) a->write(a->user, (p), 4, (uint32_t)(v))
#define CALL(e,...) a->call(a->user, (e), (const uint64_t[8]){__VA_ARGS__})
static uint32_t method(const Dw4MessengerResultsApi *a, uint32_t object, unsigned slot) {
    return P(P(object) + slot);
}
uint64_t dw4_memory_field_copy(const Dw4MessengerResultsApi *a, uint32_t entry,
                             const uint64_t v[8]) {
    uint32_t field = (uint32_t)v[0], object = (uint32_t)v[1];
    if (entry == 0x2fad50 || entry == 0x2faf10) {
        CALL(0x2fabf0, v[0], v[1]);
        if (B(field + 64)) {
            uint32_t old = P(object + P(field + 8));
            if (old) CALL(0x2ed5d0, old);
        }
        uint32_t source = (uint32_t)v[2];
        uint32_t value = P(source + P(field + 8));
        uint32_t copy = value ? (uint32_t)CALL(0x2ed530, value) : 0;
        W(object + P(field + 8), copy);
        if (entry == 0x2faf10) {
            CALL(0x2fab40, v[0], v[1]);
            return 0;
        }
        if (!P(field + 60)) return 0;
        if (CALL(0x300cd0, P(field + 60), P(0x585b20))) {
            uint32_t offset = P(field + 8);
            uint32_t src = P(source + offset), dst = P(object + offset);
            if (!src || !dst) return 0;
            uint32_t count = (uint32_t)CALL(0x2ed4e0, src) >> 2;
            for (uint32_t i = 0; i < count; ++i) {
                uint32_t element = P(src + i * 4);
                uint32_t result = element ? (uint32_t)CALL(method(a, element, 84), element, 1) : 0;
                W(dst + i * 4, result);
            }
        } else if (CALL(0x300cd0, P(field + 60), P(0x585d80))) {
            uint32_t offset = P(field + 8);
            uint32_t src = P(source + offset), dst = P(object + offset);
            /* Unlike the object-reference branch, retail has no null-buffer guard. */
            uint32_t count = (uint32_t)CALL(0x2ed4e0, src) >> 2;
            for (uint32_t i = 0; i < count; ++i) {
                uint32_t element = P(src + i * 4);
                W(dst + i * 4, element ? (uint32_t)CALL(0x2ed530, element) : 0);
            }
        }
        return 0;
    }
    if (entry == 0x2fafb0) {
        uint32_t buffer = P(object + P(field + 8));
        CALL(0x304430, 0x4faef0, v[3], P(field + 12), buffer);
        CALL(0x304680, 0);
        if (!v[2] || !buffer) return 0;
        uint32_t type = P(field + 60);
        uint32_t stride = (uint32_t)CALL(method(a, type, 104), type);
        uint32_t size = (uint32_t)CALL(0x2ed4e0, buffer);
        uint32_t count = stride ? size / stride : 0xffffffff;
        if (CALL(0x300cd0, P(field + 60), P(0x585b20))) {
            for (int32_t i = 0; i < (int32_t)count; ++i) {
                uint32_t element = P(buffer + (uint32_t)i * 4);
                if (element) CALL(0x300490, element, v[2], v[3]);
            }
        }
        return 0;
    }
    if (entry == 0x2fb0b0) {
        if (!CALL(0x300cd0, P(field + 60), P(0x585b20))) return 0;
        uint32_t buffer = P(object + P(field + 8));
        if (!buffer) return 0;
        uint32_t count = (uint32_t)CALL(0x2ed4e0, buffer) >> 2;
        for (uint32_t i = 0; i < count; ++i) {
            uint32_t cell = buffer + i * 4, element = P(cell);
            if (element) {
                CALL(method(a, element, 72), element);
                /* The prepare callback may replace this cell. Reload before visiting. */
                CALL(0x300b00, P(cell), v[2], v[3]);
            }
        }
        return 0;
    }
    return UINT64_MAX;
}
